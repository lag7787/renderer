#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourColor;

in vec4 ourPosition;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float face_opacity;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), face_opacity);
}
   