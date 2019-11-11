cmake_minimum_required(VERSION 3.8)
project(pugixml)

add_library(pugixml STATIC pugixml.cpp)

target_include_directories(pugixml PUBLIC include/)
