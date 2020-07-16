#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCord;
            
void main()
{
    v_TexCord = a_TexCord;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;

uniform sampler2D u_Texture;
            
void main()
{
    color = texture(u_Texture, v_TexCord);
}