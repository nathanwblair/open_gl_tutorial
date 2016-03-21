#include "Assets/GridMesh.h"

GridMesh::GridMesh(string _texturePath, uint _rows, uint _columns, float _scale)
	: Mesh(""),
	rows(_rows),
	columns(_columns),
	scale(_scale),
	texturePath(_texturePath),
	elapsedTime(0) 
{
	SetShader(new MeshShader("default.shader"));
}

void GridMesh::Load()
{
	GenerateGrid();
}

void GridMesh::Unload()
{

}

void GridMesh::Update(float deltaTime)
{
}

void GridMesh::Invalidate()
{
	GenerateGrid();
}

void GridMesh::GenerateGrid()
{
	uint numVerticies = rows * columns;
	vector<PositionTexCoordVertex> vertices(numVerticies);
	vector<vec3> points;

	auto width = columns * scale;
	auto height = rows * scale;

	auto halfWidth = width * 0.5f;
	auto halfHeight = height * 0.5f;

	vec3 originPosition(-halfWidth, 0, -halfHeight);

	for (uint row = 0; row < rows; row++)
	{
		for (uint column = 0; column < columns; column++)
		{
			auto index = row * columns + column;

			auto columnPosition = (float)column * scale;
			auto rowPosition = row * scale;

			vec3 position(columnPosition, 0, rowPosition);
			points.push_back(position);
			vertices[index].position = glm::vec4((originPosition + position), 1);

			glm::vec2 texCoord(row / (float)(rows), column / (float)columns);

			vertices[index].textureCoordinate = texCoord;
		}
	}
	//AddNoise(vertices);

	boundingSphere.Fit(points);

	auto numIndices = (rows - 1) * (columns - 1) * 6;


	vector<uint> indices(numIndices);

	uint index = 0;

	for (uint row = 0; row < rows - 1; row++)
	{
		for (uint column = 0; column < columns - 1; column++)
		{
			auto currentIndex = row * columns + column;
			auto nextRow = (row + 1) * columns + column;
			auto nextColumn = currentIndex + 1;
			auto nextRowNextColumn = nextRow + 1;

			assert(index + 6 <= numIndices);

			// First triangle
			indices[index++] = currentIndex;
			indices[index++] = nextRow;
			indices[index++] = nextRowNextColumn;

			// Second triangle
			indices[index++] = currentIndex;
			indices[index++] = nextRowNextColumn;
			indices[index++] = nextColumn;
		}
	}

	DynamicEnum texturePaths;
	texturePaths.Add(texturePath);

	BindVertexAndIndexData(&renderData, vertices, indices);
	BuildMaterialFromLoaderNode(&material, texturePaths);
}

void GridMesh::AddNoise(vector<PositionTexCoordVertex>& vertices) 
{
	uint numVerticies = rows * columns;
	vector<float> heightMap(numVerticies);

	for (uint row = 0; row < rows; row++)
	{
		for (uint column = 0; column < columns; column++)
		{
			vertices[row * column].position.y = heightMap[row * column];
		}
	}

	int width = 128;
	int height = 128;

	auto xRange = 1.0;
	auto yRange = 1.0;
	auto xFactor = yRange / width;
	auto yFactor = yRange / height;

	for (uint i = 0; i < width; i++)
	{
		for (uint j = 0; j < height; j++)
		{
			float x = xFactor * i;
			float y = yFactor * j;
			float z = 0.0;

			auto value = glm::perlin(vec3(x, y, z));

			value = (value + 1.0f) * 0.5f;

			value = glm::min(value, 1.0f);
			value = glm::max(value, 0.0f);

			heightMap[i * j] = value;
		}
	}


}

void GridMesh::BeforeRender(Camera& camera, Transform& lightTransform) 
{
	// So far do nothing
}