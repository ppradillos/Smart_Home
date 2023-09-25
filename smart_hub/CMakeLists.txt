# It's strongly recommended that you specify a toolchain file instead of setting everything in the root CMakeLists.txt

cmake_minimum_required(VERSION 3.22)
project(smart_hub)

# Release build by default, unless otherwise stated
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

message("-----------------------------------------------------------")
message("Creating makefile of ${CMAKE_PROJECT_NAME} as ${CMAKE_BUILD_TYPE}")

# Check if compiler has been already set via toolchain file or as external argument
if(NOT CMAKE_C_COMPILER)
  # User-defined compiler (default to gcc)
  set(CMAKE_C_COMPILER gcc)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "linux")
  set(EXTERNAL_HEADERS 
    3rd_party/log4embedded/log4embedded-1.0.0-linux-${CMAKE_SYSTEM_PROCESSOR}/include/log4embedded.h)
else()
  message("Error: 3rd party dependency only works in Linux systems")
endif()

#Files
set(HEADERS
  include/errorCodes.h
	include/smartHubService.h
  ${EXTERNAL_HEADERS})

set(SOURCES
  src/main.c
	src/smartHubService.c)

# Debug and release compiler flags
set(COMMON_C_FLAGS -Wall -Wextra -Werror -shared -fPIE -fdiagnostics-color -pedantic)
set(DEBUG_CFLAGS ${COMMON_C_FLAGS} -g -O0 -DDEBUG)
set(RELEASE_CFLAGS ${COMMON_C_FLAGS} -s -O3)

include_directories(include/
                    3rd_party/log4embedded/log4embedded-1.0.0-linux-${CMAKE_SYSTEM_PROCESSOR}/include/)

link_directories(3rd_party/log4embedded/log4embedded-1.0.0-linux-${CMAKE_SYSTEM_PROCESSOR}/lib/)

add_executable(${PROJECT_NAME} ${SOURCES})

# ${CMAKE_C_FLAGS} coming from toolchain files
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CFLAGS ${CMAKE_C_FLAGS} ${DEBUG_CFLAGS})
else()
  set(CFLAGS ${CMAKE_C_FLAGS} ${RELEASE_CFLAGS})
endif()  

# Set up installation folder, if does not exist already
if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
endif()

message("CMake's configuration done. Now navigate to the CMake's build directory you have set up: ${CMAKE_BINARY_DIR}.")
message("Once you navigate to the build directory, now you can:")
message("Run \"make\" to build the library binary in ${CMAKE_BINARY_DIR}, with no further installation.")
message("Run \"make install\" to install the files in ${CMAKE_INSTALL_PREFIX}/bin.")

# Install smart hub service binary in ${CMAKE_INSTALL_PREFIX}
install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION bin)

target_link_libraries (${PROJECT_NAME} PRIVATE -llog4embedded -lc)