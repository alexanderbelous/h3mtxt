add_executable(river_sprites_cheatsheet
    "river_sprites_cheatsheet.cpp"
)

# Dependencies:
target_link_libraries(river_sprites_cheatsheet PRIVATE h3mtxt::H3MWriter)
target_link_libraries(river_sprites_cheatsheet PRIVATE h3mtxt::Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(river_sprites_cheatsheet)
