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
		// increments on entity construction to create a unique id
		static int entity_count;

		// general info
		const int id = -1;
		std::string name;

		// constructor
		Entity(GameSession* gs, b2BodyDef arg_body_def, b2FixtureDef arg_fixture_def,
			b2PolygonShape arg_shape_def, std::string arg_name = "none");

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
		b2World* GetWorld() { return world; };
		b2PolygonShape GetShape() { return shape_def; }
		b2Body* GetBody() { return body; }

	private:
		// object references
		GameSession* gamesession = nullptr;

		// Finite state machines which observe all incoming commands
		std::vector<EntityState*> states;

		// TODO: implement components
		// Component* components[max_components]

		// TODO: render settings class
		Color render_color;

		// TODO: box2d wrapper class
		b2World* world = nullptr;
		b2Body* body = nullptr;
		b2BodyDef body_def;
		b2PolygonShape shape_def;
		b2FixtureDef fixture_def;

		//  Game loop
		void Start();
		void FixedUpdate(double alpha); // update on fixed time-steps
		void Update(double dt);			// update on every frame
		void End();
		friend class GameSession;
	};
}