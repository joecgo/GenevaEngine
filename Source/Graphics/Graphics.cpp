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
	// define static variables
	std::vector<Color> Graphics::palette = {
		Color(0x2a363b), Color(0x355c7d), Color(0x6c5b7b),
		Color(0xc06c84), Color(0xf67280), Color(0xf8b195) };
	Camera Graphics::camera(glm::vec3(0.0f, 0.0f, 3.0f));;
	GLFWwindow* Graphics::window;
	std::queue<RenderData> Graphics::render_queue_;
	std::map<std::string, Shader> Graphics::shaders_;
	std::map<std::string, Model> Graphics::models_;

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

		// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
		stbi_set_flip_vertically_on_load(true);

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		// create and save shaders and models. TODO: do this with an asset file
		SaveShader("textureShader", Shader("Shaders/Shader.vert", "Shaders/Shader.frag"));
		SaveShader("greyShader", Shader("Shaders/Shader.vert", "Shaders/GreyShader.frag"));
		SaveModel("backpack", Model("Assets/Art/Test/Backpack/backpack.obj"));
		SaveModel("kevin", Model("Assets/Art/Test/Kevin/Kevin.obj"));

		// set clear color
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

		// get view matrics from camera
		glm::mat4 view = camera.GetViewMatrix(SCR_WIDTH, SCR_HEIGHT);

		// render everything in the render queue
		while (!render_queue_.empty())
		{
			// retrieve data from front of queue
			RenderData data = render_queue_.front();
			Shader* shader = data.shader_;
			Model* model = data.model_;
			glm::mat4 worldTransform = data.world_transform_;
			render_queue_.pop();

			// render the model using shader and camera view
			shader->use();
			int viewLoc = glGetUniformLocation(shader->ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			int modelLoc = glGetUniformLocation(shader->ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(worldTransform));
			model->Draw(*shader);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*!
	 *  Queues up the provided object data to be rendered next update.
	 *
	 *      \param [in,out] model
	 *      \param [in,out] shader
	 *      \param [in]     worldTranform
	 */
	void Graphics::Render(Model* model, Shader* shader, glm::mat4 worldTranform)
	{
		// package data for rendering during next graphics update, placed in queue
		render_queue_.push(RenderData(shader, model, worldTranform));
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

	/*!
	 *  Saves a shader by name.
	 *
	 *      \param [in] name
	 *      \param [in] shader
	 */
	void Graphics::SaveShader(std::string name, Shader shader)
	{
		shaders_[name] = shader;
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
		return &(shaders_[name]);
	}

	/*!
 *  Saves a model by name.
 *
 *      \param [in] name
 *      \param [in] model
 */
	void Graphics::SaveModel(std::string name, Model model)
	{
		models_[name] = model;
	}

	/*!
	 *  Retrieves a model from Graphics system by name.
	 *
	 *      \param [in] name
	 *
	 *      \return The model.
	 */
	Model* Graphics::GetModel(std::string name)
	{
		return &(models_[name]);
	}
}