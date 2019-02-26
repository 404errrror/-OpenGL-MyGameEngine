#include "FileManager.h"

std::ofstream FileManager::m_write;
std::fstream FileManager::m_read;

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}


void FileManager::Initialize()
{
}


void FileManager::Release()
{
	// file ´Ý±â
}


int FileManager::GetBestScore()
{
	//m_read.seekg(0);
	m_read.open("BestScore.dat", std::ios::in);

	int score;
	m_read >> score;
	m_read.close();
	return score;
}


void FileManager::SetBestScore(int score)
{
	m_write.open("BestScore.dat", std::ios::out);
	m_write << score;
	m_write.close();
}