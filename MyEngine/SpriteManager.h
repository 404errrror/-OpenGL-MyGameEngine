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
	/// imagepath�� ��ο� bmp������ �ϳ� �ҷ��µ� map�� �����մϴ�.
	/// </summary>
	static bool LoadBmp(const char* imagepath, std::string imageKey);
	/// <summary>
	/// imagepath�� ��ο� png������ �ϳ� �ҷ��µ� map�� �����մϴ�.
	/// </summary>
	static bool LoadPng(const char* imagepath, std::string imageKey);
};

