#include "Ref.h"

CRef::CRef()	:
	m_iRefCount(1),
	m_bActive(true),
	m_bEnable(true)
{
}

CRef::~CRef()
{
}

bool CRef::Release()
{
	--m_iRefCount;

	if (m_iRefCount == 0)
	{
		delete	this;
		return true;
	}

	return false;
}

void CRef::AddRef()
{
	++m_iRefCount;
}
