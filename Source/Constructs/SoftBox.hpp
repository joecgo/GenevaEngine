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
  * \file SoftBox.hpp
  * \author Joe Goldman
  * \brief SoftBox construct class declaration
  *
  */

#pragma once

#include <Constructs/Construct.hpp>
#include <Core/State.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief SoftBox system
	 */
	class SoftBox : public Construct
	{
	public:
		// Construct(b2World* world) : m_world(world)
		using Construct::Construct;

		// Creation Attributes, Define these before creation

		// Public Methods
		b2Body& GetCenterBody();
		void EnableBehavior();

	private:
		// Private members
		b2Body* m_centerBody = nullptr;
		State<SoftBox>* m_state = nullptr;
		b2Body* m_bodies[5];
		b2Joint* m_joints[8];

		// Private Methods
		void HandleStateTransitions(State<SoftBox>* nextState);

		// Construct virtual functions, used by Entity
		void Create();
		void Start();					// called once before first update
		void FixedUpdate(double alpha);	// called on fixed physics time-steps
		void Update(double dt);			// called on every rendered frame
		void End();						// called once after last update
		void Notify(const Command* command);
		friend class Entity;
	};
}