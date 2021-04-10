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
#include <Physics/RayCastCallback.hpp>
#include <Constructs/Construct.hpp>
#include <Constructs/SingleShape.hpp>
#include <Core/State.hpp>
#include <Core/GameSession.hpp>
#include <Utilities/BodyUtils.hpp>

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
			xAxis = command->GetAxis();
			break;
		}

		return nullptr;
	}
	State<SingleShape>* Grounded::Update(SingleShape* singleShape, double dt)
	{
		// apply horizontal movement from xAxis input
		SingleShapeBehavior::Move(*singleShape, (float)dt, xAxis);

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
			xAxis = command->GetAxis();
			break;
		}

		return nullptr;
	}
	State<SingleShape>* Airborne::Update(SingleShape* singleShape, double dt)
	{
		// apply horizontal movement from xAxis input
		SingleShapeBehavior::Move(*singleShape, (float)dt, xAxis);

		// first check for downward vel
		b2Body* body = singleShape->GetBody();
		if (body->GetLinearVelocity().y > 0)
			return nullptr;

		// check for grounded
		RayCastCallback callback;
		float rayCastLength = BodyUtils::GetHalfHeight(*body) + 0.01f;
		b2Vec2 p1 = body->GetPosition();
		b2Vec2 p2 = body->GetPosition() + b2Vec2(0, rayCastLength * -1.0f);

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

	void SingleShapeBehavior::Move(SingleShape& singleShape, float dt, float x_axis,
		float moveStrength, float maxVelocity)
	{
		// get body
		b2Body* body = singleShape.GetBody();

		// calculate force
		float adjustedStr = moveStrength * body->GetMass() * dt;
		float forceX = 0.0;
		if (x_axis > 0)
			forceX = adjustedStr;
		else if (x_axis < 0)
			forceX = -1.0f * adjustedStr;

		// apply force
		body->ApplyLinearImpulseToCenter(b2Vec2(forceX, 0), true);

		// max velocity
		b2Vec2 velocity = body->GetLinearVelocity();
		velocity.x = b2Clamp(velocity.x, -1.0f * maxVelocity, maxVelocity);
		body->SetLinearVelocity(velocity);
	}

	void SingleShapeBehavior::Jump(SingleShape& singleShape, float jumpStrength)
	{
		b2Body* body = singleShape.GetBody();
		b2Vec2 force(0, body->GetMass() * jumpStrength);
		body->ApplyLinearImpulseToCenter(force, true);
	}
}