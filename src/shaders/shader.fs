#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

in vec4 ourPosition;

// assigning texture units to the sampler
uniform sampler2D texture1;
uniform sampler2D texture2; 
uniform vec2 res;

uniform float face_opacity;

void main()
{
    ///FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), face_opacity);
    vec2 st = gl_FragCoord.xy/res;
    float pct = 0.0;
    pct = distance(st, vec2(0.5));


    vec3 color = vec3(pct);

    FragColor = vec4(color, 1.0);
}
   