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
	Color::Color(int hexValue, float alpha) :
		r(((hexValue >> 16) & 0xFF) / 255.0f),
		g(((hexValue >> 8) & 0xFF) / 255.0f),
		b(((hexValue) & 0xFF) / 255.0f),
		a(alpha)
	{
	}

	/*!
	 *  Constructor.
	 *
	 *      \param [in] red
	 *      \param [in] green
	 *      \param [in] blue
	 *      \param [in] alpha
	 */
	Color::Color(float red, float green, float blue, float alpha) :
		r(red), g(green), b(blue), a(alpha)
	{
	}

	/*!
	 *  multiply color by scalar
	 *
	 *      \param [in] scalar
	 *
	 *      \return
	 */
	Color Color::operator*(float scalar) const
	{
		return Color(r * scalar, g * scalar, b * scalar, a * scalar);
	}
}