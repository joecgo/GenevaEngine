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
  * \file Input.hpp
  * \author Joe Goldman
  * \brief Input system class declaration
  *
  */

#pragma once

#include <Graphics/Camera.hpp>
#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  Core system for handling input
	 */
	class Input : public ASystem
	{
	private:
		// inherited methods and constructors
		using ASystem::ASystem;

		void Start();
		void Update(float dt);
		void End();

		// called on update
		void processInput(GLFWwindow* window, float dt);

		friend class GameSession;
	};
}