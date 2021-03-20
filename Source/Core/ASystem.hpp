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

namespace GenevaEngine
{
	class GameSession;

	/*!
	 *  Abstract class for game engine systems to inherit from
	 */
	class ASystem
	{
	private:
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void End() = 0;

		friend class GameSession;
	};
}