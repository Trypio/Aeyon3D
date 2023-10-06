//$$ SHADER "Standard"

//$$ PROPERTIES_BEGIN

sampler2D diffuse_texture;
sampler2D specular_texture;
sampler2D normal_texture;
sampler2D shadow_map;

vec4 diffuse_color;
vec4 specular_color;
float shininess;

//$$ PROPERTIES_END


//$$ PASS_BEGIN

//$$ VERTEX_BEGIN

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec3 in_tangent;
layout (location = 4) in vec3 in_bitangent;

out VertexData
{
    vec4 world_pos;
    vec2 uv;
    mat3 TBN;
    vec4 light_space_pos;
} vtx;

void main()
{
    vtx.world_pos = _M * in_position; ;
    vtx.uv = in_uv * _TextureScale + _TextureOffset;
    vec3 T = normalize(mat3(_MV_Inv_T) * in_tangent);
    vec3 B = normalize(mat3(_MV_Inv_T) * in_bitangent);
    vec3 N = normalize(mat3(_MV_Inv_T) * in_normal);
    vtx.TBN = mat3(T, B, N);
    vtx.light_space_pos = _WorldToLight * vtx.world_pos;

    gl_Position = _MVP * in_position;
}
//$$ VERTEX_END


//$$ FRAGMENT_BEGIN

in VertexData
{
    vec4 world_pos;
    vec2 uv;
    mat3 TBN;
    vec4 light_space_pos;
} vtx;

out vec4 frag_color;

float calcDirectionalShadow(vec4 light_dir, vec4 normal)
{
    vec3 shadow_proj_coords = (vtx.light_space_pos.xyz / vtx.light_space_pos.w) * 0.5 + 0.5;

    if (shadow_proj_coords.z > 1.0)
    return 0.0;

    float closest_depth = texture(shadow_map, shadow_proj_coords.xy).r; // overridden when PCF is enabled
    float current_depth = shadow_proj_coords.z;

    float bias = 0.002;
    float shadow = 0.0;

    // PCF
    vec2 texel_size = 1.0 / textureSize(shadow_map, 0);

    for (int x = -1; x <= 1; x++)
      for (int y = -1; y <= 1; y++)
    {
        closest_depth = texture(shadow_map, shadow_proj_coords.xy + vec2(x, y) * texel_size).r;
        shadow += current_depth - bias > closest_depth ? 1.0 : 0.0;
    }

    shadow /= 9.0; // take 9 samples

    return shadow;
}

vec4 calcDirectionalLight(int index, vec4 light_dir, vec4 eye_dir, vec4 normal)
{
    vec4 half_vec = normalize(eye_dir + light_dir);

    vec4 diffuse = diffuse_color * _LightColor[index] * max(0.0, dot(normal, light_dir)) * texture(diffuse_texture, vtx.uv);
    vec4 specular = specular_color * pow(max(0.0, dot(normal, half_vec)), shininess) * texture(specular_texture, vtx.uv).r;

    float shadow = calcDirectionalShadow(light_dir, normal);

    return (1.0 - shadow) * (diffuse + specular);
}

vec4 calcPointLight(int index, vec4 light_pos, vec4 eye_dir, vec4 normal)
{
    vec4 to_light = light_pos - _V * vtx.world_pos;
    vec4 light_dir = normalize(to_light);
    float distance = length(to_light);
    vec4 half_vec = normalize(eye_dir + light_dir);

    float attenuation = 1.0 / (_AttenuationFactors[index].x + _AttenuationFactors[index].y * distance + _AttenuationFactors[index].z * (distance * distance));

    float energy_conservation = (8.0 + shininess) / (8.0 * 3.14159265);

    vec4 diffuse = diffuse_color * _LightColor[index] * max(0.0, dot(normal, light_dir)) * attenuation * texture(diffuse_texture, vtx.uv);
    vec4 specular = specular_color * energy_conservation * pow(max(0.0, dot(normal, half_vec)), shininess) * attenuation * texture(specular_texture, vtx.uv).r;

    return diffuse + specular;
}

void main()
{
    vec4 eye_dir = -normalize(_V * vtx.world_pos - vec4(0.0, 0.0, 0.0, 1.0));

    vec4 light_sum = vec4(_AmbientColor.rgb * texture(diffuse_texture, vtx.uv).rgb, 1.0);

    vec3 n = texture(normal_texture, vtx.uv).rgb;
    n = normalize(n * 2.0 - vec3(1.0));
    n = normalize(vtx.TBN * n);

    vec4 normal = vec4(n, 0.0);

    for (int i = 0; i < 8; i++)
    {
        vec4 light_pos = _LightPosition[i], light_color = _LightColor[i];

        if (light_color.x == 0.0 && light_color.y == 0.0 && light_color.z == 0.0)
        {
            continue;
        }

        if (light_pos.w == 0.0)
        {
            light_sum.rgb += calcDirectionalLight(i, -light_pos, eye_dir, normal).rgb;
        }
        else
        {
            light_sum.rgb += calcPointLight(i, light_pos, eye_dir, normal).rgb;
        }
    }

    frag_color = light_sum;
}

//$$ FRAGMENT_END

//$$ PASS_END


//$$ PASS_BEGIN

//$$ VERTEX_BEGIN

layout (location = 0) in vec4 in_position;

void main()
{
    gl_Position = _WorldToLight * _M * in_position;
}

//$$ VERTEX_END

//$$ FRAGMENT_BEGIN

void main()
{
}

//$$ FRAGMENT_END

//$$ PASS_END
