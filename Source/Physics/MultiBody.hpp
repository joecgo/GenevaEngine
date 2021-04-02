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
  * \file MultiBody.hpp
  * \author Joe Goldman
  * \brief MultiBody class declaration
  *
  */

#pragma once

#include <box2d/box2d.h>

#include <list> //list
#include <iostream> // cout

namespace GenevaEngine
{
	class Entity;

	class MultiBody
	{
	public:
		void Initialize(); // only entity should call this
		void SetWorld(b2World* world);
		void SetPolygonShape(b2PolygonShape shapeDef, b2FixtureDef fixtureDef);
		void AddBody(b2BodyDef bodyDef, bool isAnchor = false);
		b2World* GetWorld();
		b2PolygonShape GetShape();
		b2Body* GetAnchorBody();

	private:
		b2World* m_world = nullptr;
		b2Body* m_anchorBody = nullptr;
		std::list<b2Body*> m_bodies;
		b2BodyDef m_anchorBodyDef;
		std::list<b2BodyDef> m_looseBodyDefs;
		b2PolygonShape m_shapeDef;
		b2FixtureDef m_fixtureDef;

		friend Entity;
	};
}