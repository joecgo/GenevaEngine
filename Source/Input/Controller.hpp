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

#include <map> // map

namespace GenevaEngine
{
	struct AxisKeys
	{
		AxisKeys(int arg_neg_key, int arg_pos_key) :
			pos_key(arg_pos_key), neg_key(arg_neg_key)
		{}

		bool operator<(const AxisKeys& o)  const
		{
			return pos_key > o.pos_key;
		}

		int pos_key = 0;
		int neg_key = 0;
	};

	class Controller
	{
	public:
		~Controller();
		void HandleInput();
		void Bind_KeyPress_Command(int key_value, Command* command);
		void Bind_Axis_Command(AxisKeys key_values, Command* command);
		void Possess(Entity* arg_entity);

		// commands
		void Jump();
		void Move(float axis);

	private:
		std::map<int, Command*> keypress_binds;
		std::map<AxisKeys, Command*> axis_binds;
		Entity* entity = nullptr;
	};
}