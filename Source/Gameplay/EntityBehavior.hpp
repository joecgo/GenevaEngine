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
  * \file EntityBehavior.hpp
  * \author Joe Goldman
  * \brief EntityBehavior class declaration.
  *
  */

#pragma once

#include <Core/Entity.hpp>

namespace GenevaEngine
{
	class EntityBehavior
	{
	public:
		static void Move(Entity& entity, float x_axis, float moveSpeed = 2000.0f);
		static void Jump(Entity& entity, float jumpPower = 150.0f);
	};
}