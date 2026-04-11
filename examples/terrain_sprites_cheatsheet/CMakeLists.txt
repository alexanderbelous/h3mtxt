add_executable(terrain_sprites_cheatsheet
    "terrain_sprites_cheatsheet.cpp"
)

# Dependencies:
target_link_libraries(terrain_sprites_cheatsheet PRIVATE h3mtxt::H3MWriter)
target_link_libraries(terrain_sprites_cheatsheet PRIVATE h3mtxt::Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(terrain_sprites_cheatsheet)

