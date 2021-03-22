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
  * \file Physics.hpp
  * \author Joe Goldman
  * \brief Physics system class declaration
  *
  */

#pragma once

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief Physics system
	 */
	class Physics : public ASystem
	{
	private:
		// inherited mebers, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}