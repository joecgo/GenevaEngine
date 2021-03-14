#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in float aColor; // color has attribute position 1

out vec4 VertexColor; // output a color to the fragment shader

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   
	// select which color to use at this vert
    if (aColor == 1.0f) { VertexColor = color1; }
	else if (aColor == 2.0f) { VertexColor = color2; }
	else { VertexColor = color3; }
}