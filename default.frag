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

vec4 pointLight()
{
	vec3 lightVec = lightPos - currentPos;

	// Intensity of light with respect to dist
	float dist = length(lightVec);
	float a = 3.0f;
	float b = 0.7f;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// Ambient light
	float ambient = 0.20f;

	// Diffuse light
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular Light
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return texture(diffuse0, texCoord) * (diffuse * inten + ambient) + (texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 directLight()
{
	// Ambient light
	float ambient = 0.20f;

	// Diffuse light
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular Light
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return texture(diffuse0, texCoord) * (diffuse + ambient) + (texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

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
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return texture(diffuse0, texCoord) * (diffuse * inten + ambient) + (texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main()
{
	FragColor = directLight();
}