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
  * \file Command.hpp
  * \author Joe Goldman
  * \brief Define command class
  *
  */

#pragma once

namespace GenevaEngine
{
	class Command
	{
	public:
		// list command types off here, use by observer to query the command type
		enum Type { None, Jump, Move };

		Command(Type command_type);
		void SetAxis(float axis_value);
		float GetAxis();
		Type GetType();

	private:
		float m_axis = 0; // -1 to 1, used in axis commands
		const Type m_type; // for observer to query the command type
	};
}