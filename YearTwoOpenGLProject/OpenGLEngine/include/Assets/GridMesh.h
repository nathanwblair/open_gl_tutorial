#pragma once
#include "Utils.h"
#include "Assets/MeshShader.h"

#include "Assets/Mesh.h"


class GridMesh
	: public Mesh
{
public:
	struct PositionTexCoordVertex
	{
		glm::vec4 position;
		glm::vec2 textureCoordinate;
	};
	
	uint rows, columns;
	float scale;
	float elapsedTime;

	string texturePath;

	GridMesh(string _texturePath="", uint _rows = 10, uint _columns = 10, float _scale=1.0f);

	void Load();

	void Unload();

	void Update(float deltaTime);

	void Invalidate();

	void GenerateGrid();

	void AddNoise(vector<PositionTexCoordVertex>& vertices);

	void BeforeRender(Camera& camera, Transform& lightTransform);

};