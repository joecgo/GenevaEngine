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

#include "box2d/box2d.h"

namespace GenevaEngine
{
	class RayCastCallback : public b2RayCastCallback
	{
	public:
		RayCastCallback();
		virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
			float fraction);

		bool bHit;
		b2Fixture* out_fixture = nullptr;
		b2Vec2 out_point;
		b2Vec2 out_normal;
		float out_fraction;
	};
}