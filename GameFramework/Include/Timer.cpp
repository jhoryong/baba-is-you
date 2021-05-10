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
	// ���ػ� Ÿ�̸Ӱ� 1�ʵ��� ����� �ֱ⸦ �������� ��ȯ�Ѵ�.
	QueryPerformanceFrequency(&m_tSecond);

	// ���ػ� Ÿ�̸Ӱ� ���� �ֱⰡ ��������� �����´�.
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
