#include "Assets/Material.h"

Material::Material(FBXMaterial* _material, string path) : Asset(path),
                                                          material(_material) {
	isFBXMaterial = true;
	auto sizeOfTextures = sizeof(Texture*) * TextureSlot::NumSlots;

	memset(textures, 0, sizeOfTextures);
}

Material::Material(DynamicEnum _material, string path) : Asset(path),
                                                         enumMaterial(_material) {
	isFBXMaterial = false;
	auto sizeOfTextures = sizeof(Texture*) * TextureSlot::NumSlots;

	memset(textures, 0, sizeOfTextures);
}

void Material::Load() {
	if (isFBXMaterial)
		InitializeFromLoaderMaterial(material);
	else
		InitializeFromLoaderMaterial(&enumMaterial);
}

void Material::Unload() {
	for (int i = 0; i < TextureSlot::NumSlots; i++)
	{
		if (textures[i])
		{
			textures[i]->Unload();
		}
	}
}

bool Material::HasTexture(TextureSlot slot) {
	return textures[slot] != nullptr;
}

void Material::LoadIfExists(TextureSlot slot, FBXMaterial* rawMaterial, uint textureType, string additionalPath) {
	if (rawMaterial->textures[textureType])
	{
		textures[slot] = new Texture(additionalPath + rawMaterial->textures[textureType]->path);
		textures[slot]->SetTextureSlot(slot);
	}
}

void Material::LoadIfExists(TextureSlot slot, DynamicEnum * texturePaths, uint textureType, string additionalPath) {
	if (texturePaths->Has(textureType))
	{
		textures[slot] = new Texture(additionalPath + texturePaths->Get(textureType));
		textures[slot]->SetTextureSlot(slot);
	}
}

void Material::Bind() {
	for (int i = 0; i < TextureSlot::NumSlots; i++)
	{
		if (textures[i])
		{
			textures[i]->SafeBind();
		}
	}
}

void Material::Unbind() {
	for (int i = 0; i < TextureSlot::NumSlots; i++)
	{
		if (textures[i])
		{
			textures[i]->SafeUnbind();
		}
	}
}

bool Material::IsInitialized() {
	return isInitialized;
}

Material::~Material() {
}