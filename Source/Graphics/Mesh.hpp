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
  * \file Mesh.hpp
  * \author Joe Goldman
  * \brief Mesh class declaration
  */

#pragma once

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW
#include <glm/gtc/matrix_transform.hpp> // vec2 vec3

#include <string> // string
#include <vector> // vector

#include <Graphics/Shader.hpp>

namespace GenevaEngine
{
	using std::vector;
	using std::string;

	/**
	 * \brief Container for all the data associated with a single vertex
	 */
	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	/**
	 * \brief Container for all the data associated with a single texture
	 */
	struct Texture {
		unsigned int id = 0;
		std::string type;
		std::string path;
	};

	/*!
	 *  \brief A renderable mesh which contains its own vertices, indices, and texture data.
	 */
	class Mesh {
	public:
		// mesh Data
		vector<Vertex>       vertices;
		vector<unsigned int> indices;
		vector<Texture>      textures;
		unsigned int VAO;

		// constructor
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

		// render the mesh
		void Draw(Shader& shader);

	private:
		// render data
		unsigned int VBO, EBO;

		// initializes all the buffer objects/arrays
		void setupMesh();
	};
}