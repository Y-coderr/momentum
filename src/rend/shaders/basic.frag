#version 330 core

uniform vec4 u_Color;
out vec4 OUTPUT;

void main()
{
    OUTPUT = u_Color;
}