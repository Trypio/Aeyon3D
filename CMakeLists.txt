cmake_minimum_required(VERSION 3.8)
project(Aeyon3D LANGUAGES C CXX)

add_subdirectory(engine)
add_subdirectory(samples)

#if(CMAKE_PROJECT_NAME STREQUAL Aeyon3D AND BUILD_TESTING)
    add_subdirectory(test)
#endif()