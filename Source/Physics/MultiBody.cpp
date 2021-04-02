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
  * \file MultiBody.cpp
  * \author Joe Goldman
  * \brief MultiBody class definition
  *
  **/

#include <Physics/MultiBody.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief Should only be called by Entity that owns this MultiBody on Spawning the Entity
	 */
	void MultiBody::Initialize()
	{
		// warning for existing body
		if (m_anchorBody != nullptr)
		{
			std::cout << "Warning - MultiBody::Initialize - Body is already spawned" << std::endl;
			return;
		}

		// spawn
		// todo: looseBodies
		m_anchorBody = m_world->CreateBody(&m_anchorBodyDef);
		m_fixtureDef.shape = &m_shapeDef;
		m_anchorBody->CreateFixture(&m_fixtureDef);
	}

	void MultiBody::SetWorld(b2World* world)
	{
		m_world = world;
	}

	void MultiBody::SetPolygonShape(b2PolygonShape shapeDef, b2FixtureDef fixtureDef)
	{
		m_shapeDef = shapeDef;
		m_fixtureDef = fixtureDef;
	}

	void MultiBody::AddBody(b2BodyDef bodyDef, bool isAnchor)
	{
		if (isAnchor)
			m_anchorBodyDef = bodyDef;
		else
			m_looseBodyDefs.push_back(bodyDef);
	}

	b2World* MultiBody::GetWorld()
	{
		return m_world;
	}

	b2PolygonShape MultiBody::GetShape()
	{
		return m_shapeDef;
	}

	b2Body* MultiBody::GetAnchorBody()
	{
		return m_anchorBody;
	}
}