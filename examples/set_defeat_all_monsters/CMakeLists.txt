add_executable(set_defeat_all_monsters
    "set_defeat_all_monsters.cpp"
)

# Dependencies:
target_link_libraries(set_defeat_all_monsters PRIVATE h3mtxt::H3MReader)
target_link_libraries(set_defeat_all_monsters PRIVATE h3mtxt::H3MWriter)
target_link_libraries(set_defeat_all_monsters PRIVATE h3mtxt::Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(set_defeat_all_monsters)

