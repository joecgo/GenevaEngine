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
  * \file Level.hpp
  * \author Joe Goldman
  * \brief Level class declaration
  *
  */

#pragma once

namespace GenevaEngine
{
	class GameSession;

	/*!
	 *  \brief	Base class for levels.
	 *			Currently, levels are a simple series of class
	 *			instantiations called inside GameSession::Start()
	 *
	 *			The future plan is to instantiate levels from a JSON file.
	 */
	class Level
	{
	public:
		virtual void Load(GameSession& gs) = 0;
	};
}