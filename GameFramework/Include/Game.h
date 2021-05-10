#pragma once

#define	CRTDBG_MAP_ALLOC
#define	_CRT_SECURE_NO_WARNINGS

#include "resource.h"
#include "Math.h"
#include "Struct.h"
#include "Enum.h"
#include "fmod.hpp"
#include <assert.h>

using namespace FMOD;

#pragma comment(lib, "msimg32.lib")

#ifdef _WIN64
#pragma comment(lib, "fmod64_vc.lib") // fmod 라이브러리 추가
#else
#pragma comment(lib, "fmod_vc.lib")
#endif // _WIN64


#define	NAME_SIZE		64

#define	ROOT_PATH		"RootPath"
#define	TEXTURE_PATH	"TexturePath"
#define	DATA_PATH		"DataPath"
#define SEQUENCE_PATH	"SequencePath"
#define	SOUND_PATH		"SoundPath"

#define BGM		"BGM"
#define EFFECT	"Effect"
#define UI		"UI"

#ifdef _DEBUG
#define	new		new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define	SAFE_DELETE_VECLIST(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_DELETE((*iter));\
	}\
	p.clear();\
}

#define	SAFE_DELETE_MAP(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_DELETE(iter->second);\
	}\
	p.clear();\
}

#define	SAFE_DELETE_ARRAY_VECLIST(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_DELETE_ARRAY((*iter));\
	}\
	p.clear();\
}

#define	SAFE_DELETE_ARRAY_MAP(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_DELETE_ARRAY(iter->second);\
	}\
	p.clear();\
}

#define	SAFE_RELEASE_VECLIST(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_RELEASE((*iter));\
	}\
	p.clear();\
}

#define	SAFE_RELEASE_MAP(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_RELEASE(iter->second);\
	}\
	p.clear();\
}

#define	DECLARE_SINGLE(Type)\
private:\
	static Type*	m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

#define	DEFINITION_SINGLE(Type)		Type* Type::m_pInst = nullptr;
#define	GET_SINGLE(Type)			Type::GetInst()
#define	DESTROY_SINGLE(Type)		Type::DestroyInst()

#define WINDOWINSTANCE	GET_SINGLE(CGameManager)->GetWindowInstance()
#define WINDOWHANDLE	GET_SINGLE(CGameManager)->GetWindowHandle()
#define WINDOWDC		GET_SINGLE(CGameManager)->GetWindowDC()
#define WINDOWBACKDC	GET_SINGLE(CGameManager)->GetBackDC()
#define RESOLUTION		GET_SINGLE(CGameManager)->GetResolution()
#define ALPHADC			GET_SINGLE(CGameManager)->GetAlphaDC()

#define	GREENBRUSH			GET_SINGLE(CGameManager)->GetGreenBrush()
#define	BLUEBRUSH			GET_SINGLE(CGameManager)->GetBlueBrush()
#define	REDBRUSH			GET_SINGLE(CGameManager)->GetRedBrush()
#define	TRANSPARENTBRUSH	GET_SINGLE(CGameManager)->GetTransparentBrush()
#define	BGBRUSH				GET_SINGLE(CGameManager)->GetBGBrush()

#define TRANSPARENTPEN	GET_SINGLE(CGameManager)->GetTransparentPen()
#define	GREENPEN		GET_SINGLE(CGameManager)->GetGreenPen()
#define	REDPEN			GET_SINGLE(CGameManager)->GetRedPen()
#define BLUEPEN			GET_SINGLE(CGameManager)->GetBluePen()



//extern int g_iNumber;
