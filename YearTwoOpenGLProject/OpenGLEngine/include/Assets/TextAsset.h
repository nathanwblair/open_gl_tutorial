#pragma once
#include "Assets/Asset.h"
#include "Utils.h"

class TextAsset
    : public Asset
{
public:
	TextAsset(string _path);

	string GetFile(string _path);
};