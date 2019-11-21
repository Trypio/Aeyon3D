cmake_minimum_required(VERSION 3.8)
project(catch)

add_library(catch INTERFACE)

target_include_directories(catch INTERFACE include/)