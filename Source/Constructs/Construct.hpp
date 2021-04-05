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
  * \file Construct.hpp
  * \author Joe Goldman
  * \brief Base construct class declaration
  *
  */

#pragma once

#include <Physics/Box2d.hpp>

#include <list> //list
#include <vector> // vector

namespace GenevaEngine
{
	class Command;

	enum class ConstructQuery { IsGrounded };
	enum class ExistanceState { Standby, Created };

	struct BodyRenderData
	{
		b2Body* Body = nullptr;
		b2PolygonShape Shape;
	};

	class Construct
	{
	public:
		Construct(b2World* world);
		void SetWorld(b2World* world);
		b2World* GetWorld();
		// return a list of body render data for rendering all the verts in graphics system
		std::list<BodyRenderData>* GetConstructRenderData();

	protected:
		// currenty state this object is not Created twice
		ExistanceState m_state = ExistanceState::Standby;
		// reference to b2World object
		b2World* m_world = nullptr;
		// collection of data for graphics to use for rendering
		std::list<BodyRenderData> m_constructRenderData;

		// private methods
		void SafeCreate();							// does a safety check then calls Create()
		virtual void Notify(const Command* command) = 0;
		virtual void Create() = 0;
		virtual void Start() = 0;					// called once before first update
		virtual void FixedUpdate(double alpha) = 0;	// called on fixed physics time-steps
		virtual void Update(double dt) = 0;			// called on every rendered frame
		virtual void End() = 0;						// called once after last update
		friend class Entity;
	};
}