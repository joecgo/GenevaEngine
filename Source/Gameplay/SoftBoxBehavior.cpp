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
  * \file SoftBoxBehavior.cpp
  * \author Joe Goldman
  * \brief Behavior for the soft box
  *
  **/
#include <Gameplay/SoftBoxBehavior.hpp>
#include <Input/Command.hpp>
#include <Physics/RayCastCallback.hpp>
#include <Constructs/Construct.hpp>
#include <Constructs/SoftBox.hpp>
#include <Core/State.hpp>
#include <Core/GameSession.hpp>
#include <Utilities/BodyUtils.hpp>

namespace GenevaEngine
{
	// GROUNDED
	void Grounded_SoftBox::Enter(SoftBox* softBox)
	{
	}

	State<SoftBox>* Grounded_SoftBox::Notify(SoftBox* owner, const Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Jump:
			SoftBoxBehavior::Jump(*owner, 5000.0f);
			return new Airborne_SoftBox();

		case Command::Move:
			xAxis = command->GetAxis();
			break;
		}

		return nullptr;
	}
	State<SoftBox>* Grounded_SoftBox::Update(SoftBox* softBox, double dt)
	{
		// apply horizontal movement from xAxis input
		SoftBoxBehavior::Move(*softBox, (float)dt, xAxis, 5000.0f);

		return nullptr;
	}
	void Grounded_SoftBox::Exit(SoftBox* softBox)
	{
	}

	// AIRBOURNE
	void Airborne_SoftBox::Enter(SoftBox* softBox)
	{
	}
	State<SoftBox>* Airborne_SoftBox::Notify(SoftBox* softBox, const Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Move:
			xAxis = command->GetAxis();
			break;
		}

		return nullptr;
	}
	State<SoftBox>* Airborne_SoftBox::Update(SoftBox* softBox, double dt)
	{
		// apply horizontal movement from xAxis input
		SoftBoxBehavior::Move(*softBox, (float)dt, xAxis, 5000.0f);

		// first check for downward vel
		b2Body& body = softBox->GetCenterBody();
		if (body.GetLinearVelocity().y > 0)
			return nullptr;

		// check for grounded
		RayCastCallback callback;
		float rayCastLength = softBox->Size.y + 0.01f;
		b2Vec2 p1 = body.GetPosition();
		b2Vec2 p2 = body.GetPosition() + b2Vec2(0, rayCastLength * -1.0f);

		softBox->GetWorld()->RayCast(&callback, p1, p2);

		if (callback.Hit)
		{
			return new Grounded_SoftBox();
		}

		return nullptr;
	}
	void Airborne_SoftBox::Exit(SoftBox* softBox)
	{
	}

	void SoftBoxBehavior::Move(SoftBox& softBox, float dt, float x_axis,
		float moveStrength, float maxVelocity)
	{
		// get body
		b2Body& body = softBox.GetCenterBody();

		// calculate force
		float adjustedStr = moveStrength * body.GetMass() * dt;
		float forceX = 0.0;
		if (x_axis > 0)
			forceX = adjustedStr;
		else if (x_axis < 0)
			forceX = -1.0f * adjustedStr;

		// apply force
		body.ApplyLinearImpulseToCenter(b2Vec2(forceX, 0), true);

		// max velocity
		b2Vec2 velocity = body.GetLinearVelocity();
		velocity.x = b2Clamp(velocity.x, -1.0f * maxVelocity, maxVelocity);
		body.SetLinearVelocity(velocity);
	}

	void SoftBoxBehavior::Jump(SoftBox& softBox, float jumpStrength)
	{
		b2Body& body = softBox.GetCenterBody();
		b2Vec2 force(0, body.GetMass() * jumpStrength);
		body.ApplyLinearImpulseToCenter(force, true);
	}
}