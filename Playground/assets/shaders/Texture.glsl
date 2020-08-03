#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCord;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCord;
            
void main()
{
    v_Color = a_Color;
    v_TexCord = a_TexCord;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCord;

uniform vec4 u_Color;
uniform float u_TilingFactor;
uniform sampler2D u_Texture;
            
void main()
{
    // color = texture(u_Texture, v_TexCord * u_TilingFactor) * u_Color;
    color = v_Color;
}