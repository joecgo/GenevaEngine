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
  * \file GameCommon.hpp
  * \author Joe Goldman
  * \brief Includes all the common classes for the game engine in one place
  *
  */

#pragma once

  // Disable warning messages from box2d: C26812 C26495
#pragma warning( disable : 26812 26495)

#include <box2d/box2d.h> // box2d
#include <Core/GameSession.hpp>
#include <Core/System.hpp>
#include <Core/Entity.hpp>
#include <Graphics/Graphics.hpp>
#include <Input/Input.hpp>
#include <Physics/Physics.hpp>