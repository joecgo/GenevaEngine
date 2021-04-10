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
  * \file SoftBoxDemo.cpp
  * \author Joe Goldman
  * \brief SoftBoxDemo level
  *
  **/

#include <Levels/SoftBoxDemo.hpp>
#include <Core/GameSession.hpp>
#include <Core/Entity.hpp>
#include <Constructs/SingleShape.hpp>
#include <Input/Controller.hpp>
#include <Constructs/SoftBox.hpp>

namespace GenevaEngine
{
	void SoftBoxDemo::Load(GameSession& gs)
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
		hero->BodyDef.linearDamping = 0.1f;
		hero->FixtureDef.density = 1.0f;
		hero->FixtureDef.friction = 3.0f;
		hero->Shape.SetAsBox(3.0f, 3.0f);
		hero->EnableBehavior();
		// create entity
		Entity* hero_entity = new Entity(&gs, "hero");
		hero_entity->AddConstruct(hero);
		hero_entity->SetRenderColor(5);
		gs.GetInput()->GetPlayerController()->Possess(hero_entity);

		// create construct
		SoftBox* softbox = new SoftBox(world);
		// create entity
		Entity* softbox_entity = new Entity(&gs, "softbox");
		softbox_entity->AddConstruct(softbox);
		softbox_entity->SetRenderColor(3);
	}
}