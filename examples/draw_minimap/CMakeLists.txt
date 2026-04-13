add_executable(draw_minimap "draw_minimap.cpp")
# Dependencies:
target_link_libraries(draw_minimap PRIVATE h3mtxt::H3MReader)
target_link_libraries(draw_minimap PRIVATE h3mtxt::Minimap)
# Set compiler options.
h3mtxt_add_common_compiler_options(draw_minimap)
