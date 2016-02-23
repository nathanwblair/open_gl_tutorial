#pragma once

#include "Utils.h"

using std::string;

class Asset
{
public:
    string path;

    Asset(string _path) : path(_path)
    {

    }

    virtual void Load(string _filePath) = 0;

    virtual void Unload() = 0;

    string GetDirectory()
    {
        auto lastSlash = path.find_last_of("/");

        if (lastSlash == string::npos)
            return path;

        return path.substr(0, lastSlash + 1);
    }

protected:
    string filePath;
};
