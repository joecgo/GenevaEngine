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
  * \file Graphics.cpp
  * \author Joe Goldman
  * \brief Graphics system class definition
  *
  **/

#include <Graphics\Graphics.hpp>

namespace GenevaEngine
{
	// define static variables
	std::vector<Color> Graphics::palette = {
		Color(0x2a363b), Color(0x355c7d), Color(0x6c5b7b),
		Color(0xc06c84), Color(0xf67280), Color(0xf8b195) };
	Camera Graphics::camera(glm::vec3(0.0f, 0.0f, 3.0f));;
	GLFWwindow* Graphics::window;

	void Graphics::Start()
	{
		// glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw: window creation
		window = glfwCreateWindow(Graphics::SCR_WIDTH, Graphics::SCR_HEIGHT,
			"GenevaEngine", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return; // TODO: inform GameSession of fatal error
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, Input::mouse_callback);
		glfwSetScrollCallback(window, Input::scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return; // TODO: inform GameSession of fatal error
		}

		// build and compile shaders
		textureShader = Shader("Shaders/Shader.vert", "Shaders/Shader.frag");
		greyShader = Shader("Shaders/Shader.vert", "Shaders/GreyShader.frag");

		// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
		stbi_set_flip_vertically_on_load(true);

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		// load models
		testModel = Model("Assets/Art/Test/Backpack/backpack.obj");
		kevinModel = Model("Assets/Art/Test/Kevin/Kevin.obj");

		// set starting clear color
		Graphics::SetClearColor(Graphics::palette[0]);
	}

	void Graphics::End()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	void Graphics::Update()
	{
		// clear graphics before the work starts
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
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*!
	 *  Sets window the clear color.
	 *
	 *      \param [in] color Color to set.
	 */
	void Graphics::SetClearColor(Color color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
	}

	/*!
	 *  Callback for the framebuffer
	 *
	 *      \param [in,out] window
	 *      \param [in]     width
	 *      \param [in]     height
	 */
	void Graphics::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}