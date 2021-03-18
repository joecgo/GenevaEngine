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

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GenevaEngine
{
	/*!
	 *  \brief Manages a single shader program.
	 */
	class Shader
	{
	public:
		unsigned int ID = -1;

		// default contructor
		Shader() {};
		// constructor generates the shader on the fly
		Shader(const char* vertexPath, const char* fragmentPath);

		// activate the shader
		void use();
		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

	private:
		// utility function for checking shader compilation/linking errors.
		// ------------------------------------------------------------------------
		void checkCompileErrors(unsigned int shader, std::string type);
	};
}