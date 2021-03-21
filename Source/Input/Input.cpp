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
  * \file Input.cpp
  * \author Joe Goldman
  * \brief Input system class definition
  *
  **/

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	void Input::Start()
	{
	}

	void Input::End()
	{
	}

	void Input::Update()
	{
		processInput(gamesession->graphics->window);
	}

	/*!
	 *  Processes the input.
	 *
	 *      \param [in,out] window
	 */
	void Input::processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		Graphics* gfx = gamesession->graphics;
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			gfx->SetClearColor(gfx->palette[0]);
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			gfx->SetClearColor(gfx->palette[1]);
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
			gfx->SetClearColor(gfx->palette[2]);
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			gfx->SetClearColor(gfx->palette[3]);
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
			gfx->SetClearColor(gfx->palette[4]);
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
			gfx->SetClearColor(gfx->palette[5]);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			gfx->camera.ProcessKeyboard(Camera::Movement::FORWARD, DT());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			gfx->camera.ProcessKeyboard(Camera::Movement::BACKWARD, DT());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			gfx->camera.ProcessKeyboard(Camera::Movement::LEFT, DT());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			gfx->camera.ProcessKeyboard(Camera::Movement::RIGHT, DT());
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			gfx->camera.ProcessKeyboard(Camera::Movement::DOWN, DT());
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			gfx->camera.ProcessKeyboard(Camera::Movement::UP, DT());
	}
}