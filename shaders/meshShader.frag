#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D diffuse1;

void main()
{
    FragColor = texture(diffuse1, TexCoord);
}