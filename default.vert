#version 330 core
// Position/Coords
layout (location = 0) in vec3 aPos;
// Normal
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture
layout (location = 3) in vec2 aTex;

// Output current pos to fragment shader
out vec3 currentPos;
// Output normal to fragment shader
out vec3 Normal;
// Output color for fragment shader
out vec3 color;
// Outputs texture coord to fragment shader
out vec2 texCoord;

// Import cam matrix from main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	// Calculates current pos
	currentPos = vec3(model * vec4(aPos, 1.0f));
	// Assigns the normal from the vertex data to "Normal"
	Normal = aNormal;
	// Assigns the colors from Vertex data to "color"
	color = aColor;
	// Assigns the texture coords from vertex data to "texCoord"
	texCoord = aTex;

	// Outputs position/coords of all vertices
	gl_Position = camMatrix * vec4(currentPos, 1.0);
}

