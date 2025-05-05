#include "src/Settings.hpp"
#include "src/Devices.hpp"
#include "src/Utils.hpp"
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

#include "include/DDNG_API.h"

#include <d3d11.h>
#include <windows.h>
#include <debugapi.h>
#include <chrono>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include <unordered_set>
#include <algorithm>

using namespace SKSE::log;
using namespace SKSE::stl;
using namespace SKSE;

namespace DCURSES {
    //GLOBALS
    

    void InitializeLogging() {
        auto path = log_directory();
        if (!path) {
            report_and_fail("Unable to lookup SKSE logs directory.");
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

    void P_OnUpdate(RE::StaticFunctionTag*) {
        auto c1 = std::chrono::high_resolution_clock::now();
        EventsUpdate();
        auto c2 = std::chrono::high_resolution_clock::now();
        SexUpdate();
        //QIUpdate();
        auto c3 = std::chrono::high_resolution_clock::now();
        MarkControllerUpdate();
        auto c4 = std::chrono::high_resolution_clock::now();
        OppDeviceUpdate();
        auto c5 = std::chrono::high_resolution_clock::now();
        
        auto d1 = (c2 - c1).count() / 1000.0;
        auto d2 = (c3 - c2).count() / 1000.0;
        auto d3 = (c4 - c3).count() / 1000.0;
        auto d4 = (c5 - c4).count() / 1000.0;
        auto dt = (c5 - c1).count() / 1000.0;

        log::trace("UPDATE: E: {:.2f}, S: {:.2f}, M: {:.2f}, O: {:.2f} total: {:.2f}", d1, d2, d3, d4, dt);

        //Always do last!
        counters.tick();
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

    void P_Test(RE::StaticFunctionTag*) {
        log::trace("DCURSES test");
        auto player = RE::PlayerCharacter::GetSingleton();
        
        auto mark = GetLewdMark(player);
        if (mark) {
            RemoveLewdMark(player);
        }
        else {
            DoLewdMarkEvent("", false);
        }
        

    }

    bool PapyrusFunctions(RE::BSScript::IVirtualMachine* ivm) {
        ivm->RegisterFunction("Test", "DCursesLib", P_Test);
        ivm->RegisterFunction("GetRandomEquipableDevice", "DCursesLib", P_GetRandomEquipableDevice);
        ivm->RegisterFunction("NumDevicesVisible", "DCursesLib", P_numDevicesVisible);
        ivm->RegisterFunction("OnUpdate", "DCursesLib", P_OnUpdate);
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

    log::info("Initializing DeviousCurses");

    //

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        switch (message->type)
        {
        case SKSE::MessagingInterface::kDataLoaded: {
            if (!DCURSES::CheckESPLoaded()) {
                log::critical("Devious curses ESP not loaded. Mod will be disabled.");
                stl::report_and_fail("Devious Curses ESP is not loaded. If you are on skyrim version older than 1.6.1130 (Not AE) make sure to install Backported Extended ESL Support.");
                return;
            }
            else {
                log::trace("ESP Loaded.");
            }

            log::trace("Calling JCWrapper init()");
            DCURSES::jcontainers::JCWrapper::GetSingleton()->Init();
            DCURSES::RegisterEventSinks();

            DCURSES::QLIEAttemptInit();

            break;
        }
        case SKSE::MessagingInterface::kNewGame:
        case SKSE::MessagingInterface::kPostLoadGame: {
            auto perk = DCURSES::StaticDataHolder::GetSingleton()->LookupForm<RE::BGSPerk>(DCURSES::MGEF_CONTROLLER, "Devious Curses.esp");
            auto player = RE::PlayerCharacter::GetSingleton();
            if (!player->HasPerk(perk)) {
                player->AddPerk(perk);
            }

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

            DCURSES::StartPapyrusTimer();
            DCURSES::EventsStartup();

            DCURSES::LoadMCMSettings();
            DCURSES::RecalculateDeviceLists();
            //DCURSES::P_UpdateSKSE(nullptr);
            //DCURSES::counters.clock_lastSex = -10;
            break;
        }
        case SKSE::MessagingInterface::kPostLoad: {
            DCURSES::CreateExclusionsFileIfNeeded();
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
            DCURSES::counters.clock_SexTimeout = -2;
            DCURSES::SaveMCMSettings();
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