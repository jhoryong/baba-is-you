#include "SceneEdit.h"

#include "../Object/UIButton.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../GameManager.h"
#include "SceneManager.h"
#include "../Object/MapObj.h"
#include "../TileMap/TileMap.h"
#include "../Input.h"
#include "../MapToolDlg.h"
#include "../Object/BlockObj.h"

CSceneEdit::CSceneEdit()	:
	m_pMapToolDlg(nullptr)
{
	m_eType = SCENE_TYPE::EDIT;
}

CSceneEdit::~CSceneEdit()
{
	SAFE_DELETE(m_pMapToolDlg);
}

bool CSceneEdit::Init()
{
	m_pMainCamera->SetWorldSize(1000.f, 1000.f);

	LoadTexture();
	LoadAnimation();

	GET_SINGLE(CInput)->AddAxisKey("EditorMoveUPDown", 'W', -1.f);
	GET_SINGLE(CInput)->AddAxisKey("EditorMoveUPDown", 'S', 1.f);
	GET_SINGLE(CInput)->AddBindAxis("EditorMoveUPDown", this, &CSceneEdit::MoveUPDown);

	GET_SINGLE(CInput)->AddAxisKey("EditorMoveSide", 'A', -1.f);
	GET_SINGLE(CInput)->AddAxisKey("EditorMoveSide", 'D', 1.f);
	GET_SINGLE(CInput)->AddBindAxis("EditorMoveSide", this, &CSceneEdit::MoveSide);

	GET_SINGLE(CInput)->AddActionKey("MapEdit", VK_F1);
	GET_SINGLE(CInput)->AddBindAction("MapEdit", KEY_TYPE::DOWN, this, &CSceneEdit::OnMapToolEditor);

	GET_SINGLE(CInput)->AddActionKey("MapEdit", 'M');
	GET_SINGLE(CInput)->AddActionKeyUnion("MapEdit", 'M', KEY_UNION::CONTROL);
	GET_SINGLE(CInput)->AddBindAction("MapEdit", KEY_TYPE::DOWN, this, &CSceneEdit::OnMapToolEditor);

	return true;
}

void CSceneEdit::Start()
{
	CScene::Start();
}

void CSceneEdit::Update(float fTime)
{
	CScene::Update(fTime);

	if (m_pMapToolDlg)
	{
		//if (m_pMapToolDlg->GetMapObj())
		//	m_pMapToolDlg->GetMapObj()->SetTileMapRenderPos(m_pMainCamera->GetPos());

		if (GET_SINGLE(CInput)->IsLButtonClick()) // 타일이 클릭되면
		{
			PlaceObject();
		}

		if (GET_SINGLE(CInput)->IsRButtonClick()) // 타일이 클릭되면
		{
			EraseObject();
		}
	}
}

void CSceneEdit::LoadTexture()
{
	CScene::LoadTexture();
}

void CSceneEdit::LoadAnimation()
{
	CScene::LoadAnimation();
}

void CSceneEdit::AddPrototype()
{
	CScene::AddPrototype();
}

class CBlockObj* CSceneEdit::CreateBlockObj(const char* cName)
{
	return CScene::CreateBlockObj(cName);
}

void CSceneEdit::MoveUPDown(float fScale, float fTime)
{
	Vector2	vMove = Vector2(0.f, 500.f) * fScale * fTime;

	m_pMainCamera->Move(vMove);
}

void CSceneEdit::MoveSide(float fScale, float fTime)
{
	Vector2	vMove = Vector2(500.f, 0.f) * fScale * fTime;

	m_pMainCamera->Move(vMove);
}

void CSceneEdit::OnMapToolEditor(float fTime)
{
	if (!m_pMapToolDlg)
		m_pMapToolDlg = new CMapToolDlg;

	m_pMapToolDlg->OnDialog(IDD_DIALOG_MAPTOOL); // 다이얼로그의 ID를 넣고 창을 만들고 띄운다.
}

void CSceneEdit::PlaceObject()
{
	if (m_pMapToolDlg)
		m_pMapToolDlg->PlaceObject();
}

void CSceneEdit::EraseObject()
{
	if (m_pMapToolDlg)
		m_pMapToolDlg->EraseObject();
}



CObj* CSceneEdit::FindObject(int iIndex_X, int iIndex_Y)
{
	auto iter = m_ObjList->begin();
	auto iterEnd = m_ObjList->end();

	for (; iter != iterEnd; ++iter)
	{
		if (((CBlockObj*)(*iter))->GetIndexX() == iIndex_X)
		{
			if (((CBlockObj*)(*iter))->GetIndexY() == iIndex_Y)
			{
				(*iter)->AddRef();
				return (*iter);
			}
			else
				continue;
		}
		else
			continue;
	}

	return nullptr;
}

void CSceneEdit::SaveObjectList(FILE* pFile)
{
	while (m_ObjList)
	{
		auto iter = m_ObjList->begin();
		auto iterEnd = m_ObjList->end();

		for (; iter != iterEnd; ++iter)
		{
			const char* cName = (*iter)->GetName().c_str();

			char cName1[50] = {};
			strcpy(cName1, cName);
			strcat(cName1, "\n");
			fputs(cName1, pFile);

			int iIndexX = ((CBlockObj*)(*iter))->GetIndexX();
			int iIndexY = ((CBlockObj*)(*iter))->GetIndexY();
			fprintf(pFile, "%d, %d\n", iIndexX, iIndexY);
		}

		const char* cEnd = "END";
		fputs(cEnd, pFile);
		break;
	}
}
