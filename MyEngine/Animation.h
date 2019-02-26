#pragma once
#include "Component.h"
#include "Global.h"
#include "Sprite.h"

class Image;
class Animation :
	public Component
{
public:
	static std::list<Animation*> list;
	std::unordered_map<const char*, std::list<const char*>*> clip;

public:
	Animation(GameObject& gameObject);
	~Animation();

	void Initialize() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// �ִϸ��̼� Ŭ���� �ϳ� �߰��մϴ�.
	/// </summary>
	void AddClip(const char* clipKey);
	/// <summary>
	/// �ִϸ��̼� Ŭ���� �������� �ϳ� �߰��մϴ�.
	/// </summary>
	void SetFrame(const char* clipKey, const char* spriteKey);
	/// <summary>
	/// ���� ����� Ŭ���� �����մϴ�.
	/// </summary>
	void SetClip(const char* clipKey);
	/// <summary>
	/// �ִϸ��̼��� ������ ������ �ӵ��� �����մϴ�
	/// </summary>
	void SetFrameDelay(float delay);
	/// <summary>
	/// �ִϸ��̼��� �ݺ���� �� ������ �����մϴ�.
	/// </summary>
	void SetLoop(bool isLoop);

	/// <summary>
	/// ���� ���õ� Ŭ���� �̸��� �����ɴϴ�.
	/// </summary>
	const char* GetClipKey();
	bool IsLoop();
	bool IsPlay();


	void Play();
	void Stop();

private:
	float		m_frameDelay;
	float		m_accTime;
	bool		m_isPlay;
	bool		m_isLoop;
	const char* m_nowClip;

	std::list<const char*>::iterator aniIteractor;
	std::list<const char*>::iterator aniBegin;
	std::list<const char*>::iterator aniEnd;

	Image* m_pImage;
};