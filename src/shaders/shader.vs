#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float horizontalOffset;
uniform float verticalOffset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec4 ourPosition;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos.x + horizontalOffset, aPos.y + verticalOffset, aPos.z, 1.0);
    ourPosition =  gl_Position;
    TexCoord = aTexCoord;
}
