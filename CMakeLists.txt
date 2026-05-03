cmake_minimum_required(VERSION 3.25)

project(VoxelEngine
    VERSION 0.1.0
    DESCRIPTION "A voxel engine built with modern C++ and OpenGL"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected — defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(voxel_compiler_flags INTERFACE)

target_compile_options(voxel_compiler_flags INTERFACE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:
        -Wall -Wextra -Wpedantic -Wshadow
        -Wnon-virtual-dtor -Wold-style-cast
        -Woverloaded-virtual -Wnull-dereference
        $<$<CONFIG:Debug>:-g -O0 -fsanitize=address,undefined>
        $<$<CONFIG:Release>:-O3 -DNDEBUG -march=native>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g -DNDEBUG>
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX /permissive-
        $<$<CONFIG:Debug>:/Od /Zi /fsanitize=address>
        $<$<CONFIG:Release>:/O2 /DNDEBUG>
    >
)

target_link_options(voxel_compiler_flags INTERFACE
    $<$<AND:$<CXX_COMPILER_ID:GNU,Clang>,$<CONFIG:Debug>>:
        -fsanitize=address,undefined>
)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v2.0.6
    GIT_SHALLOW    TRUE
    SOURCE_SUBDIR  cmake
)
FetchContent_MakeAvailable(glad)
glad_add_library(glad_gl_core REPRODUCIBLE API gl:core=4.6)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.14.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(stb)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE "${stb_SOURCE_DIR}")

add_subdirectory(engine)

add_subdirectory(game)


#  Tests  (optional, enable with -DVOXEL_BUILD_TESTS=ON)

option(VOXEL_BUILD_TESTS "Build unit tests" OFF)
if(VOXEL_BUILD_TESTS)
    enable_testing()
    # add_subdirectory(tests)
endif()

include(GNUInstallDirs)
install(TARGETS VoxelGame
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY assets/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/VoxelEngine/assets
)