#pragma once
#ifndef __VBO_H_
#define __VBO_H_

#include <glad/glad.h>

class VBO
{
public:
	// ID reference of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // __VBO_H_