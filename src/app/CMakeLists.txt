set(target_name app)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    app/main.cpp
)

target_link_libraries(
  ${target_name}
  PRIVATE
    parser
    indexer
    searcher
    CLI11
    nlohmann_json::nlohmann_json
)