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
	int Entity::m_entityCount = 0;

	Entity::Entity(GameSession* gs, b2BodyDef bodyDef, b2FixtureDef fixtureDef,
		b2PolygonShape shapeDef, std::string name) :
		m_gameSession(gs),
		m_bodyDef(bodyDef),
		m_fixtureDef(fixtureDef),
		m_shapeDef(shapeDef),
		Name(name),
		ID(++m_entityCount),
		m_world(gs->GetWorld())
	{
		m_gameSession->AddEntity(this); // add to gamesession entities
	}

	void Entity::Start()
	{
		Spawn();
	}

	void Entity::Spawn()
	{
		// error check for existing body
		if (m_body != nullptr)
		{
			std::cout << "Error - Entity::Spawn - Entity is already spawned" << std::endl;
			return;
		}

		// spawn
		m_body = m_world->CreateBody(&m_bodyDef);
		m_fixtureDef.shape = &m_shapeDef;
		m_body->CreateFixture(&m_fixtureDef);

		// enter any initial states
		for (EntityState* state : m_states)
			state->Enter(*this);
	}

	void Entity::AddFSM(EntityState* initial_state)
	{
		m_states.push_back(initial_state);
	}

	void Entity::Notify(Command* command)
	{
		// iterate through states
		for (int i = 0; i < m_states.size(); i++)
		{
			EntityState* state = m_states[i];
			EntityState* next_state = state->Notify(*this, command);
			if (next_state != nullptr)
			{
				state->Exit(*this);
				delete state;
				next_state->Enter(*this);
				m_states[i] = next_state;
			}
		}
	}

	void Entity::Update(double dt)
	{
		// iterate through states
		for (int i = 0; i < m_states.size(); i++)
		{
			EntityState* state = m_states[i];
			EntityState* next_state = state->Update(*this);
			if (next_state != nullptr)
			{
				state->Exit(*this);
				delete state;
				next_state->Enter(*this);
				m_states[i] = next_state;
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
		m_render_color = m_gameSession->GetGraphics()->GetPaletteColor(palette_color_id);
	}

	void Entity::SetRenderColor(Color color)
	{
		m_render_color = color;
	}

	Color Entity::GetRenderColor() const
	{
		return m_render_color;
	}

	float Entity::FrameTime()
	{
		return (float)m_gameSession->FrameTime;
	}
}