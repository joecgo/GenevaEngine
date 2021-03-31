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
  * \file Commands.hpp
  * \author Joe Goldman
  * \brief Contains Base Command class and all inherited commands
  *
  */

#pragma once

#include <Input/Controller.hpp>

namespace GenevaEngine
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(Controller& controller) = 0;
		void SetAxis(float axis_value);

	protected:
		float axis; // -1 to 1, used in axis commands
	};

	class JumpCommand : public Command
	{
	public:
		void Execute(Controller& controller);
	};

	class MoveCommand : public Command
	{
	public:
		void Execute(Controller& controller);
	};
}