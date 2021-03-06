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
  * \file SingleShape.cpp
  * \author Joe Goldman
  * \brief SingleShape class definition
  *
  **/

#include <Constructs/SingleShape.hpp>
#include <Gameplay/SingleShapeBehavior.hpp>
#include <Core/GameSession.hpp>

namespace GenevaEngine
{
	void SingleShape::Notify(const Command* command)
	{
		if (m_state == nullptr) return;

		State<SingleShape>* next_state = m_state->Notify(this, command);
		if (next_state != nullptr)
		{
			m_state->Exit(this);
			delete m_state;
			next_state->Enter(this);
			m_state = next_state;
		}
	}

	void SingleShape::Create()
	{
		// create body
		m_body = m_world->CreateBody(&BodyDef);
		FixtureDef.shape = &Shape;
		m_body->CreateFixture(&FixtureDef);

		// add body and shape to render data
		BodyRenderData brData;
		brData.Body = m_body;
		m_renderData.BodyRenderList.push_back(brData);
	}

	b2Body* SingleShape::GetBody()
	{
		return m_body;
	}

	void SingleShape::EnableBehavior()
	{
		if (m_state == nullptr)
		{
			m_state = new Grounded_SingleShape();
		}
	}

	void SingleShape::Start()
	{
	}

	void SingleShape::FixedUpdate(double alpha)
	{
		if (m_state == nullptr) return;

		State<SingleShape>* next_state = m_state->Update(this, alpha);
		if (next_state != nullptr)
		{
			m_state->Exit(this);
			delete m_state;
			next_state->Enter(this);
			m_state = next_state;
		}
	}

	void SingleShape::Update(double dt)
	{
	}

	void SingleShape::End()
	{
		if (m_state != nullptr)
			delete m_state;
	}
}