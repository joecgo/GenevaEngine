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
#include <queue> // queue

#include <Graphics/Shader.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Color.hpp>

namespace GenevaEngine
{
	struct RenderData
	{
		RenderData(Shader* shader, Model* model, glm::mat4 world_tranform);
		Shader* shader_;
		Model* model_;
		glm::mat4 world_transform_;
	};

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
		static Shader* GetShader(std::string name);
		// model storage and access methods
		void SaveModel(std::string name, Model model);
		static Model* GetModel(std::string name);
		static void Render(Model* model, Shader* shader, glm::mat4 worldTranform);

	private:
		// asset storage in maps
		static std::map<std::string, Shader> shaders_;
		static std::map<std::string, Model> models_;
		static std::queue<RenderData> render_queue_;

		// inherited methods and constructors
		using ASystem::ASystem;
		void Start();
		void Update();
		void End();
	};
}