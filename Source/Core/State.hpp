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
  * \file State.hpp
  * \author Joe Goldman
  * \brief State class declaration
  *
  */

#pragma once

#include <string>

namespace GenevaEngine
{
	class Command;
	class Construct;

	/*!
	 *  \brief  State for use in FSMs
	 */
	template <class T>
	class State
	{
	public:
		virtual void Enter(T* owner) = 0;
		virtual State<T>* Notify(T* owner, const Command* command) = 0;
		virtual State<T>* Update(T* owner, double dt) = 0;
		virtual void Exit(T* owner) = 0;
	};
}