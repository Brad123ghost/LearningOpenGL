#version 330 core
// Position/Coords
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture
layout (location = 2) in vec2 aTex;

// Output color for fragment shader
out vec3 color;

// Outputs texture coord to fragment shader
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0);
	color = aColor;
	texCoord = aTex;
}

