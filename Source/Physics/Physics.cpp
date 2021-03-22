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
  * \file Physics.cpp
  * \author Joe Goldman
  * \brief Physics system class definition
  *
  **/

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	void Physics::Start()
	{
	}

	void Physics::End()
	{
	}

	void Physics::Update(double dt)
	{
		for (Entity* entity : gamesession->entities)
		{
			entity->previous_state = entity->current_state;
			MotionState* state = &(entity->current_state);
			state->acceleration += entity->impulse * entity->mass;		// acceleration
			entity->impulse = glm::vec3();
			if (entity->use_gravity)
				state->velocity += gravity * (float)dt;					// gravity
			state->velocity += state->acceleration * (float)dt;			// velocity
			state->position += state->velocity * (float)dt;				// position
		}
	}

	void Physics::InterpolateMotion(float alpha)
	{
		for (Entity* entity : gamesession->entities)
		{
			entity->interpolated_state.position =
				entity->current_state.position * alpha +
				entity->previous_state.position * (1.0f - alpha);

			entity->interpolated_state.velocity =
				entity->current_state.velocity * alpha +
				entity->previous_state.velocity * (1.0f - alpha);

			entity->interpolated_state.acceleration =
				entity->current_state.acceleration * alpha +
				entity->previous_state.acceleration * (1.0f - alpha);
		}
	}
}