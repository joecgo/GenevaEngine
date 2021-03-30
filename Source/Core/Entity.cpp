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
  * \file Entity.cpp
  * \author Joe Goldman
  * \brief Entity class definition
  *
  **/

#include <Core/GameCommon.hpp>

using namespace std;
namespace GenevaEngine
{
	// static members
	int Entity::entity_count = 0;

	Entity::Entity(GameSession* gs, b2BodyDef arg_body_def, b2FixtureDef arg_fixture_def,
		b2PolygonShape arg_shape_def, std::string arg_name) :
		gamesession(gs),
		body_def(arg_body_def),
		fixture_def(arg_fixture_def),
		shape_def(arg_shape_def),
		name(arg_name),
		id(++entity_count),
		world(gs->GetWorld())
	{
		gamesession->AddEntity(this); // add to gamesession entities
	}

	void Entity::Start()
	{
		Spawn();
	}

	void Entity::Spawn()
	{
		// error check for existing body
		if (body != nullptr)
		{
			std::cout << "Error - Entity::Spawn - Entity is already spawned" << std::endl;
			return;
		}

		// spawn
		body = world->CreateBody(&body_def);
		fixture_def.shape = &shape_def;
		body->CreateFixture(&fixture_def);
	}

	void Entity::Update(double dt)
	{
	}

	void Entity::FixedUpdate(double alpha)
	{
	}

	void Entity::End()
	{
	}

	void Entity::SetRenderColor(int palette_color_id)
	{
		render_color = gamesession->graphics->GetPaletteColor(palette_color_id);
	}

	void Entity::SetRenderColor(Color color)
	{
		render_color = color;
	}

	Color Entity::GetRenderColor() const
	{
		return render_color;
	}

	void Entity::Jump()
	{
		b2Vec2 force(0, body->GetMass() * 50.0f);
		body->ApplyLinearImpulseToCenter(force, true);
	}

	void Entity::Move(float x)
	{
		float dt = FrameTime();
		b2Vec2 vel = body->GetLinearVelocity();
		if (x > 0)
			vel.x = 2000.0f * dt;
		else if (x < 0)
			vel.x = -2000.0f * dt;
		body->SetLinearVelocity(vel);
		std::cout << x << std::endl;
	}

	float Entity::FrameTime()
	{
		return (float)gamesession->frame_time;
	}
}