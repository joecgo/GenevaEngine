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
 * \file WebDemo.cpp
 * \author Joe Goldman
 * \brief WebDemo class definition
 *
 **/

#include <Levels/WebDemo.hpp>
#include <Core/GameSession.hpp>
#include <Constructs/Web.hpp>
#include <Core/Entity.hpp>

namespace GenevaEngine
{
	void WebDemo::Load(GameSession& gs)
	{
		// get world from physics system
		b2World* world = gs.GetPhysics()->GetWorld();

		// create entity
		Entity* web_entity = new Entity(&gs, "web");
		web_entity->AddConstruct(new Web(world));
		web_entity->SetRenderColor(5);
	}
}