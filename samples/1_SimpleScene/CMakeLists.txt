cmake_minimum_required(VERSION 3.8)
project(1_SimpleScene VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES main.cpp FirstPersonSystem.cpp)

add_executable(1_SimpleScene ${SOURCE_FILES})

target_compile_features(1_SimpleScene PUBLIC cxx_std_17)

target_link_libraries(1_SimpleScene PRIVATE Aeyon3D)
