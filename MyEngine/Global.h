#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>

#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Box2D\Box2D.h"

#include "Random.h"
#include "Vector3.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "MouseManager.h"
#include "Time.h"
#include "Physics2D.h"

#ifdef _WIN64
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib, "./lib/glfw3.lib")
#pragma comment(lib, "./lib/glfw3dll.lib")
#pragma comment(lib, "./lib/glew32.lib")
#pragma comment(lib, "./lib/glew32s.lib")



#elif _WIN32
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib, "./lib(x86)/glfw3.lib")
#pragma comment(lib, "./lib(x86)/glfw3dll.lib")
#pragma comment(lib, "./lib(x86)/glew32.lib")
#pragma comment(lib, "./lib(x86)/glew32s.lib")
#pragma comment(lib, "./lib(x86)/libpng16.lib")
#pragma comment(lib, "./lib(x86)/zdll.lib")
#pragma comment(lib, "./lib(x86)/al/OpenAL32.lib")
#pragma comment(lib, "./lib(x86)/al/EFX-Util.lib")


#ifdef _DEBUG
#pragma comment(lib, "./lib(x86)/Debug/Box2D.lib")
#else // Release
#pragma comment(lib, "./lib(x86)/Release/Box2D.lib")
#endif // _DEBUG


#endif


//#define NO_SOUND
#define DEBUG
#define PIXEL_PER_UNIT 32			// 1유닛당 픽셀 몇개를 할당할 것인지.
#define METER_PER_UNIT 1			// 1유닛당 몇 미터로 할것인지. -> 중력과 같은 물리 계산 속도에 영향을 미침.

// Layer
#define LAYER_CURSOR -20.0f
#define LAYER_UI -30.0f
#define LAYER_BLOCK -40.0f
#define LAYER_ITEM -45.0f
#define LAYER_CHARATER -50.0f
#define LAYER_BLOCK_BACKGROUND -60.0f
#define LAYER_SKY -70.0f

// Variable
extern int g_width;
extern int g_height;
extern float g_coordHeight;
extern float g_coordWidth;
extern float g_screenpixelPerUnit;
extern GLFWwindow* g_window;


// Function

bool _trace(TCHAR *format, ...);
#define TRACE _trace


glm::vec2 ScreenToWorld(glm::vec2& screenPositon);