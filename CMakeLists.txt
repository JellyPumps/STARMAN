cmake_minimum_required(VERSION 3.30)
project(STARMAN)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(raylib QUIET)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR WIN32)
    set(FETCH_RAYLIB TRUE)
endif()

if (NOT raylib_FOUND OR FETCH_RAYLIB)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.5
    )

    if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR WIN32)
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build raylib as a static library" FORCE)
    endif()

    FetchContent_MakeAvailable(raylib)
endif ()

set(SOURCE_FILES
    src/main.cpp
        src/App.cpp
        src/App.hpp
        src/SceneManager.cpp
        src/SceneManager.hpp
        src/SceneMenu.cpp
        src/SceneMenu.hpp
        src/Scene.hpp
        src/SceneIntro.cpp
        src/SceneIntro.hpp
        src/ConfigManager.cpp
        src/ConfigManager.hpp
)

add_executable(STARMAN ${SOURCE_FILES})

target_link_libraries(STARMAN PRIVATE raylib)

# macOS Frameworks
if (APPLE)
    target_link_libraries(STARMAN PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif ()

# Linux X11 / Wayland
if (UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(WAYLAND QUIET wayland-client wayland-cursor wayland-egl)
    if (WAYLAND_FOUND)
        message(STATUS "Using Wayland for Raylib")
        target_compile_definitions(STARMAN PRIVATE PLATFORM_DESKTOP USE_WAYLAND)
        target_link_libraries(STARMAN PRIVATE wayland-client wayland-cursor wayland-egl)
    else ()
        message(STATUS "Using X11 for Raylib")
        find_package(X11 REQUIRED)
        target_link_libraries(STARMAN PRIVATE m pthread dl rt X11)
    endif ()
endif ()

# Windows (Native or Cross-Compilation)
if (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(STARMAN PRIVATE winmm)
endif ()