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
	/*!
	 *  Sets horizontal velocity
	 *
	 *      \param [in,out] entity
	 *      \param [in]     x_axis
	 *      \param [in]     moveSpeed
	 */
	void EntityBehavior::Move(Entity& entity, float x_axis, float moveSpeed)
	{
		b2Body* body = entity.GetAnchorBody();
		const float dt = entity.FrameTime();

		b2Vec2 vel = body->GetLinearVelocity();
		if (x_axis > 0)
			vel.x = moveSpeed * dt;
		else if (x_axis < 0)
			vel.x = -1.0f * moveSpeed * dt;
		body->SetLinearVelocity(vel);
	}

	/*!
	 *  Jump via a great upward force
	 *
	 *      \param [in,out] entity
	 *      \param [in]     jumpPower
	 */
	void EntityBehavior::Jump(Entity& entity, float jumpPower)
	{
		b2Body* body = entity.GetAnchorBody();
		b2Vec2 force(0, body->GetMass() * jumpPower);
		body->ApplyLinearImpulseToCenter(force, true);
	}
}