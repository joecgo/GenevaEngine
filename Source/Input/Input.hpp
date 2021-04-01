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

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW

#include <map>

#include <Input/Controller.hpp>
#include <Core/System.hpp>

namespace GenevaEngine
{
	class Command;

	/*!
	 *  \brief Core system for handling input
	 */
	class Input : public System
	{
	public:
		// key state enums
		enum KeyState { Up, Pressed, Down, Released };

		// Attributes
		bool DevCheatsOn = false;

		// Key state
		static KeyState GetKeyState(int key);
		static bool KeyDown(int key);
		static bool KeyUp(int key);
		static bool KeyPressed(int key);
		static bool KeyReleased(int key);

		// Player controller
		Controller* GetPlayerController(); // TODO: add player IDs for multiplayer

	private:
		// key state data
		static std::map<int, KeyState> keys;

		// controllers
		Controller* m_playerController;

		// key state handling
		void SetupKeyInputs(GLFWwindow* window);
		static void KeyStateEvent(int key, bool is_down);
		// progresses key states forward one step (i.e. Pressed -> Down)
		void UpdateKeyStates();
		// The GLFW callback for key events.  Sends events to all KeyInput instances
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		// process input from GLFW for camera cheats I set up during GLFW tutorials
		void ProcessDevCheats(GLFWwindow* window, double dt);

		// inherited methods and constructors
		using System::System;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}