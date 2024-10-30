#version 330 core

out vec3 WorldPos;
out vec3 CameraPos;
out float GridSize;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 camera_position;
uniform float gGridSize = 100.0;

const vec3 Pos[4] = vec3[4](
    vec3(-1.0f, 0.0f, -1.0f), //bl
    vec3(1.0f, 0.0f, -1.0f), // br
    vec3(1.0f, 0.0f, 1.0f), //tr
    vec3(-1.0f, 0.0f, 1.0f) //tl
);

const int Indices[6] = int[6](0,2,1,2,0,3);

void main() {
    int Index = Indices[gl_VertexID];

    vec3 vPos3 = Pos[Index] * gGridSize;
    vPos3.x += camera_position.x;
    vPos3.z += camera_position.z;

    vec4 vPos = vec4(vPos3, 1.0);
    gl_Position = projection * view * vPos;

    WorldPos = vPos3;
    CameraPos = camera_position;
    GridSize = gGridSize;
}