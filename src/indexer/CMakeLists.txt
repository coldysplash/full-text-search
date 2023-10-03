set(target_name indexer)

add_library(${target_name} STATIC 
    indexer/indexer.cpp
    indexer/indexer.hpp)

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
      picosha2
)

add_executable(
  indexer.test
  indexer/indexer.test.cpp
)

target_link_libraries(
  indexer.test
  GTest::gtest_main
  indexer
  parser
)

include(GoogleTest)
gtest_discover_tests(indexer.test)