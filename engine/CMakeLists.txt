add_library(VoxelEngine STATIC
    # core
    src/core/Window.cpp
    src/core/Application.cpp
    src/core/Logger.cpp
    src/core/Time.cpp

    # rendering
    src/rendering/Renderer.cpp
    src/rendering/Shader.cpp
    src/rendering/Texture.cpp
    src/rendering/Camera.cpp
    src/rendering/Mesh.cpp
    src/rendering/ChunkMesher.cpp

    # world
    src/world/Chunk.cpp
    src/world/World.cpp
    src/world/Block.cpp
    src/world/ChunkManager.cpp
    src/world/NoiseGenerator.cpp
 "include/Logger.h")

target_include_directories(VoxelEngine
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(VoxelEngine
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        glfw
        glad_gl_core
        stb_image
        voxel_compiler_flags
)

target_compile_definitions(VoxelEngine PRIVATE
    $<$<CONFIG:Debug>:VOXEL_DEBUG>
)