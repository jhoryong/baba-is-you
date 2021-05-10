
#include "Word.h"
class CNumber :
    public CWord
{
public:
	CNumber();
	CNumber(const CNumber& obj);

protected:
	virtual ~CNumber();

protected:
	int m_iNumber = 0;

public:
	virtual bool Init();
	virtual bool Init(const char* pFileName,
		const string& strPathName = DATA_PATH);
	virtual void Start();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void PrevRender(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual void PostRender(float fTime);
	virtual CNumber* Clone();

private:
	void ChangeNumberAnimation();

public:
	void SetNumber(int iNumber)
	{
		m_iNumber = iNumber;
	}

	int GetNumber()
	{
		return m_iNumber;
	}
};
