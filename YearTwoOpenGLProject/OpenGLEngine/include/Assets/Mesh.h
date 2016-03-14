#pragma once
#include <vector>
#include <assert.h>
#include <unordered_map>

#include "Utils.h"

#include "Rendering/RenderData.h"
#include "MeshShader.h"

#include "Assets/Material.h"
#include "Assets/Asset.h"

#include "MathTypes\Transform.h"
#include "Cameras\Camera.h"
#include "MathTypes\BoundingSphere.h"

class Mesh 
	: public Asset
{
private:
	bool isValidated;

public:
	BoundingSphere boundingSphere;
    std::vector<Mesh*> subMeshes;
	Material * material;

	MeshShader * shader;


	RenderData * renderData;

	Mesh(string path="")
		: Asset(path),
		renderData(nullptr),
		shader(nullptr),
		material(nullptr),
		isValidated(nullptr)
	{
		if (path != "")
		{
			Load();
		}
	}


	void SetShader(MeshShader * _shader)
	{
		shader = _shader;
	}


	void Unload() override
	{
		Unbind();

		material->Unload();

		for (auto subMesh : subMeshes)
		{
			subMesh->Unload();
		}

		subMeshes.clear();
	}

	template<class T>
	void BuildMaterialFromLoaderNode(Material** material, T* loaderMaterial, string additionalPath = "")
	{
		assert(loaderMaterial);

		*material = new Material(loaderMaterial, loaderMaterial->name);
	}

	template<typename t_vertex>
	void BindVertexAndIndexData(RenderData** _renderData, vector<t_vertex>& vertices, vector<uint>& indices)
	{
		assert(_renderData);

		*_renderData = new RenderData();
		(*_renderData)->GenerateBuffers(RenderData::Buffers::ALL);

		(*_renderData)->Bind();

		glBufferData(GL_ARRAY_BUFFER,
			vertices.size() * sizeof(float),
			vertices.data(), GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(uint),
			indices.data(), GL_STATIC_DRAW);

		shader->EnableAndInitAttributes();

		(*_renderData)->SetIndexCount(indices.size());

		(*_renderData)->Unbind();
	}

	void Render(Camera& camera, Transform& lightTransform, Transform& transform, bool bindShaderUnifroms)
	{
		if (!isInitialized)
			return;

		if (bindShaderUnifroms)
		{
			shader->UpdateUniforms(camera, lightTransform, transform);
		}
	}

	
	virtual void Update(float deltaTime)
	{
	}
};