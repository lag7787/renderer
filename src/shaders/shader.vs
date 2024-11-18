#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform float horizontalOffset;
uniform float verticalOffset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 FragPos;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos.x + horizontalOffset, aPos.y + verticalOffset, aPos.z, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;
    // inverting a matrix is a costly operation to do on the GPU
}


// proboably have some sort of bool and conditionally apply one transform or another 