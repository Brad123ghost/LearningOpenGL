#version 330 core
// Position/Coords
layout (location = 0) in vec3 aPos;
// Normal
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture
layout (location = 3) in vec2 aTex;
layout (location = 4) in mat4 instanceMatrix;

out DATA
{
	vec3 Normal;
	vec3 color;
	vec2 texCoord;
	mat4 projection;
} data_out;

out vec3 currentPos;

// Import cam matrix from main function
uniform mat4 camMatrix;


void main()
{
	currentPos = vec3(instanceMatrix * vec4(aPos, 1.0f));
	data_out.Normal = aNormal;
	data_out.color = aColor;
	data_out.texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	data_out.projection = camMatrix;
	gl_Position = vec4(currentPos, 1.0f);
}
