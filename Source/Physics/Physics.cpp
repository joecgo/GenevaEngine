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
			if (!entity->rigid) continue;

			for (Entity* other : gamesession->entities)
			{
				if (!other->rigid) continue;
				if (entity == other) continue;

				float t = 0;
				if (Collision_AABB_AABB(t, entity->previous_state, entity->rect_collider,
					other->current_state, other->rect_collider))
				{
					// resolve collision
					entity->current_state =
						entity->current_state * t +
						entity->previous_state * (1.0f - t);
					entity->current_state.velocity = glm::vec3(0, 0, 0);
				}
			}
		}
	}

	void Physics::InterpolateMotion(float alpha)
	{
		for (Entity* entity : gamesession->entities)
		{
			if (entity->stationary) continue;

			entity->interpolated_state =
				entity->current_state * alpha +
				entity->previous_state * (1.0f - alpha);
		}
	}

	bool Physics::Intersect_AABB_AABB(
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

	bool Physics::Collision_AABB_AABB(float& t,
		MotionState a_state, glm::vec2 a_rect,
		MotionState b_state, glm::vec2 b_rect)
	{
		t = 2.0f; // default value for no collision

		// get bounds of AABBs
		float a_maxY = a_state.position.y + 0.5f * a_rect.y;
		float a_minY = a_state.position.y - 0.5f * a_rect.y;
		float b_maxY = b_state.position.y + 0.5f * b_rect.y;
		float b_minY = b_state.position.y - 0.5f * b_rect.y;
		float a_maxX = a_state.position.x + 0.5f * a_rect.x;
		float a_minX = a_state.position.x - 0.5f * a_rect.x;
		float b_maxX = b_state.position.x + 0.5f * b_rect.x;
		float b_minX = b_state.position.x - 0.5f * b_rect.x;

		// calculate possible solutions for t (smallest value between 0 - 0.01)
		float t1 = (b_maxY - a_minY) / (a_state.velocity.y - b_state.velocity.y);
		//float t2 = (a_maxY - b_minY) / (a_state.velocity.y - b_state.velocity.y);
		//float t3 = b_maxX - a_minX / (a_state.velocity.x - b_state.velocity.x)*-1.0;
		//float t4 = a_maxX - b_minX / (b_state.velocity.x - a_state.velocity.x)*-1.0;

		// logic for saving the correct solution to t
		if (!isinf(t1) && t1 >= 0 && t1 <= 0.01f) t = t1 * 100.0f;
		//if (!isinf(t2) && t2 >= 0 && t2 <= 0.01f && t2 < t) t = t2 * 100.0f;
		//if (t3 >= 0 && t3 <= 1.0f && t3 < t) t = t3;
		//if (t4 >= 0 && t4 <= 1.0f && t4 < t) t = t4;

		if (t != 2.0f)
		{
			std::cout << "HERE" << std::endl;
		}
		return t != 2.0f; // return true if collision: 0 < t < 1
	}
}