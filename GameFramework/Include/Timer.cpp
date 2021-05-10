#include "Timer.h"

CTimer::CTimer():
	m_tSecond{},
	m_tPrevTime{},
	m_fDeltaTime(0.f),
	m_fFPS(0.f),
	m_fFPSTime(0.f),
	m_iFrame(0)
{
}

CTimer::~CTimer()
{
}

bool CTimer::Init()
{
	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime = 0.f;
	m_iFrame = 0;

	return true;
}

void CTimer::Start()
{
	// 고해상도 타이머가 1초동안 몇번의 주기를 갖는지를 반환한다.
	QueryPerformanceFrequency(&m_tSecond);

	// 고해상도 타이머가 현재 주기가 몇번인지를 가져온다.
	QueryPerformanceCounter(&m_tPrevTime);
}

void CTimer::Update()
{
	LARGE_INTEGER		tCurTime;

	QueryPerformanceCounter(&tCurTime);

	m_fDeltaTime = (tCurTime.QuadPart - m_tPrevTime.QuadPart) /
		(float)m_tSecond.QuadPart;

	m_tPrevTime = tCurTime;

	++m_iFrame;
	m_fFPSTime += m_fDeltaTime;

	if (m_fFPSTime >= 1.f)
	{
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;
	}
}
