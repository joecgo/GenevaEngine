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

#include <Core/Entity.hpp>

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
	Entity::Entity(glm::vec3 pos, glm::vec3 scale, string model_name, string shader_name) :
		position_(pos),
		scale_(scale),
		model_name_(model_name),
		shader_name_(shader_name)
	{
	}

	void Entity::Start()
	{
	}

	void Entity::Update()
	{
	}

	void Entity::End()
	{
	}
}