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
			if (entity->stationary) continue;

			entity->previous_state = entity->current_state;
			MotionState* state = &(entity->current_state);

			// acceleration (sum forces)
			glm::vec3 acceleration = entity->impulse * entity->mass;
			if (entity->use_gravity)
				acceleration += gravity;
			entity->impulse = glm::vec3();

			state->velocity += acceleration * (float)dt;		// velocity
			state->position += state->velocity * (float)dt;		// position
		}

		// collision checks
		for (Entity* entity : gamesession->entities)
		{
			if (!entity->rigid || entity->stationary) continue;

			for (Entity* other : gamesession->entities)
			{
				if (!other->rigid) continue;
				if (entity == other) continue;

				if (Intersect_Rect_Rect(
					entity->current_state.position,
					entity->rect_collider,
					other->current_state.position,
					other->rect_collider))
				{
					// resolve collision
					entity->current_state = entity->previous_state;
					entity->current_state.velocity = glm::vec3();
				}
			}
		}
	}

	void Physics::InterpolateMotion(float alpha)
	{
		for (Entity* entity : gamesession->entities)
		{
			if (entity->stationary) continue;

			entity->interpolated_state.position =
				entity->current_state.position * alpha +
				entity->previous_state.position * (1.0f - alpha);

			entity->interpolated_state.velocity =
				entity->current_state.velocity * alpha +
				entity->previous_state.velocity * (1.0f - alpha);
		}
	}

	bool Physics::Intersect_Rect_Rect(
		glm::vec3 a_pos, glm::vec2 a_rect,
		glm::vec3 b_pos, glm::vec2 b_rect)
	{
		return (glm::abs(a_pos.x - b_pos.x) * 2.0f < (a_rect.x + b_rect.x)) &&
			(glm::abs(a_pos.y - b_pos.y) * 2.0f < (a_rect.y + a_rect.y));
	}

	bool Physics::Intersect_Sphere_Sphere(
		glm::vec3 a_pos, float a_radius,
		glm::vec3 b_pos, float b_radius)
	{
		float rSum = a_radius + b_radius;
		float rSumSq = rSum * rSum;
		float distSq = Vec3LengthSq(a_pos - b_pos);
		return rSumSq < distSq;
	}

	float Physics::Vec3LengthSq(glm::vec3 v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
}