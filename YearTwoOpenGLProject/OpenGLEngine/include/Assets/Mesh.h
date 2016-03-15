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

#include "dynamic_enum\DynamicEnum.h"

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

	Mesh(string path = "")
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

	virtual void Load()
	{
		isInitialized = true;
	}


	void SetShader(MeshShader * _shader)
	{
		shader = _shader;

		for (auto subMesh : subMeshes)
		{
			subMesh->SetShader(_shader);
		}
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

	void BuildMaterialFromLoaderNode(Material** material, DynamicEnum loaderMaterial, string additionalPath = "")
	{
		*material = new Material(loaderMaterial, "");
	}

	void BuildMaterialFromLoaderNode(Material** material, FBXMaterial* loaderMaterial, string additionalPath = "")
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
			vertices.size() * sizeof(t_vertex),
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

		SafeBind();
		renderData->Render();
		SafeUnbind();

		for (uint i = 0; i < subMeshes.size(); ++i)
		{
			Mesh* subMesh = subMeshes[i];
			subMesh->Render(camera, lightTransform, transform, false);
		}
	}

	
	virtual void Update(float deltaTime)
	{

	}	
	
	void Mesh::Bind()
	{
		if (shader)
			shader->Bind();
		if (material)
			material->Bind();

		renderData->Bind();
	}

	void Mesh::Unbind()
	{
		if (shader)		
			shader->Unbind();
		if (material)	
			material->Unbind();

		renderData->Unbind();
	}
};