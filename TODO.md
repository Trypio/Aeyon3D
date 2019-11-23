# Shader / Material
- Add spotlights
- Add multiple light support
- Fix calculation of directional light shadow range
- Create a fallback texture that is loaded if a material's texture failed to load
- Implement specific shadow mapping for point and spot lights and passing of multiple WorldToLight matrices.
- Add shadow quality options (shadow map resolution, bias, smooth/hard shadows etc.)
- Implement cascaded shadow mapping

# Engine
- Add persisting settings functionality for apps

# Model Importer
- Implement importing of extern materials
- Decide on how to handle OBJ files with multiple objects in terms of submeshes

# Entity Component System
- Implement querying of entities with a specific component
- Add hierarchy / scene graph functionality to entities
- Implement a dynamic bitset class

# Rendering
- Implement post-processing
- Improve gamma correction implementation
- Implement Color32 class to reduce the size of stored color information (?)
- Implement HDR rendering and bloom

# GUI
- Implement displaying and changing ECS components
- Implement Lua support for UI scripting

# Audio
- Implement audio functionality via OpenAL
