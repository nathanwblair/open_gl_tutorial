#pragma once
#include <vector>
#include <assert.h>
#include <unordered_map>

#include "Utils.h"

#include "Rendering/RenderData.h"
#include "MeshShader.h"

#include "Assets/Material.h"
#include "Assets/Asset.h"

#include "MathTypes/Transform.h"
#include "Cameras/Camera.h"
#include "MathTypes/BoundingSphere.h"

#include "dynamic_enum/DynamicEnum.h"

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

	Mesh(string path = "");

	virtual void Load() override = 0;
	//{
	//	isInitialized = true;
	//}

	void SetShader(MeshShader * _shader);

	void Unload();

	void BuildMaterialFromLoaderNode(Material** material, DynamicEnum loaderMaterial, string additionalPath = "");

	void BuildMaterialFromLoaderNode(Material** material, FBXMaterial* loaderMaterial, string additionalPath = "");

	template<typename vertex_t>
	void BindVertexAndIndexData(RenderData** _renderData, vector<vertex_t>& vertices, vector<uint>& indices)
	{
		assert(_renderData);

		vector<vec3> points(vertices.size());

		for (uint index = 0; index < vertices.size(); index++)
		{
			points[index] = vec3(vertices[index].position);
		}

		*_renderData = new RenderData();
		(*_renderData)->GenerateBuffers(RenderData::Buffers::ALL);

		(*_renderData)->Bind();

		glBufferData(GL_ARRAY_BUFFER,
			vertices.size() * sizeof(vertex_t),
			vertices.data(), GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(uint),
			indices.data(), GL_STATIC_DRAW);

		shader->SetVertexSize<vertex_t>();

		shader->EnableAndInitAttributes();

		(*_renderData)->SetIndexCount(indices.size());

		(*_renderData)->Unbind();
	}

	void Render(Camera& camera, Transform& lightTransform, Transform& transform, bool bindShaderUnifroms);

	virtual void Update(float deltaTime);

	void Bind();

	void Unbind();
};