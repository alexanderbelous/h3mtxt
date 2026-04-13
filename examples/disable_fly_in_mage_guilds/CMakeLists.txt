add_executable(disable_fly_in_mage_guilds
    "disable_fly_in_mage_guilds.cpp"
)

# Dependencies:
target_link_libraries(disable_fly_in_mage_guilds PRIVATE h3mtxt::H3MReader)
target_link_libraries(disable_fly_in_mage_guilds PRIVATE h3mtxt::H3MWriter)
target_link_libraries(disable_fly_in_mage_guilds PRIVATE h3mtxt::Map)

# Set compiler options.
h3mtxt_add_common_compiler_options(disable_fly_in_mage_guilds)

