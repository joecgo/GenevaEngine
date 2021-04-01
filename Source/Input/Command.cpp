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
  * \brief Define command class
  *
  **/

#include <Input/Command.hpp>

namespace GenevaEngine
{
	Command::Command(Type command_type) : m_type(command_type)
	{
	}
	void Command::SetAxis(float axis_value)
	{
		m_axis = axis_value;
	}
	float Command::GetAxis()
	{
		return m_axis;
	}
	Command::Type Command::GetType()
	{
		return m_type;
	}
}