cmake_minimum_required(VERSION 3.8)
project(2_NewTest VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES main.cpp ../../engine/src/Transform.cpp)

add_executable(2_NewTest ${SOURCE_FILES})

target_compile_features(2_NewTest PUBLIC cxx_std_17)

target_include_directories(2_NewTest PUBLIC ../../engine/include)