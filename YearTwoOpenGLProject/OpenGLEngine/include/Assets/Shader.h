#pragma once

#include <string>
#include <typeinfo>
#include <map>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <unordered_map>
#include <functional>

#include "dynamic_enum/DynamicEnum.h"

#include "Rendering/RenderData.h"

#include "Utils.h"
#include "TextAsset.h"
#include "merge_structs/Merger.h"

class Shader :
        public TextAsset
{
private:
	int currentOffset;

	bool isInitializingAttributes;

	uint TSize;

	void BaseSetUniform(string name, uint value);

	void BaseSetUniform(string name, int value);

	void BaseSetUniform(string name, float value);

	void BaseSetUniform(string name, glm::mat4& value, int count = 1);

	void BaseSetUniform(string name, glm::vec3& value, int count = 1);

	void BaseSetUniform(string name, glm::vec4& value, int count=1);


public:
    int shaderID;

	DynamicEnum attributes;
	DynamicEnum uniforms;

	Shader(string _path);

	void Init();

	virtual void InitializeUniforms() = 0;
	virtual void InitializeAttributes() = 0;

	//template<class T>
	//vector<float> ToFloatArray(vector<T>& input)
	//{
	//	TSize = sizeof(T);

	//	verticies.assign((float*)input.data(), (float*)input.data() + (input.size() * sizeof(T)) / sizeof(float));
	//}

	void PrepareUniforms(vector<string> names);

	void EnableAndInitAttributes();

	template<typename type>
	void SetAttribute(string name, GL::Primitive primitive = GL::Primitive::Float);

	void PrepareUniform(string name);

	template<typename type>
	void SetUniform(string name, type value);

	template<typename type>
	void SetArrayUniform(string name, type * valueArr, int count);

	virtual void Load();

	void Unload();

	void LoadShaderProgramFromFile();

	void CheckForGLSLErrors();

	int Load(GLenum eType, string& filePath);

	bool HasUniform(string name);

	int GetUniformLocation(string name);

	void EnableAttributes();

	void SetupAttributeBindings();

	void Bind();

	void Unbind();
};

template<typename type>
void Shader::SetAttribute(string name, GL::Primitive primitive) {
	assert(isInitializingAttributes && "Is not initializing attributes");

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

template<typename type>
void Shader::SetArrayUniform(string name, type * valueArr, int count) 
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

template<typename type>
void Shader::SetUniform(string name, type value) 
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