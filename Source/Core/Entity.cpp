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
  * \file Entity.cpp
  * \author Joe Goldman
  * \brief Entity class definition
  *
  **/

#include <Core/GameCommon.hpp>

using namespace std;
namespace GenevaEngine
{
	/*!
	 *  Constructor
	 *
	 *      \param [in] modelName
	 *      \param [in] shaderName
	 *      \param [in] position
	 *      \param [in] scale
	 *
	 *      \return
	 */
	Entity::Entity(GameSession* gs, glm::vec3 pos, glm::vec3 scale,
		string model_name, string shader_name) :
		gamesession(gs),
		startPosition(pos),
		scale(scale),
		model_name(model_name),
		shader_name(shader_name)
	{
		gamesession->AddEntity(this);
	}

	void Entity::Start()
	{
		// get a pointer to the Entity's model and shader referenced by name in the constructor
		model = gamesession->graphics->GetModel(model_name);
		shader = gamesession->graphics->GetShader(shader_name);

		// physics stuff
		current_state.position = startPosition;
		previous_state.position = startPosition;
		interpolated_state.position = startPosition;
	}

	void Entity::Update(double dt)
	{
	}

	void Entity::FixedUpdate(double alpha)
	{
	}

	void Entity::End()
	{
	}

	glm::vec3 Entity::Position()
	{
		return interpolated_state.position;
	}
}