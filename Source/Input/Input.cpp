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

	void Input::Update(float dt)
	{
		processInput(gamesession->graphics->window, dt);
	}

	/*!
	 *  Processes the input.
	 *
	 *      \param [in,out] window
	 */
	void Input::processInput(GLFWwindow* window, float dt)
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

		float sensitivity = 5.0f;
		float moveRate = dt * sensitivity;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			gfx->camera.ProcessCameraMovement(Camera::Movement::FORWARD, moveRate);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			gfx->camera.ProcessCameraMovement(Camera::Movement::BACKWARD, moveRate);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			gfx->camera.ProcessCameraMovement(Camera::Movement::LEFT, moveRate);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			gfx->camera.ProcessCameraMovement(Camera::Movement::RIGHT, moveRate);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			gfx->camera.ProcessCameraMovement(Camera::Movement::DOWN, moveRate);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			gfx->camera.ProcessCameraMovement(Camera::Movement::UP, moveRate);
	}
}