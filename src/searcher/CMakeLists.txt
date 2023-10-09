set(target_name searcher)

add_library(${target_name} STATIC 
    searcher/searcher.cpp
    searcher/searcher.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
    ${target_name}
    PRIVATE
      parser
      indexer
      picosha2
)

add_executable(
  searcher.test
  searcher/searcher.test.cpp
)

target_link_libraries(
  searcher.test
  GTest::gtest_main
  searcher
  parser
)

include(GoogleTest)
gtest_discover_tests(searcher.test)