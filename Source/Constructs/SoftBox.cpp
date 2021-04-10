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
  * \file SoftBox.cpp
  * \author Joe Goldman
  * \brief SoftBox system class definition
  *
  **/

#include <Constructs/SoftBox.hpp>

namespace GenevaEngine
{
	void SoftBox::Create()
	{
		const bool drawCircles = false;
		const b2Vec2 hsize = 0.5f * Size;
		b2CircleShape shape;
		b2FixtureDef fd;
		b2BodyDef bd;

		fd.shape = &shape;
		fd.restitution = 0.5f;
		bd.type = b2_dynamicBody;
		bd.fixedRotation = true;

		fd.density = 0.5;
		shape.m_radius = InnerCircleRadius;
		bd.position = StartPos;
		m_bodies[0] = m_world->CreateBody(&bd);
		m_bodies[0]->CreateFixture(&fd);

		fd.density = 1.0f;
		shape.m_radius = OuterCircleRadius;
		bd.position -= hsize;
		m_bodies[1] = m_world->CreateBody(&bd);
		m_bodies[1]->CreateFixture(&shape, 5.0f);

		bd.position.y += Size.y;
		m_bodies[2] = m_world->CreateBody(&bd);
		m_bodies[2]->CreateFixture(&shape, 5.0f);

		bd.position.x += Size.x;
		m_bodies[3] = m_world->CreateBody(&bd);
		m_bodies[3]->CreateFixture(&shape, 5.0f);

		bd.position.y -= Size.y;
		m_bodies[4] = m_world->CreateBody(&bd);
		m_bodies[4]->CreateFixture(&shape, 5.0f);

		// add bodies and shapes to render data
		if (drawCircles)
		{
			for (int i = 0; i < 5; i++)
			{
				BodyRenderData brData;
				brData.Body = m_bodies[i];
				m_renderData.BodyRenderList.push_back(brData);
			}
		}

		b2DistanceJointDef jd;
		b2Vec2 p1, p2, d;

		float frequencyHz = 8.0f;
		float dampingRatio = 0.01f;

		jd.bodyA = m_bodies[0];
		jd.bodyB = m_bodies[1];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[0] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[0];
		jd.bodyB = m_bodies[2];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[1] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[0];
		jd.bodyB = m_bodies[3];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[2] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[0];
		jd.bodyB = m_bodies[4];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[3] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[1];
		jd.bodyB = m_bodies[2];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[4] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[2];
		jd.bodyB = m_bodies[3];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[5] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[3];
		jd.bodyB = m_bodies[4];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[6] = m_world->CreateJoint(&jd);

		jd.bodyA = m_bodies[4];
		jd.bodyB = m_bodies[1];
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
		m_joints[7] = m_world->CreateJoint(&jd);

		// add joints and to render data
		for (int j = 4; j < 8; j++)
		{
			JointRenderData jrData;
			jrData.Joint = m_joints[j];
			m_renderData.JointRenderList.push_back(jrData);
		}
	}

	void SoftBox::Start()
	{
	}

	void SoftBox::FixedUpdate(double alpha)
	{
	}

	void SoftBox::Update(double dt)
	{
		// run a step in the state machine
		if (m_state != nullptr)
			HandleStateTransitions(m_state->Update(this, dt));
	}

	void SoftBox::End()
	{
		if (m_state != nullptr)
			delete m_state;
	}

	void SoftBox::Notify(const Command* command)
	{
		// Notify state machine
		if (m_state != nullptr)
			HandleStateTransitions(m_state->Notify(this, command));
	}

	void SoftBox::EnableBehavior()
	{
		if (m_state == nullptr)
		{
			// m_state = new **STATE CONSTRUCTOR HERE**
		}
	}

	void SoftBox::HandleStateTransitions(State<SoftBox>* nextState)
	{
		if (nextState != nullptr)
		{
			m_state->Exit(this);
			delete m_state;
			nextState->Enter(this);
			m_state = nextState;
		}
	}

	b2Body& SoftBox::GetCenterBody()
	{
		return *m_centerBody;
	}

	const ConstructRenderData& SoftBox::GetConstructRenderData()
	{
		const float offsetDist = b2Sqrt(OuterCircleRadius * 2.0f);
		const b2Vec2 center = m_bodies[0]->GetPosition();

		//// adjust render offset of joints to wrap the outside of the shapes
		for (int i = 0; i < 4; i++)
		{
			b2Vec2 anchorA = m_renderData.JointRenderList[i].Joint->GetAnchorA();
			b2Vec2 anchorB = m_renderData.JointRenderList[i].Joint->GetAnchorB();
			b2Vec2 outwardVecA = (anchorA - center).UnitVector();
			b2Vec2 outwardVecB = (anchorB - center).UnitVector();
			m_renderData.JointRenderList[i].aOffset = offsetDist * outwardVecA;
			m_renderData.JointRenderList[i].bOffset = offsetDist * outwardVecB;
		}

		return m_renderData;
	}
}