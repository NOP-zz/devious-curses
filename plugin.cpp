#include "include/DDNG_API.h"
#include "include/form_ids.h"
#include "include/quicklootAPI.h"
#include "include/SexLabPPFunctions.h"
#include "include/SlaveTatsNG_Interface.h"

#include "src/Utils.hpp"
#include "src/Settings.hpp"
#include "src/Devices.hpp"
#include "src/Scripting.hpp"
#include "src/Serializer.hpp"
#include "src/sex.hpp"
#include "src/events.hpp"
#include "src/Consequences.hpp"
#include "src/TESEvents.hpp"
#include "src/QLIEIntegration.hpp"
#include "src/themes.hpp"
#include "src/Contraptions.hpp"
#include "src/O_Devices.hpp"
#include "src/QuestInteractions.hpp"
#include "src/ModEvents.hpp"
#include "src/MinAI.hpp"

#include "src/Translation.hpp"

#include <d3d11.h>
#include <windows.h>
#include <debugapi.h>
#include <chrono>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include <unordered_set>
#include <algorithm>

using namespace SKSE;

namespace DCURSES {
    //GLOBALS
    constexpr auto VERSION = "0.8.1";

    void InitializeLogging() {
        auto path = log::log_directory();
        if (!path) {
            stl::report_and_fail("Unable to lookup SKSE logs directory.");
        }
        *path /= PluginDeclaration::GetSingleton()->GetName();
        *path += L".log";

        auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
        auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));

        spdlog::set_default_logger(std::move(loggerPtr));
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        spdlog::set_level(spdlog::level::trace);
        spdlog::flush_on(spdlog::level::trace);
    }

    static bool UPDATE_LOOP_RUNNING = false;

    void StartUpdateLoop() {
        if (UPDATE_LOOP_RUNNING) {
            return;
        }

        UPDATE_LOOP_RUNNING = true;

        std::thread{ [] {

            while (true) {
                std::this_thread::sleep_for(1000ms);

                if (IsModDisabled()) {
                    //log::trace("Event timer skipped, mod is disabled.");
                    continue;
                }

                if (RE::UI::GetSingleton()->GameIsPaused()) {
                    //log::trace("Event timer skipped, game is paused.");
                    continue;
                }

                auto player = RE::PlayerCharacter::GetSingleton();

                if (player->IsDead() || player->IsDeleted() || player->IsDisabled()) {
                    continue;
                }

                RE::TESFaction* SexlabAnimatingFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("00E50F", 0, 16), "SexLab.esm");
                RE::TESFaction* ZadAnimatingFaction = StaticDataHolder::GetSingleton()->LookupForm<RE::TESFaction>(std::stoi("029567", 0, 16), "Devious Devices - Integration.esm");
                bool isAnimating = player->IsInFaction(SexlabAnimatingFaction) || player->IsInFaction(ZadAnimatingFaction);

                auto c1 = std::chrono::high_resolution_clock::now();
                SexUpdate();
                auto c2 = std::chrono::high_resolution_clock::now();
                if (!isAnimating) { TatsUpdate(); }
                auto c3 = std::chrono::high_resolution_clock::now();
                if (!isAnimating) { OppDeviceUpdate(); }
                auto c4 = std::chrono::high_resolution_clock::now();

                auto d1 = (c2 - c1).count() / 1000000.0;
                auto d2 = (c3 - c2).count() / 1000000.0;
                auto d3 = (c4 - c3).count() / 1000000.0;
                auto dt = (c4 - c1).count() / 1000000.0;

                if (dt >= 10) {
                    log::trace("Notable Update Time: Sex: {:.4f}, Marks: {:.4f}, ODevices: {:.4f} total: {:.4f}ms", d1, d2, d3, dt);
                }

                //Always do last!
                counters.tick();
            }
        } }.detach();
    }
    
    RE::TESObjectARMO* P_GetRandomEquipableDevice(RE::StaticFunctionTag*) {
        auto dev = GetRandomEquipableDevice(RE::PlayerCharacter::GetSingleton(), std::vector<std::string>());
        if (dev) {
            return dev.value().inv;
        }
        return nullptr;
    }

    int P_numDevicesVisible(RE::StaticFunctionTag*, RE::Actor* akActor) {
        return numDevicesVisible(akActor);
    }

    int P_numDevicesEquipped(RE::StaticFunctionTag*, RE::Actor* akActor) {
        return GetWornDeviceCount(akActor);
    }

    bool P_WearingOppressiveDevice(RE::StaticFunctionTag*) {
        return GetOppDeviceMask();
    }

    static int TEST = 0;

    void P_Test(RE::StaticFunctionTag*) {
        log::trace("DCURSES Test");
        //Util::GetWatchingActors(RE::PlayerCharacter::GetSingleton());
        OppDoMadnessEffect();
    }

    bool PapyrusFunctions(RE::BSScript::IVirtualMachine* ivm) {
        ivm->RegisterFunction("Test", "DCursesLib", P_Test);
        ivm->RegisterFunction("GetRandomEquipableDevice", "DCursesLib", P_GetRandomEquipableDevice);
        ivm->RegisterFunction("NumDevicesVisible", "DCursesLib", P_numDevicesVisible);
        ivm->RegisterFunction("NumDevicesEquipped", "DCursesLib", P_numDevicesEquipped);
        //ivm->RegisterFunction("OnUpdate", "DCursesLib", P_OnUpdate);
        ivm->RegisterFunction("WearingOppressiveDevice", "DCurses_MCM", P_WearingOppressiveDevice);
        PapyrusFunctionsSettigns(ivm);
        PapyrusFunctionsSex(ivm);
        PapyrusFunctionsTats(ivm);
        return true;
    }

}

