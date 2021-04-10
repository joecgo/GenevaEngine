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
  * \file BodyUtils.hpp
  * \author Joe Goldman
  * \brief BodyUtils class declaration. Utilities related to b2Body
  *
  */

#pragma once

#include <Physics/Box2d.hpp>

namespace GenevaEngine
{
	class BodyUtils
	{
	public:
		static float GetHalfHeight(const b2Body& body);
	};
}