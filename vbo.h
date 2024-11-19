#pragma once
#ifndef __VBO_H_
#define __VBO_H_

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	// ID reference of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);
	VBO(std::vector<glm::mat4>& mat4s);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // __VBO_H_