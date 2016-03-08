#pragma once
#include <vector>
#include <assert.h>
#include "Utils.h"

#include "Rendering/RenderData.h"
#include "MeshShader.h"

#include "Assets/Material.h"
#include "Assets/Asset.h"

class Mesh 
	: public Asset
{
private:
    std::vector<Mesh*> subMeshes;
	MeshShader * shader;
	Material * material;

	RenderData * renderData;

	bool isValidated;

public:
	
	Mesh(string path)
		: Asset(path),
		renderData(nullptr),
		shader(nullptr),
		material(nullptr),
		isValidated(nullptr)
	{
		auto indexFileExtension = path.find_last_of(".") + 1;
		
		assert(indexFileExtension != 0 && "Need to include file extension");

		auto fileExtension = path.substr(indexFileExtension);

		if (fileExtension == "fbx")
		{
			LoadFromFBX();
		}
	}

	void LoadFromFBX()
	{
		FBXFile * file = new FBXFile;

		auto isLoaded = file->load(path.c_str());
		if (!isLoaded)
		{
			assert(false && "ERROR: Failed to load FBX file!");
			return;
		}

		FBXMeshNode * mesh = file->getMeshByIndex(0);
		assert(mesh && "Require at least one mesh in your FBX");

		//BuildRenderDataFromLoaderNode

	}

//	void BU

};