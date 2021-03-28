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
  * \file Color.hpp
  * \author Joe Goldman
  * \brief Color class declaration
  */

#pragma once

namespace GenevaEngine
{
	/*!
	 * \brief A container for a single color.
	 */
	class Color
	{
	public:
		float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;

		Color(int hexValue = 0x000000, float a = 1.0f);
		Color(float r, float g, float b, float a = 1.0f);
		Color operator*(float scalar);
	};
}