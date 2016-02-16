#pragma once

#include <string>

using std::string;

class Asset
{
public:
    virtual void Load(string _filePath) = 0;

    void Unload();

protected:
    string filePath;
};
