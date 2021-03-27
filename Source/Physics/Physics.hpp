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

  // Disable warning messages from box2d: C26812 C26495
#pragma warning( disable : 26812 26495)

#include <box2d/box2d.h> // box2d
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

	private:
		// box2d
		const b2Vec2 gravity = b2Vec2(0, -10.0f);
		b2World b2_world = b2World(gravity);

		// inherited members, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}