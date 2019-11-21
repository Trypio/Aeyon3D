cmake_minimum_required(VERSION 3.8)
project(imgui)

add_library(imgui STATIC imgui.cpp imgui_draw.cpp imgui_impl_opengl3.cpp imgui_impl_sdl.cpp imgui_widgets.cpp)

target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS} include/  ${glad_SOURCE_DIR}/include)
target_link_directories(imgui PUBLIC glad ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY})