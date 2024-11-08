#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"

// Triangle
//// Vertices coordinates
//GLfloat vertices[] = {
//		-0.5f, -0.5f * float(sqrt(3)) /	3,     0.0f, 0.8f, 0.3f,  0.02f, // Lower left corner
//		 0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f, 0.8f, 0.3f,  0.02f,// Lower right corner
//		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f,  0.32f,// Upper corner
//		-0.25f, 0.5f * float(sqrt(3)) / 6,	   0.0f, 0.9f, 0.45f, 0.17f,// Inner left
//		 0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f, 0.9f, 0.45f, 0.17f,// Inner right
//		 0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f, 0.8f, 0.3f,  0.02f,// Inner down
//};
//
//// Indices for vertices order
//GLuint indices[] = {
//	0, 3, 5, // Lower left triangle
//	3, 2, 4, // Lower right triangle
//	5, 4, 1 // Upper triangle
//};

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

// Square
//GLfloat vertices[] =
//{
//	// CORDS				// COLORS 		    // Texture cords
//	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower Left corner
//	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper Left corner
//	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper Right corner
//	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower Right corner
//};
//
//GLuint indices[] =
//{
//	0, 1, 2, // Upper Triangle
//	0, 2, 3  // Lower Triangle
//};

// Pyrimid
GLfloat vertices[] =
{
	// CORDS				// COLORS 				// Texture cords
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Lower Left corner
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f, // Lower Right corner
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Upper Right corner
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f, // Upper Left corner
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,	2.5f, 5.0f  // Top corner
};

GLuint indices[] =
{
	0, 1, 2, // Lower Triangle
	0, 2, 3, // Upper Triangle
	0, 1, 4, // Left Triangle
	1, 2, 4, // Front Triangle
	2, 3, 4, // Right Triangle
	3, 0, 4  // Back Triangle
};

int main()
{
	// Initialize GLFW
	glfwInit();

	// Telling GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Telling GLFW we are using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "First OpenGL Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, WIDTH, HEIGHT);

	// Create the vertex shader
	Shader shaderProgram("default.vert", "default.frag");

	// Generate Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and link it to vertices
	VBO VBO1(vertices, sizeof(vertices));

	// Generate Element Buffer Object and link it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes to VAO (cords, colors & textures)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture stable("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	stable.texUnit(shaderProgram, "tex0", 0);

	// Variables to help with rotation
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables Depth
	glEnable(GL_DEPTH_TEST);

	// Mian while loop
	while (!glfwWindowShouldClose(window))
	{
		// Color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean back and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// What shader program to use
		shaderProgram.Activate();

		// Simple timer
		double currTime = glfwGetTime();
		if(currTime - prevTime >= 1/60.0f)
		{
			rotation += 0.5f;
			prevTime = currTime;
		}

		// Initialize matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assign different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(WIDTH/HEIGHT), 0.1f, 100.0f);

		// Inputting the matrices into the vertex shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; Must always be done after activating the shader
		glUniform1f(uniID, 0.5f);
		// Bind texture so that is appears in the window
		stable.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, data type of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	stable.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}