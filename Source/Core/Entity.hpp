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

#include <string> // string
#include <vector> // vector

#include <Input/Command.hpp>
#include <Graphics/Shader.hpp>
#include <Gameplay/EntityState.hpp>
#include <Physics/MultiBody.hpp>

namespace GenevaEngine
{
	class GameSession;
	class Controller;

	/*!
	 *  \brief An object that populates the game. Like an actor or game object.
	 */
	class Entity
	{
	public:
		// Attributes
		const int ID;		// unique ID
		std::string Name;	// A recognizable name for debugging

		// constructor
		Entity(GameSession* gs, std::string name = "none");

		void Spawn();							// puts this instance into the game
		void AddMultiBody(MultiBody* multiBody);// attach a multibody to the entity
		void AddFSM(EntityState* initState);	// add an initial state for a FSM
		void Notify(const Command* command);	// Notify FSMs of incoming command
		float FrameTime();						// Dt since last frame was rendered
		b2World* GetWorld();					// Box2d world object
		b2PolygonShape GetShape();				// Box2d shape for this entity
		b2Body* GetAnchorBody();				// Box2d anchoring body from Entity's MultiBody

		// TODO: render settings class
		void SetRenderColor(int palette_color_id);
		void SetRenderColor(Color color);
		Color GetRenderColor() const;

	private:
		// increments on entity construction to create a unique id
		static int m_entityCount;

		GameSession* m_gameSession = nullptr;	// object references
		std::vector<EntityState*> m_states; 	// FSMs which observe incoming commands
		MultiBody* m_multiBody;					// composite of multiple box2d bodies

		// TODO: implement components
		// Component* components[max_components]

		// TODO: render settings class
		Color m_render_color;

		//  Game loop
		void Start();							// called once before first update
		void FixedUpdate(double alpha);			// called on fixed physics time-steps
		void Update(double dt);					// called on every rendered frame
		void End();								// called once after last update
		friend class GameSession;
	};
}