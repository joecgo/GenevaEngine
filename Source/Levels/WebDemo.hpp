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
 * \file WebDemo.hpp
 * \author Joe Goldman
 * \brief WebDemo level declaration
 *
 */

#pragma once

#include <Levels/Level.hpp>

namespace GenevaEngine
{
	class GameSession;

	class WebDemo : public Level
	{
	public:
		static void Load(GameSession& gs);
	};
}