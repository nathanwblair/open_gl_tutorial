#include "Assets/Mesh.h"

Mesh::Mesh(string path) : Asset(path),
                               renderData(nullptr),
                               shader(nullptr),
                               material(nullptr),
                               isValidated(nullptr) 
{
	//if (path != "")
	//{
	//	Load();
	//}
}

void Mesh::SetShader(MeshShader * _shader) {
	shader = _shader;

	for (auto subMesh : subMeshes)
	{
		subMesh->SetShader(_shader);
	}
}

void Mesh::Unload() {
	Unbind();

	material->Unload();

	for (auto subMesh : subMeshes)
	{
		subMesh->Unload();
	}

	subMeshes.clear();
}

void Mesh::BuildMaterialFromLoaderNode(Material** material, DynamicEnum loaderMaterial, string additionalPath) {
	*material = new Material(loaderMaterial, "");
}

void Mesh::BuildMaterialFromLoaderNode(Material** material, FBXMaterial* loaderMaterial, string additionalPath) {
	assert(loaderMaterial);

	*material = new Material(loaderMaterial, loaderMaterial->name);
}

void Mesh::Render(Camera& camera, Transform& lightTransform, Transform& transform, bool bindShaderUnifroms) {
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

void Mesh::Update(float deltaTime) {

}

void Mesh::Bind() {
	if (shader)
		shader->Bind();
	if (material)
		material->Bind();

	renderData->Bind();
}

void Mesh::Unbind() {
	if (shader)
		shader->Unbind();
	if (material)
		material->Unbind();

	renderData->Unbind();
}