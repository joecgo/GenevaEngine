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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <iostream> // cout, endl
#include <vector>

#include <Graphics/Shader.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Color.hpp>
#include <Core/GameSession.hpp>
#include <Core/ASystem.hpp>

namespace GenevaEngine
{
	static class Graphics : public ASystem
	{
	public:
		// temp for testing
		Model kevinModel;
		Model testModel;
		Shader textureShader;
		Shader greyShader;

		// window constants
		static const unsigned int SCR_WIDTH = 1200;
		static const unsigned int SCR_HEIGHT = 900;

		// colors
		static std::vector<Color> palette;
		// Camera
		static Camera camera;
		// window
		static GLFWwindow* window;

		// glfw wrappers
		static void SetClearColor(Color color);

		// constructor
		Graphics() {};

		// glfw callbacks
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	private:
		// inherited virtual methods
		void Start() override;
		void Update() override;
		void End() override;
	};
}