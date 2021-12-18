# TermAPI/v3
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	# Fix MSVC __cplusplus macro
	string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")
endif()

find_package(307lib::shared REQUIRED)
find_package(307lib::str-lib REQUIRED)

project("TermAPI" VERSION 3.0.0)

set(HEADERS
	"./include/ANSIDefs.h"
	"./include/color-values.h"
	"./include/color-transform.hpp"

	"./include/format-functions.hpp"
	"./include/FormatFlag.hpp"
	"./include/Layer.hpp"
	"./include/setcolor.hpp"
	"./include/setcolor-functions.hpp"
	"./include/ColorPalette.hpp"

	"./include/Message.hpp"
	"./include/Sequence.hpp"
	"./include/SequenceDefinitions.hpp"
	"./include/TermAPIQuery.hpp"
	"./include/TermAPI.hpp"
	"./include/CursorOrigin.h"

	"./include/LineCharacter.hpp"
)
if(WIN32) # Add windows-specific functionality if target is windows
	list(APPEND HEADERS "./include/TermAPIWin.hpp")
endif()


option(TERMAPI_ENABLE_XLOG "Enable the xLog.hpp header." ON)
if (TERMAPI_ENABLE_XLOG)
	list(APPEND HEADERS "./include/xLog.hpp")
endif()

set(SRC
	"./src/setcolor.cpp"
)

add_library(TermAPI STATIC ${HEADERS} ${SRC})

target_link_libraries(TermAPI PUBLIC 307lib::shared 307lib::str-lib)

target_include_directories(TermAPI PUBLIC 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:include>"
)
target_link_directories(TermAPI PUBLIC 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
	"$<INSTALL_INTERFACE:src>"
)

# Packaging
include(GenerateExportHeader)
generate_export_header(TermAPI EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/export.h")

# Include packaging by default if this is the top-level directory
if (307lib_ENABLE_PACKAGING)
	add_subdirectory("packaging")
endif()

