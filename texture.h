#pragma once
#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLuint type;
	GLuint unit;

	Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // __TEXTURE_H_