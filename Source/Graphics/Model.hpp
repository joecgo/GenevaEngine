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
  * \file Model.hpp
  * \author Joe Goldman
  * \brief Model class declaration
  */

#pragma once

  // Disable warning messages from assimp: C26812 C26451
#pragma warning( disable : 26812 26451)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb/stb_image.h>

#include <Graphics/Mesh.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

namespace GenevaEngine
{
	/*!
	 *  \brief A renderable model which contains its own textures and meshes.
	 */
	class Model
	{
	public:
		// model data
		vector<Texture> textures_loaded; // stores all the textures loaded so far
		vector<Mesh>    meshes;
		string directory;
		bool gammaCorrection = false;

		// default contructor
		Model() {};

		// constructor, expects a filepath to a 3D model.
		Model(string const& path, bool gamma = false);

		// draws the model, and thus all its meshes
		void Draw(Shader& shader);

	private:
		// loads a model with supported ASSIMP extensions from file and stores the
		// resulting meshes in the meshes vector.
		void loadModel(string const& path);

		// processes a node in a recursive fashion. Processes each individual mesh located at
		// the node and repeats this process on its children nodes (if any).
		void processNode(aiNode* node, const aiScene* scene);

		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		// checks all material textures of a given type and loads the textures if they're
		// not loaded yet. The required info is returned as a Texture struct.

		/**
		 * .
		 *
		 * \param mat
		 * \param type
		 * \param typeName
		 * \return
		 */
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		unsigned int TextureFromFile(const char* path, const string& directory,
			bool gamma = false);
	};
}