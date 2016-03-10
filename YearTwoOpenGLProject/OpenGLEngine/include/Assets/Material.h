#include "Asset.h"

#include <assert.h>

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"

#include "Utils.h"

#include "Texture.h"

#include "FBXFile.h"

class Material 
	: public Asset
{
private:
	FBXMaterial * material;
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
	

	Material(FBXMaterial* _material, string path)
		: Asset(path),
			material(_material)
	{
		auto sizeOfTextures = sizeof(Texture*) * TextureSlot::NumSlots;

		memset(textures, 0, sizeOfTextures);
	}

	
	~Material()
	{
		for (int i = 0; i < TextureSlot::NumSlots; i++)
		{
			if (textures[i])
			{
				textures[i]->Unload();
			}
		}
	}


	void Load() override
	{
		InitializeFromLoaderMaterial(material);
	}

	void Unload() override
	{
	}


	void InitializeFromLoaderMaterial(FBXMaterial* material, std::string additionalPath="")
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


	bool HasTexture(TextureSlot slot)
	{
		return textures[slot] != nullptr;
	}

	bool IsInitialized()
	{
		return isInitialized;
	}

	void LoadIfExists(TextureSlot slot, FBXMaterial* rawMaterial, uint textureType, string additionalPath)
	{
		if (rawMaterial->textures[textureType])
		{
			textures[slot] = new Texture(additionalPath + rawMaterial->textures[textureType]->path);
			textures[slot]->SetTextureSlot(slot);
		}
	}

	void Bind() override
	{
		for (int i = 0; i < TextureSlot::NumSlots; i++)
		{
			if (textures[i])
			{
				textures[i]->SafeBind();
			}
		}
	}

	void Unbind()
	{
		for (int i = 0; i < TextureSlot::NumSlots; i++)
		{
			if (textures[i])
			{
				textures[i]->SafeUnbind();
			}
		}
	}
};