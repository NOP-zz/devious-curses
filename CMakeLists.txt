# It's recommended to set a minimum CMake version.
# If you use CMake features from higher versions, update this to match.
cmake_minimum_required(VERSION 3.21)

# Set your project name. This will be the name of your SKSE .dll file.
project(DeviousCurses VERSION 0.0.1 LANGUAGES CXX)


set(sources
        plugin.cpp
)

add_custom_target(
    Codegen ALL
    COMMENT "Running Python Codegen"
    COMMAND python CODEGEN.py
    WORKING_DIRECTORY ./../../
    VERBATIM
)

set(OUTPUT_FOLDER "S:/Skyrim/MO2/mods/DeviousCurses")
set(OUTPUT_FOLDER_VR "S:/SkyrimVR/mo2/mods/DeviousCurses")

# set(CommonLibSSE_DIR "S:/Skyrim/modding/CommonLibVR/build/debug-msvc-vcpkg-all")

# Setup your SKSE plugin as an SKSE plugin!
find_package(directxtk CONFIG REQUIRED)
find_package(CommonLibSSE CONFIG REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${sources}) # <--- specifies plugin.cpp
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23) # <--- use C++23 standard
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h) # <--- PCH.h is required!
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11.dll)
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft::DirectXTK)
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
add_dependencies(${PROJECT_NAME} Codegen)


set(SKYRIM_FOLDER "S:/SteamLibrary/steamapps/common/Skyrim Special Edition") # Change this to your skyrim instalation location
set(SCRIPTS_SOURCE "${CMAKE_SOURCE_DIR}/SourceScripts/")


add_custom_command(
    TARGET "${PROJECT_NAME}"
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${OUTPUT_FOLDER}/SKSE/Plugins"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_FOLDER}/SKSE/Plugins/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${OUTPUT_FOLDER_VR}/SKSE/Plugins"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_FOLDER_VR}/SKSE/Plugins/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    VERBATIM
)

add_custom_target(
    Papyrus ALL
    COMMENT "Compiling MCM"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/DCurses_MCM.psc" "${OUTPUT_FOLDER}/scripts/source/DCurses_MCM.psc"
    COMMAND "${SKYRIM_FOLDER}/Papyrus Compiler/PapyrusCompiler.exe" DCurses_MCM.psc -f="${SKYRIM_FOLDER}/Data/Scripts/Source/TESV_Papyrus_Flags.flg" -i="${SCRIPTS_SOURCE}\;${SKYRIM_FOLDER}/Data/Scripts/Source/" -o="${OUTPUT_FOLDER}/scripts" -q
    
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/DCurses_MCM.psc" "${OUTPUT_FOLDER_VR}/scripts/source/DCurses_MCM.psc"
    COMMAND "${SKYRIM_FOLDER}/Papyrus Compiler/PapyrusCompiler.exe" DCurses_MCM.psc -f="${SKYRIM_FOLDER}/Data/Scripts/Source/TESV_Papyrus_Flags.flg" -i="${SCRIPTS_SOURCE}\;${SKYRIM_FOLDER}/Data/Scripts/Source/" -o="${OUTPUT_FOLDER_VR}/scripts" -q
    WORKING_DIRECTORY "${OUTPUT_FOLDER}/scripts/source"
)
add_dependencies(Papyrus Codegen)

add_custom_target(
    Translations ALL
    COMMENT "Preparing Translation Files"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/translationData/Devious Curses_English.json" "${OUTPUT_FOLDER}/translations/Devious Curses_ENGLISH.json"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/translationData/Devious Curses_English.txt" "${OUTPUT_FOLDER}/interface/translations/Devious Curses_ENGLISH.txt"

    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/translationData/Devious Curses_English.json" "${OUTPUT_FOLDER_VR}/translations/Devious Curses_ENGLISH.json"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/translationData/Devious Curses_English.txt" "${OUTPUT_FOLDER_VR}/interface/translations/Devious Curses_ENGLISH.txt"
)
add_dependencies(Translations Codegen)

