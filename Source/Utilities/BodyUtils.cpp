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
  * \file BodyUtils.cpp
  * \author Joe Goldman
  * \brief BodyUtils class definition. Utilities related to b2Body
  *
  **/

#include <Utilities/BodyUtils.hpp>
#include <iostream>

namespace GenevaEngine
{
	float BodyUtils::GetHalfHeight(const b2Body& body)
	{
		return body.GetFixtureList()->GetAABB(0).GetExtents().y;
	}
}