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
  * \file Box2d.hpp
  * \author Joe Goldman
  * \brief Box2d include without the vs compiler warnings
  *
  */

#pragma once

  // Disable warning messages from box2d: C26812 C26495
#pragma warning( disable : 26812 26495)

#include <box2d/box2d.h> // box2d