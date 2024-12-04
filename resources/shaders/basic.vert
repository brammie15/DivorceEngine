#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 texCoordOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

    texCoordOut = texCoord;


    gl_Position = projection * view * model * vec4(position, 1.0);
}