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
  * \file SingleShapeBehavior.cpp
  * \author Joe Goldman
  * \brief SingleShapeBehavior definitions
  *
  **/

#include <Gameplay/SingleShapeBehavior.hpp>
#include <Input/Command.hpp>
#include <Gameplay/RayCastCallback.hpp>
#include <Physics/Construct.hpp>
#include <Physics/SingleShape.hpp>
#include <Core/State.hpp>
#include <Core/GameSession.hpp>

namespace GenevaEngine
{
	// GROUNDED
	void Grounded::Enter(SingleShape* singleShape)
	{
	}

	State<SingleShape>* Grounded::Notify(SingleShape* owner, const Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Jump:
			SingleShapeBehavior::Jump(*owner, 150.0f);
			return new Airborne();

		case Command::Move:
			SingleShapeBehavior::Move(*owner, command->GetAxis());
			break;
		}

		return nullptr;
	}
	State<SingleShape>* Grounded::Update(SingleShape* singleShape, double dt)
	{
		return nullptr;
	}
	void Grounded::Exit(SingleShape* singleShape)
	{
	}

	// AIRBOURNE
	void Airborne::Enter(SingleShape* singleShape)
	{
	}
	State<SingleShape>* Airborne::Notify(SingleShape* singleShape, const Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Move:
			SingleShapeBehavior::Move(*singleShape, command->GetAxis());
			break;
		}

		return nullptr;
	}
	State<SingleShape>* Airborne::Update(SingleShape* singleShape, double dt)
	{
		// first check for downward vel
		b2Body* body = singleShape->GetBody();
		if (body->GetLinearVelocity().y > 0)
			return nullptr;

		// check for grounded
		RayCastCallback callback;
		float boxHeight = -3.1f; // TODO: figure out a better way to get this
		b2Vec2 p1 = body->GetPosition();
		b2Vec2 p2 = body->GetPosition() + b2Vec2(0, boxHeight);
		singleShape->GetWorld()->RayCast(&callback, p1, p2);

		if (callback.Hit)
		{
			return new Grounded();
		}

		return nullptr;
	}
	void Airborne::Exit(SingleShape* singleShape)
	{
	}

	void SingleShapeBehavior::Move(SingleShape& singleShape, float x_axis, float moveSpeed)
	{
		float dt = (float)GameSession::FrameTime;
		float moveScalar = 20000.0f;
		b2Body* body = singleShape.GetBody();
		b2Vec2 vel = body->GetLinearVelocity();
		if (x_axis > 0)
			vel.x = moveSpeed * dt * moveScalar;
		else if (x_axis < 0)
			vel.x = -1.0f * moveSpeed * dt * moveScalar;
		body->SetLinearVelocity(vel);
	}

	void SingleShapeBehavior::Jump(SingleShape& singleShape, float jumpPower)
	{
		b2Body* body = singleShape.GetBody();
		b2Vec2 force(0, body->GetMass() * jumpPower);
		body->ApplyLinearImpulseToCenter(force, true);
	}
}