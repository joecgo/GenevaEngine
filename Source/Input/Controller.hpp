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
	/*!
	 *  \brief pos key and neg key pair to create axis input
	 */
	struct AxisKeys
	{
		int pos_key;
		int neg_key;

		AxisKeys(int arg_neg_key, int arg_pos_key) :
			pos_key(arg_pos_key), neg_key(arg_neg_key)
		{}
	};

	/*!
	 *  \brief a list of neg key, pos key pairs and a command
	 */
	struct AxisBinding
	{
		std::list<AxisKeys> key_pairs;
		Command* command;
	};

	/*!
	 *  \brief a key and command
	 */
	struct KeyBinding
	{
		int key;
		Command* command;
	};

	/*!
	 *  \brief Controller translates input into commands for entitys to follow
	 */
	class Controller
	{
	public:
		~Controller();
		void HandleInput();
		void BindCommand(int key, Command* command);
		void BindCommand(std::list<AxisKeys> keys_pairs, Command* command);
		void Possess(Entity* entity);

	private:
		std::list<KeyBinding> keypress_binds;
		std::list<AxisBinding> axis_binds;
		Entity* m_entity = nullptr;
	};
}