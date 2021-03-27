#version 330 core
layout (location = 0) in vec3 aPos;

in vec4 Color;

out vec4 FragColor;

void main()
{    
	FragColor = Color;
}