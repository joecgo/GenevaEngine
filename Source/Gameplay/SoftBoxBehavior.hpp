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
  * \file SoftBoxBehavior.hpp
  * \author Joe Goldman
  * \brief  Behavior for the soft box declarations
  *
  */

#pragma once
#include <Core/State.hpp>

namespace GenevaEngine
{
	class SoftBox;
	class Command;

	/*!
	 *  \brief Grounded state for Character FSM
	 */
	class Grounded_SoftBox : public State<SoftBox>
	{
	public:
		void Enter(SoftBox* owner);
		State<SoftBox>* Notify(SoftBox* owner, const Command* command);
		State<SoftBox>* Update(SoftBox* owner, double dt);
		void Exit(SoftBox* owner);

	private:
		float xAxis = 0.0f; // horizontal axis applied by controller
	};

	/*!
	 *  \brief Airborne state for Character FSM
	 */
	class Airborne_SoftBox : public State<SoftBox>
	{
	public:
		void Enter(SoftBox* owner);
		State<SoftBox>* Notify(SoftBox* owner, const Command* command);
		State<SoftBox>* Update(SoftBox* owner, double dt);
		void Exit(SoftBox* owner);
	private:
		float xAxis = 0.0f; // horizontal axis applied by controller
	};

	class SoftBoxBehavior
	{
	public:
		static void Move(SoftBox& singleShape, float dt, float x_axis,
			float moveStrength = 500.0f, float maxVelocity = 45.0f);
		static void Jump(SoftBox& singleShape, float jumpStrength = 150.0f);
	};
}