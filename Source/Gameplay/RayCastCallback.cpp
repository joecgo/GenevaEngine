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
  * \file RayCastCallback.cpp
  * \author Joe Goldman
  * \brief RayCastCallback class definition
  *
  **/

#include <Gameplay/RayCastCallback.hpp>

namespace GenevaEngine
{
	RayCastCallback::RayCastCallback()
	{
		bHit = false;
	}

	float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float fraction)
	{
		bHit = true;
		out_fixture = fixture;
		out_point = point;
		out_normal = normal;
		out_fraction = fraction;
		return 0;
	}
}