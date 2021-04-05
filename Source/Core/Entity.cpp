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

#include <Core/Entity.hpp>
#include <Core/GameSession.hpp>
#include <Physics/Box2d.hpp>
#include <Physics/Construct.hpp>

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

	Construct* Entity::GetConstruct()
	{
		return m_construct;
	}

	void Entity::Spawn()
	{
		// initialize bodies
		if (m_construct != nullptr)
			m_construct->SafeCreate();
	}

	// Add a composite of box2d objects and properties
	void Entity::AddConstruct(Construct* construct)
	{
		// TODO: allow for an entity to have multiple constructs
		if (m_construct != nullptr)
			delete m_construct;

		m_construct = construct;
	}

	/*!
	 *  Notifies the entity of incoming commands
	 *
	 *      \param [in] command
	 */
	void Entity::Notify(const Command* command)
	{
		if (m_construct != nullptr)
			m_construct->Notify(command);
	}

	/*!
	 *  Called every render update. dt is the FrameTime
	 *
	 *      \param [in] dt
	 */
	void Entity::Update(double dt)
	{
		if (m_construct != nullptr)
			m_construct->Update(dt);
	}

	/*!
	 *  Called every physics update. alpha is time between physics steps
	 *
	 *      \param [in] alpha
	 */
	void Entity::FixedUpdate(double alpha)
	{
		if (m_construct != nullptr)
			m_construct->FixedUpdate(alpha);
	}

	/*!
	 *  Entity is being removed from the game.
	 *  Clean up pointers and memory that belongs to the Entity
	 */
	void Entity::End()
	{
		// construct clean up
		if (m_construct != nullptr)
		{
			m_construct->End();
			delete m_construct;
			m_construct = nullptr;
		}
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
}