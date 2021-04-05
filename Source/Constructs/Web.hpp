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
  * \file Web.hpp
  * \author Joe Goldman
  * \brief Web class declaration
  *
  */

#pragma once

#include <Constructs/Construct.hpp>
#include <Core/State.hpp>

namespace GenevaEngine
{
	class Web : public Construct
	{
	public:
		// Construct(b2World* world) : m_world(world)
		using Construct::Construct;

		// Creation Attributes, Define these before creation

		// Public Methods
		void EnableBehavior();

	private:
		// Private Members
		State<Web>* m_state = nullptr;
		b2Body* m_bodies[4];
		b2Joint* m_joints[8];

		// Private Methods
		void HandleStateTransitions(State<Web>* nextState);

		// Construct virtual functions, used by Entity
		void Notify(const Command* command);
		void Create();
		void Start();					// called once before first update
		void FixedUpdate(double alpha);	// called on fixed physics time-steps
		void Update(double dt);			// called on every rendered frame
		void End();						// called once after last update
		friend class Entity;
	};
}