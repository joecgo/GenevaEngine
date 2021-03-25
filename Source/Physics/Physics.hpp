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
  * \file Physics.hpp
  * \author Joe Goldman
  * \brief Physics system class declaration
  *
  */

#pragma once

#include <glm/gtc/matrix_transform.hpp> // vec3

#include <vector> // vector
#include <cmath> // signbit
#include <queue> // priority_queue
#include <set> // set

#include <Core/GameCommon.hpp>
#include <Physics/MotionState.hpp>

namespace GenevaEngine
{
	struct CollisionData
	{
		float t;
		Entity* entity_a;
		Entity* entity_b;

		// constructor
		CollisionData(float time, Entity* a, Entity* b) : t(time), entity_a(a), entity_b(b) {}
	};

	/*!
	 *  \brief Physics system
	 */
	class Physics : public ASystem
	{
	public:

	private:
		static constexpr float epsilon = 0.0001f;
		static constexpr float neg_epsilon = -0.0001f;

		const glm::vec3 gravity = glm::vec3(0, -50.0f, 0);

		void InterpolateMotion(float alpha);

		static float Vec3LengthSq(glm::vec3 v);
		static bool Intersect_Sphere_Sphere(
			glm::vec3 a_pos, float a_radius,
			glm::vec3 b_pos, float b_radius);
		static bool Intersect_AABB_AABB(
			glm::vec3 a_pos, glm::vec2 a_rect,
			glm::vec3 b_pos, glm::vec2 b_rect);
		static bool Collision_AABB_AABB(float& t, float dt,
			glm::vec3 a_pos, glm::vec3 a_vel, glm::vec2 a_rect,
			glm::vec3 b_pos, glm::vec3 b_vel, glm::vec2 b_rect);

		// inherited members, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}