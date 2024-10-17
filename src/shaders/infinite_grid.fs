#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 WorldPos;

uniform float gGridCellSize = 0.09;
uniform vec4 gGridColorThin = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4 gGridColorThick = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    vec2 dvx = vec2(dFdx(WorldPos.x), dFdy(WorldPos.x));
    vec2 dvy = vec2(dFdx(WorldPos.z), dFdy(WorldPos.z));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);
    dudv *= 4.0;

    float Lod0a = mod(WorldPos.z, gGridCellSize) / dFdy(WorldPos.z);
    //float Lod0a = max2(mod(WorldPos.xz, gGridCellSize) / dudv);
    //vec2 mod_div_dudv = mod(WorldPos.xz, gGridCellSize) / dudv;
    //float Lod0a = max(ve2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    vec4 Color;

    Color = gGridColorThick;
    Color.a *= mod(WorldPos.z, gGridCellSize);

    FragColor = Color;
}
   