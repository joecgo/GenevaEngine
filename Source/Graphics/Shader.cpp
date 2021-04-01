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
  * \file Shader.cpp
  * \author Joe Goldman
  * \brief Shader class definition
  */

#include <Graphics/Shader.hpp>

namespace GenevaEngine
{
	/*!
	 *  constructor generates the shader a fragment shader and vertex shader file path
	 *
	 *      \param [in] vertexPath
	 *      \param [in] fragmentPath
	 */
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		//// ---------------------------------------------------------------
		/// 1. retrieve the vertex/fragment source code from filePath
		// -----------------------------------------------------------------
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//// ---------------------------------------------------------------
		/// 2. compile shaders
		// -------------------------------------------------------------
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");
		// shader Program
		m_programId = glCreateProgram();
		glAttachShader(m_programId, vertex);
		glAttachShader(m_programId, fragment);
		glLinkProgram(m_programId);
		CheckCompileErrors(m_programId, "PROGRAM");

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		// manage variables for shader
		glUseProgram(m_programId);
		m_vertexAttribute = 0;
		m_colorAttribute = 1;

		// Generate 1 vertex buffer and 2 vertex arrays
		glGenVertexArrays(1, &m_vaoId);
		glGenBuffers(3, m_vboIds);
		glBindVertexArray(m_vaoId);
		glEnableVertexAttribArray(m_vertexAttribute);
		glEnableVertexAttribArray(m_colorAttribute);

		// Vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
		glVertexAttribPointer(m_vertexAttribute, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
		glVertexAttribPointer(m_colorAttribute, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_DYNAMIC_DRAW);

		// save uniform location for later use
		m_projectionUniform = glGetUniformLocation(m_programId, "projectionMatrix");

		// clean up
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		CheckErrors();
	}

	Shader::~Shader()
	{
		if (m_vaoId)
		{
			glDeleteVertexArrays(1, &m_vaoId);
			glDeleteBuffers(2, m_vboIds);
		}
	}

	void Shader::UpdateProjection(float* projection)
	{
		m_projectionMatrix = projection;
	}

	void Shader::Vertex(const b2Vec2& v, const Color& c)
	{
		if (m_count == k_maxVertices)
			Flush();

		m_vertices[m_count] = v;
		m_colors[m_count] = c;
		++m_count;
	}

	void Shader::Flush()
	{
		if (m_count == 0)
			return;

		glUseProgram(m_programId);

		glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, m_projectionMatrix);

		glBindVertexArray(m_vaoId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(b2Vec2), m_vertices); // m_vertices);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(Color), m_colors); // m_colors);

		if (DrawType == GL_TRIANGLES)
		{ // TRIANGLES
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDrawArrays(DrawType, 0, m_count);
			glDisable(GL_BLEND);
		}
		else
		{ // LINES
			glDrawArrays(DrawType, 0, m_count);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		CheckErrors();

		m_count = 0;
	}

	void Shader::CheckErrors()
	{
		GLenum errCode = glGetError();
		if (errCode != GL_NO_ERROR)
		{
			fprintf(stderr, "OpenGL error = %d\n", errCode);
			assert(false);
		}
	}

	/*!
	 *  Utility function for checking shader compilation/linking errors.
	 *
	 *      \param [in] shader
	 *      \param [in] type
	 */
	void Shader::CheckCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
					<< infoLog << "\n -- ---- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
					<< infoLog << "\n -- ---- -- " << std::endl;
			}
		}
	}
};