cmake_minimum_required(VERSION 3.8)
project(Aeyon3D LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/Event/Event.cpp
        src/Event/EventSystem.cpp
        src/Input/SDLInput.cpp
        src/Bounds.cpp
        src/Plane.cpp
        src/Graphics/Frustum.cpp
        src/Graphics/IndexBuffer.cpp
        src/Graphics/VertexBuffer.cpp
        src/Graphics/Camera.cpp
        src/Color.cpp
        src/Engine.cpp
        src/Graphics/GraphicsSystem.cpp
        src/Graphics/Light.cpp
        src/Graphics/Material.cpp
        src/Graphics/Mesh.cpp
        src/Graphics/SDLWindow.cpp
        src/Graphics/Shader.cpp
        src/Graphics/ShaderProgram.cpp
        src/Graphics/Texture.cpp
        src/Time.cpp
        src/Transform.cpp
        src/Graphics/ShaderParser.cpp
        src/Graphics/PixelFormat.cpp
        src/Graphics/PropertyVisitor.cpp
        src/SceneLoader.cpp
        include/Graphics/VertexAttribute.hpp
        src/Graphics/MeshRenderer.cpp src/Actor.cpp src/Component.cpp src/BehaviorSystem.cpp)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm 0.9.8 REQUIRED)
find_package(assimp REQUIRED)
find_package(spdlog REQUIRED)


set(INCLUDE_DIRS_PUBLIC include ${SDL2_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})
set(LINK_LIBS_PUBLIC glad stb_image pugixml imgui stduuid spdlog::spdlog_header_only EnumFlags ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} ${ASSIMP_LIBRARIES})

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

add_subdirectory(lib)

add_library(Aeyon3D ${SOURCE_FILES})


target_include_directories(Aeyon3D PUBLIC ${INCLUDE_DIRS_PUBLIC})
target_link_libraries(Aeyon3D PUBLIC ${LINK_LIBS_PUBLIC})

