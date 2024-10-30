#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 WorldPos;
in vec3 CameraPos;
in float GridSize;

uniform float gGridMinPixelsBetweenCells = 2.0;
uniform float gGridCellSize = 0.025;
uniform vec4 gGridColorThin = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4 gGridColorThick = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
    vec2 dvx = vec2(dFdx(WorldPos.x), dFdy(WorldPos.x));
    vec2 dvy = vec2(dFdx(WorldPos.z), dFdy(WorldPos.z));

    float lx = length(dvx); //vector length
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);

    float l = length(dudv);
    
    float logTen = 1  / log(10);
    float LOD = max(0.0, (logTen * log(l * gGridMinPixelsBetweenCells / gGridCellSize)) + 1.0);

    float gGridCellSizeLod0 = gGridCellSize * pow(10.0, floor(LOD));
    float gGridCellSizeLod1 = gGridCellSizeLod0 * 10.0;
    float gGridCellSizeLod2 = gGridCellSizeLod1 * 10.0;

    float tmp1 = 1.0 - abs(clamp(mod(WorldPos.x, gGridCellSizeLod0) / (4.0 * lx), 0.0, 1.0) * 2.0 - 1.0);
    float tmp2 = 1.0 - abs(clamp(mod(WorldPos.z, gGridCellSizeLod0) / (4.0 * ly), 0.0, 1.0) * 2.0 - 1.0);

    float Lod0a = max(tmp1,tmp2);

    tmp1 = 1.0 - abs(clamp(mod(WorldPos.x, gGridCellSizeLod1) / (4.0 * lx), 0.0, 1.0) * 2.0 - 1.0);
    tmp2 = 1.0 - abs(clamp(mod(WorldPos.z, gGridCellSizeLod1) / (4.0 * ly), 0.0, 1.0) * 2.0 - 1.0);

    float Lod1a = max(tmp1,tmp2);

    tmp1 = 1.0 - abs(clamp(mod(WorldPos.x, gGridCellSizeLod2) / (4.0 * lx), 0.0, 1.0) * 2.0 - 1.0);
    tmp2 = 1.0 - abs(clamp(mod(WorldPos.z, gGridCellSizeLod2) / (4.0 * ly), 0.0, 1.0) * 2.0 - 1.0);

    float Lod2a = max(tmp1,tmp2);

    float LOD_fade = fract(LOD);
    vec4 Color;

    if (Lod2a > 0.0) {
        Color = gGridColorThick;
        Color.a *= Lod2a;
    } else {
        if (Lod1a > 0.0) {
            Color = mix(gGridColorThick, gGridColorThin, LOD_fade);
            Color.a *= Lod1a;
        } else {
            Color = gGridColorThin;
            Color.a *= (Lod0a * (1.0 - LOD_fade));
        }
    }
    //float tmp = clamp(length(WorldPos.xz - CameraPos.xz) / gGridSize, 0.0, 1.0);


    float OpacityFalloff = (1.0 - clamp(length(WorldPos.xz - CameraPos.xz) / GridSize, 0.0, 1.0));
    Color.a *= OpacityFalloff;

    FragColor = Color;
}
   