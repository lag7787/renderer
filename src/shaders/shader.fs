#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 ourPosition;

uniform sampler2D texture1;
uniform sampler2D texture2; 

uniform float face_opacity; // should also be u_face_opacity
uniform float u_time;
uniform vec2 u_res;

float plot(vec2 st) {
    return smoothstep(0.02, 0.0, abs(st.y - st.x));
}

void main()
{
    vec2 st = gl_FragCoord.xy/u_res;
    FragColor = vec4(st.x, st.y, 0.0, 1.0);

}
   