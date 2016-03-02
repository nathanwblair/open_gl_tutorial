#pragma once

#include "Utils.h"

using std::string;

class Asset
{
protected:
	string filePath;
	bool isInitialized;
	bool isBound;

	virtual void Unbind()
	{

	}
	virtual void Bind()
	{

	}

public:
    string path;

	Asset(string _path) : path(_path), isInitialized(false), isBound(false)
    {

    }

    virtual void Load() = 0;

    virtual void Unload() = 0;

	bool BindIfNeeded()
	{
		if (!isBound)
		{
			SafeUnbind();
			return true;
		}

		return false;
	}

	void UnbindIfNeeded(bool check)
	{
		if (check)
			SafeUnbind();
	}

	void UnbindIfNeeded()
	{
		if (isBound)
			SafeUnbind();
	}

	void SafeBind()
	{
		isBound = true;

	}

	void SafeUnbind()
	{
		isBound = false;
	}

    string GetDirectory()
    {
        auto lastSlash = path.find_last_of("/");

        if (lastSlash == string::npos)
            return path;

        return path.substr(0, lastSlash + 1);
    }
};
