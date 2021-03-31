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

		// enter any initial states
		for (EntityState* state : states)
			state->Enter(*this);
	}

	void Entity::AddFSM(EntityState* initial_state)
	{
		states.push_back(initial_state);
	}

	void Entity::Notify(Command* command)
	{
		// iterate through states
		for (int i = 0; i < states.size(); i++)
		{
			EntityState* state = states[i];
			EntityState* next_state = state->Notify(*this, command);
			if (next_state != nullptr)
			{
				state->Exit(*this);
				delete state;
				next_state->Enter(*this);
				states[i] = next_state;
			}
		}
	}

	void Entity::Update(double dt)
	{
		// iterate through states
		for (int i = 0; i < states.size(); i++)
		{
			EntityState* state = states[i];
			EntityState* next_state = state->Update(*this);
			if (next_state != nullptr)
			{
				state->Exit(*this);
				delete state;
				next_state->Enter(*this);
				states[i] = next_state;
			}
		}
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

	float Entity::FrameTime()
	{
		return (float)gamesession->frame_time;
	}
}