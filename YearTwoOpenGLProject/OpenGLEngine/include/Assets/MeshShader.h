#pragma once

#include "merge_structs\Merger.h"
#include "FBXFile.h"
#include "Shader.h"

template<class vertex_struct>
class MeshShader
	: public Shader<vertex_struct>
{
	typedef FBXVertex default_vertex_struct;
};

template<>
class MeshShader<FBXVertex>
	: public Shader<FBXVertex>
{
	
};

