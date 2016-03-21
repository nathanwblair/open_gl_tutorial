#include "Asset.h"

#include <assert.h>
#include <dynamic_enum/DynamicEnum.h>

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"

#include "Utils.h"

#include "Texture.h"

#include "FBXFile.h"

class Material 
	: public Asset
{
private:
	bool isFBXMaterial;
	FBXMaterial * material;
	DynamicEnum enumMaterial;
public:
	enum TextureSlot
	{
		DiffuseTexture = 0,
		AmbientTexture,
		GlowTexture,
		SpecularTexture,
		GlossTexture,
		NormalTexture,
		AlphaTexture,
		DisplacementTexture,

		NumSlots
	};

	Texture * textures[TextureSlot::NumSlots];

	Material(FBXMaterial* _material, string path);

	Material(DynamicEnum _material, string path);

	~Material();

	void Load();

	void Unload();

	template<class T>
	void InitializeFromLoaderMaterial(T* material, std::string additionalPath="");

	bool HasTexture(TextureSlot slot);

	bool IsInitialized();

	void LoadIfExists(TextureSlot slot, FBXMaterial* rawMaterial, uint textureType, string additionalPath);

	void LoadIfExists(TextureSlot slot, DynamicEnum * texturePaths, uint textureType, string additionalPath);

	void Bind();

	void Unbind();
};

template<class T>
void Material::InitializeFromLoaderMaterial(T* material, std::string additionalPath)
{
	LoadIfExists(TextureSlot::DiffuseTexture, material, TextureSlot::DiffuseTexture, additionalPath);
	LoadIfExists(TextureSlot::AmbientTexture, material, TextureSlot::AmbientTexture, additionalPath);
	LoadIfExists(TextureSlot::GlowTexture, material, TextureSlot::GlowTexture, additionalPath);
	LoadIfExists(TextureSlot::SpecularTexture, material, TextureSlot::SpecularTexture, additionalPath);
	LoadIfExists(TextureSlot::GlossTexture, material, TextureSlot::GlossTexture, additionalPath);
	LoadIfExists(TextureSlot::NormalTexture, material, TextureSlot::NormalTexture, additionalPath);
	LoadIfExists(TextureSlot::AlphaTexture, material, TextureSlot::AlphaTexture, additionalPath);
	LoadIfExists(TextureSlot::DisplacementTexture, material, TextureSlot::DisplacementTexture, additionalPath);

	isInitialized = true;
}