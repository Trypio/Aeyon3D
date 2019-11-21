cmake_minimum_required(VERSION 3.8)
project(Aeyon3DTest VERSION 1.0 LANGUAGES C CXX)

set(SOURCE_FILES main.cpp ECSTestSuite.cpp)

add_executable(Aeyon3DTest ${SOURCE_FILES})

add_subdirectory(lib)

target_compile_features(Aeyon3DTest PUBLIC cxx_std_17)
target_link_libraries(Aeyon3DTest PUBLIC Aeyon3D catch)
