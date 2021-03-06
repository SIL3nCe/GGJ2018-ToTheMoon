cmake_minimum_required(VERSION 3.1)

set(SHINE_EDITOR_EXT_DIR "" CACHE PATH "Extension directory")
set(SHSDK_EDITOR_LIBRARIES "" CACHE PATH "ShSDK (editor) path") # FIXME

FILE(MAKE_DIRECTORY ${SHINE_EDITOR_EXT_DIR})

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Extension files
set(SOURCES_Extension Extension.cpp Extension.h)
source_group("Extension" FILES ${SOURCES_Extension})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_main} ${SOURCES_Extension})

add_library(ExtGGJ2018 SHARED ${SOURCES})

set_property(TARGET ExtGGJ2018 PROPERTY FOLDER "Editor")

set_property(TARGET ExtGGJ2018 APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET ExtGGJ2018 APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET ExtGGJ2018 APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")
set_property(TARGET ExtGGJ2018 APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME

set_property(TARGET ExtGGJ2018 APPEND PROPERTY COMPILE_DEFINITIONS "PLUGIN_PATH=\"$<TARGET_FILE:Plugin_Editor>\"")

target_link_libraries(ExtGGJ2018 PRIVATE ${SHSDK_EDITOR_LIBRARIES})
target_include_directories(ExtGGJ2018 PRIVATE ${SHSDK_INCLUDE_DIR} "$<TARGET_PROPERTY:Plugin_Editor,INTERFACE_INCLUDE_DIRECTORIES>")

if (WIN32)
	set_property(TARGET ExtGGJ2018 PROPERTY RUNTIME_OUTPUT_DIRECTORY "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtGGJ2018 PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtGGJ2018 PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SHINE_EDITOR_EXT_DIR}")
else (WIN32)
	set_property(TARGET ExtGGJ2018 PROPERTY LIBRARY_OUTPUT_DIRECTORY "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtGGJ2018 PROPERTY LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SHINE_EDITOR_EXT_DIR}")
	set_property(TARGET ExtGGJ2018 PROPERTY LIBRARY_OUTPUT_DIRECTORY_RELEASE "${SHINE_EDITOR_EXT_DIR}")
endif (WIN32)

set_property(TARGET ExtGGJ2018 PROPERTY PREFIX "")
set_property(TARGET ExtGGJ2018 PROPERTY DEBUG_POSTFIX "_Debug")
set_property(TARGET ExtGGJ2018 PROPERTY RELEASE_POSTFIX "_Release")

file(COPY "GGJ2018.configext" DESTINATION "${SHINE_EDITOR_EXT_DIR}")
