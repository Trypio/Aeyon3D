cmake_minimum_required(VERSION 3.8)
project(Aeyon3DTests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES EventTest.cpp)

find_package(Catch2 3 REQUIRED)

add_executable(Aeyon3DTests ${SOURCE_FILES})
target_link_libraries(Aeyon3DTests PRIVATE Aeyon3D Catch2::Catch2WithMain)
