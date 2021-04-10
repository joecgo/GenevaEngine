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
  * \file Entity.hpp
  * \author Joe Goldman
  * \brief Entity class declaration
  *
  */

#pragma once

#include <Graphics/Color.hpp>

#include <string> // string

namespace GenevaEngine
{
	class GameSession;
	class Controller;
	class Command;
	class Construct;

	/*!
	 *  \brief An object that populates the game. Like a UE4 Actor or Unity GameObject.
	 */
	class Entity
	{
	public:
		// Attributes
		const int ID;							// unique ID
		std::string Name;						// A recognizable name for debugging

		// Constructor
		Entity(GameSession* gs, std::string name = "none");

		// Public methods
		void Spawn();							// puts this instance into the game
		float FrameTime();						// Dt since last frame was rendered
		void Notify(const Command* command);	// Notify Construct of incoming commands
		void AddConstruct(Construct* Construct);// Add composite of box2d objects and properties
		Construct& GetConstruct() const;		// Get construct (box2d composite)
		void SetRenderColor(int colorID);		// Set base color for rendering (from palette ID)
		void SetRenderColor(Color color);		// Set base color for rendering
		const Color GetRenderColor() const;		// Get base color for rendering

	private:
		// increments on entity construction to create a unique id
		static int m_entityCount;

		// object references
		GameSession* m_gameSession = nullptr;
		Construct* m_construct = nullptr;

		// base color for rendering
		Color m_render_color;

		//  Game loop (only called by GameSession)
		void Start();							// called once before first update
		void FixedUpdate(double alpha);			// called on fixed physics time-steps
		void Update(double dt);					// called on every rendered frame
		void End();								// called once after last update
		friend class GameSession;
	};
}