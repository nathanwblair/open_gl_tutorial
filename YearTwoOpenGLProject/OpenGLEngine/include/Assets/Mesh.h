#pragma once
#include <vector>
#include <assert.h>
#include "Utils.h"

#include "Rendering/RenderData.h"
#include "Shader.h"

#include "Assets/Material.h"

class Mesh 
	: public Asset
{
private:
    std::vector<Mesh*> subMeshes;
	Shader * shader;
	Material * material;

public:
    Mesh(string _path)
        : Asset(_path)
    {

    }


};