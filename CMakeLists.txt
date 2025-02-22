cmake_minimum_required(VERSION 3.10)

project(lazy_writer LANGUAGES CXX)

add_executable(lazy_writer src/main.cpp include/lorem.hpp)

target_include_directories(lazy_writer PUBLIC include)


