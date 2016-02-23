#pragma once

#include "Rendering/RenderData.h"

#include <vector>
#include <assert.h>
#include "Utils.h"

#ifdef FBX_SUPPORTED
#include "FBXFile.h"
#endif

class Mesh : public Asset
{
private:
    std::vector<Mesh*> subMeshes;

public:
    Mesh(string _path)
        : Asset(_path)
    {

    }
};