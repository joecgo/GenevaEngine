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
#include <list> // list
#include <cmath> // signbit

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief Physics system
	 */
	class Physics : public ASystem
	{
	public:
		void SaveBodyDef(std::string name, b2BodyDef bodyDef);
		b2BodyDef GetBodyDef(std::string name);
		b2World* GetWorld();

	private:
		// box2d
		const int32 velocity_iterations = 6; // setting for constraint solver
		const int32 position_iterations = 2; // setting for constraint solver
		const b2Vec2 gravity = b2Vec2(0, -10.0f);
		b2World world = b2World(gravity);
		std::map<std::string, b2BodyDef> body_defs; // save BodyDef's for reuse

		// inherited members, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}