#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

in vec4 ourPosition;

// assigning texture units to the sampler
uniform sampler2D texture1;
uniform sampler2D texture2; 

uniform float face_opacity;

void main()
{
    ///FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), face_opacity);
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
   