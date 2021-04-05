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
  * \file SingleShapeBehavior.hpp
  * \author Joe Goldman
  * \brief SingleShapeBehavior class declarations
  *
  */

#pragma once

#include <Core/State.hpp>

namespace GenevaEngine
{
	class SingleShape;
	class Command;

	/*!
	 *  \brief Grounded state for Character FSM
	 */
	class Grounded : public State<SingleShape>
	{
	public:
		void Enter(SingleShape* owner);
		State<SingleShape>* Notify(SingleShape* owner, const Command* command);
		State<SingleShape>* Update(SingleShape* owner, double dt);
		void Exit(SingleShape* owner);
	};

	/*!
	 *  \brief Airborne state for Character FSM
	 */
	class Airborne : public State<SingleShape>
	{
	public:
		void Enter(SingleShape* owner);
		State<SingleShape>* Notify(SingleShape* owner, const Command* command);
		State<SingleShape>* Update(SingleShape* owner, double dt);
		void Exit(SingleShape* owner);
	};

	class SingleShapeBehavior
	{
	public:
		static void Move(SingleShape& singleShape, float x_axis, float moveSpeed = 1.0f);
		static void Jump(SingleShape& singleShape, float jumpPower = 150.0f);
	};
}