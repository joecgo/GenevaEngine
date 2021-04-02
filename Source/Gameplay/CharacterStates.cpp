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
  * \file CharacterStates.cpp
  * \author Joe Goldman
  * \brief Character State definitions
  *
  **/

#include <Gameplay/CharacterStates.hpp>

namespace GenevaEngine
{
	// GROUNDED
	void Grounded::Enter(Entity& entity)
	{
	}
	EntityState* Grounded::Notify(Entity& entity, const Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Jump:
			EntityBehavior::Jump(entity, 150.0f);
			return new Airborne();

		case Command::Move:
			EntityBehavior::Move(entity, command->GetAxis(), 2000.0f);
			break;
		}

		return nullptr;
	}
	EntityState* Grounded::Update(Entity& entity)
	{
		return nullptr;
	}
	void Grounded::Exit(Entity& entity)
	{
	}

	// AIRBOURNE
	void Airborne::Enter(Entity& entity)
	{
	}
	EntityState* Airborne::Notify(Entity& entity, const Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Move:
			EntityBehavior::Move(entity, command->GetAxis(), 2000.0f);
			break;
		}

		return nullptr;
	}
	EntityState* Airborne::Update(Entity& entity)
	{
		// check for grounded
		RayCastCallback callback;
		float boxHeight = -3.1f; // TODO: figure out a better way to get this
		b2Body* body = entity.GetAnchorBody();
		b2Vec2 p1 = body->GetPosition();
		b2Vec2 p2 = body->GetPosition() + b2Vec2(0, boxHeight);
		entity.GetWorld()->RayCast(&callback, p1, p2);

		if (callback.Hit)
			return new Grounded();

		return nullptr;
	}
	void Airborne::Exit(Entity& entity)
	{
	}
}