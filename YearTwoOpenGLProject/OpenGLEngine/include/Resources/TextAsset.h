#pragma once
#include "Asset.h"

#include <string>

using std::string;

class TextAsset
    : public Asset
{
public:
    string GetFile(string path)
    {
        std::ifstream file;
        file.open(path);
        assert(file.good() && "Unable to open asset file");

        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        return ss.str();
    }
};