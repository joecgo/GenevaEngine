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

namespace GenevaEngine
{
	class GameSession;

	/*!
	 *  \brief Abstract class for game engine systems to inherit from
	 */
	class System
	{
	protected:
		GameSession* m_gameSession = nullptr;
	private:
		System(GameSession* gs);

		virtual void Start() = 0;
		virtual void Update(double dt) = 0;
		virtual void End() = 0;

		friend GameSession;
	};
}