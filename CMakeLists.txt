cmake_minimum_required(VERSION 3.11)
project(2DWarGame)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(include)
add_subdirectory(src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textures/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/font.ttf)