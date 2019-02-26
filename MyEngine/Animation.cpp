#include "Animation.h"
#include "SpriteManager.h"
#include "GameObject.h"
#include "Image.h"

std::list<Animation*> Animation::list;

Animation::Animation(GameObject& gameObject) : Component(gameObject)
{
	list.push_back(this);
	m_frameDelay = 0.5f;
	m_accTime = 0.0f;
	m_isPlay = false;
	m_isLoop = true;
	m_nowClip = "";

	m_pImage = nullptr;
}


Animation::~Animation()
{
}


void Animation::Initialize()
{
	Component::Initialize();

}

void Animation::Update()
{
	Component::Update();

	if (m_isPlay)
	{
		m_accTime += Time::GetDeltaTime();
		if (m_accTime >= m_frameDelay)
		{
			m_accTime = 0;
			if (aniIteractor == aniEnd)
			{
				if (m_isLoop)
					aniIteractor = aniBegin;
				else
				{
					Stop();
					return;
				}
			}
			m_pImage->SetSprite(*aniIteractor);
			++aniIteractor;

		}
	}
}


void Animation::Release()
{
	Component::Release();

	for (std::unordered_map<const char*, std::list<const char*>*>::iterator it = clip.begin();
		it != clip.end(); ++it)
	{
		delete it->second;
	}

	for (std::list<Animation*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			return;
		}
	}
}


void Animation::AddClip(const char* clipKey)
{
	clip.insert(
		std::pair<const char*, std::list<const char*>*>(clipKey, new std::list<const char*>)
	);
}


void Animation::SetFrame(const char* clipKey, const char* spriteKey)
{
	clip[clipKey]->push_back(spriteKey);
}


void Animation::SetClip(const char* clipKey)
{
	m_nowClip = clipKey;

}


void Animation::SetFrameDelay(float delay)
{
	m_frameDelay = delay;
}


void Animation::SetLoop(bool isLoop)
{
	m_isLoop = isLoop;
}


const char* Animation::GetClipKey()
{
	return m_nowClip;
}


bool Animation::IsLoop()
{
	return m_isLoop;
}


bool Animation::IsPlay()
{
	return m_isPlay;
}


void Animation::Play()
{
	m_isPlay = true;
	if (m_pImage == nullptr)
		m_pImage = gameObject.transform.GetComponent<Image>();

	if (m_nowClip == "")
		printf("Animation::Play()   어떤 애니메이션 클립을 실행해야할지 알 수 없습니다. SetClip()을 해주세요.\n");
	else
	{
		aniBegin = aniIteractor = clip[m_nowClip]->begin();
		aniEnd = clip[m_nowClip]->end();
		m_pImage->SetSprite(*aniIteractor);
	}
}


void Animation::Stop()
{
	m_isPlay = false;
}