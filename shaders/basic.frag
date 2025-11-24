#version 410 core

out vec4 fragmentColor;

uniform vec4 uObjectColor;

void main()
{
    fragmentColor = uObjectColor;
}