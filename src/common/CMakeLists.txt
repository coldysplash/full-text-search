set(target_name parser)

add_library(${target_name} STATIC 
    common/parser.cpp
    common/parser.hpp)

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
  parser.test
  common/parser.test.cpp
)

target_link_libraries(
  parser.test
  GTest::gtest_main
  parser
)

include(GoogleTest)
gtest_discover_tests(parser.test)