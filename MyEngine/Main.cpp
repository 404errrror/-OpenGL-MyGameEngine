
#include "Global.h"
#include "GameLoop.h"


int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);									// 1x 안티에일리어싱
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// MacOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// 옛날 OpenGL은 안쓰게.


	// 새창을 열고, OpenGL 컨텍스트 생성.
	g_window = glfwCreateWindow(g_width, g_height, "MyEngine", NULL, NULL);
	if (g_window == NULL)
	{
		fprintf(stderr, "GLFW 윈도우를 여는데 실패했습니다. Intel GPU를 사용한다면 3.3을 지원하지 않습니다.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(g_window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLE\n");
		return -1;
	}

	glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//메모리 누수 체크.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_crtBreakAlloc = 4347;


	// glSetting

	//// set up view
	//glViewport(0, 0, g_width, g_height);
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glDepthMask(GL_TRUE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	}


	////glEnable(GL_DEPTH_TEST);
	////glEnable(GL_COLOR);
	//glDepthFunc(GL_LEQUAL);
	////glDepthMask(true);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	//glDisable(GL_POINT_SMOOTH);
	//glDisable(GL_LINE_SMOOTH);
	//glDisable(GL_POLYGON_SMOOTH);
	//glDisable(GL_MULTISAMPLE);
	glfwSwapInterval(0);				// 수직동기화 끄기
	glDisable(GL_CULL_FACE);

	GameLoop gameLoop;
	_CrtDumpMemoryLeaks();
	gameLoop.Initialize();
	while (gameLoop.Update());
	gameLoop.Release();
	_CrtDumpMemoryLeaks();
	return 0;
}