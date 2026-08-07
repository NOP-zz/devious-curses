cmake_minimum_required(VERSION 3.21)

project(DeviousCurses VERSION 0.9.0 LANGUAGES CXX)


set(sources
        plugin.cpp
        src/Consequences.cpp
        src/Contraptions.cpp
        src/DebugMode.cpp
        src/Devices.cpp
        src/Events.cpp
        src/FastTravel.cpp
        src/Locations.cpp
        src/MGEF_Controller.cpp
        src/Migration.cpp
        src/ModEvents.cpp
        src/OppDevices.cpp
        src/QuestInteractions.cpp
        src/Scripting.cpp
        src/Serializer.cpp
        src/Settings.cpp
        src/Tats.cpp
        src/TESEvents.cpp
        src/Themes.cpp
        src/Translation.cpp
        src/Utils.cpp
        src/Sex.cpp

        src/Quest/Radiant.cpp
        src/Quest/QuestSettings.cpp
        src/Quest/QuestEvents.cpp
        src/Quest/Serialized.cpp
)


# Setup your SKSE plugin as an SKSE plugin!
find_package(directxtk CONFIG REQUIRED)
find_package(CommonLibSSE CONFIG REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${sources}) # <--- specifies plugin.cpp
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23) # <--- use C++23 standard
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h) # <--- PCH.h is required!
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11.dll)
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft::DirectXTK)
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
target_include_directories(${PROJECT_NAME} PRIVATE include)
