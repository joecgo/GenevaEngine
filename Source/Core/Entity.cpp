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
		gamesession_(gs),
		position_(pos),
		scale_(scale),
		model_name_(model_name),
		shader_name_(shader_name)
	{
		gamesession_->AddEntity(this);
	}

	void Entity::Start()
	{
		model_ = Graphics::GetModel(model_name_);
		shader_ = Graphics::GetShader(shader_name_);
	}

	void Entity::Update()
	{
		Render();
	}

	void Entity::End()
	{
	}

	void Entity::Render()
	{
		// TODO: move caclculation of world transformation to transform component
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position_);
		transform = glm::scale(transform, scale_);

		Graphics::Render(model_, shader_, transform);
	}
}