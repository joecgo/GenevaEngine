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
	// define static variables
	bool Input::firstMouse_ = true;;
	double Input::lastX_ = Graphics::SCR_WIDTH / 2.0;;
	double Input::lastY_ = Graphics::SCR_HEIGHT / 2.0;;

	void Input::Start()
	{
	}

	void Input::End()
	{
	}

	void Input::Update()
	{
		processInput(Graphics::window);
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

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			Graphics::SetClearColor(Graphics::palette[0]);
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			Graphics::SetClearColor(Graphics::palette[1]);
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
			Graphics::SetClearColor(Graphics::palette[2]);
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			Graphics::SetClearColor(Graphics::palette[3]);
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
			Graphics::SetClearColor(Graphics::palette[4]);
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
			Graphics::SetClearColor(Graphics::palette[5]);

		float dt = GameSession::GetDeltaTime();
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			Graphics::camera.ProcessKeyboard(Camera::Movement::FORWARD, dt);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			Graphics::camera.ProcessKeyboard(Camera::Movement::BACKWARD, dt);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			Graphics::camera.ProcessKeyboard(Camera::Movement::LEFT, dt);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			Graphics::camera.ProcessKeyboard(Camera::Movement::RIGHT, dt);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			Graphics::camera.ProcessKeyboard(Camera::Movement::DOWN, dt);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			Graphics::camera.ProcessKeyboard(Camera::Movement::UP, dt);
	}

	/*!
	 *  Callback for mouse input
	 *
	 *      \param [in,out] window
	 *      \param [in]     xpos
	 *      \param [in]     ypos
	 */
	void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse_)
		{
			lastX_ = xpos;
			lastY_ = ypos;
			firstMouse_ = false;
		}

		double xoffset = xpos - lastX_;
		double yoffset = lastY_ - ypos; // reversed since y-coordinates go from bottom to top
		lastX_ = xpos;
		lastY_ = ypos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		Graphics::camera.ProcessMouseMovement((float)xoffset, (float)yoffset);
	}

	/*!
	 *  callback for scroll input
	 *
	 *      \param [in,out] window
	 *      \param [in]     xoffset
	 *      \param [in]     yoffset
	 */
	void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Graphics::camera.ProcessMouseScroll((float)yoffset);
	}
}