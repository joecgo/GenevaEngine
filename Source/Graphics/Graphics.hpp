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

#include <iostream> // cout, endl
#include <unordered_map> // unordered_map
#include <string> // string

#include <Core/System.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Color.hpp>

namespace GenevaEngine
{
	class Entity;

	/*!
	 *  \brief Sets up shaders, window, and renders the game. Uses GLFW
	 */
	class Graphics : public System
	{
	public:
		// window constants
		static const unsigned int SCR_WIDTH = 1200;
		static const unsigned int SCR_HEIGHT = SCR_WIDTH * 9 / 16;

		// glfw callbacks
		static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

		// getters & setters
		Color GetPaletteColor(int color_id);
		void SetClearColor(Color color);
		GLFWwindow* GetWindow();
		Camera* GetCamera();

		// Asset storage and access methods
		void SaveShader(std::string name, Shader shader);
		Shader* GetShader(std::string name);

	private:
		// color palette
		std::vector<Color> m_palette = {
			Color(0x383838), Color(0x355c7d), Color(0x6c5b7b),
			Color(0xc06c84), Color(0xf67280), Color(0xf8b195) };

		// object references
		Camera m_camera = Camera(b2Vec2(0.0f, 30.0f));
		GLFWwindow* m_window;
		Shader* m_triangle_shader = nullptr;
		Shader* m_line_shader = nullptr;

		// Assets, mapped to keys
		std::unordered_map<std::string, Shader> m_shaders;

		// verts used in a single shape perspective transformation
		b2Vec2 m_transformedVerts[512];

		// debug camera methods
		void UpdateCameraMovement();

		// render methods
		void RenderEntity(Entity& entity);
		void DrawCircle(const b2Vec2& center, float radius, const Color& color);
		void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const Color& color);
		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const Color& color);
		void Flush();

		// inherited mebers, methods, and constructors
		using System::System;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}