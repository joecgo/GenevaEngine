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
  * \file Color.cpp
  * \author Joe Goldman
  * \brief Color class definition
  */

#include <Graphics/Color.hpp>

namespace GenevaEngine
{
	/*!
	 *  Constructor using RGB hex value
	 *
	 *      \param [in] hexValue
	 */
	Color::Color(int hexValue, float arg_a) :
		r(((hexValue >> 16) & 0xFF) / 255.0f),
		g(((hexValue >> 8) & 0xFF) / 255.0f),
		b(((hexValue) & 0xFF) / 255.0f)
	{
	}

	Color::Color(float arg_r, float arg_g, float arg_b, float arg_a) :
		r(arg_r), g(arg_g), b(arg_b), a(arg_a)
	{
	}

	Color Color::operator*(float scalar)
	{
		return Color(r * scalar, g * scalar, b * scalar, a * scalar);
	}
}