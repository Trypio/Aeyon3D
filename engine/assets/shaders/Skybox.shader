//$$ SHADER "Skybox"

//$$ PROPERTIES_BEGIN

samplerCube skybox;

//$$ PROPERTIES_END

//$$ PASS_BEGIN

//$$ VERTEX_BEGIN

layout (location = 0) in vec3 in_position;

out vec3 tex_coord;

void main()
{
    vec4 pos = _P * mat4(mat3(_V)) * vec4(in_position, 1.0);
    gl_Position = pos.xyww;
    tex_coord = in_position;
}

//$$ VERTEX_END


//$$ FRAGMENT_BEGIN

in vec3 tex_coord;

out vec4 frag_color;

void main()
{
    frag_color = texture(skybox, tex_coord);
}

//$$ FRAGMENT_END

//$$ PASS_END
