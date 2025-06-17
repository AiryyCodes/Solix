#version 410 core

in vec3 v_Normal;
in vec2 v_TexCoord;
flat in uint v_Flags;

out vec4 v_FragColor;

uniform sampler2D u_Texture;
uniform bool u_HasTexture;

void main()
{
    bool hasUV = (v_Flags & 1u) != 0u;

    if (u_HasTexture && hasUV)
    {
        v_FragColor = texture(u_Texture, v_TexCoord);
    }
    else
    {
        v_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}
