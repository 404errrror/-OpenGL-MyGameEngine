#pragma once
#include "Global.h"
#include <iostream>
#include <fstream>
class FileManager
{
public:
	FileManager();
	~FileManager();

	static void Initialize();
	static void Release();
	static int GetBestScore();
	static void SetBestScore(int score);
private:
	static std::ofstream m_write;
	static std::fstream m_read;
};

