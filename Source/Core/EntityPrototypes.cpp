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
  * \file EntityPrototypes.cpp
  * \author Joe Goldman
  * \brief EntityPrototypes class definition
  *
  **/

#include <box2d/box2d.h>

#include <Core/EntityPrototypes.hpp>

namespace GenevaEngine
{
	//Entity* Web(b2World* world)
	//{
	//	b2PolygonShape shape;
	//	shape.SetAsBox(0.5f, 0.5f);
	//
	//	b2BodyDef bd;
	//	bd.type = b2_dynamicBody;
	//
	//	bd.position.Set(-5.0f, 5.0f);
	//	m_bodies[0] = world->CreateBody(&bd);
	//	m_bodies[0]->CreateFixture(&shape, 5.0f);
	//
	//	bd.position.Set(5.0f, 5.0f);
	//	m_bodies[1] = world->CreateBody(&bd);
	//	m_bodies[1]->CreateFixture(&shape, 5.0f);
	//
	//	bd.position.Set(5.0f, 15.0f);
	//	m_bodies[2] = world->CreateBody(&bd);
	//	m_bodies[2]->CreateFixture(&shape, 5.0f);
	//
	//	bd.position.Set(-5.0f, 15.0f);
	//	m_bodies[3] = world->CreateBody(&bd);
	//	m_bodies[3]->CreateFixture(&shape, 5.0f);
	//
	//	b2DistanceJointDef jd;
	//	b2Vec2 p1, p2, d;
	//
	//	float frequencyHz = 2.0f;
	//	float dampingRatio = 0.0f;
	//
	//	jd.bodyA = ground;
	//	jd.bodyB = m_bodies[0];
	//	jd.localAnchorA.Set(-10.0f, 0.0f);
	//	jd.localAnchorB.Set(-0.5f, -0.5f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[0] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = ground;
	//	jd.bodyB = m_bodies[1];
	//	jd.localAnchorA.Set(10.0f, 0.0f);
	//	jd.localAnchorB.Set(0.5f, -0.5f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[1] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = ground;
	//	jd.bodyB = m_bodies[2];
	//	jd.localAnchorA.Set(10.0f, 20.0f);
	//	jd.localAnchorB.Set(0.5f, 0.5f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[2] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = ground;
	//	jd.bodyB = m_bodies[3];
	//	jd.localAnchorA.Set(-10.0f, 20.0f);
	//	jd.localAnchorB.Set(-0.5f, 0.5f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[3] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = m_bodies[0];
	//	jd.bodyB = m_bodies[1];
	//	jd.localAnchorA.Set(0.5f, 0.0f);
	//	jd.localAnchorB.Set(-0.5f, 0.0f);;
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[4] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = m_bodies[1];
	//	jd.bodyB = m_bodies[2];
	//	jd.localAnchorA.Set(0.0f, 0.5f);
	//	jd.localAnchorB.Set(0.0f, -0.5f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[5] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = m_bodies[2];
	//	jd.bodyB = m_bodies[3];
	//	jd.localAnchorA.Set(-0.5f, 0.0f);
	//	jd.localAnchorB.Set(0.5f, 0.0f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[6] = world->CreateJoint(&jd);
	//
	//	jd.bodyA = m_bodies[3];
	//	jd.bodyB = m_bodies[0];
	//	jd.localAnchorA.Set(0.0f, -0.5f);
	//	jd.localAnchorB.Set(0.0f, 0.5f);
	//	p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
	//	p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
	//	d = p2 - p1;
	//	jd.length = d.Length();
	//	b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);
	//	m_joints[7] = world->CreateJoint(&jd);
	//}
}