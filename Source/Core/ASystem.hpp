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
  * \file ASystem.hpp
  * \author Joe Goldman
  * \brief Abstract system class declaration
  *
  */

#pragma once
#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  Abstract class for game engine systems to inherit from
	 */
	class ASystem
	{
	private:
		GameSession* gamesession_;

		ASystem(GameSession* gs) : gamesession_(gs) { gamesession_->AddSystem(this); }
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void End() = 0;

		friend class GameSession;
	};
}