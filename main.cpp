#include "model.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

const unsigned int numWindows = 100;
glm::vec3 positionsWin[numWindows];
float rotationsWin[numWindows];

unsigned int orderDraw[numWindows];
float distanceCamera[numWindows];

int compare(const void* a, const void* b)
{
	double diff = distanceCamera[*(int*)b] - distanceCamera[*(int*)a];
	return (0 < diff) - (diff < 0);
}

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

	// Generate shader object
	Shader shaderProgram("default.vert", "default.frag");
	Shader grassProgram("default.vert", "grass.frag");
	Shader winProgram("default.vert", "windows.frag");

	// Outline shader object
	//Shader outliningProgram("outlining.vert", "outlining.frag");

	// Lighting related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	grassProgram.Activate();
	glUniform4f(glGetUniformLocation(grassProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(grassProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	winProgram.Activate();
	glUniform4f(glGetUniformLocation(winProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(winProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Variables to help with rotation
	float rotation = 0.0f;
	double prevDTime = glfwGetTime();

	// Variables for time
	double prevTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	// Enables Depth
	glEnable(GL_DEPTH_TEST);
	
	// Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Depth buffer
	//glDepthFunc(GL_LESS);

	// Stencil outline
	/*glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/

	// Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	Model grassModel("models/grass/scene.gltf");
	Model groundModel("models/ground/scene.gltf");
	Model windowsModel("models/windows/scene.gltf");

	// Randomize windows positions
	for (unsigned int i = 0; i < numWindows; i++)
	{
		positionsWin[i] = glm::vec3
		(
			-15.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (15.0f - (-15.0f)))),
			1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4.0f - 1.0f))),
			-15.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (15.0f - (-15.0f))))
		);
		rotationsWin[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0f));
		orderDraw[i] = i;
	}

	// Mian while loop
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		timeDiff = currentTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000.0);
			std::string newTitle = "First OpenGL Window: " + FPS + " | ms: " + ms;
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = currentTime;
			counter = 0;
		}

		// Delta Time
		double deltaTime = (glfwGetTime() - prevDTime);
		if(currentTime - prevDTime >= 1.0 / 60.0)
		{
			prevDTime = currentTime;
		}

		// Color of background
		// glClearColor(0.85f, 0.85f, 0.9f, 1.0f);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean back and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Handle camera input
		camera.Inputs(window, deltaTime);
		// Update export cam matrix to Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Draw model
		/*glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);*/
		groundModel.Draw(shaderProgram, camera);
		glDisable(GL_CULL_FACE);
		grassModel.Draw(grassProgram, camera);
		glEnable(GL_BLEND);
		// Calculate distance from camera to windows
		for (unsigned int i = 0; i < numWindows; i++)
		{
			distanceCamera[i] = glm::length(camera.Position - positionsWin[i]);
		}
		qsort(orderDraw, numWindows, sizeof(unsigned int), compare);
		for (unsigned int i = 0; i < numWindows; i++)
		{
			windowsModel.Draw(winProgram, camera, positionsWin[orderDraw[i]], glm::quat(1.0f, 0.0f, rotationsWin[orderDraw[i]], 0.0f));
		}
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);

		/*glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		outliningProgram.Activate();
		glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
		model.Draw(outliningProgram, camera);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glEnable(GL_DEPTH_TEST);*/

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	grassProgram.Delete();
	winProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}