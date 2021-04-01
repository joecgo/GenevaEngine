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
  * \file EntityBehavior.cpp
  * \author Joe Goldman
  * \brief EntityBehavior class definition
  *
  **/

#include <Gameplay/EntityBehavior.hpp>

namespace GenevaEngine
{
	void EntityBehavior::Move(Entity& entity, float x_axis, float move_speed)
	{
		b2Body* body = entity.GetBody();
		const float dt = entity.FrameTime();

		b2Vec2 vel = body->GetLinearVelocity();
		if (x_axis > 0)
			vel.x = move_speed * dt;
		else if (x_axis < 0)
			vel.x = -1.0f * move_speed * dt;
		body->SetLinearVelocity(vel);
	}

	void EntityBehavior::Jump(Entity& entity, float jump_power)
	{
		b2Body* body = entity.GetBody();
		b2Vec2 force(0, body->GetMass() * jump_power);
		body->ApplyLinearImpulseToCenter(force, true);
	}
}