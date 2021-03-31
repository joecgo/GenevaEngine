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
		name = "grounded";
	}
	EntityState* Grounded::Notify(Entity& entity, Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Jump:
			Jump(entity);
			return new Airborne();

		case Command::Move:
			Move(entity, command->GetAxis());
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
	void Grounded::Jump(Entity& entity)
	{
		b2Body* body = entity.GetBody();
		float jump_power = 150.0f;
		b2Vec2 force(0, body->GetMass() * jump_power);
		body->ApplyLinearImpulseToCenter(force, true);
	}
	void Grounded::Move(Entity& entity, float x)
	{
		b2Body* body = entity.GetBody();
		const float dt = entity.FrameTime();
		const float move_speed = 2000.0f;

		b2Vec2 vel = body->GetLinearVelocity();
		//vel.x = 0;
		if (x > 0)
			vel.x = move_speed * dt;
		else if (x < 0)
			vel.x = -1.0f * move_speed * dt;
		body->SetLinearVelocity(vel);
	}

	// AIRBOURNE
	void Airborne::Enter(Entity& entity)
	{
		name = "airbourne";
	}
	EntityState* Airborne::Notify(Entity& entity, Command* command)
	{
		switch ((int)command->GetType())
		{
		case Command::Move:
			Move(entity, command->GetAxis());
			break;
		}

		return nullptr;
	}
	EntityState* Airborne::Update(Entity& entity)
	{
		RayCastCallback callback;
		float boxHeight = -3.1f; // TODO: figure out a better way to get this
		b2Body* body = entity.GetBody();
		b2Vec2 p1 = body->GetPosition();
		b2Vec2 p2 = body->GetPosition() + b2Vec2(0, boxHeight);
		entity.GetWorld()->RayCast(&callback, p1, p2);

		if (callback.bHit)
			return new Grounded();

		return nullptr;
	}
	void Airborne::Exit(Entity& entity)
	{
	}

	void Airborne::Move(Entity& entity, float x)
	{
		b2Body* body = entity.GetBody();
		const float dt = entity.FrameTime();
		const float move_speed = 2000.0f;

		b2Vec2 vel = body->GetLinearVelocity();
		//vel.x = 0;
		if (x > 0)
			vel.x = move_speed * dt;
		else if (x < 0)
			vel.x = -1.0f * move_speed * dt;
		body->SetLinearVelocity(vel);
	}
}