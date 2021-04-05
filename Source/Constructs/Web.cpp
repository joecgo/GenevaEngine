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
  * \file Web.cpp
  * \author Joe Goldman
  * \brief Web construct class definition
  *
  **/

#include <Constructs/Web.hpp>

namespace GenevaEngine
{
	void Web::Create()
	{
		b2Body* ground = nullptr;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);

			// BodyRenderData brData;
			// brData.Body = ground;
			// brData.Shape = shape;
			// m_constructRenderData.push_back(brData);
		}

		{
			b2PolygonShape shape;
			b2PolygonShape shapes[4];
			shape.SetAsBox(0.5f, 0.5f);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			bd.position.Set(-5.0f, 5.0f);
			m_bodies[0] = m_world->CreateBody(&bd);
			m_bodies[0]->CreateFixture(&shape, 5.0f);
			shapes[0] = shape;

			bd.position.Set(5.0f, 5.0f);
			m_bodies[1] = m_world->CreateBody(&bd);
			m_bodies[1]->CreateFixture(&shape, 5.0f);
			shapes[1] = shape;

			bd.position.Set(5.0f, 15.0f);
			m_bodies[2] = m_world->CreateBody(&bd);
			m_bodies[2]->CreateFixture(&shape, 5.0f);
			shapes[2] = shape;

			bd.position.Set(-5.0f, 15.0f);
			m_bodies[3] = m_world->CreateBody(&bd);
			m_bodies[3]->CreateFixture(&shape, 5.0f);
			shapes[3] = shape;

			// add bodies and shapes to render data
			for (int i = 0; i < 4; i++)
			{
				BodyRenderData brData;
				brData.Body = m_bodies[i];
				brData.Shape = shapes[i];
				m_constructRenderData.push_back(brData);
			}

			b2DistanceJointDef jd;
			b2Vec2 p1, p2, d;

			float frequencyHz = 2.0f;
			float dampingRatio = 0.0f;

			jd.bodyA = ground;
			jd.bodyB = m_bodies[0];
			jd.localAnchorA.Set(-10.0f, 0.0f);
			jd.localAnchorB.Set(-0.5f, -0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[0] = m_world->CreateJoint(&jd);

			jd.bodyA = ground;
			jd.bodyB = m_bodies[1];
			jd.localAnchorA.Set(10.0f, 0.0f);
			jd.localAnchorB.Set(0.5f, -0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[1] = m_world->CreateJoint(&jd);

			jd.bodyA = ground;
			jd.bodyB = m_bodies[2];
			jd.localAnchorA.Set(10.0f, 20.0f);
			jd.localAnchorB.Set(0.5f, 0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[2] = m_world->CreateJoint(&jd);

			jd.bodyA = ground;
			jd.bodyB = m_bodies[3];
			jd.localAnchorA.Set(-10.0f, 20.0f);
			jd.localAnchorB.Set(-0.5f, 0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[3] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[0];
			jd.bodyB = m_bodies[1];
			jd.localAnchorA.Set(0.5f, 0.0f);
			jd.localAnchorB.Set(-0.5f, 0.0f);;
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[4] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[1];
			jd.bodyB = m_bodies[2];
			jd.localAnchorA.Set(0.0f, 0.5f);
			jd.localAnchorB.Set(0.0f, -0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[5] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[2];
			jd.bodyB = m_bodies[3];
			jd.localAnchorA.Set(-0.5f, 0.0f);
			jd.localAnchorB.Set(0.5f, 0.0f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[6] = m_world->CreateJoint(&jd);

			jd.bodyA = m_bodies[3];
			jd.bodyB = m_bodies[0];
			jd.localAnchorA.Set(0.0f, -0.5f);
			jd.localAnchorB.Set(0.0f, 0.5f);
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
			m_joints[7] = m_world->CreateJoint(&jd);
		}
	}

	void Web::Start()
	{
	}

	void Web::FixedUpdate(double alpha)
	{
	}

	void Web::Update(double dt)
	{
		// run a step in the state machine
		if (m_state != nullptr)
			HandleStateTransitions(m_state->Update(this, dt));
	}

	void Web::End()
	{
		if (m_state != nullptr)
			delete m_state;
	}

	void Web::Notify(const Command* command)
	{
		// Notify state machine
		if (m_state != nullptr)
			HandleStateTransitions(m_state->Notify(this, command));
	}

	void Web::EnableBehavior()
	{
		if (m_state == nullptr)
		{
			// m_state = new **STATE CONSTRUCTOR HERE**
		}
	}

	void Web::HandleStateTransitions(State<Web>* nextState)
	{
		if (nextState != nullptr)
		{
			m_state->Exit(this);
			delete m_state;
			nextState->Enter(this);
			m_state = nextState;
		}
	}
}