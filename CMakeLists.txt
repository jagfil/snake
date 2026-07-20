cmake_minimum_required(VERSION 3.27)
project(snake)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG        2.6.1
)

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SFML)

add_executable(snake
        main.cpp
        Snake.hpp
        Fruit.hpp
        Game.hpp
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

target_compile_definitions(snake PRIVATE SFML_STATIC)

target_link_libraries(snake PRIVATE sfml-graphics sfml-window sfml-system)
