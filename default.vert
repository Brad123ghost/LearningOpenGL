#version 330 core
// Position/Coords
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture
layout (location = 2) in vec2 aTex;
// Normal
layout (location = 3) in vec3 aNormal;

// Output color for fragment shader
out vec3 color;

// Outputs texture coord to fragment shader
out vec2 texCoord;

out vec3 Normal;
out vec3 currentPos;

// Import cam matrix from main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	currentPos = vec3(model * vec4(aPos, 1.0f));

	gl_Position = camMatrix * vec4(currentPos, 1.0);
	color = aColor;
	texCoord = aTex;
	Normal = aNormal;
}

