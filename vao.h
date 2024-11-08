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
	
	void LinkVBO(VBO& VBO, GLuint layout);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // __VAO_H_