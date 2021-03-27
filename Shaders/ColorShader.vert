#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform vec4 uTint;
uniform mat4 uObject;
uniform mat4 uCameraView;

out vec4 FragColor;

void main()
{    
	gl_Position = uCameraView * uObject * vec4(aPos, 1.0);
	FragColor = aColor * uTint;

	// work in progress glow effect, set up post process effect?
	// vec4(5.0 / (40.0 * abs(2.0 * length(gl_Position)-1.0) )) * aColor * uTint;
}