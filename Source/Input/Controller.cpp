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
		// delete commands
		for (auto const& [key, val] : key_binds)
		{
			delete val;
		}
	}

	void Controller::BindCommand(int key_value, Command* command)
	{
		key_binds[key_value] = command;
	}

	void Controller::HandleInput()
	{
		// iterate through key binds, polling each global key state
		for (auto const& [key, val] : key_binds)
		{
			// if key is pressed, execute command
			if (Input::KeyPressed(key))
				key_binds[key]->Execute(*this);
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
}