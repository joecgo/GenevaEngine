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

  // Disable warning messages from Shader: C6386
#pragma warning( disable : 6386)

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Physics/Box2d.hpp> // b2Vec2
#include <Graphics/Color.hpp>

#define BUFFER_OFFSET(x)  ((const void*) (x))

namespace GenevaEngine
{
	/*!
	 *  \brief Manages a single shader program, adding verts to the buffer,
	 *         and all the steps to interface with opengl.
	 */
	class Shader
	{
	public:
		// attributes
		GLint DrawType = GL_TRIANGLES;

		// constructors
		Shader() {};
		Shader(const char* vertexPath, const char* fragmentPath);

		// destructor
		~Shader();

		// render methods
		void UpdateProjection(float* projection);
		void Vertex(const b2Vec2& v, const Color& c);
		void Flush();

	private:
		// member vars
		static constexpr int k_maxVertices = 4096;
		b2Vec2 m_vertices[k_maxVertices];
		Color m_colors[k_maxVertices];
		int32 m_count = 0;
		GLuint m_programId = -1;
		GLuint m_vaoId;
		GLuint m_vboIds[2];
		GLint m_projectionUniform;
		GLint m_vertexAttribute;
		GLint m_colorAttribute;
		float* m_projectionMatrix;

		// utility function for checking shader compilation/linking errors.
		void CheckCompileErrors(unsigned int shader, std::string type);
		void CheckErrors();
	};
}