#pragma once
#include "Global.h"
#include "Sprite.h"
#include "png.h"
#include "pngstruct.h"
#include "pnginfo.h"
class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();

	static void ImageLoading();
	static void Release();

	static Sprite* GetImagePtr(const char* imageKey);
private:
	static std::unordered_map<std::string, Sprite*> imageMap;

	/// <summary>
	/// imagepath의 경로에 bmp파일을 하나 불러온뒤 map에 저장합니다.
	/// </summary>
	static bool LoadBmp(const char* imagepath, std::string imageKey);
	/// <summary>
	/// imagepath의 경로에 png파일을 하나 불러온뒤 map에 저장합니다.
	/// </summary>
	static bool LoadPng(const char* imagepath, std::string imageKey);
};

