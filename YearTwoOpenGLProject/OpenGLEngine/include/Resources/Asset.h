#pragma once

#include <string>

using std::string;

class Asset
{
public:
    virtual void Load(string _filePath) = 0;

    Asset() = delete;
    Asset(Asset&& other) = delete;
    Asset& operator=(Asset&& other) = delete;
    Asset(const Asset& other) = delete; //No copy
    Asset& operator=(Asset& other) = delete;

    void Unload();

protected:
    string filePath;
};
