add_executable(make_all_monsters_savage
    "make_all_monsters_savage.cpp"
)

# Dependencies:
target_link_libraries(make_all_monsters_savage PRIVATE h3mtxt::H3MReader)
target_link_libraries(make_all_monsters_savage PRIVATE h3mtxt::H3MWriter)
target_link_libraries(make_all_monsters_savage PRIVATE h3mtxt::Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(make_all_monsters_savage)

