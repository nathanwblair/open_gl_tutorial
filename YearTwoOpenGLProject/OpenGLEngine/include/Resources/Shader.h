#pragma once

#include <string>
#include <typeinfo>
#include <map>
#include <fstream>
#include <assert.h>
#include <sstream>

#include "Utils.h"
#include "TextAsset.h"

using std::string;
using std::map;

class Shader :
        public TextAsset
{
    int shaderID;
    
    Shader() 
        : shaderID(-1)
    {
        
    }


    template <typename type>
    void SetUniform(string name, type value)
    {
        string typeName = NAME(type);
        
        if (typeName == NAME(uint))
        {
            glUniform1ui(GetUniformLocation(name), value);
        }
        else if (typeName == NAME(int))
        {
            glUniform1i(GetUniformLocation(name), value);
        }
        else if (typeName == NAME(float))
        {
            glUniform1f(GetUniformLocation(name), value);
        }
        else if (typeName == NAME(glm::mat4))
        {
            glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
        }
        else if (typeName == NAME(glm::vec3))
        {
            glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
        }
        else if (typeName == NAME(glm::vec4))
        {
            glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
        }
    }


    void LoadShaderProgramFromFile(string& path)
    {
        assert(shaderID < 0 && "Already have loaded a shader");

        std::ifstream file;
        file.open(path, std::ifstream::in);

        assert(file.good() && "Failed to open shader file!");

        string fullFilePath = path.substr(0, path.find_last_of('/') + 1);

        auto vertShaderID = 0;
        auto fragShaderID = 0;

        while (file.good())
        {
            string line = "";
            std::getline(file, line);

            auto fileToLoadPath = fullFilePath + line.substr(5);
            auto fileToLoad = line.substr(0, 4);

            if (fileToLoad == "vert")
            {
                vertShaderID = LoadShader(GL_VERTEX_SHADER, fileToLoadPath);
            }
            else if (fileToLoad == "frag")
            {
                fragShaderID = LoadShader(GL_VERTEX_SHADER, fileToLoadPath);
            }
        }

        shaderID = glCreateProgram();
        glAttachShader((GLuint)shaderID, (GLuint)fragShaderID);
        glAttachShader((GLuint)shaderID, (GLuint)vertShaderID);

        glLinkProgram(shaderID);

        // Error checking
        {
            int success = GL_FALSE;
            glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        }
    }


    int LoadShader(GLenum eType, string& filePath)
    {
        uint iShader = glCreateShader(eType);

        std::ifstream file;
        file.open(filePath);
        assert(file.good() && "Unable to open shader file");

        std::stringstream ss;
        ss << file.rdbuf();
        file.close();


        string shaderCode = ss.str();
        const char* pCode = shaderCode.c_str();
        glShaderSource(iShader, 1, (const char**)&pCode, 0);
        glCompileShader(iShader);

        return iShader;
    }


    void AddUniform(string name)
    {
        GetUniformLocation(name);
    }

    int GetUniformLocation(string name)
    {
        return glGetUniformLocation(shaderID, name.c_str());
    }
    
    
    void Bind()
    {
        glUseProgram(shaderID);
    }


    void Unbind()
    {
        glUseProgram(0);
    }
};