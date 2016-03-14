#pragma once
#include "Mesh.h"

#include "AnimatedMeshShader.h"


class FBXMesh
	: public Mesh
{
	FBXFile fbxFile;
	float elapsedTime;

public:
	FBXMesh(string path = "")
		: Mesh(path),
		elapsedTime(0)
	{
	}

	void Load() override
	{
		auto indexFileExtension = path.find_last_of(".") + 1;

		assert(indexFileExtension != 0 && "Need to include file extension in path");

		auto fileExtension = path.substr(indexFileExtension);

		if (fileExtension == "fbx")
		{
			LoadFromFBX();
		}
		else
		{
			throw std::exception("Invalid file type");
		}
	}


	void Update(float deltaTime) override
	{
		UpdateAnimation(deltaTime);
	}


	void LoadFromFBX()
	{
		auto isLoaded = fbxFile.load(path.c_str());
		if (!isLoaded)
		{
			assert(false && "ERROR: Failed to load FBX file!");
			return;
		}

		FBXMeshNode * meshNode = fbxFile.getMeshByIndex(0);
		assert(meshNode && "At least one mesh in your FBX is required");

		BindVertexAndIndexData(&renderData, meshNode->m_vertices, meshNode->m_indices);
		BuildMaterialFromLoaderNode(&material, meshNode->m_materials[0]);

		for (uint index = 1; index < fbxFile.getMeshCount(); ++index)
		{
			auto subMesh = new FBXMesh();
			auto subMeshNode = fbxFile.getMeshByIndex(index);

			BindVertexAndIndexData(&(subMesh->renderData), subMeshNode->m_vertices, subMeshNode->m_indices);
			BuildMaterialFromLoaderNode(&subMesh->material, meshNode->m_materials[0]);

			if (shader)
				subMesh->SetShader(shader);

			subMesh->isInitialized = true;
			subMeshes.push_back(subMesh);
		}
	}


	void UpdateAnimation(float deltaTime)
	{
		// Function stolen from https://github.com/johnsietsma/RefEngine/ and then messed with

		elapsedTime += deltaTime;

		vector<FBXSkeleton*>& skeletons = fbxFile.getSkeletons();
		auto& animationMap = fbxFile.getAnimations();

		if (skeletons.size() == 0 || animationMap.size() == 0)
		{
			return;
		}

		// Just use the first skeleton and first animation.
		FBXSkeleton* skeleton = skeletons[0];
		const FBXAnimation* animation = animationMap.begin()->second;
		assert(animation->totalFrames() > 0);

		// Get the position, scale, rotation values of the keyframes in the animation at m_elapsedTime.
		// Interpolate between the two closest keyframes and set the local transform of animation nodes.
		skeleton->evaluate(animation, elapsedTime);

		for (uint boneIndex = 0; boneIndex < skeleton->m_boneCount; boneIndex++)
		{
			// Refresh the global transform now that we've updated the local transform
			skeleton->m_nodes[boneIndex]->updateGlobalTransform();
		}
	}


	void BeforeRender(Camera& camera, Transform& lightTransform)
	{
		shader->BindIfNeeded();

		std::vector<FBXSkeleton*>& skeletons = fbxFile.getSkeletons();

		if (shader->HasUniform("Bones") && skeletons.size() > 0)
		{
			FBXSkeleton* skeleton = skeletons[0];

			skeleton->updateBones();

			((AnimatedMeshShader*)shader)->UpdateBones(skeleton->m_bones, skeleton->m_boneCount);
		}
	}

};