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
		position(pos),
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
	}

	void Entity::Update(double dt)
	{
		Render();
	}

	void Entity::End()
	{
	}

	/*!
	 *  Calculates world transform and makes a request to the graphics system to render
	 *  this entity.
	 */
	void Entity::Render()
	{
		// TODO: add rotation tranformation
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, scale);

		gamesession->graphics->Render(model, shader, transform);
	}
}