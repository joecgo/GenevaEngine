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
  * \file System.hpp
  * \author Joe Goldman
  * \brief Base system class declaration
  *
  */

#pragma once
#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  Abstract class for game engine systems to inherit from
	 */
	class System
	{
	protected:
		GameSession* gamesession = nullptr;
	private:
		/*!
		 *  Constructor.
		 *
		 *      \param [in] gs
		 */
		System(GameSession* gs) : gamesession(gs) { gamesession->AddSystem(this); }

		virtual void Start() = 0;
		virtual void Update(double dt) = 0;
		virtual void End() = 0;

		friend class GameSession;
	};
}