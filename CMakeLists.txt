cmake_minimum_required(VERSION 3.9)

project(vector LANGUAGES C)

add_library(vector STATIC)

target_sources(vector PRIVATE
    src/vector.c
)

target_include_directories(vector PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(vector
)
