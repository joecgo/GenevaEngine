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

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	// define static member variables for mouse callback function
	double Graphics::mouse_x = 0.0;
	double Graphics::mouse_y = 0.0;
	double Graphics::mouse_scroll = 0.0;

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

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return; // TODO: inform GameSession of fatal error
		}

		// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
		stbi_set_flip_vertically_on_load(true);

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		// create, save, and assign shaders. TODO: do this with a config file
		SaveShader("ColorShader", Shader("Shaders/ColorShader.vert", "Shaders/ColorShader.frag"));
		default_shader = GetShader("ColorShader");
		default_shader->use();

		// set clear color
		Graphics::SetClearColor(Graphics::palette[0]);
	}

	void Graphics::End()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	void Graphics::Update(double dt)
	{
		// clear graphics before the work starts
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// get view matrics from camera
		glm::mat4 viewTransform = camera.GetViewMatrix(SCR_WIDTH, SCR_HEIGHT);

		// save view matrix to shader uniform value
		int camera_view_loc = glGetUniformLocation(default_shader->ID, "uCameraView");
		glUniformMatrix4fv(camera_view_loc, 1, GL_FALSE, glm::value_ptr(viewTransform));

		// render entities
		for (Entity* entity : gamesession->entities)
			RenderEntity(entity, viewTransform);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Graphics::RenderEntity(Entity* entity, glm::mat4 viewTransform) const
	{
		// calc entity's world transform
		glm::mat4 worldTransform = glm::mat4(1.0f);
		worldTransform = glm::translate(worldTransform, entity->startPosition);
		worldTransform = glm::scale(worldTransform, entity->scale);

		// pass world tranform to shader as a uniform value "uObject"
		int object_loc = glGetUniformLocation(default_shader->ID, "uObject");
		glUniformMatrix4fv(object_loc, 1, GL_FALSE, glm::value_ptr(worldTransform));

		// draw the entity
		//Draw(entity);
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
	 *  Saves a shader by name.
	 *
	 *      \param [in] name
	 *      \param [in] shader
	 */
	void Graphics::SaveShader(std::string name, Shader shader)
	{
		shaders[name] = shader;
	}

	/*!
	 *  Retrieves a shader from Graphics system by name.
	 *
	 *      \param [in] name
	 *
	 *      \return The shader.
	 */
	Shader* Graphics::GetShader(std::string name)
	{
		return &(shaders[name]);
	}

	void Graphics::UpdateCameraMovement()
	{
		if (firstMouse)
		{
			lastX = mouse_x;
			lastY = mouse_y;
			firstMouse = false;
		}

		float xoffset = (float)mouse_x - (float)lastX;
		float yoffset = (float)lastY - (float)mouse_y; // reversed since y-coordinates go from bottom to top
		lastX = mouse_x;
		lastY = mouse_y;

		float look_sensitivity = 0.1f;
		float scroll_sensitivity = 3.0f;
		xoffset *= look_sensitivity;
		yoffset *= look_sensitivity;
		float mouseScrollDelta = (float)mouse_scroll * scroll_sensitivity;
		mouse_scroll = 0.0; // reset value

		camera.ProcessMouseMovement(xoffset, yoffset);
		camera.ProcessMouseScroll(mouseScrollDelta);
	}

	/*!
	 *  callback for the mouse position
	 *
	 *      \param [in,out] window
	 *      \param [in]     xpos
	 *      \param [in]     ypos
	 */
	void Graphics::mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mouse_x = xpos;
		mouse_y = ypos;
	}

	/*!
	 *  callback for scroll input
	 *
	 *      \param [in,out] window
	 *      \param [in]     xoffset
	 *      \param [in]     yoffset
	 */
	void Graphics::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouse_scroll = yoffset;
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