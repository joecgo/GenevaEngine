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
		const int ID;
		std::string Name;

		// constructor
		Entity(GameSession* gs, b2BodyDef bodyDef, b2FixtureDef fixtureDef,
			b2PolygonShape shapeDef, std::string name = "none");

		// puts this instance into the game
		void Spawn();
		// add an initial state for a finite state machine
		void AddFSM(EntityState* initial_state);
		// Notify state machines of incoming command
		void Notify(Command* command);
		// Global state getters
		float FrameTime();

		// TODO: render settings class
		void SetRenderColor(int palette_color_id);
		void SetRenderColor(Color color);
		Color GetRenderColor() const;

		// TODO: box2d wrapper class
		b2World* GetWorld() { return m_world; };
		b2PolygonShape GetShape() { return m_shapeDef; }
		b2Body* GetBody() { return m_body; }

	private:
		// increments on entity construction to create a unique id
		static int m_entityCount;

		// object references
		GameSession* m_gameSession = nullptr;

		// Finite state machines which observe incoming commands
		std::vector<EntityState*> m_states;

		// TODO: implement components
		// Component* components[max_components]

		// TODO: render settings class
		Color m_render_color;

		// TODO: box2d wrapper class
		b2World* m_world = nullptr;
		b2Body* m_body = nullptr;
		b2BodyDef m_bodyDef;
		b2PolygonShape m_shapeDef;
		b2FixtureDef m_fixtureDef;

		//  Game loop
		void Start();
		void FixedUpdate(double alpha); // update on fixed time-steps
		void Update(double dt);			// update on every frame
		void End();
		friend class GameSession;
	};
}