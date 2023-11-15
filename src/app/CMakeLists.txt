set(target_name fts)

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
    driver
    CLI11
)
