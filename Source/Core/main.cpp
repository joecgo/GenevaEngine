/****************************************************************************
 * Copyright (C) 2021 by Joe Goldman	                                    *
 *                                                                          *
 * This file is part of GenevaEngine.                                       *
 *                                                                          *
 *   GenevaEngine is a custom C++ engine built for the purposes of 			*
 *	 learning and fun. You can reach me at joecgo@gmail.com. 				*
 *                                                                          *
 ****************************************************************************/

 /**
  * \file main.cpp
  * \author Joe Goldman
  * \brief main file currently used for testing and tutorials, contains main()
  */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <iostream> // cout, endl

#include <Graphics/Shader.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Color.hpp>

namespace GenevaEngine
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);

	// settings
	const unsigned int SCR_WIDTH = 1200;
	const unsigned int SCR_HEIGHT = 900;

	// mouse input
	bool firstMouse = true;
	double lastX = SCR_WIDTH / 2.0;
	double lastY = SCR_HEIGHT / 2.0;

	//camera
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	typedef std::vector<Color> Palette;
	Palette palette{
	  Color(0x7eed94),
	  Color(0x1a2c79),
	  Color(0xe6a26e),
	  Color(0x64a6ea),
	  Color(0xa163a2),
	};

	glm::vec3 generateRandRotAxis()
	{
		return glm::vec3(
			(rand() % 200) - 100 / 100.0f,
			(rand() % 200) - 100 / 100.0f,
			(rand() % 200) - 100 / 100.0f
		);
	}

	void setClearColor(Color color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			setClearColor(Color(000000));
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			setClearColor(palette[0]);
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
			setClearColor(palette[1]);
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			setClearColor(palette[2]);
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
			setClearColor(palette[3]);
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
			setClearColor(palette[4]);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Movement::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Movement::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Movement::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Movement::RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Movement::DOWN, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			camera.ProcessKeyboard(Camera::Movement::UP, deltaTime);
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		camera.ProcessMouseMovement((float)xoffset, (float)yoffset);
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll((float)yoffset);
	}
}

using namespace GenevaEngine;
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GenevaEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile shaders
	// -------------------------
	Shader textureShader("Shaders/Shader.vert", "Shaders/Shader.frag");
	Shader greyShader("Shaders/Shader.vert", "Shaders/GreyShader.frag");

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// load model
// -----------
	Model testModel("Assets/Art/Test/Backpack/backpack.obj");
	Model kevinModel("Assets/Art/Test/Kevin/Kevin.obj");

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// practice with coordinate systems and camera view
		textureShader.use();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Fov),
			(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		int viewLoc = glGetUniformLocation(textureShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLoc = glGetUniformLocation(textureShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// render the test model
		glm::mat4 model1 = glm::mat4(1.0f);
		model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f));
		model1 = glm::scale(model1, glm::vec3(1.0f, 1.0f, 1.0f));
		int modelLoc1 = glGetUniformLocation(textureShader.ID, "model");
		glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model1));
		testModel.Draw(textureShader);

		// practice with coordinate systems and camera view
		greyShader.use();
		int viewLoc2 = glGetUniformLocation(greyShader.ID, "view");
		glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLoc2 = glGetUniformLocation(greyShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(projection));

		// render kevin
		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::translate(model2, glm::vec3(5.0f, -2.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(5.0f, 5.0f, 5.0f));
		int modelLoc2 = glGetUniformLocation(greyShader.ID, "model");
		glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
		kevinModel.Draw(greyShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}