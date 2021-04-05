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
  * \file SingleShape.hpp
  * \author Joe Goldman
  * \brief SingleShape class declaration
  *
  */

#pragma once

#include <Constructs/Construct.hpp>
#include <Core/State.hpp>

namespace GenevaEngine
{
	class SingleShape : public Construct
	{
	public:
		using Construct::Construct;

		// Attributes, define these before creation
		b2FixtureDef FixtureDef;
		b2PolygonShape Shape;
		b2BodyDef BodyDef;

		b2Body* GetBody();
		void EnableBehavior();

	private:
		b2Body* m_body = nullptr;
		State<SingleShape>* m_state = nullptr;

		void Notify(const Command* command);
		void Create();
		void Start();					// called once before first update
		void FixedUpdate(double alpha);	// called on fixed physics time-steps
		void Update(double dt);			// called on every rendered frame
		void End();						// called once after last update
		friend class Entity;
	};
}