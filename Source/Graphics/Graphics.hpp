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

#include <Core/GameCommon.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <iostream> // cout, endl
#include <vector> // vector
#include <map> // map

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
		static const unsigned int SCR_HEIGHT = 900;

		// static variable declarations
		static std::vector<Color> palette;
		static Camera camera;
		static GLFWwindow* window;

		// glfw wrappers
		static void SetClearColor(Color color);
		// glfw callbacks
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		// shader storage and access methods
		void SaveShader(std::string name, Shader shader);
		Shader GetShader(std::string name);
		// model storage and access methods
		void SaveModel(std::string name, Model model);
		Model GetModel(std::string name);

	private:
		// asset storage in maps
		std::map<std::string, Shader> shaders_;
		std::map<std::string, Model> models_;

		// inherited methods and constructors
		using ASystem::ASystem;
		void Start();
		void Update();
		void End();
	};
}