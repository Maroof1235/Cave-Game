cmake_minimum_required(VERSION 3.21)
project(CaveGame C)

# Use C99 and sane defaults
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Enable folders in IDEs like Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# vcpkg-provided config
find_package(raylib CONFIG REQUIRED)

# Be robust across ports: prefer namespaced if present, else plain.
if (TARGET raylib::raylib)
  set(RAYLIB_TARGET raylib::raylib)
elseif (TARGET raylib)
  set(RAYLIB_TARGET raylib)
else()
  message(FATAL_ERROR
    "raylib was found but exported no known CMake target. "
    "Known targets: 'raylib::raylib' or 'raylib'. "
    "CMAKE_PREFIX_PATH='${CMAKE_PREFIX_PATH}'")
endif()

add_executable(cave-game
    tech-demo/src/main.c
)

target_link_libraries(cave-game PRIVATE ${RAYLIB_TARGET})

# On MSVC, set working directory for debugging to the binary dir
if (MSVC)
    set_target_properties(cave-game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# Install rules (optional)
include(GNUInstallDirs)
install(TARGETS cave-game RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
