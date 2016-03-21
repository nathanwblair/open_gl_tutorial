#include "Asset.h"

#include <assert.h>
#include "stb_image.h"

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"

#include "Utils.h"


class Texture :
	public Asset
{
public:

	Texture(string path);

	~Texture();

	void SetTextureSlot(uint uiSlot);

	void Load();

	void Unload();

private:
	uint uiTextureID;

	int textureFormat;
	int imageWidth;
	int imageHeight;

	uint uiTextureSlot;

	void Bind();

	void Unbind();

	void LoadWithSTBImage();
};