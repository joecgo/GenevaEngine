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
	std::map<int, Input::KeyState> Input::keys;

	void Input::Start()
	{
		// keys
		SetupKeyInputs(gamesession->graphics->window);

		// set up player controller
		// commands deleted in ~Controller
		player_controller = new Controller();
		player_controller->BindCommand((int)GLFW_KEY_SPACE, new JumpCommand());
	}

	void Input::End()
	{
		delete player_controller;
	}

	void Input::Update(double dt)
	{
		UpdateKeyStates();
		glfwPollEvents();
		player_controller->HandleInput();
		ProcessDevCheats(gamesession->graphics->window, dt);
	}

	void Input::UpdateKeyStates()
	{
		for (auto const& [key, val] : keys)
		{
			if (val == KeyState::Pressed)
				keys[key] = KeyState::Down;
			if (val == KeyState::Released)
				keys[key] = KeyState::Up;
		}
	}

	Input::KeyState Input::GetKeyState(int key)
	{
		return keys[key];
	}

	bool Input::KeyDown(int key)
	{
		return (keys[key] == KeyState::Down) || (keys[key] == KeyState::Pressed);
	}

	bool Input::KeyUp(int key)
	{
		return (keys[key] == KeyState::Up) || (keys[key] == KeyState::Released);
	}

	bool Input::KeyPressed(int key)
	{
		return keys[key] == KeyState::Pressed;
	}

	bool Input::KeyReleased(int key)
	{
		return keys[key] == KeyState::Released;
	}

	void Input::KeyStateEvent(int key, bool is_down)
	{
		if (keys[key] == KeyState::Up && is_down)
			keys[key] = KeyState::Pressed;
		else if (keys[key] == KeyState::Down && !is_down)
			keys[key] = KeyState::Released;
	}

	void Input::SetupKeyInputs(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, Input::KeyCallback);
	}

	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Send key event to all KeyInput instances
		Input::KeyStateEvent(key, action == GLFW_PRESS);
	}

	/*!
	 *  Processes the input.
	 *
	 *      \param [in,out] window
	 */
	void Input::ProcessDevCheats(GLFWwindow* window, double dt)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

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
		float moveRate = (float)dt * sensitivity;
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