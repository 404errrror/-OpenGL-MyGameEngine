#include "ShaderManager.h"

std::unordered_map<std::string, GLuint*> ShaderManager::map;

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}


void ShaderManager::Release()
{
	for (std::unordered_map<std::string, GLuint*>::unordered_map::iterator it = map.begin(); it != map.end(); ++it)
	{
		delete it->second;
	}
}


void ShaderManager::ShaderLoading()
{
	LoadShaders("TestVertexShader.vertexshader", "TestFragmentShader.fragmentshader", "TestShader");
	LoadShaders("ImageVertexShader.vertexshader", "ImageFragmentShader.fragmentshader", "ImageShader");
	LoadShaders("LineVertexShader.vertexshader", "LineFragmentShader.fragmentshader", "LineShader");
	LoadShaders("AddColorVertexShader.vertexshader", "AddColorFragmentShader.fragmentshader", "AddColor");
}


GLuint* ShaderManager::GetShader(const char* shaderKey)
{
	return map[shaderKey];
}


bool ShaderManager::LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* shaderKey) {

	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", vertex_file_path);
		getchar();
		return false;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// 버텍스 쉐이더를 컴파일
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// 프래그먼트 쉐이더를 컴파일
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// 프로그램에 링크
	printf("Linking program\n");
	GLuint* ProgramID = new GLuint(glCreateProgram());

	glAttachShader(*ProgramID, VertexShaderID);
	glAttachShader(*ProgramID, FragmentShaderID);
	glLinkProgram(*ProgramID);

	// 프로그램 검사
	glGetProgramiv(*ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(*ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(*ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(*ProgramID, VertexShaderID);
	glDetachShader(*ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	map.insert(std::pair<std::string, GLuint*>(shaderKey, ProgramID));
	return true;
}

