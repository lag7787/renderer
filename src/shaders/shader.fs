#version 330 core
//out vec4 FragColor;
layout(location = 0) out vec4 FragColor;
in vec2 TexCoord;

in vec4 ourPosition;

// assigning texture units to the sampler
uniform sampler2D texture1;
uniform sampler2D texture2; 

uniform float face_opacity;

void main()
{
    FragColor = vec4(0);
}
   