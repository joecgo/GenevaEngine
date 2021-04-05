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
  * \file Construct.cpp
  * \author Joe Goldman
  * \brief Construct class definition
  *
  **/

#include <iostream>

#include <Physics/Construct.hpp>
#include <Core/State.hpp>

namespace GenevaEngine
{
	Construct::Construct(b2World* world) : m_world(world)
	{
	}

	/*!
	 *  \brief Checks thats construct isn't already created, then creates it
	 *
	 */
	void Construct::SafeCreate()
	{
		// If already created, behavior is to not create again.
		if (m_state == ExistanceState::Created)
		{
			std::cout << "Warning - Construct::SafeCreate - Already created" << std::endl;
			return;
		}

		// Check if world was never assigned to construct
		if (m_world == nullptr)
		{
			std::cout << "Warning - Construct::SafeCreate - Missing world" << std::endl;
			return;
		}

		// all is good! Create construct
		m_state = ExistanceState::Created;
		Create();
	}

	void Construct::SetWorld(b2World* world)
	{
		m_world = world;
	}

	b2World* Construct::GetWorld()
	{
		return m_world;
	}

	std::list<BodyRenderData>* Construct::GetConstructRenderData()
	{
		return &m_constructRenderData;
	}
}