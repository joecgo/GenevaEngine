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

#include <glm/glm.hpp> // vec3

#include <string> // string

#include <Graphics/Shader.hpp>
#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
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

		// box2d getters
		b2PolygonShape GetShape() { return shape_def; }
		b2Body* GetBody() { return body; }

	private:
		// object references
		GameSession* gamesession = nullptr;

		// box2d
		b2World* world = nullptr;
		b2Body* body = nullptr;
		b2BodyDef body_def;
		b2PolygonShape shape_def;
		b2FixtureDef fixture_def;

		// GameSession calls
		void Start();
		void FixedUpdate(double alpha); // update on fixed time-steps
		void Update(double dt);			// update on every frame
		void End();
		friend class GameSession;
	};
}