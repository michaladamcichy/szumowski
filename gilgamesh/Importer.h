#pragma once

#include "stdafx.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include "Mesh.h"
#include "Vertex.h"

struct RawMesh {
	vector <Vertex> vertices;
	vector <uint> indices;
};

class Importer {
public:

	static void loadMeshes(string path, vector <RawMesh>& meshes) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);
		if (scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode)
		{
			extractMeshes(scene->mRootNode, scene, meshes);

			Log::print("\nCreated a model.");
		}
		else {
			Log::print("\nERROR::ASSIMP:: ", importer.GetErrorString());
		}
	}

	static void extractMeshes(aiNode* node, const aiScene* scene, vector <RawMesh>& target)
	{
		for (uint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			target.push_back(processMesh(mesh, scene));
		}
		for (uint i = 0; i < node->mNumChildren; i++) {
			extractMeshes(node->mChildren[i], scene, target);
		}
	}

	static RawMesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector <Vertex> vertices;
		std::vector <uint> indices;
		//std::vector <TextureInfo> texturesInfo;

		struct Vertex vertex;
		for (int i = 0; i < mesh->mNumVertices; i++) {
			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex.normal = glm::normalize(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			if (mesh->HasTextureCoords(0)) {
				vertex.uv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				/*for (int j = 1; j < mesh->GetNumUVChannels; j++) {

				}*/
			}
			vertices.push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		/*aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiString path;
		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			path.Clear();
			material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			texturesInfo.push_back({ directory + '/' + path.C_Str(), TEXTURE_DIFFUSE });
		}
		if (material->GetTextureCount(aiTextureType_SPECULAR)) {
			path.Clear();
			material->GetTexture(aiTextureType_SPECULAR, 0, &path);
			texturesInfo.push_back({ directory + '/' + path.C_Str(), TEXTURE_SPECULAR });
		}
		if (material->GetTextureCount(aiTextureType_NORMALS)) {
			path.Clear();
			material->GetTexture(aiTextureType_NORMALS, 0, &path);
			texturesInfo.push_back({ directory + '/' + path.C_Str(), TEXTURE_NORMALS });
		}*/

		return { vertices, indices };
	}
};