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
  * \file Controller.cpp
  * \author Joe Goldman
  * \brief Controller class definition
  *
  **/

#include <Input/Controller.hpp>

namespace GenevaEngine
{
	Controller::~Controller()
	{
		// delete press commands
		for (auto const& [key, val] : keypress_binds)
			delete val;

		// delete axis commands
		for (auto const& [key, val] : axis_binds)
			delete val;
	}

	void Controller::BindCommand(int key_value, Command* command)
	{
		keypress_binds[key_value] = command;
	}

	void Controller::BindCommand(AxisKeys key_values, Command* command)
	{
		axis_binds[key_values] = command;
	}

	void Controller::HandleInput()
	{
		// iterate through key press binds, polling each global key state
		for (auto const& [key, val] : keypress_binds)
		{
			// if key is pressed, execute command
			if (Input::KeyPressed(key))
				keypress_binds[key]->Execute(*this);
		}

		// iterate through axis binds, polling each global key state
		for (auto const& [key, val] : axis_binds)
		{
			float axis = 0;
			if (Input::KeyDown(key.pos_key))
				axis = 1.0f;
			if (Input::KeyDown(key.neg_key))
				axis -= 1.0f;

			axis_binds[key]->SetAxis(axis);
			axis_binds[key]->Execute(*this);
		}
	}

	void Controller::Possess(Entity* arg_entity)
	{
		entity = arg_entity;
	}

	void Controller::Jump()
	{
		entity->Jump();
	}

	void Controller::Move(float axis)
	{
		entity->Move(axis);
	}
}