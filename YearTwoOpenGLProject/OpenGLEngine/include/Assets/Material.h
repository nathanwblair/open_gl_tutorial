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
	enum TextureSlot
	{
		DiffuseTexture = 0,
		AmbientTexture,
		GlowTexture,
		GlossTexture,
		NormalTexture,
		AlphaTexture,
		DisplacementTexture,

		NumSlots
	};

	Texture * textures[TextureSlot::NumSlots];
	

	Material(string path)
		: Asset(path)
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