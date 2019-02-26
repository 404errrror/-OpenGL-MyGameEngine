#pragma once
#include "GameObject.h"
#include "Global.h"

class Image;
class GalagaNumber :
	public GameObject
{
public:
	enum Aligh
	{
		Left,Right
	};
public:
	GalagaNumber();
	~GalagaNumber();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;

	int operator= (int data);
	int operator+ (int data);
	int operator- (int data);
	int operator+= (int data);
	int operator++ ();

	void SetAligh(Aligh aligh);
	void SetUnit(const char* spriteKey);
	void SetColor(glm::vec4 color);

	int GetData();


private:
	int m_data;
	int m_length;
	std::string m_dataString;
	glm::vec3 m_tempPosition;

	Image* m_pImage;
	Aligh m_aligh;
	std::string m_spriteKey;
private:
	void UpdateData();
	int GetLength();
};

