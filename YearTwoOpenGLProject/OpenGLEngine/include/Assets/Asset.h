#pragma once

#include "Utils.h"

using std::string;

class Asset
{
public:
	string filePath;
	bool isInitialized;
	bool isBound;

	virtual void Unbind();

	virtual void Bind();

    string path;

	Asset(string _path);

    virtual void Load() = 0;

    virtual void Unload() = 0;

	bool BindIfNeeded();

	void UnbindIfNeeded(bool check);

	void UnbindIfNeeded();

	void SafeBind();

	void SafeUnbind();

	string GetDirectory();
};
