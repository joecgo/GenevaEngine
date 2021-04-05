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
  * \file RayCastCallback.hpp
  * \author Joe Goldman
  * \brief RayCastCallback class declaration
  *
  */

#pragma once

#include <Physics/Box2d.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief implement box2d's abstract RayCast class
	 */
	class RayCastCallback : public b2RayCastCallback
	{
	public:
		RayCastCallback();
		virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
			float fraction);

		bool Hit = false;
		b2Fixture* Fixture = nullptr;
		b2Vec2 Point;
		b2Vec2 Normal;
		float Fraction;
	};
}