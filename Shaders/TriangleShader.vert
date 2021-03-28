#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

//uniform vec4 colorTint;
uniform mat4 projectionMatrix;

out vec4 Color;

void main()
{    
	Color =  aColor; // * uTint;

	gl_Position = projectionMatrix * vec4(aPos, 0, 1.0);

	// work in progress glow effect, set up post process effect?
	// vec4(5.0 / (40.0 * abs(2.0 * length(gl_Position)-1.0) )) * aColor * uTint;
}
