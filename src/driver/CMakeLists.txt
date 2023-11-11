set(target_name driver)

add_library(${target_name} STATIC 
    driver/driver.cpp
    driver/driver.hpp)

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
      searcher
      CLI11
      replxx
)