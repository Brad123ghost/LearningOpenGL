#pragma once
#ifndef __EBO_H_
#define __EBO_H_

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	// ID reference of elements buffer object
	GLuint ID;
	// constructor that generates an elements buffer object and links to indices
	EBO(std::vector<GLuint>& indices);
	// binds ebo
	void Bind();
	// unbinds ebo
	void Unbind();
	// deletes ebo
	void Delete();
};

#endif // __EBO_H_