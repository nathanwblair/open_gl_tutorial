#include "Asset.h"

#include <assert.h>
#include "stb_image.h"

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"

#include "Utils.h"

/* Material.h

class TextureSlots
{
	enum TextureSlots
	{
		DiffuseTexture = 0,
		AmbientTexture,
		GlowTexture,
		GlossTexture,
		NormalTexture,
		AlphaTexture,
		DisplacementTexture,

		TextureSlots_Count
	};
}

*/

class Texture :
	public Asset
{
public:

	Texture(string path) : Asset(path)
	{
		LoadWithSTBImage(path);
	}

	~Texture()
	{

	}

	void SetTextureSlot(uint uiSlot)
	{
		uiTextureSlot = uiSlot;
	}

private:
	uint uiTextureID;

	int textureFormat;
	int imageWidth;
	int imageHeight;

	uint uiTextureSlot;

	void Bind() override
	{
		glActiveTexture(GL_TEXTURE0 + uiTextureSlot);
		glBindTexture(GL_TEXTURE_2D, uiTextureID);
	}

	void Unbind() override
	{

	}

	void LoadWithSTBImage(string& _path)
	{
		auto data = stbi_load(path.c_str(), 
			&imageWidth, 
			&imageHeight, 
			&textureFormat, 
			STBI_default);

		if (!data)
		{
			// Failed to load texture
			return;
		}

		auto uiTextureFormat = GL_RGB;

		switch (textureFormat)
		{
		case 1:
			uiTextureFormat = GL_RED;
			break;
		case 2:
			uiTextureFormat = GL_RG;
			break;
		case 3:
			uiTextureFormat = GL_RGB;
			break;
		case 4:
			uiTextureFormat = GL_RGBA;
			break;
		default:
			assert("Unknown texture format");
		}

		glGenTextures(1, &uiTextureID);
		glBindTexture(GL_TEXTURE_2D, uiTextureID);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			uiTextureFormat,
			imageWidth, 
			imageHeight, 
			0, 
			uiTextureFormat, 
			GL_UNSIGNED_BYTE, 
			data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		isInitialized = true;
	}
};