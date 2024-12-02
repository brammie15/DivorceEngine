#version 330 core
out vec4 FragColor;

uniform sampler2D sampler;
in vec2 texCoordOut;

void main()
{
//    FragColor = texture(sampler, texCoordOut);
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}