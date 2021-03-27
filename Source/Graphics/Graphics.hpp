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
	class Graphics : public ASystem
	{
	public:
		// window constants
		static const unsigned int SCR_WIDTH = 1200;
		static const unsigned int SCR_HEIGHT = SCR_WIDTH * 9 / 16;

		// member variables
		std::vector<Color> palette = {
		Color(0x2a363b), Color(0x355c7d), Color(0x6c5b7b),
		Color(0xc06c84), Color(0xf67280), Color(0xf8b195) };
		Camera camera = Camera(
			glm::vec3(0.0f, 8.3f, 23.0f)); // position
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

	private:
		// mouse state
		static double mouse_y;
		static double mouse_x;
		static double mouse_scroll;
		bool firstMouse;
		double lastX = SCR_WIDTH / 2.0f;
		double lastY = SCR_HEIGHT / 2.0f;

		// Asset references references
		Shader* default_shader;
		std::map<std::string, Shader> shaders;

		void UpdateCameraMovement();
		void RenderEntity(Entity* entity, glm::mat4 viewTransform) const;

		// inherited mebers, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}