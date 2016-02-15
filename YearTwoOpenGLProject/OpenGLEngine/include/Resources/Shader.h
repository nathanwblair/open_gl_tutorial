#pragma once

#include <string>
#include <typeinfo>
#include <map>

#include "Utils.h"
#include "TextAsset.h"

using std::string;
using std::map;

class Shader :
        public TextAsset
{
    uint shaderID;
    
    Shader() 
        : shaderID(0)
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