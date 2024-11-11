#version 330 core
// Outputs colors in RGBA
out vec4 FragColor;

// Input color from vertex shader
in vec3 color;
// Input texture coordinates from vertex shader
in vec2 texCoord;

in vec3 Normal;
in vec3 currentPos;

// Texture unit from main function
uniform sampler2D tex0;
// Light from main function
uniform vec4 lightColor;
// Light position from main function
uniform vec3 lightPos;
// camera position from main function
uniform vec3 camPos;

void main()
{
	// Ambient light
	float ambient = 0.20f;

	// Diffuse light
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular Light
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}