#include "Asset.h"

#include <assert.h>

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"

#include "Utils.h"

class Material 
	: public Asset
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