local cube_transform_1
local cube_transform_2
local light_transform

function start()
    print("Lua script is running...")

    local stone_diffuse = aeyon.resources.load_texture_2D('textures/StoneBricks_COLOR.jpg', aeyon.PixelFormat.SRGB8, true)
    local stone_gloss = aeyon.resources.load_texture_2D('textures/StoneBricks_GLOSS.jpg', aeyon.PixelFormat.R8, true)
    local stone_normal = aeyon.resources.load_texture_2D('textures/StoneBricks_NORMAL.jpg', aeyon.PixelFormat.RGB8, true)
    local ground_diffuse = aeyon.resources.load_texture_2D('textures/GroundForest003_COLOR.jpg', aeyon.PixelFormat.SRGB8, true)
    local ground_gloss = aeyon.resources.load_texture_2D('textures/GroundForest003_GLOSS.jpg', aeyon.PixelFormat.R8, true)
    local ground_normal = aeyon.resources.load_texture_2D('textures/GroundForest003_NORMAL.jpg', aeyon.PixelFormat.RGB8, true)

    local skybox_cubemap = aeyon.resources.load_texture_cube({
        "textures/right.jpg",
        "textures/left.jpg",
        "textures/top.jpg",
        "textures/bottom.jpg",
        "textures/front.jpg",
        "textures/back.jpg"
    }, aeyon.PixelFormat.SRGB8, true)

    local standard_shader = aeyon.resources.load_shader('shaders/Standard.shader')
    local skybox_shader = aeyon.resources.load_shader('shaders/Skybox.shader')

    local cube_material = aeyon.Material:new(standard_shader);
    cube_material:set_texture('diffuse_texture', stone_diffuse)
    cube_material:set_texture('specular_texture', stone_gloss)
    cube_material:set_texture('normal_texture', stone_normal)

    local ground_material = aeyon.Material:new(standard_shader)
    ground_material:set_texture('diffuse_texture', ground_diffuse)
    ground_material:set_texture('specular_texture', ground_gloss)
    ground_material:set_texture('normal_texture', ground_normal)

    local skybox_material = aeyon.Material:new(skybox_shader)
    skybox_material:set_texture('skybox', skybox_cubemap)

    local skybox = aeyon.primitive.create_cube()
    skybox:remove_box_collider()
    local skybox_mesh = skybox:get_mesh_renderer().shared_mesh
    local positions = skybox_mesh.positions

    for key, val in ipairs(positions) do
        positions[key] = val * 2
    end

    skybox_mesh.positions = positions
    skybox_mesh.shared_material = skybox_material
    skybox_mesh:apply()

    aeyon.graphics.skybox = skybox

    local cube1 = aeyon.primitive.create_cube()
    cube_transform_1 = cube1:get_transform()
    cube_transform_1.position = aeyon.math.Vec3:new(0, 0.5, 0.0)
    local cube_mesh_1 = cube1:get_mesh_renderer().shared_mesh
    cube_mesh_1.shared_material = cube_material

    local cube2 = aeyon.primitive.create_cube()
    cube_transform_2 = cube2:get_transform()
    cube_transform_2.position = aeyon.math.Vec3:new(2, 0.5, 0.0)
    local cube_mesh_2 = cube2:get_mesh_renderer().shared_mesh
    cube_mesh_2.shared_material = cube_material

    local ground = aeyon.primitive.create_plane()
    local ground_transform = ground:get_transform()
    ground_transform.scale = aeyon.math.Vec3:new(50, 0.1, 50)
    local ground_mesh = ground:get_mesh_renderer().shared_mesh
    ground_material.texture_scale = aeyon.math.Vec2:new(50, 50)
    ground_mesh.shared_material = ground_material

    local light = aeyon.create_entity()
    light_transform = light:add_transform()
    local light_light = light:add_light()
    light_light.intensity = 1.5
    light_transform:rotate(aeyon.math.Vec3:new(45, 35, 0))

    local camera = aeyon.create_entity()
    local camera_transform = camera:add_transform()
    camera:add_camera()
    local controller = camera:add_first_person_controller()
    controller.move_speed = 0.003
    controller.mouse_sensitivity = 0.1

    camera_transform:translate(aeyon.math.Vec3:new(0, 0.5, -2))
end

function update()
    if aeyon.input.key_down(aeyon.KeyCode.ESCAPE) then
        aeyon.window.close()
    end

    if aeyon.input.key_down(aeyon.KeyCode.KEYPAD_8) then
        cube_transform_1:translate(aeyon.math.Vec3:new(0, 0, 0.001))
        end
end