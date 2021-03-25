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
	// for sorting by t
	bool operator<(const CollisionData& a, const CollisionData& b)
	{
		return a.t > b.t; // flipped > so lowest value is prioritized
	}

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
		std::priority_queue<CollisionData> collisions;
		std::set<Entity*> objs;
		for (Entity* entity : gamesession->entities)
		{
			if (entity->stationary || !entity->rigid) continue;
			objs.insert(entity);
		}

		do
		{ // while collisions is not empty
			if (!collisions.empty())
			{
				CollisionData col = collisions.top();
				collisions = std::priority_queue<CollisionData>();

				// resolve collision
				// entity a
				col.entity_a->current_state =
					col.entity_a->current_state * col.t +
					col.entity_a->previous_state * (1.0f - col.t);
				col.entity_a->current_state.velocity = glm::vec3(0, 0, 0);
				col.entity_a->previous_state = col.entity_a->current_state;
				objs.erase(col.entity_a);

				// entity b
				if (!col.entity_b->stationary)
				{
					col.entity_b->current_state =
						col.entity_b->current_state * col.t +
						col.entity_b->previous_state * (1.0f - col.t);
					col.entity_b->current_state.velocity = glm::vec3(0, 0, 0);
					col.entity_b->previous_state = col.entity_b->current_state;

					objs.erase(col.entity_b);
				}
			}

			for (Entity* entity : objs)
			{
				for (Entity* other : gamesession->entities)
				{
					if (!other->rigid || entity == other) continue;

					float t = 0;
					if (Collision_AABB_AABB(t, (float)dt,
						entity->previous_state.position + entity->collider_offset,
						entity->current_state.velocity,
						entity->rect_collider,
						other->previous_state.position + other->collider_offset,
						other->current_state.velocity,
						other->rect_collider))
					{
						// save resolution
						collisions.push(CollisionData(t, entity, other));
					}
				}
			}
		} while (!collisions.empty());
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
		return (glm::abs(a_pos.x - b_pos.x) * 2.0f <= (a_rect.x + b_rect.x + epsilon)) &&
			(glm::abs(a_pos.y - b_pos.y) * 2.0f <= (a_rect.y + b_rect.y + epsilon));
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

	bool Physics::Collision_AABB_AABB(float& t, float dt,
		glm::vec3 a_pos, glm::vec3 a_vel, glm::vec2 a_rect,
		glm::vec3 b_pos, glm::vec3 b_vel, glm::vec2 b_rect)
	{
		t = 2.0f; // default value for no collision

		// get bounds of AABBs from position and xy extends
		float a_top = a_pos.y + 0.5f * a_rect.y;
		float a_bottom = a_pos.y - 0.5f * a_rect.y;
		float b_top = b_pos.y + 0.5f * b_rect.y;
		float b_bottom = b_pos.y - 0.5f * b_rect.y;
		float a_right = a_pos.x + 0.5f * a_rect.x;
		float a_left = a_pos.x - 0.5f * a_rect.x;
		float b_right = b_pos.x + 0.5f * b_rect.x;
		float b_left = b_pos.x - 0.5f * b_rect.x;

		// calculate possible solutions for t (smallest value between 0 and dt)
		float t1 = 0, t2 = 0;
		glm::vec3 approach_vel = a_vel - b_vel;
		if (Vec3LengthSq(approach_vel) == 0) return false;				  // no approaching vel
		if (approach_vel.y < 0) t1 = (b_top - a_bottom) / approach_vel.y; // approaching b_top
		else					t1 = (b_bottom - a_top) / approach_vel.y; // approaching b_bottom
		if (approach_vel.x < 0) t2 = (b_right - a_left) / approach_vel.x; // approaching b_right
		else					t2 = (b_left - a_right) / approach_vel.x; // approaching b_left

		// logic for saving the correct solution to t
		if (t1 > neg_epsilon && t1 < dt + epsilon &&
			Intersect_AABB_AABB(a_pos + a_vel * t1, a_rect, b_pos + b_vel * t1, b_rect))
			t = t1;
		if (t2 > neg_epsilon && t2 < dt + epsilon && t2 < t1 &&
			Intersect_AABB_AABB(a_pos + a_vel * t2, a_rect, b_pos + b_vel * t2, b_rect))
			t = t2;

		// scale by 1/dt to a 0 - 1 value
		t /= dt;

		// return true if collision: 0 < t < 1
		return (t > neg_epsilon && t < 1.0f + epsilon);
	}
}