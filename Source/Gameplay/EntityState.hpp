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
  * \file EntityState.hpp
  * \author Joe Goldman
  * \brief EntityState class declaration
  *
  */

#pragma once

#include <string>

namespace GenevaEngine
{
	class Command;
	class Entity;

	class EntityState
	{
	public:
		std::string name = "none";
		virtual void Enter(Entity& entity) = 0;
		virtual EntityState* Notify(Entity& entity, Command* command) = 0;
		virtual EntityState* Update(Entity& entity) = 0;
		virtual void Exit(Entity& entity) = 0;
	};
}