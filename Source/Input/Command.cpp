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
	/*!
	 *  Constructor.
	 *
	 *      \param [in] command_type
	 */
	Command::Command(Type command_type) : m_type(command_type)
	{
	}

	/*!
	 *  Sets the command's axis value.
	 *
	 *      \param [in] axis_value
	 */
	void Command::SetAxis(float axis_value)
	{
		m_axis = axis_value;
	}

	/*!
	 *  Returns the command's axis value
	 *
	 *      \return The axis.
	 */
	float Command::GetAxis() const
	{
		return m_axis;
	}

	/*!
	 *  Returns the command's type.
	 *
	 *      \return The type.
	 */
	Command::Type Command::GetType() const
	{
		return m_type;
	}
}