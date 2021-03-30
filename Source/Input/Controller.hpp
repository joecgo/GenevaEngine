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
  * \file Controller.hpp
  * \author Joe Goldman
  * \brief Controller class declaration
  *
  */

#pragma once

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW

#include <Core/GameCommon.hpp>
#include <Input/Commands.hpp>

#include <iostream>

namespace GenevaEngine
{
	class Controller
	{
	public:
		~Controller();
		void HandleInput();
		void BindCommand(int key_value, Command* command);
		void Possess(Entity* arg_entity);

		// commands
		void Jump();

	private:
		std::map<int, Command*> key_binds;
		Entity* entity = nullptr;
	};
}