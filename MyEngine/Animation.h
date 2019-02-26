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
	/// 애니메이션 클립을 하나 추가합니다.
	/// </summary>
	void AddClip(const char* clipKey);
	/// <summary>
	/// 애니메이션 클립에 프레임을 하나 추가합니다.
	/// </summary>
	void SetFrame(const char* clipKey, const char* spriteKey);
	/// <summary>
	/// 현재 재생할 클립을 설정합니다.
	/// </summary>
	void SetClip(const char* clipKey);
	/// <summary>
	/// 애니메이션의 프레임 딜레이 속도를 조정합니다
	/// </summary>
	void SetFrameDelay(float delay);
	/// <summary>
	/// 애니메이션을 반복재생 할 것인지 설정합니다.
	/// </summary>
	void SetLoop(bool isLoop);

	/// <summary>
	/// 현재 선택된 클립의 이름을 가져옵니다.
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