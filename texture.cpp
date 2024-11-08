#include "texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
	: type(0)
	, ID(0)
{
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &ID);
	// Assign texture to a texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texType, ID);

	// Configure type of algorithim to use for scaling
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configure the way texture repeats itself (if it does)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Incased used for GL_CLAMP_TO_BORDER
	// float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assign image to OpenGL Texture
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMap
	glGenerateMipmap(texType);

	// Deletes image data as it is already stored in the texture
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, "tex0");
	shader.Activate();
	glUniform1i(texUni, 0);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}	