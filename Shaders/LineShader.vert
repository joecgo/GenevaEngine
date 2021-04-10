#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 projectionMatrix;
out vec4 Color;

void main()
{    
	Color =  aColor;
	gl_Position = projectionMatrix * vec4(aPos, 0, 1.0);
}