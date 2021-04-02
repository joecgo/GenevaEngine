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

	/*!
	 *  Constructor.
	 *
	 *      \param [in] gs
	 *      \param [in] bodyDef
	 *      \param [in] fixtureDef
	 *      \param [in] shapeDef
	 *      \param [in] name
	 */
	Entity::Entity(GameSession* gs, std::string name) :
		m_gameSession(gs),
		Name(name),
		ID(++m_entityCount)
	{
		m_gameSession->AddEntity(this); // add to gamesession entities
	}

	// First call to entity from gamesession
	void Entity::Start()
	{
		Spawn();
	}

	void Entity::Spawn()
	{
		// initialize bodies
		m_multiBody->Initialize();

		// enter any initial states
		for (EntityState* state : m_states)
			state->Enter(*this);
	}

	// Multibody is deleted in End() call of Entity
	void Entity::AddMultiBody(MultiBody* multiBody)
	{
		m_multiBody = multiBody;
	}

	/*!
	 *  Adds a FSM by providing the initial state to the entity
	 *
	 *      \param [in,out] initial_state
	 */
	void Entity::AddFSM(EntityState* initial_state)
	{
		m_states.push_back(initial_state);
	}

	/*!
	 *  Notifies the entity of incoming commands
	 *
	 *      \param [in] command
	 */
	void Entity::Notify(const Command* command)
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

	/*!
	 *  Called every render update. dt is the FrameTime
	 *
	 *      \param [in] dt
	 */
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

	/*!
	 *  Called every physics update. alpha is time between physics steps
	 *
	 *      \param [in] alpha
	 */
	void Entity::FixedUpdate(double alpha)
	{
	}

	/*!
	 *  Ends call for Entity
	 */
	void Entity::End()
	{
		delete m_multiBody;
	}

	/*!
	 *  Sets the entity's render color.
	 *
	 *      \param [in] palette_color_id
	 */
	void Entity::SetRenderColor(int palette_color_id)
	{
		m_render_color = m_gameSession->GetGraphics()->GetPaletteColor(palette_color_id);
	}

	/*!
	 *  Sets the entity's render color.
	 *
	 *      \param [in] color
	 */
	void Entity::SetRenderColor(Color color)
	{
		m_render_color = color;
	}

	/*!
	 *  Returns the entity's render color.
	 *
	 *      \return The render color.
	 */
	Color Entity::GetRenderColor() const
	{
		return m_render_color;
	}

	/*!
	 *  Amount of time between frames being rendered
	 *
	 *      \return frame time
	 */
	float Entity::FrameTime()
	{
		return (float)m_gameSession->FrameTime;
	}

	b2World* Entity::GetWorld()
	{
		return m_multiBody->GetWorld();
	};

	b2PolygonShape Entity::GetShape()
	{
		return m_multiBody->GetShape();
	}

	b2Body* Entity::GetAnchorBody()
	{
		return m_multiBody->GetAnchorBody();
	}
}