#pragma once
#include "Asset.h"

#include <string>

using std::string;

class TextAsset
    : public Asset
{
public:
    TextAsset(string _path)
            : Asset(_path)
    {

    }

    string GetFile(string _path)
    {
        std::ifstream file;
        file.open(_path);
        assert(file.good() && "Unable to open asset file");

        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        return ss.str();
    }
};