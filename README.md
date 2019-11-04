# Aeyon3D

## Description

Aeyon3D is a 3D game engine written in C++17. I've been occasionally working on it since 2018 and it currently comprises several 
subsystems that are managed by a custom Entity Component System (ECS)
architecture.

## Features (Implemented)
* **Rendering System** based on OpenGL 3.3
    - Blinn-Phong Shading
    - Normal Mapping
    - Shadow Mapping
    - Skyboxes
    - Material System
    - Preprocessed Multi-Pass Custom Shaders
    - Lua Scripting (_currently disabled due to long compile times_)
* **Entity Component System**
* **Cross-Platform Input**

## Features (Planned)
* Model Importing
* Displacement Mapping
* Reflections (Screen Space, Planar, Environment Mapping)
* HDR rendering + Bloom
* Anti-Aliasing
* PBR
* Ambient Occlusion
* **Physics System**
* **Audio System**

## Screenshots
![alt text](https://github.com/Trypio/Aeyon3D/blob/master/screenshots/Screen1.jpg "Two boxes with shadows")
![alt text](https://github.com/Trypio/Aeyon3D/blob/master/screenshots/Screen2.jpg "A box with normal mapping")


## Libraries
- SDL2 (https://www.libsdl.org/)
- OpenGL (https://www.opengl.org/)
- Glad (https://glad.dav1d.de/)
- GLM (https://glm.g-truc.net/0.9.8/index.html)
- pugixml (https://pugixml.org/)
- stb_image, stb_vorbis (https://github.com/nothings/stb)
- Lua (https://www.lua.org/)
- sol3 (https://github.com/ThePhD/sol2)

## Resources
- Textures:
    - https://cc0textures.com/
    - https://learnopengl.com/