std::string getJContainersPluginName() {
    auto patchVersion = REL::Module::get().version().patch();

    std::string pluginName{ "JContainers64" };
    if (REL::Module::IsVR()) {
        pluginName = "JContainersVR";
    }
    else if (patchVersion == 659 || patchVersion == 1179) {
        pluginName = "JContainersGOG";
    }

    return pluginName;
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);

    DCURSES::InitializeLogging();

    log::info("Initializing DeviousCurses version {}", DCURSES::VERSION);

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        switch (message->type)
        {
        case SKSE::MessagingInterface::kDataLoaded: {
            if (!DCURSES::CheckESPLoaded()) {
                stl::report_and_fail("Devious Curses ESP is not loaded. If you are on skyrim version older than 1.6.1130 (Not AE) make sure to install Backported Extended ESL Support.");
                return;
            }
            else {
                log::trace("ESP Loaded.");
            }

            static auto tweaks = GetModuleHandle(L"po3_Tweaks");
            if (!tweaks) {
                stl::report_and_fail("Devious Curses requires powerofthree's Tweaks to function correctly. Please refer to the mod page requirements and installation instructions.");
            }
            else {
                log::trace("po3 tweaks installed");
            }

            log::trace("Calling JCWrapper init()");
            DCURSES::jcontainers::JCWrapper::GetSingleton()->Init();
            DCURSES::RegisterEventSinks();

            DCURSES::QLIEAttemptInit();

            break;
        }

        case SKSE::MessagingInterface::kNewGame:
        case SKSE::MessagingInterface::kPostLoadGame: {
            DCURSES::MGEFOnGameLoad();

            DCURSES::StaticDataHolder::GetSingleton()->InvalidateCache();

            bool DDNG_loaded = DeviousDevicesAPI::LoadAPI();

            if (!DDNG_loaded) {
                log::critical("Devious Devices NG not loaded. Mod will be disabled.");
                stl::report_and_fail("Devious devices NG not loaded for Devious Curses. Please check to make sure that you have version 4.0+");
            }
            else {
                log::trace("Devious Devices NG loaded: {}.", DeviousDevicesAPI::g_API->GetDatabase().size());
            }

            if (!DCURSES::QLIEAttemptRegisterEvent()) {
                log::info("Quick Loot IE Not Loaded.");
            }

            DCURSES::EventsStartup();

            DCURSES::LoadMCMSettings();
            DCURSES::RecalculateDeviceLists();
            DCURSES::ScriptingManager().MCMRegisterModEvents();

            DCURSES::counters.clock_SexTimeout -= 2;
           

            DCURSES::Util::ExecuteWithDelay(2s, [] {
                DCURSES::StartUpdateLoop();
            });

            break;
        }
        case SKSE::MessagingInterface::kPostLoad: {
            DCURSES::CreateExclusionsFileIfNeeded();
            DCURSES::CreateModExclusionsFileIfNeeded();
            DCURSES::CreateThemesFileIfNeeded();

            std::string pluginName = getJContainersPluginName();

            SKSE::GetMessagingInterface()->RegisterListener("SlaveTatsNG", slavetats_ng::messaging_hook);
            SKSE::GetMessagingInterface()->RegisterListener(pluginName.c_str(), [](SKSE::MessagingInterface::Message* a_msg) {
                if (a_msg && a_msg->type == jc::message_root_interface) {
                    const jc::root_interface* root = jc::root_interface::from_void(a_msg->data);
                    if (root)
                        DCURSES::jcontainers::JCWrapper::GetSingleton()->PreInit(root);
                }
                });

            break;

        }
        case SKSE::MessagingInterface::kSaveGame: {
            DCURSES::counters.clock_SexTimeout -= 2;
            DCURSES::SaveMCMSettings();
            break;
        }
        case SKSE::MessagingInterface::kInputLoaded: {
            DCURSES::Translator::CheckMCMTranslations();
            DCURSES::Translator::UpdateTranslations();
        }
        }
        
    });

    log::trace("Initializing Papyrus binding...");
    if (GetPapyrusInterface()->Register(DCURSES::PapyrusFunctions)) {
        log::trace("Papyrus functions bound.");
    } else {
        stl::report_and_fail("Failure to register Papyrus bindings.");
    }

    DCURSES::InitializeSerialization();

    return true;
}