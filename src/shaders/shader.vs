#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float horizontalOffset;
uniform float verticalOffset;
uniform mat4 transform;

out vec2 TexCoord;
out vec3 ourColor;
out vec4 ourPosition;

void main()
{
    gl_Position =  vec4(aPos.x + horizontalOffset, aPos.y + verticalOffset, aPos.z, 1.0);
    ourColor = aColor;
    ourPosition =  vec4(aPos.x + horizontalOffset, aPos.y + verticalOffset, aPos.z, 1.0);
    TexCoord = aTexCoord;
}