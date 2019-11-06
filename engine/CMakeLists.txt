project(Aeyon3D LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/ECS/Component.cpp
        src/ECS/Entity.cpp
        src/ECS/EntityHandle.cpp
        src/ECS/EntityMap.cpp
        src/ECS/EntityStore.cpp
        src/ECS/System.cpp
        src/ECS/World.cpp
        src/Event/Event.cpp
        src/Event/EventSystem.cpp
        src/Input/SDLInput.cpp
        src/Bounds.cpp
        src/Plane.cpp
        src/Graphics/Frustum.cpp
        src/Graphics/IndexBuffer.cpp
        src/Graphics/VertexBuffer.cpp
        src/BoxCollider.cpp
        src/Camera.cpp
        src/Color.cpp
        src/Engine.cpp
        src/Graphics/GraphicsSystem.cpp
        src/Graphics/Light.cpp
        src/Graphics/Material.cpp
        src/Graphics/Mesh.cpp
        src/Graphics/MeshRenderer.cpp
        src/Scene.cpp
        src/SDLException.cpp
        src/SDLWindow.cpp
        src/Graphics/Shader.cpp
        src/Graphics/ShaderProgram.cpp
        src/Graphics/Texture.cpp
        src/Time.cpp
        src/Transform.cpp
        src/ECS/ComponentInstance.cpp
        src/ECS/ECSException.cpp
        src/Graphics/ShaderParser.cpp
        src/Graphics/PixelFormat.cpp
        src/Graphics/PropertyVisitor.cpp)

find_package(OpenGL REQUIRED)
find_package(glm 0.9.8 REQUIRED)
find_package(SDL2 REQUIRED)

set(INCLUDE_DIRS_PUBLIC include ${SDL2_INCLUDE_DIRS})
set(LINK_LIBS_PUBLIC glad stb_vorbis stb_image pugixml ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY})

if(${USE_LUA})
    find_package(Lua 5.3 REQUIRED)
    list(APPEND INCLUDE_DIRS_PUBLIC ${LUA_INCLUDE_DIR})
    list(APPEND LINK_LIBS_PUBLIC sol ${LUA_LIBRARIES})
endif(${USE_LUA})

add_subdirectory(lib)

add_library(Aeyon3D STATIC ${SOURCE_FILES})

target_include_directories(Aeyon3D PUBLIC ${INCLUDE_DIRS_PUBLIC})
target_link_libraries(Aeyon3D PUBLIC ${LINK_LIBS_PUBLIC})
