set(target_name searcher-c)

add_library(${target_name} SHARED
    searcher-c/searcher-c.cpp
    searcher-c/searcher-c.h)

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
    searcher
)