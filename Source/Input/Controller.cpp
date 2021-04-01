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
	/*!
	 *  Destructor. deletes commands from memory here
	 */
	Controller::~Controller()
	{
		// delete press commands
		for (KeyBinding kb : keypress_binds)
			delete kb.command;

		// delete axis commands
		for (AxisBinding ka : axis_binds)
			delete ka.command;
	}

	/*!
	 *  Binds key to a command. Command sent when key is pressed
	 *
	 *      \param [in]     key
	 *      \param [in,out] command
	 */
	void Controller::BindCommand(int key, Command* command)
	{
		KeyBinding kb;
		kb.command = command;
		kb.key = key;
		keypress_binds.push_back(kb);
	}

	/*!
	 *  Binds an axis value to a command sent every frame
	 *  neg key is -1 and pos key is 1
	 *      \param [in]     keys_pairs
	 *      \param [in,out] command
	 */
	void Controller::BindCommand(std::list<AxisKeys> keys_pairs, Command* command)
	{
		AxisBinding ab;
		ab.command = command;
		ab.key_pairs = keys_pairs;
		axis_binds.push_back(ab);
	}

	/*!
	 *  Polls input system for input
	 */
	void Controller::HandleInput()
	{
		// iterate through key press binds, polling each global key state
		for (KeyBinding kb : keypress_binds)
		{
			// if key is pressed, execute command
			if (Input::KeyPressed(kb.key))
				m_entity->Notify(kb.command);
		}

		// iterate through axis bind pairs, adding to axis values, then executing
		for (AxisBinding axis_bind : axis_binds)
		{
			float axis = 0;
			for (AxisKeys key_pair : axis_bind.key_pairs)
			{
				// TODO: handle joystick/trigger input
				// keydown style input
				if (Input::KeyDown(key_pair.pos_key))
					axis += 1.0f;
				if (Input::KeyDown(key_pair.neg_key))
					axis -= 1.0f;
			}

			axis_bind.command->SetAxis(std::clamp(axis, -1.0f, 1.0f));
			m_entity->Notify(axis_bind.command);
		}
	}

	/*!
	 *  Controller that posseses an entity then controls it
	 *
	 *      \param [in,out] entity
	 */
	void Controller::Possess(Entity* entity)
	{
		m_entity = entity;
	}
}