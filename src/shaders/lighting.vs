#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;

uniform float horizontalOffset;
uniform float verticalOffset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 ourPosition;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos.x + horizontalOffset, aPos.y + verticalOffset, aPos.z, 1.0);
    ourPosition =  gl_Position;
}


// proboably have some sort of bool and conditionally apply one transform or another 