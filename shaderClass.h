#pragma once
#ifndef __SHADERCLASS_H_
#define __SHADERCLASS_H_

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

	void Activate();
	void Delete();

private:
	void compileErrors(unsigned int shader, const char* type);
};

#endif // __SHADERCLASS_H_