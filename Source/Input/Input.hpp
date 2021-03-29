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

#include <map>

#include <Input/Controller.hpp>
#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	class Command;

	/*!
	 *  Core system for handling input
	 */
	class Input : public System
	{
	public:
		static std::map<int, bool> keys;

		// returns pressed state.  Else returns false.
		bool KeyDown(int key);

	private:
		// controllers
		Controller* player_controller;

		// key state handling
		static void SetKeyValue(int key, bool value);
		static void SetupKeyInputs(GLFWwindow* window);
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