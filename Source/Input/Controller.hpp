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
#include <Input/Command.hpp>

#include <list> // list
#include <set> // set
#include <algorithm> // clamp

namespace GenevaEngine
{
	struct AxisKeys
	{
		int pos_key;
		int neg_key;

		AxisKeys(int arg_neg_key, int arg_pos_key) :
			pos_key(arg_pos_key), neg_key(arg_neg_key)
		{}
	};

	struct AxisBinding
	{
		std::list<AxisKeys> key_pairs;
		Command* command;
	};

	struct KeyBinding
	{
		int key;
		Command* command;
	};

	class Controller
	{
	public:
		~Controller();
		void HandleInput();
		void BindCommand(int key, Command* command);
		void BindCommand(std::list<AxisKeys> keys_pairs, Command* command);
		void Possess(Entity* arg_entity);

	private:
		std::list<KeyBinding> keypress_binds;
		std::list<AxisBinding> axis_binds;
		Entity* entity = nullptr;
	};
}