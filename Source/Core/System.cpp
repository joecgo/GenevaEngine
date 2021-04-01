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
  * \file System.cpp
  * \author Joe Goldman
  * \brief Abstract System class definition
  *
  **/

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	System::System(GameSession* gs) : gamesession(gs)
	{
		gamesession->AddSystem(this);
	}
}