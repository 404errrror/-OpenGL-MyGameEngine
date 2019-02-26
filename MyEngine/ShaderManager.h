#pragma once
#include "Global.h"
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	static void Release();
	static void ShaderLoading();
	static GLuint* GetShader(const char* shaderKey);

private:
	static std::unordered_map<std::string, GLuint*> map;

private:
	
	/// <summary>
	/// 쉐이더파일을 읽고 map에 저장합니다.
	/// <summary>
	static bool LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char* shaderKey);
};

