#version 410 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in uint a_Flags;

out vec3 v_Normal;
out vec2 v_TexCoord;
flat out uint v_Flags;

uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0f);

    v_Normal = a_Normal;
    v_TexCoord = a_TexCoord;
    v_Flags = a_Flags;
}
