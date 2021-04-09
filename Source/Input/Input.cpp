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

#include <Input/Input.hpp>
#include <Core/GameSession.hpp>
#include <Input/Command.hpp>
#include <Input/Controller.hpp>
#include <Graphics/Camera.hpp>

namespace GenevaEngine
{
	std::map<int, Input::KeyState> Input::keys;

	/*!
	 *  Start called before gamesession game loop
	 */
	void Input::Start()
	{
		// keys
		SetupKeyInputs(m_gameSession->GetGraphics()->GetWindow());

		// set up player controller
		// commands deleted in ~Controller
		m_playerController = new Controller();
		Controller* pc = m_playerController; // for readibility

		// JUMP
		pc->BindCommand(GLFW_KEY_SPACE, new Command(Command::Jump));

		// MOVE
		std::list<AxisKeys> move_keys{
			AxisKeys(GLFW_KEY_A, GLFW_KEY_D),
			AxisKeys(GLFW_KEY_LEFT, GLFW_KEY_RIGHT) };
		pc->BindCommand(move_keys, new Command(Command::Move));
	}

	/*!
	 *  Ends after gameloop is done
	 */
	void Input::End()
	{
		if (m_playerController != nullptr)
			delete m_playerController;
	}

	/*!
	 *  Updates input system every frame
	 *
	 *      \param [in] dt
	 */
	void Input::Update(double dt)
	{
		UpdateKeyStates();
		glfwPollEvents();

		if (m_playerController != nullptr)
			m_playerController->HandleInput();

		if (DevCheatsOn)
			ProcessDevCheats(m_gameSession->GetGraphics()->GetWindow(), dt);
	}

	/*!
	 *  Returns the player controller.
	 *
	 *      \return The player controller.
	 */
	Controller* Input::GetPlayerController()
	{
		return m_playerController;
	}

	/*!
	 *  steps forward the key states 1 frame
	 *  Pressed -> Down and Released -> Up
	 */
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

	/*!
	 *  Get a specific gets state (UP, DOWN, PRESSED, RELEASED)
	 *
	 *      \param [in] key
	 *
	 *      \return The key state.
	 */
	Input::KeyState Input::GetKeyState(int key)
	{
		return keys[key];
	}

	/*!
	 *  Is the key down? (Down or Pressed)
	 *
	 *      \param [in] key
	 *
	 *      \return
	 */
	bool Input::KeyDown(int key)
	{
		return (keys[key] == KeyState::Down) || (keys[key] == KeyState::Pressed);
	}

	/*!
	 *  is the key up? (UP or Released)
	 *
	 *      \param [in] key
	 *
	 *      \return
	 */
	bool Input::KeyUp(int key)
	{
		return (keys[key] == KeyState::Up) || (keys[key] == KeyState::Released);
	}

	/*!
	 *  Is the key pressed? Only pressed for 1 frame, then becomes "Down" state
	 *
	 *      \param [in] key
	 *
	 *      \return
	 */
	bool Input::KeyPressed(int key)
	{
		return keys[key] == KeyState::Pressed;
	}

	/*!
	 *  Is the key released? Only released for 1 frame, then becomes "Up" state
	 *
	 *      \param [in] key
	 *
	 *      \return
	 */
	bool Input::KeyReleased(int key)
	{
		return keys[key] == KeyState::Released;
	}

	/*!
	 *  Something is happening with this key. GLFW tells us so. Adjust state.
	 *
	 *      \param [in] key
	 *      \param [in] is_down
	 */
	void Input::KeyStateEvent(int key, bool is_down)
	{
		if (keys[key] == KeyState::Up && is_down)
			keys[key] = KeyState::Pressed;
		else if (keys[key] == KeyState::Down && !is_down)
			keys[key] = KeyState::Released;
	}

	/*!
	 *  Sets key input callback in GLFW
	 *
	 *      \param [in,out] window
	 */
	void Input::SetupKeyInputs(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, Input::KeyCallback);
	}

	/*!
	 *  Key input callback. This is passed to GLFW
	 *
	 *      \param [in,out] window
	 *      \param [in]     key
	 *      \param [in]     scancode
	 *      \param [in]     action
	 *      \param [in]     mods
	 */
	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Send key event to all KeyInput instances
		Input::KeyStateEvent(key, action != GLFW_RELEASE);
	}

	/*!
	 *  A place for special cheats like debug camera fly
	 *
	 *      \param [in,out] window
	 */
	void Input::ProcessDevCheats(GLFWwindow* window, double dt)
	{
		Camera* cam = m_gameSession->GetGraphics()->GetCamera();
		float sensitivity = 5.0f;
		float moveRate = (float)dt * sensitivity;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cam->ProcessCameraMovement(Camera::Movement::FORWARD, moveRate);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cam->ProcessCameraMovement(Camera::Movement::BACKWARD, moveRate);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cam->ProcessCameraMovement(Camera::Movement::LEFT, moveRate);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cam->ProcessCameraMovement(Camera::Movement::RIGHT, moveRate);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cam->ProcessCameraMovement(Camera::Movement::DOWN, moveRate);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cam->ProcessCameraMovement(Camera::Movement::UP, moveRate);
	}
}