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
  * @file Mesh.hpp
  * @author Joe Goldman
  * @brief Mesh class declaration
  **/

#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Graphics/Shader.hpp>

#include <string>
#include <vector>
using namespace std;

namespace GenevaEngine
{
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

	struct Texture {
		unsigned int id;
		string type;
		string path;
	};

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