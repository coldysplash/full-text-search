set(target_name fts)

add_library(${target_name} STATIC
  libfts/fts.cpp
  libfts/fts.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
  ${target_name}
  PRIVATE
)

add_executable(
  fts.test
  libfts/fts.test.cpp
)

target_link_libraries(
  fts.test
  GTest::gtest_main
  fts
)

target_include_directories(
    fts.test
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

include(GoogleTest)
gtest_discover_tests(fts.test)