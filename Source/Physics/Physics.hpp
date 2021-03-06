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

#include <Physics/Box2d.hpp>
#include <Core/System.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief Physics system. Uses box2d
	 */
	class Physics : public System
	{
	public:
		b2World* GetWorld();

	private:
		// box2d
		const int32 k_velocity_iterations = 6; // setting for constraint solver
		const int32 k_position_iterations = 2; // setting for constraint solver
		b2Vec2 m_gravity = b2Vec2(0, -200.0f);
		b2World m_world = b2World(m_gravity);

		// inherited members, methods, and constructors
		using System::System;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}