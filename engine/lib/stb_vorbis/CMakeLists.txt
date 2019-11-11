cmake_minimum_required(VERSION 3.8)
project(stb_vorbis)

add_library(stb_vorbis STATIC stb_vorbis.c)

target_include_directories(stb_vorbis PUBLIC include/)
