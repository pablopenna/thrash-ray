cmake_minimum_required(VERSION 3.5)
project(my_raylib_game C)
set(CMAKE_C_STANDARD 99)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

# Platform auto-detection (native Linux builds only). Values are cache defaults, override with -D on the command line
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT CMAKE_CROSSCOMPILING)
    # Raspberry Pi: device-tree model looks like "Raspberry Pi 4 Model B Rev 1.4"
    set(IS_RASPBERRY_PI FALSE)
    if(EXISTS "/proc/device-tree/model")
        file(READ "/proc/device-tree/model" _model)
        if(_model MATCHES "Raspberry Pi")
            set(IS_RASPBERRY_PI TRUE)
            message(STATUS "Detected: ${_model}")
        endif()
    endif()

    # Pi 4/5 support desktop GL 3.1 at most, but raylib defaults to 3.3. DRM builds pick GLES on their own
    if(IS_RASPBERRY_PI AND (NOT DEFINED PLATFORM OR PLATFORM STREQUAL "Desktop"))
        set(OPENGL_VERSION "2.1" CACHE STRING "Force a specific OpenGL Version?")
    endif()

    # Build the GLFW backend matching the current session. If unknown (SSH, TTY, CI) build both, GLFW picks one at runtime
    set(_session "$ENV{XDG_SESSION_TYPE}")
    if(_session STREQUAL "wayland")
        set(_wayland ON)
        set(_x11 OFF)
    elseif(_session STREQUAL "x11")
        set(_wayland OFF)
        set(_x11 ON)
    else()
        set(_wayland ON)
        set(_x11 ON)
    endif()
    set(GLFW_BUILD_WAYLAND ${_wayland} CACHE BOOL "Build the bundled GLFW with Wayland support")
    set(GLFW_BUILD_X11     ${_x11}     CACHE BOOL "Build the bundled GLFW with X11 support")
    message(STATUS "Session '${_session}': GLFW Wayland=${GLFW_BUILD_WAYLAND} X11=${GLFW_BUILD_X11}")
endif()

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/sources/*.c") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
