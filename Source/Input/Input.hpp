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
  * \file Input.hpp
  * \author Joe Goldman
  * \brief Input system class declaration
  *
  */

#pragma once

#include <Core/ASystem.hpp>

#include <Graphics/Graphics.hpp>
#include <Graphics/Camera.hpp>

namespace GenevaEngine
{
	/*!
	 *  Core system for handling input
	 */
	class Input : public ASystem
	{
	public:
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		// mouse input state
		static bool firstMouse_;
		static double lastX_;
		static double lastY_;

		// inherited virtual methods
		void Start();
		void Update();
		void End();

		// called on update
		static void processInput(GLFWwindow* window);
	};
}