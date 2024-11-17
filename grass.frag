#version 330 core
// Outputs colors in RGBA
out vec4 FragColor;

// Input position from vertex shader
in vec3 currentPos;
// Input normal from vertex shader
in vec3 Normal;
// Input color from vertex shader
in vec3 color;
// Input texture coordinates from vertex shader
in vec2 texCoord;

// Texture unit from main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// Light from main function
uniform vec4 lightColor;
// Light position from main function
uniform vec3 lightPos;
// camera position from main function
uniform vec3 camPos;

vec4 directLight()
{
	// Ambient light
	float ambient = 0.20f;

	// Diffuse light
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(abs(dot(normal, lightDirection)), 0.0f); // absolute helps with grass shading

	// Specular Light
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	if(texture(diffuse0, texCoord).a < 0.1)
	{
		discard;
	}

	return texture(diffuse0, texCoord) * (diffuse + ambient) + (texture(specular0, texCoord).r * specular) * lightColor;
}

void main()
{
	FragColor = directLight();
}