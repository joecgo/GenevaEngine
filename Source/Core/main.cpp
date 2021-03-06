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
  * \file Main.cpp
  * \author Joe Goldman
  * \brief Launches engine in main()
  */

#include <Core/GameSession.hpp>

int main()
{
	GenevaEngine::GameSession gs;
	while (gs.IsRunning) {}

	return 0;
}