#pragma once
#ifndef __MESH_H_
#define __MESH_H_

#include <string>

#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "texture.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
};

#endif // __MESH_H_