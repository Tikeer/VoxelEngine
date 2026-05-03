add_executable(VoxelGame
    src/main.cpp
    src/GameApp.cpp
)

target_link_libraries(VoxelGame
    PRIVATE
        VoxelEngine
        voxel_compiler_flags
)

add_custom_command(TARGET VoxelGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:VoxelGame>/assets"
    COMMENT "Copying assets to output directory"
)