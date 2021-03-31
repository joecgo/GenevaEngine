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
  * \file CharacterStates.hpp
  * \author Joe Goldman
  * \brief Character State class declarations
  *
  */

#pragma once

#include <Gameplay/EntityState.hpp>
#include <Input/Command.hpp>
#include <Core/Entity.hpp>
#include <Gameplay/RayCastCallback.hpp>

namespace GenevaEngine
{
	class Grounded : public EntityState
	{
	public:
		virtual void Enter(Entity& entity);
		virtual EntityState* Notify(Entity& entity, Command* command);
		virtual EntityState* Update(Entity& entity);
		virtual void Exit(Entity& entity);
	private:
		void Jump(Entity& entity);
		void Move(Entity& entity, float x);
	};

	class Airborne : public EntityState
	{
	public:
		virtual void Enter(Entity& entity);
		virtual EntityState* Notify(Entity& entity, Command* command);
		virtual EntityState* Update(Entity& entity);
		virtual void Exit(Entity& entity);
	private:
		void Move(Entity& entity, float x);
	};
}