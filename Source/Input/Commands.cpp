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
  * \file Commands.cpp
  * \author Joe Goldman
  * \brief Definitions for command classes
  *
  **/

#include <Input/Commands.hpp>

namespace GenevaEngine
{
	void Command::SetAxis(float arg_axis)
	{
		axis = arg_axis;
	}

	void JumpCommand::Execute(Controller& controller)
	{
		controller.Jump();
	}

	void MoveCommand::Execute(Controller& controller)
	{
		controller.Move(axis);
	}
}