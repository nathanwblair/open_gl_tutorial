#pragma once

#include <string>
#include <typeinfo>
#include <map>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <unordered_map>

#include "dynamic_enum\DynamicEnum.h"

#include "Rendering\RenderData.h"

#include "Utils.h"
#include "TextAsset.h"
#include "merge_structs\Merger.h"

template <typename vertex_data_type>
class Shader :
        public TextAsset
{
private:
	int currentOffset;

	bool isInitializingAttributes;
public:
    int shaderID;

	typedef vertex_data_type vertex_type;
	DynamicEnum attributes;
	DynamicEnum uniforms;

	typedef vector<vertex_data_type> vertex_array_type;
	typedef vector<uint> index_array_type;

	vertex_array_type verticies;
	index_array_type indicies;

    
	Shader(string _path, 
		vertex_array_type  _verticies = vertex_array_type(), 
		index_array_type _indicies = index_array_type())
		: TextAsset(_path),
			shaderID(-1),
			verticies(_verticies),
			indicies(_indicies)
    {
        
    }

	virtual void InitializeUniforms() = 0;
	virtual void InitializeAttributes() = 0;


	void BindVertexAndIndexData(RenderData** renderData)
	{		
		assert(renderData);

		*renderData = new RenderData();
		(*renderData)->GenerateBuffers(RenderData::Buffers::ALL);

		(*renderData)->Bind();

		glBufferData(GL_ARRAY_BUFFER,
			verticies.size() * sizeof(vertex_data_type),
			verticies.data(), GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indicies.size() * sizeof(uint),
			indicies.data(), GL_STATIC_DRAW);

		EnableAttributes();
		InitializeAttributes();

		(*renderData)->SetIndexCount(indicies.size());

		(*renderData)->Unbind();

	}


	//(void*)(offsetof(FBXVertex, normal))
	template <typename type>
	void SetAttribute(string name, type value)
	{
		if (!isInitializingAttributes)
			throw std::bad_function_call("Cannot set attribute until initializing attributes");

		if (attributes.Find(name) == -1)
		{
			attributes.Add(name);
		}

		if (NAME(type) == NAME(float))
		{
			glVertexAttribPointer(attributes.Get(name), sizeof(type), GL_FLOAT, GL_FALSE, sizeof(vertex_data_type), (void*)(currentOffset));
		}
		else
		{
			throw std::invalid_argument("Attribute type unsupported");
		}

		currentOffset += sizeof(type);
	}
	
    template <typename type>
    void SetUniform(string name, type value)
    {
		if (uniforms.Find(name) == -1)
		{
			uniforms.Add(name);
		}

		auto wasBound = BindIfNeeded();

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

		UnbindIfNeeded(wasBound);
    }

	void Load()
	{
		LoadShaderProgramFromFile();
	}

    void LoadShaderProgramFromFile()
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

        CheckForGLSLErrors();

        glDeleteShader(fragShaderID);
        glDeleteShader(fragShaderID);


        InitializeUniforms();
    }


    void CheckForGLSLErrors()
    {
        int success = GL_FALSE;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &success);
        if (success == GL_FALSE) {
            auto infoLogLength = 0;
            glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

            char *infoLog = new char[infoLogLength];
            glGetProgramInfoLog(shaderID, infoLogLength, 0, infoLog);

            printf("Error: Failed to link shader program!\n");
            printf("%s\n", infoLog);

            delete[] infoLog;
        }
    }


    int LoadShader(GLenum eType, string& filePath)
    {
        uint glslShaderID = glCreateShader(eType);

        std::ifstream file;
        assert(file.good() && "Unable to open shader file");

        auto shaderCode = GetFile(filePath);
        const auto pCode = shaderCode.c_str();
        glShaderSource(glslShaderID, 1, &pCode, 0);
        glCompileShader(glslShaderID);

        return glslShaderID;
    }


	bool HasUniform(string name)
	{
		return uniforms.Find(name) != -1;
	}


    int GetUniformLocation(string name)
    {
        return glGetUniformLocation(shaderID, name.c_str());
    }


	void EnableAttributes()
	{
		for (uint index = 0; index < attributes.Size(); index++)
		{
			glEnableVertexAttribArray(index); 
		}
	}


	void SetupAttributeBindings()
	{
		for (uint index = 0; index < attributes.Size(); index++)
		{
			glBindAttribLocation(shaderID, index, attributes.Get(index));
		}
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