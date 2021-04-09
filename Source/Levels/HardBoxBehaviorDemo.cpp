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
 * \file HardBoxBehaviorDemo.cpp
 * \author Joe Goldman
 * \brief HardBoxBehaviorDemo class definition
 *
 **/

#include <Levels/HardBoxBehaviorDemo.hpp>
#include <Core/GameSession.hpp>
#include <Core/Entity.hpp>
#include <Constructs/SingleShape.hpp>
#include <Input/Controller.hpp>

namespace GenevaEngine
{
	void HardBoxBehaviorDemo::Load(GameSession& gs)
	{
		// get world from physics system
		b2World* world = gs.GetPhysics()->GetWorld();

		// create construct
		SingleShape* ground = new SingleShape(world);
		ground->BodyDef.position.Set(0.0f, -10.0f);
		ground->BodyDef.type = b2_staticBody;
		ground->FixtureDef.density = 0.0f;
		ground->Shape.SetAsBox(50.0f, 10.0f);
		// create entity
		Entity* ground_entity = new Entity(&gs, "box");
		ground_entity->AddConstruct(ground);
		ground_entity->SetRenderColor(2);

		// create construct
		SingleShape* hero = new SingleShape(world);
		hero->BodyDef.position.Set(5.0f, 5.0f);
		hero->BodyDef.type = b2_dynamicBody;
		hero->FixtureDef.density = 1.0f;
		hero->FixtureDef.friction = 5.0f;
		hero->Shape.SetAsBox(3.0f, 3.0f);
		hero->EnableBehavior();
		// create entity
		Entity* hero_entity = new Entity(&gs, "hero");
		hero_entity->AddConstruct(hero);
		hero_entity->SetRenderColor(5);
		gs.GetInput()->GetPlayerController()->Possess(hero_entity);

		// create dynamic boxes
		for (size_t i = 0; i < 50; i++)
		{
			// create  construct
			SingleShape* box = new SingleShape(world);
			box->BodyDef.position.Set(0, i * 5.0f);
			box->BodyDef.type = b2_dynamicBody;
			box->FixtureDef.density = 0.01f;
			box->FixtureDef.friction = 0.3f;
			box->Shape.SetAsBox(1.0f, 1.0f);
			// create entity
			Entity* box_entity = new Entity(&gs, "box");
			box_entity->AddConstruct(box);
			box_entity->SetRenderColor(3);
		}
	}
}