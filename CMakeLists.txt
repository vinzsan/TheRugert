cmake_minimum_required(VERSION 3.10)

project(${CMAKE_SOURCE_DIR} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test src/main.cpp
        include/BaseWindow.hpp
        include/MouseHandler.hpp
        include/SharedMetadata.hpp
        include/Player.hpp)

target_link_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(test PRIVATE raylib)
target_compile_options(test PRIVATE -O3 -fno-rtti -fno-exceptions)
