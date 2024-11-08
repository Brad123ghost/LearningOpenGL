#pragma once
#ifndef __VAO_H_
#define __VAO_H_

#include <glad/glad.h>
#include "vbo.h"

class VAO
{
public:
	// ID reference of the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();
	
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // __VAO_H_