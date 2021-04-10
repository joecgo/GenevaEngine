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
  * \file SoftBoxDemo.hpp
  * \author Joe Goldman
  * \brief SoftBoxDemo level declaration
  *
  */

#pragma once

#include <Levels/Level.hpp>

namespace GenevaEngine
{
	class GameSession;

	class SoftBoxDemo : public Level
	{
	public:
		static void Load(GameSession& gs);
	};
}