#pragma once

#include <fsteram>
#include <sstream>
#include <string>

using std::string;

class Shader
{
    uint shaderID;
    
    Shader() 
        : shaderID(-1)
    {
        
    }
    
    template <typename type>
    void SetUniform(string name, type value)
    {
        string name = typeid(name).name();
        
        if (name == "unsigned int")
        {
            
        }
        else if (name == "int")
        {
            
        }
        else if (name == "float")
        {
            
        }
        else if (name == "mat4")
        {
            
            
            glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::Projection], 1, GL_FALSE, glm::value_ptr(mat));
        }
        else if (name == "vec4")
        {
            
            
            glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::Projection], 1, GL_FALSE, glm::value_ptr(mat));
        }
        else if (name == "vec3")
        {
            
            
            glUniformMatrix4fv(m_shaderUniforms[SupportedShaderUniforms::Projection], 1, GL_FALSE, glm::value_ptr(mat));
        }
        

    }
    
    
    template <typename type>
    void CreateUniform(string name)
    {
        
    }
    
    
    void Bind()
    {
        glUseProgram(shaderID)
    }
    
    void Unbind()
    {
        glUseProgram(0)
    }
}