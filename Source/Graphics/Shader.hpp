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
  * \file Shader.hpp
  * \author Joe Goldman
  * \brief Shader class declaration
  */

#pragma once

  // Disable warning messages from box2d: C26812 C26495
#pragma warning( disable : 26812 26495)

  // Disable warning messages from Shader: C6386
#pragma warning( disable : 6386)

#include <box2d/box2d.h>

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW
#include <glm/gtc/matrix_transform.hpp> // mat4
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Graphics/Color.hpp>

#define BUFFER_OFFSET(x)  ((const void*) (x))

namespace GenevaEngine
{
	/*!
	 *  \brief Manages a single shader program.
	 */
	class Shader
	{
	public:
		// member vars
		static constexpr int e_maxVertices = 512;
		b2Vec2 m_vertices[e_maxVertices];
		Color m_colors[e_maxVertices];
		int32 m_count = 0;
		GLuint m_programId = -1;
		GLuint m_vaoId;
		GLuint m_vboIds[2];
		GLint m_projectionUniform;
		GLint m_vertexAttribute;
		GLint m_colorAttribute;
		glm::mat4 m_projectionMatrix;

		// constructors
		Shader() {};
		Shader(const char* vertexPath, const char* fragmentPath);

		// destructor
		~Shader();

		// render methods
		void UpdateProjection(glm::mat4 projection);
		void Vertex(const b2Vec2& v, const Color& c);
		void Flush();

	private:
		// utility function for checking shader compilation/linking errors.
		void CheckCompileErrors(unsigned int shader, std::string type);
		void CheckErrors();
	};
}