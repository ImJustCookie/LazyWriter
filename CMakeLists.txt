cmake_minimum_required(VERSION 3.10)

# Enable C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name and languages
project(lazy_writer LANGUAGES CXX)

# Find the required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Enable automatic MOC (Meta-Object Compiler)
set(CMAKE_AUTOMOC ON)

# Add your executable
add_executable(lazy_writer src/main.cpp include/lorem.hpp include/Window.hpp src/Window.cpp)

# Link Qt libraries to your executable
target_link_libraries(lazy_writer PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Include directories
target_include_directories(lazy_writer PUBLIC include)