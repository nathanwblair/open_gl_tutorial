#include "Assets/Shader.h"
#include <iostream>

void Shader::BaseSetUniform(string name, uint value) 
{
	glUniform1ui(GetUniformLocation(name), value);
}

void Shader::BaseSetUniform(string name, int value) 
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::BaseSetUniform(string name, float value) 
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::BaseSetUniform(string name, glm::mat4& value, int count) 
{
	glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(value));
}

void Shader::BaseSetUniform(string name, glm::vec3& value, int count) 
{
	glUniform3fv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::BaseSetUniform(string name, glm::vec4& value, int count) 
{
	glUniform4fv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::PrepareUniforms(vector<string> names) 
{
	for (auto& name : names)
	{
		PrepareUniform(name);
	}
}

void Shader::EnableAndInitAttributes() 
{
	isInitializingAttributes = true;

	InitializeAttributes();
}

void Shader::PrepareUniform(string name) 
{
	SafeBind();
	if (uniforms.Find(name) == -1)
	{
		uniforms.Add(name);
	}

	GetUniformLocation(name);
	SafeUnbind();
}

void Shader::Load() 
{
	LoadShaderProgramFromFile();
}

void Shader::Unload() 
{

}

void Shader::LoadShaderProgramFromFile() 
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

		if (line == "")
			break;

		auto fileToLoadPath = fullFilePath + line.substr(5);
		auto fileToLoad = line.substr(0, 4);

		if (fileToLoad == "vert")
		{
			vertShaderID = Load(GL_VERTEX_SHADER, fileToLoadPath);
		}
		else if (fileToLoad == "frag")
		{
			fragShaderID = Load(GL_FRAGMENT_SHADER, fileToLoadPath);
		}
	}

	shaderID = glCreateProgram();
	glAttachShader((GLuint)shaderID, (GLuint)fragShaderID);
	glAttachShader((GLuint)shaderID, (GLuint)vertShaderID);

	SetupAttributeBindings();

	glLinkProgram(shaderID);

	CheckForGLSLErrors();

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	BindIfNeeded();
	InitializeUniforms();
	UnbindIfNeeded();
}

// Check whether a shader compile succeeded.
// Logs to stderr and returns false if ti has failed.
// From https://github.com/johnsietsma/RefEngine/blob/4fbfe5e01cd97d1522e8ec273a396e41e29d3b29/Engine/src/graphics/Program.cpp
bool CheckCompileStatus(GLuint glslShaderID)
{
	GLint result = GL_FALSE;
	int logLength = 0;
	glGetShaderiv(glslShaderID, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE) 
	{
		glGetShaderiv(glslShaderID, GL_INFO_LOG_LENGTH, &logLength);

		auto logBuffer = new char[logLength];
		glGetShaderInfoLog(glslShaderID, logLength, NULL, logBuffer);

		std::cerr << "Compile Error: " << logBuffer << std::endl;

		delete[] logBuffer;
		return false;
	}

	return true;
}



void Shader::CheckForGLSLErrors() 
{
	auto success = 0;
	glGetProgramiv((uint)shaderID, GL_LINK_STATUS, &success);

	auto infoLogLength = 0;
	if (success == GL_FALSE)
	{
		glGetProgramiv((uint)shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		auto infoLog = new char[infoLogLength];
		glGetProgramInfoLog((uint)shaderID, infoLogLength, NULL, infoLog);

		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);

		delete[] infoLog;
	}
}

int Shader::Load(GLenum eType, string& filePath) 
{
	uint glslShaderID = glCreateShader(eType);

	std::ifstream file;
	assert(file.good() && "Unable to open shader file");

	auto shaderCode = GetFile(filePath);
	const auto pCode = shaderCode.c_str();

	glShaderSource(glslShaderID, 1, &pCode, 0);
	glCompileShader(glslShaderID);

	CheckCompileStatus(glslShaderID);

	return glslShaderID;
}

bool Shader::HasUniform(string name) 
{
	return uniforms.Find(name) != -1;
}

int Shader::GetUniformLocation(string name) 
{
	return glGetUniformLocation(shaderID, name.c_str());
}

void Shader::EnableAttributes()
{
	for (uint index = 0; index < attributes.Size(); index++)
	{
		glEnableVertexAttribArray(index);
	}
}

void Shader::SetupAttributeBindings() 
{
	for (uint index = 0; index < attributes.Size(); index++)
	{
		glBindAttribLocation(shaderID, index, attributes.Get(index).c_str());
	}
}

void Shader::Bind() 
{
	glUseProgram(shaderID);
}

void Shader::Unbind() 
{
	glUseProgram(0);
}

Shader::Shader(string _path) 
	: TextAsset("data/shaders/" + _path),
	shaderID(-1) 
{
}

void Shader::Init()
{
	Load();
}