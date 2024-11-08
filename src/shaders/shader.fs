#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 ourPosition;

uniform sampler2D texture1;
uniform sampler2D texture2; 

uniform float face_opacity; // should also be u_face_opacity
uniform float u_time;
uniform vec2 u_res;

#define PI 3.14159265359

float plot(vec2 st) {
    return smoothstep(0.02, 0.0, abs(st.y - st.x));
}

float plot(vec2 st, float pct) {
    return smoothstep(pct-0.02, pct, st.y) - smoothstep(pct, pct+0.02, st.y);
}

void main()
{
    vec2 st = gl_FragCoord.xy/u_res;

    float y = smoothstep(0.2,0.5,st.x) - smoothstep(0.5,0.8,st.x);

    vec3 color = vec3(y);

    float pct = plot(st, y);
    color = (1.0 - pct) * color + pct*vec3(0.0,1.0,0.0);

    FragColor = vec4(color, 1.0);
}
   