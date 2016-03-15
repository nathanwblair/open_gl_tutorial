#pragma once

#include <string>
#include <typeinfo>
#include <map>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <unordered_map>
#include <functional>

#include "dynamic_enum\DynamicEnum.h"

#include "Rendering\RenderData.h"

#include "Utils.h"
#include "TextAsset.h"
#include "merge_structs\Merger.h"

class Shader :
        public TextAsset
{
private:
	int currentOffset;

	bool isInitializingAttributes;

	uint TSize;

	void BaseSetUniform(string name, uint value)
	{
		glUniform1ui(GetUniformLocation(name), value);
	}


	void BaseSetUniform(string name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}


	void BaseSetUniform(string name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}


	void BaseSetUniform(string name, glm::mat4& value, int count = 1)
	{
		glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(value));
	}


	void BaseSetUniform(string name, glm::vec3& value, int count = 1)
	{
		glUniform3fv(GetUniformLocation(name), count, glm::value_ptr(value));
	}


	void BaseSetUniform(string name, glm::vec4& value, int count=1)
	{
		glUniform4fv(GetUniformLocation(name), count, glm::value_ptr(value));
	}
public:
    int shaderID;

	DynamicEnum attributes;
	DynamicEnum uniforms;
    
	Shader(string _path)
		: TextAsset("shaders/" + _path),
			shaderID(-1)
    {
        
    }

	virtual void InitializeUniforms() = 0;
	virtual void InitializeAttributes() = 0;

	//template<class T>
	//vector<float> ToFloatArray(vector<T>& input)
	//{
	//	TSize = sizeof(T);

	//	verticies.assign((float*)input.data(), (float*)input.data() + (input.size() * sizeof(T)) / sizeof(float));
	//}


	void PrepareUniforms(vector<string> names)
	{
		for (auto& name : names)
		{
			PrepareUniform(name);
		}
	}


	void EnableAndInitAttributes()
	{
		//EnableAttributes();
		InitializeAttributes();
	}

	template <typename type>
	void SetAttribute(string name, GL::Primitive primitive = GL::Primitive::Float)
	{
		if (!isInitializingAttributes)
			throw std::exception("Cannot set attribute until initializing attributes");
		
		if (primitive != GL::Primitive::Float)
		{
			throw std::invalid_argument("Attribute type unsupported, floats are the only supported primitive");
		}
		
		if (attributes.Find(name) == -1)
		{
			attributes.Add(name);
		}

		glEnableVertexAttribArray(attributes.Get(name));
		
		glVertexAttribPointer(attributes.Get(name), sizeof(type) / (GLenum)GL::SizeOf(primitive), (GLenum)primitive, GL_FALSE, TSize, (void*)(currentOffset));

		currentOffset += sizeof(type);
	}

	void PrepareUniform(string name)
	{
		SafeBind();
		if (uniforms.Find(name) == -1)
		{
			uniforms.Add(name);
		}

		GetUniformLocation(name);
		SafeUnbind();
	}

	// Eventually will support struct uniforms through magical hackery + templating (hence templating)
	template <typename type>
	void SetUniform(string name, type value)
	{
		if (uniforms.Find(name) == -1)
		{
			uniforms.Add(name);
		}

		auto wasBound = BindIfNeeded();

		//      string typeName = NAME(type);        
		//		auto isUInt =	(typeName == NAME(uint));
		//		auto isInt =	(typeName == NAME(int));
		//		auto isFloat =	(typeName == NAME(float));
		//		auto isMat4 =	(typeName == NAME(glm::mat4));
		//		auto isVec3 =	(typeName == NAME(glm::vec3));
		//		auto isVec4 =	(typeName == NAME(glm::vec4));
		//
		BaseSetUniform(name, value);

		UnbindIfNeeded(wasBound);
	}

	// Eventually will support struct uniforms through magical hackery + templating (hence templating)
	template <typename type>
	void SetArrayUniform(string name, type * valueArr, int count)
	{
		if (uniforms.Find(name) == -1)
		{
			uniforms.Add(name);
		}

		auto wasBound = BindIfNeeded();

		//      string typeName = NAME(type);        
		//		auto isUInt =	(typeName == NAME(uint));
		//		auto isInt =	(typeName == NAME(int));
		//		auto isFloat =	(typeName == NAME(float));
		//		auto isMat4 =	(typeName == NAME(glm::mat4));
		//		auto isVec3 =	(typeName == NAME(glm::vec3));
		//		auto isVec4 =	(typeName == NAME(glm::vec4));
		//
		BaseSetUniform(name, *valueArr, count);

		UnbindIfNeeded(wasBound);
	}


	void Load() override
	{
		LoadShaderProgramFromFile();
	}


	void Unload() override
	{

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
                vertShaderID = Load(GL_VERTEX_SHADER, fileToLoadPath);
            }
            else if (fileToLoad == "frag")
            {
                fragShaderID = Load(GL_VERTEX_SHADER, fileToLoadPath);
            }
        }

        shaderID = glCreateProgram();
        glAttachShader((GLuint)shaderID, (GLuint)fragShaderID);
        glAttachShader((GLuint)shaderID, (GLuint)vertShaderID);

		SetupAttributeBindings();

        glLinkProgram(shaderID);

        CheckForGLSLErrors();

        glDeleteShader(fragShaderID);
        glDeleteShader(fragShaderID);

		BindIfNeeded();
        InitializeUniforms();
		UnbindIfNeeded();
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


    int Load(GLenum eType, string& filePath)
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
			glBindAttribLocation(shaderID, index, attributes.Get(index).c_str());
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