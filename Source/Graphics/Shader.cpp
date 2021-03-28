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
	float debugVertices[] = {
		// positions
		0.5f, -0.5f,   // bottom right
	   -0.5f, -0.5f,   // bottom left
		0.0f,  0.5f,   // top
	};

	float debugColors[] = {
		// colors
		0.0f, 1.0f, 0.0f, 1.0f,   // bottom right
		0.0f, 0.0f, 1.0f, 1.0f,   // bottom left
		1.0f, 0.0f, 0.0f, 1.0f    // top
	};

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
		m_projectionUniform = glGetUniformLocation(m_programId, "projectionMatrix");
		m_vertexAttribute = 0;
		m_colorAttribute = 1;

		// Generate 1 vertex buffer and 2 vertex arrays
		glGenVertexArrays(1, &m_vaoId);
		glGenBuffers(2, m_vboIds);

		glBindVertexArray(m_vaoId);
		glEnableVertexAttribArray(m_vertexAttribute);
		glEnableVertexAttribArray(m_colorAttribute);

		// Vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
		glVertexAttribPointer(m_vertexAttribute, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBufferData(GL_ARRAY_BUFFER, sizeof(debugVertices), debugVertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
		glVertexAttribPointer(m_colorAttribute, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBufferData(GL_ARRAY_BUFFER, sizeof(debugColors), debugColors, GL_DYNAMIC_DRAW);

		// Cleanup
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Shader::~Shader()
	{
		if (m_vaoId)
		{
			glDeleteVertexArrays(1, &m_vaoId);
			glDeleteBuffers(2, m_vboIds);
		}
	}

	void Shader::UpdateProjection(glm::mat4 projection)
	{
		glUniformMatrix4fv(m_projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void Shader::Vertex(const b2Vec2& v, const Color& c)
	{
		if (m_count == e_maxVertices)
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

		// testing only (REMOVE)
		m_count = 3;

		glBindVertexArray(m_vaoId);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(b2Vec2), debugVertices); // m_vertices);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(Color), debugColors); // m_colors);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_TRIANGLES, 0, m_count);
		glDisable(GL_BLEND);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		m_count = 0;
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