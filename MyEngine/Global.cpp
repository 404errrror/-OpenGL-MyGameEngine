#include "Global.h"

int g_width = 1024;
int g_height = 720;

float g_coordHeight = 15;		// ÁÂÇ¥°è Å©±â. (¾Æ·§ÂÊ -100 À§ÂÊ +100)
float g_coordWidth = g_coordHeight * ((float)g_width / (float)g_height) ;

float g_screenpixelPerUnit = g_height / g_coordHeight;
GLFWwindow* g_window;


// Function
bool _trace(TCHAR *format, ...)
{
#ifdef _DEBUG

	TCHAR buffer[1000];

	va_list argptr; 
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);

	OutputDebugString(buffer);

#endif
	return true;
}


glm::vec2 ScreenToWorld(glm::vec2& screenPositon)
{
	glm::vec2 position;

	position.x	=	screenPositon.x - g_width * 0.5f;
	position.y	=	-screenPositon.y;
	position.y	+=	g_height * 0.5f;

	position.x *= g_coordWidth / g_width;
	position.y *= g_coordHeight / g_height;

	return position;
}