#include "Sink.h"



CSink::CSink()
{
	m_eStateType = STATE_TYPE::SINK;
}

CSink::CSink(const CSink& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::SINK;
}

CSink::~CSink()
{
}

bool CSink::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Sink");
	//AddAnimationSequence("Sink_Off");

	return true;
}

bool CSink::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CSink::Start()
{
	CState::Start();
}

void CSink::Update(float fTime)
{
	CState::Update(fTime);
}

void CSink::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CSink::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CSink::PrevRender(float fTime)
{
	CState::PrevRender(fTime);

	/*if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("Sink");

		else
			ChangeAnimation("Sink_Off");
	}*/

}

void CSink::Render(HDC hDC, float fTime)
{
	CState::Render(hDC, fTime);
}

void CSink::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CSink* CSink::Clone()
{
	return new CSink(*this);
}