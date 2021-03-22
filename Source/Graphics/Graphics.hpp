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
  * \file Graphics.hpp
  * \author Joe Goldman
  * \brief Graphics system class declaration
  *
  */

#pragma once

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW
#include <glm/gtc/matrix_transform.hpp> // vec3 mat4
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include <stb/stb_image.h> // stbi_set_flip_vertically_on_load

#include <iostream> // cout, endl
#include <vector> // vector
#include <map> // map
#include <queue> // queue

#include <Core/GameCommon.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Color.hpp>

namespace GenevaEngine
{
	struct RenderData
	{
		RenderData(Shader* arg_shader, Model* arg_model, glm::mat4 arg_world_tranform) :
			shader(arg_shader), model(arg_model), world_transform(arg_world_tranform) {}
		Shader* shader;
		Model* model;
		glm::mat4 world_transform;
	};

	class Graphics : public ASystem
	{
	public:
		// window constants
		static const unsigned int SCR_WIDTH = 1200;
		static const unsigned int SCR_HEIGHT = 900;

		// member variables
		std::vector<Color> palette = {
		Color(0x2a363b), Color(0x355c7d), Color(0x6c5b7b),
		Color(0xc06c84), Color(0xf67280), Color(0xf8b195) };
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		GLFWwindow* window;

		// glfw callbacks
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

		// glfw wrappers
		void SetClearColor(Color color);
		// shader storage and access methods
		void SaveShader(std::string name, Shader shader);
		Shader* GetShader(std::string name);
		// model storage and access methods
		void SaveModel(std::string name, Model model);
		Model* GetModel(std::string name);
		// render model
		void Render(Model* model, Shader* shader, glm::mat4 worldTranform);

	private:
		// mouse state
		static double mouse_y;
		static double mouse_x;
		static double mouse_scroll;
		bool firstMouse;
		double lastX = SCR_WIDTH / 2.0f;
		double lastY = SCR_HEIGHT / 2.0f;

		// asset storage in maps
		std::map<std::string, Shader> shaders;
		std::map<std::string, Model> models;
		std::queue<RenderData> render_queue;

		void UpdateCameraMovement(double dt);

		// inherited mebers, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}