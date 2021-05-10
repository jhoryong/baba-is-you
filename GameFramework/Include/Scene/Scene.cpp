#include "Scene.h"

#include "SceneResource.h"
#include "Camera.h"
#include "../GameManager.h"
#include "SceneCollision.h"
#include "../Object/UI.h"
#include "../TileMap/TileMap.h"
#include "../Input.h"
#include "../Object/Character.h"
#include "../Object/BlockObj.h"
#include "../Object/Word.h"
#include "../Object/Name.h"
#include "../Object/BackgroundObj.h"


#include "../Object/Baba.h"
#include "../Object/Rock.h"
#include "../Object/Flag.h"
#include "../Object/Wall.h"
#include "../Object/BabaName.h"
#include "../Object/Is.h"
#include "../Object/You.h"
#include "../Object/FlagName.h"
#include "../Object/Win.h"
#include "../Object/WallName.h"
#include "../Object/Stop.h"
#include "../Object/RockName.h"
#include "../Object/Push.h"
#include "../Object/GroundTile.h"
#include "../Object/Grass.h"
#include "../Object/Water.h"
#include "../Object/Sink.h"
#include "../Object/WaterName.h"
#include "../Object/Defeat.h"
#include "../Object/Skull.h"
#include "../Object/SkullName.h"
#include "../Object/GrassName.h"
#include "../Object/Flower.h"
#include "../Object/Brick.h"
#include "../Object/Lava.h"
#include "../Object/Melt.h"
#include "../Object/Hot.h"
#include "../Object/LavaName.h"
#include "../Object/LavaName2.h"

#include "SceneMainMap.h"
#include "SceneStage.h"
#include "../PathManager.h"


bool CScene::m_bInitial = true;

CScene::CScene() :
	m_pPlayer(nullptr),
	m_bStart(false),
	m_eType(SCENE_TYPE::STAGE)
{
	m_pResource = new CSceneResource;

	m_pMainCamera = new CCamera;

	m_pMainCamera->Init();

	m_mapCamera.insert(make_pair("MainCamera", m_pMainCamera));

	Vector2	vRS = GET_SINGLE(CGameManager)->GetResolution();

	m_pMainCamera->SetResolution(vRS);

	m_pCollision = new CSceneCollision;

	m_vecCharacterCount.resize((int)CHARACTER_TYPE::END);
	m_vecNameCount.resize((int)NAME_TYPE::END);
	m_vecConnectCount.resize((int)CONNECT_TYPE::END);
	m_vecStateCount.resize((int)STATE_TYPE::END);

	m_pCollision->Init();

	m_ObjList = new list<class CObj*>;
}

CScene::~CScene()
{
	{
		auto iter = m_ObjList->begin();
		auto iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			CObj* pObj = (*iter);
			SAFE_RELEASE(pObj);
			iter = m_ObjList->erase(iter);
			iterEnd = m_ObjList->end();
		}
	}
	SAFE_DELETE(m_ObjList);

	auto iter = m_vecObjList.begin();
	auto iterEnd = m_vecObjList.end();

	for (; iter != iterEnd;)
	{
		list<CObj*>* pList = (*iter);
		auto listiter = pList->begin();
		auto listiterEnd = pList->end();

		for (; listiter != listiterEnd;)
		{
			SAFE_RELEASE((*listiter));
			listiter = pList->erase(listiter);
			listiterEnd = pList->end();
		}

		SAFE_DELETE(pList);
		iter = m_vecObjList.erase(iter);
		iterEnd = m_vecObjList.end();
	}
	
	SAFE_DELETE_MAP(m_mapCamera);
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE_VECLIST(m_UIList);
	SAFE_RELEASE_VECLIST(m_EnvironmentList);
	SAFE_RELEASE_MAP(m_mapPrototype);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pResource);
	SAFE_DELETE(m_pBackgroundObj);
}


void CScene::Start()
{
	if (m_eType == SCENE_TYPE::MAINMAP || m_eType == SCENE_TYPE::STAGE)
	{
		GET_SINGLE(CInput)->DeleteBindAction("Undo");
		GET_SINGLE(CInput)->AddActionKey("Undo", 'Z');
		GET_SINGLE(CInput)->AddBindAction("Undo", KEY_TYPE::DOWN, this, &CScene::Undo);

		GET_SINGLE(CInput)->DeleteBindAction("Restart");
		GET_SINGLE(CInput)->AddActionKey("Restart", 'R');
		GET_SINGLE(CInput)->AddBindAction("Restart", KEY_TYPE::DOWN, this, &CScene::Restart);
	}

	if (m_pBackgroundObj)
	{
		m_pBackgroundObj->Start();
		m_pBackgroundObj->EnableStart();
	}

	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Start();
			(*iter)->EnableStart();
		}
	}

	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Start();
			(*iter)->EnableStart();
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Start();
			(*iter)->EnableStart();
		}
	}
}

void CScene::Update(float fTime)
{
	if (m_pBackgroundObj)
	{
		m_pBackgroundObj->Update(fTime);
	}


	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_EnvironmentList.erase(iter);
				iterEnd = m_EnvironmentList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_UIList.erase(iter);
				iterEnd = m_UIList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(fTime);
			++iter;
		}
	}

	m_pMainCamera->Update(fTime);


	if (m_eReRegisterKeyChar != CHARACTER_TYPE::END /*&& !m_bUndo*/)
	{
		ReRegisterKey(m_eReRegisterKeyChar); // list 한번 쭉 돈다.
		m_eReRegisterKeyChar = CHARACTER_TYPE::END;
		//m_bUndo = false;
	}
}

void CScene::PostUpdate(float fTime)
{
	if (m_pBackgroundObj)
	{
		m_pBackgroundObj->PostUpdate(fTime);
	}

	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_EnvironmentList.erase(iter);
				iterEnd = m_EnvironmentList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_UIList.erase(iter);
				iterEnd = m_UIList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(fTime);
			++iter;
		}
	}

	/*if (m_bInitial)
	{
		auto Listiter = m_ObjList->begin();
		auto ListiterEnd = m_ObjList->end();

		list<CObj*>* pList = new list<CObj*>;

		for (; Listiter != ListiterEnd; ++Listiter)
		{
			CObj* pObj = (*Listiter)->Clone();
			
			pList->push_back(pObj);
		}

		m_vecObjList.push_back(pList);
	}*/

	if (m_bInitialFrame && (m_eType == SCENE_TYPE::MAINMAP || m_eType == SCENE_TYPE::STAGE))
	{
		auto Listiter = m_ObjList->begin();
		auto ListiterEnd = m_ObjList->end();

		list<CObj*>* pList = new list<CObj*>;

		for (; Listiter != ListiterEnd; ++Listiter)
		{
			CObj* pObj = (*Listiter)->Clone();

			pList->push_back(pObj);
		}

		m_vecObjList.push_back(pList);
	}

	 if ((m_bMelt || m_bDefeat || m_bSink || m_bMoved) && (m_eType == SCENE_TYPE::MAINMAP || m_eType == SCENE_TYPE::STAGE))
	 {
		 if (m_bSink)
			 m_bSink = false;

		 if (m_bDefeat)
			 m_bDefeat = false;

		 if (m_bMelt)
			 m_bMelt = false;

		auto Listiter = m_ObjList->begin();
		auto ListiterEnd = m_ObjList->end();

		list<CObj*>* pList = new list<CObj*>;

		for (; Listiter != ListiterEnd; ++Listiter)
		{
			/*if (((CBlockObj*)(*Listiter))->GetUndo())
			{
				SAFE_DELETE(pList);
				return;
			}*/

			CObj* pObj = (*Listiter)->Clone();

			pList->push_back(pObj);
		}

		m_vecObjList.push_back(pList);
	 }
}

void CScene::Collision(float fTime)
{
	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_EnvironmentList.erase(iter);
				iterEnd = m_EnvironmentList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Collision(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Collision(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_UIList.erase(iter);
				iterEnd = m_UIList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Collision(fTime);
			++iter;
		}
	}

	m_pCollision->Collision(fTime);
}

void CScene::PrevRender(float fTime)
{
	if (m_pBackgroundObj)
	{
		m_pBackgroundObj->PrevRender(fTime);
	}
	// 2개의 리스트를 정렬한다.
	if (m_ObjList->size() >= 2)
		m_ObjList->sort(CScene::SortObjZOrder);

	if (m_EnvironmentList.size() >= 2)
		m_EnvironmentList.sort(CScene::SortY);

	if (m_UIList.size() >= 2)
		m_UIList.sort(CScene::SortZOrder);

	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_EnvironmentList.erase(iter);
				iterEnd = m_EnvironmentList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PrevRender(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PrevRender(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_UIList.erase(iter);
				iterEnd = m_UIList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PrevRender(fTime);
			++iter;
		}
	}
}

void CScene::Render(HDC hDC, float fTime)
{
	if (m_pBackgroundObj)
	{
		m_pBackgroundObj->Render(hDC, fTime);
	}
	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_EnvironmentList.erase(iter);
				iterEnd = m_EnvironmentList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, fTime);
			++iter;
		}
	}
	
	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, fTime);
			++iter;
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_UIList.erase(iter);
				iterEnd = m_UIList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, fTime);
			++iter;
		}
	}
}

void CScene::PostRender(float fTime)
{
	if (m_pBackgroundObj)
	{
		m_pBackgroundObj->PostRender(fTime);
	}
	{
		auto	iter = m_EnvironmentList.begin();
		auto	iterEnd = m_EnvironmentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}
			
			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_EnvironmentList.erase(iter);
				iterEnd = m_EnvironmentList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostRender(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_ObjList->begin();
		auto	iterEnd = m_ObjList->end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostRender(fTime);
			++iter;
		}
	}

	{
		auto	iter = m_UIList.begin();
		auto	iterEnd = m_UIList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsStart())
			{
				(*iter)->EnableStart();
				(*iter)->Start();
			}

			if (!(*iter)->IsActive())
			{
				SAFE_RELEASE((*iter));
				iter = m_UIList.erase(iter);
				iterEnd = m_UIList.end();
				continue;
			}

			else if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostRender(fTime);
			++iter;
		}
	}

	SetMoved(false);
	m_bInitialFrame = false;
	m_bPlayDefeatSound = false;
}

void CScene::Undo(float fTime)
{
	//m_bUndo = true;

	PlayUndoSound();

	size_t iSize = m_vecObjList.size();
	
	if (iSize >= 2)
	{
		{
			auto iter = m_TileMapList.begin();
			auto iterEnd = m_TileMapList.end();

			for (; iter != iterEnd; ++iter)
			{
				(*iter)->ClearTile();
			}
		}
		{
			auto iter = m_ObjList->begin();
			auto iterEnd = m_ObjList->end();

			for (; iter != iterEnd;)
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
			}

			SAFE_DELETE(m_ObjList);
		}
		{
			auto iter = m_vecObjList.end() - 2;
			auto iterEnd = m_vecObjList.end();

			// 마지막 -1에 저장한 위치를 복사하여 지정

			if (iter != iterEnd)
			{
				auto Listiter = (*iter)->begin();
				auto ListiterEnd = (*iter)->end();

				list<CObj*>* pList = new list<CObj*>;

				for (; Listiter != ListiterEnd; ++Listiter)
				{
					CObj* pObj = (*Listiter)->Clone();
					
					((CBlockObj*)pObj)->EnableUndo();

					pList->push_back(pObj);
				}

				m_ObjList = pList;

				// 복사후 해당 가장 최근 위치정보 삭제
				// 만약 현재 시작위치라면 삭제하지 않음.

				++iter;

				if (iter != m_vecObjList.begin())
				{
					for (; iter != iterEnd;)
					{
						auto iter1 = (*iter)->begin();
						auto iter1End = (*iter)->end();

						auto iter2 = m_ObjList->begin();
						auto iter2End = m_ObjList->end();

						for (; iter1 != iter1End;)
						{
							/*Vector2 vPos = (*iter1)->GetPos();

							if (iter2 != iter2End)
							{
								((CBlockObj*)(*iter2))->SetBackPos((*iter2)->GetPos());
								(*iter2)->SetPos(vPos);
								++iter2;
							}*/

							SAFE_RELEASE((*iter1));
							iter1 = (*iter)->erase(iter1);
							iter1End = (*iter)->end();
						}

						SAFE_DELETE((*iter))
						iter = m_vecObjList.erase(iter);
						iterEnd = m_vecObjList.end();
					}
				}
			}

			// start 실행

			auto iter1 = m_ObjList->begin();
			auto iterEnd1 = m_ObjList->end();
			for (; iter1 != iterEnd1; ++iter1)
			{
				(*iter1)->Start();
			}
		}
	}
}

void CScene::PlayUndoSound()
{
	int iNumber = rand() % 5;

	switch (iNumber)
	{
	case 0:
		m_pResource->SoundPlay("Undo_0");
		break;
	case 1:
		m_pResource->SoundPlay("Undo_1");
		break;
	case 2:
		m_pResource->SoundPlay("Undo_2");
		break;
	case 3:
		m_pResource->SoundPlay("Undo_3");
		break;
	case 4:
		m_pResource->SoundPlay("Undo_4");
		break;
	}
}

void CScene::Restart(float fTime)
{
	m_pResource->SoundPlay("Restart");

	if (!m_vecObjList.empty())
	{
		// 타일 클리어
		{
			auto iter = m_TileMapList.begin();
			auto iterEnd = m_TileMapList.end();

			for (; iter != iterEnd; ++iter)
			{
				(*iter)->ClearTile();
			}
		}

		//현재 ObjList 삭제
		{
			auto iter = m_ObjList->begin();
			auto iterEnd = m_ObjList->end();

			for (; iter != iterEnd;)
			{
				SAFE_RELEASE((*iter));
				iter = m_ObjList->erase(iter);
				iterEnd = m_ObjList->end();
			}

			SAFE_DELETE(m_ObjList);
		}

		// 첫번째꺼만 빼고 다 삭제
		{
			auto iter = m_vecObjList.begin();
			auto iterEnd = m_vecObjList.end();

			// 첫번째 오브젝트 리스트를 현재 오브젝트 리스트로 복사

			if (iter != iterEnd)
			{
				list<CObj*>* pObjList = new list<CObj*>;

				auto Listiter = (*iter)->begin();
				auto ListiterEnd = (*iter)->end();

				for (; Listiter != ListiterEnd; ++Listiter)
				{
					CObj* pObj = (*Listiter)->Clone();

					pObjList->push_back(pObj);
				}

				m_ObjList = pObjList;
			}

			// 나머지 이터레이터 삭제
			++iter;

			for (; iter != iterEnd;)
			{
				//list<CObj*>* pList = (*iter);
				auto listiter = (*iter)->begin();
				auto listiterEnd = (*iter)->end();

				for (; listiter != listiterEnd;)
				{
					SAFE_RELEASE((*listiter));
					listiter = (*iter)->erase(listiter);
					listiterEnd = (*iter)->end();
				}

				SAFE_DELETE((*iter));
				iter = m_vecObjList.erase(iter);
				iterEnd = m_vecObjList.end();
			}
			//m_vecObjList;

			// Start 수행
			auto iter1 = m_ObjList->begin();
			auto iterEnd1 = m_ObjList->end();

			for (; iter1 != iterEnd1; ++iter1)
			{
				(*iter1)->Start();
			}
		}
	}
}

void CScene::ReRegisterKey(CHARACTER_TYPE eCharacterType)
{
	auto iter = m_ObjList->begin();
	auto iterEnd = m_ObjList->end();

	for (; iter != iterEnd; ++iter)
	{
		if (((CBlockObj*)(*iter))->GetBlockObjType() == BLOCKOBJ_TYPE::CHARACTER)
		{
			if (((CCharacter*)(*iter))->GetCharacterType() == eCharacterType)
			{
				switch (eCharacterType)
				{
				case CHARACTER_TYPE::BABA:
					((CBaba*)(*iter))->RegisterKey();
				case CHARACTER_TYPE::WALL:
					((CWall*)(*iter))->RegisterKey();
				case CHARACTER_TYPE::ROCK:
					((CRock*)(*iter))->RegisterKey();
				case CHARACTER_TYPE::FLAG:
					((CFlag*)(*iter))->RegisterKey();
				}

			}
		}
	}
}


CObj* CScene::FindObject(const string& strName)
{
	auto iter = m_ObjList->begin();
	auto iterEnd = m_ObjList->end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

vector<CName*> CScene::FindName(CHARACTER_TYPE eCharacterType)
{
	auto iter = m_ObjList->begin();
	auto iterEnd = m_ObjList->end();

	vector<CName*> vecName;

	for (; iter != iterEnd; ++iter)
	{
		if (((CBlockObj*)(*iter))->GetBlockObjType() == BLOCKOBJ_TYPE::WORD)
		{
			if (((CWord*)(*iter))->GetWordType() == WORD_TYPE::NAME)
			{
				if ((int)((CName*)(*iter))->GetNameType() == (int)eCharacterType)
				{
					(*iter)->AddRef();

					vecName.push_back((CName*)(*iter));
					// (CName*)*iter;
				}
					
			}
		}
	}

	return vecName;
}

void CScene::LoadTexture()
{	
	// Sprite
	m_pResource->LoadTexture("Sprite", TEXT("Sprite.bmp"));
	m_pResource->SetColorKey("Sprite", 255, 0, 255);

	// Sprite Off
	m_pResource->LoadTexture("Sprite2", TEXT("Sprite2.bmp"));
	m_pResource->SetColorKey("Sprite2", 255, 0, 255);
}

void CScene::LoadAnimation()
{
	float fSize = 24.f;
	float fLoopTime = 0.7f;

	// Baba
	m_pResource->CreateAnimationSequence("Baba_Right_Normal", "Baba_Right_Normal.asq");
	m_pResource->CreateAnimationSequence("Baba_Right_Open", "Baba_Right_Open.asq");
	m_pResource->CreateAnimationSequence("Baba_Right_Close", "Baba_Right_Close.asq");
	m_pResource->CreateAnimationSequence("Baba_Up_Normal", "Baba_Up_Normal.asq");
	m_pResource->CreateAnimationSequence("Baba_Up_Open", "Baba_Up_Open.asq");
	m_pResource->CreateAnimationSequence("Baba_Up_Close", "Baba_Up_Close.asq");
	m_pResource->CreateAnimationSequence("Baba_Left_Normal", "Baba_Left_Normal.asq");
	m_pResource->CreateAnimationSequence("Baba_Left_Open", "Baba_Left_Open.asq");
	m_pResource->CreateAnimationSequence("Baba_Left_Close", "Baba_Left_Close.asq");
	m_pResource->CreateAnimationSequence("Rock", "Rock.asq");
	m_pResource->CreateAnimationSequence("Flag", "Flag.asq");
	m_pResource->CreateAnimationSequence("GroundTile", "GroundTile.asq");
	m_pResource->CreateAnimationSequence("Skull", "Skull.asq");
	m_pResource->CreateAnimationSequence("Flower", "Flower.asq");


	m_pResource->CreateAnimationSequence("Push", "Push.asq");
	m_pResource->CreateAnimationSequence("Push_Off", "Push_Off.asq");
	m_pResource->CreateAnimationSequence("Stop", "Stop.asq");
	m_pResource->CreateAnimationSequence("Stop_Off", "Stop_Off.asq");
	m_pResource->CreateAnimationSequence("Win", "Win.asq");
	m_pResource->CreateAnimationSequence("Win_Off", "Win_Off.asq");
	m_pResource->CreateAnimationSequence("You", "You.asq");
	m_pResource->CreateAnimationSequence("You_Off", "You_Off.asq");
	m_pResource->CreateAnimationSequence("Sink", "Sink.asq");
	m_pResource->CreateAnimationSequence("Defeat", "Defeat.asq");
	m_pResource->CreateAnimationSequence("Defeat_Off", "Defeat_Off.asq");
	m_pResource->CreateAnimationSequence("Melt", "Melt.asq");
	m_pResource->CreateAnimationSequence("Hot", "Hot.asq");

	m_pResource->CreateAnimationSequence("Is", "Is.asq");
	m_pResource->CreateAnimationSequence("Is_Off", "Is_Off.asq");

	m_pResource->CreateAnimationSequence("BabaName", "BabaName.asq");
	m_pResource->CreateAnimationSequence("BabaName_Off", "BabaName_Off.asq");
	m_pResource->CreateAnimationSequence("RockName", "RockName.asq");
	m_pResource->CreateAnimationSequence("RockName_Off", "RockName_Off.asq");
	m_pResource->CreateAnimationSequence("WallName", "WallName.asq");
	m_pResource->CreateAnimationSequence("WallName_Off", "WallName_Off.asq");
	m_pResource->CreateAnimationSequence("FlagName", "FlagName.asq");
	m_pResource->CreateAnimationSequence("FlagName_Off", "FlagName_Off.asq");
	m_pResource->CreateAnimationSequence("WaterName", "WaterName.asq");
	m_pResource->CreateAnimationSequence("SkullName", "SkullName.asq");
	m_pResource->CreateAnimationSequence("SkullName_Off", "SkullName_Off.asq");
	m_pResource->CreateAnimationSequence("GrassName", "GrassName.asq");
	m_pResource->CreateAnimationSequence("LavaName", "LavaName.asq");
	m_pResource->CreateAnimationSequence("LavaName2", "LavaName2.asq");

	m_pResource->CreateAnimationSequence("Wall_0", "Wall_0.asq");
	m_pResource->CreateAnimationSequence("Wall_1", "Wall_1.asq");
	m_pResource->CreateAnimationSequence("Wall_2", "Wall_2.asq");
	m_pResource->CreateAnimationSequence("Wall_3", "Wall_3.asq");
	m_pResource->CreateAnimationSequence("Wall_4", "Wall_4.asq");
	m_pResource->CreateAnimationSequence("Wall_5", "Wall_5.asq");
	m_pResource->CreateAnimationSequence("Wall_6", "Wall_6.asq");
	m_pResource->CreateAnimationSequence("Wall_7", "Wall_7.asq");
	m_pResource->CreateAnimationSequence("Wall_8", "Wall_8.asq");
	m_pResource->CreateAnimationSequence("Wall_9", "Wall_9.asq");
	m_pResource->CreateAnimationSequence("Wall_10", "Wall_10.asq");
	m_pResource->CreateAnimationSequence("Wall_11", "Wall_11.asq");
	m_pResource->CreateAnimationSequence("Wall_12", "Wall_12.asq");
	m_pResource->CreateAnimationSequence("Wall_13", "Wall_13.asq");
	m_pResource->CreateAnimationSequence("Wall_14", "Wall_14.asq");
	m_pResource->CreateAnimationSequence("Wall_15", "Wall_15.asq");

	m_pResource->CreateAnimationSequence("Grass_0", "Grass_0.asq");
	m_pResource->CreateAnimationSequence("Grass_1", "Grass_1.asq");
	m_pResource->CreateAnimationSequence("Grass_2", "Grass_2.asq");
	m_pResource->CreateAnimationSequence("Grass_3", "Grass_3.asq");
	m_pResource->CreateAnimationSequence("Grass_4", "Grass_4.asq");
	m_pResource->CreateAnimationSequence("Grass_5", "Grass_5.asq");
	m_pResource->CreateAnimationSequence("Grass_6", "Grass_6.asq");
	m_pResource->CreateAnimationSequence("Grass_7", "Grass_7.asq");
	m_pResource->CreateAnimationSequence("Grass_8", "Grass_8.asq");
	m_pResource->CreateAnimationSequence("Grass_9", "Grass_9.asq");
	m_pResource->CreateAnimationSequence("Grass_10", "Grass_10.asq");
	m_pResource->CreateAnimationSequence("Grass_11", "Grass_11.asq");
	m_pResource->CreateAnimationSequence("Grass_12", "Grass_12.asq");
	m_pResource->CreateAnimationSequence("Grass_13", "Grass_13.asq");
	m_pResource->CreateAnimationSequence("Grass_14", "Grass_14.asq");
	m_pResource->CreateAnimationSequence("Grass_15", "Grass_15.asq");

	m_pResource->CreateAnimationSequence("Water_0", "Water_0.asq");
	m_pResource->CreateAnimationSequence("Water_1", "Water_1.asq");
	m_pResource->CreateAnimationSequence("Water_2", "Water_2.asq");
	m_pResource->CreateAnimationSequence("Water_3", "Water_3.asq");
	m_pResource->CreateAnimationSequence("Water_4", "Water_4.asq");
	m_pResource->CreateAnimationSequence("Water_5", "Water_5.asq");
	m_pResource->CreateAnimationSequence("Water_6", "Water_6.asq");
	m_pResource->CreateAnimationSequence("Water_7", "Water_7.asq");
	m_pResource->CreateAnimationSequence("Water_8", "Water_8.asq");
	m_pResource->CreateAnimationSequence("Water_9", "Water_9.asq");
	m_pResource->CreateAnimationSequence("Water_10", "Water_10.asq");
	m_pResource->CreateAnimationSequence("Water_11", "Water_11.asq");
	m_pResource->CreateAnimationSequence("Water_12", "Water_12.asq");
	m_pResource->CreateAnimationSequence("Water_13", "Water_13.asq");
	m_pResource->CreateAnimationSequence("Water_14", "Water_14.asq");
	m_pResource->CreateAnimationSequence("Water_15", "Water_15.asq");

	m_pResource->CreateAnimationSequence("Brick_0", "Brick_0.asq");
	m_pResource->CreateAnimationSequence("Brick_1", "Brick_1.asq");
	m_pResource->CreateAnimationSequence("Brick_2", "Brick_2.asq");
	m_pResource->CreateAnimationSequence("Brick_3", "Brick_3.asq");
	m_pResource->CreateAnimationSequence("Brick_4", "Brick_4.asq");
	m_pResource->CreateAnimationSequence("Brick_5", "Brick_5.asq");
	m_pResource->CreateAnimationSequence("Brick_6", "Brick_6.asq");
	m_pResource->CreateAnimationSequence("Brick_7", "Brick_7.asq");
	m_pResource->CreateAnimationSequence("Brick_8", "Brick_8.asq");
	m_pResource->CreateAnimationSequence("Brick_9", "Brick_9.asq");
	m_pResource->CreateAnimationSequence("Brick_10", "Brick_10.asq");
	m_pResource->CreateAnimationSequence("Brick_11", "Brick_11.asq");
	m_pResource->CreateAnimationSequence("Brick_12", "Brick_12.asq");
	m_pResource->CreateAnimationSequence("Brick_13", "Brick_13.asq");
	m_pResource->CreateAnimationSequence("Brick_14", "Brick_14.asq");
	m_pResource->CreateAnimationSequence("Brick_15", "Brick_15.asq");

	m_pResource->CreateAnimationSequence("Lava_0", "Lava_0.asq");
	m_pResource->CreateAnimationSequence("Lava_1", "Lava_1.asq");
	m_pResource->CreateAnimationSequence("Lava_2", "Lava_2.asq");
	m_pResource->CreateAnimationSequence("Lava_3", "Lava_3.asq");
	m_pResource->CreateAnimationSequence("Lava_4", "Lava_4.asq");
	m_pResource->CreateAnimationSequence("Lava_5", "Lava_5.asq");
	m_pResource->CreateAnimationSequence("Lava_6", "Lava_6.asq");
	m_pResource->CreateAnimationSequence("Lava_7", "Lava_7.asq");
	m_pResource->CreateAnimationSequence("Lava_8", "Lava_8.asq");
	m_pResource->CreateAnimationSequence("Lava_9", "Lava_9.asq");
	m_pResource->CreateAnimationSequence("Lava_10", "Lava_10.asq");
	m_pResource->CreateAnimationSequence("Lava_11", "Lava_11.asq");
	m_pResource->CreateAnimationSequence("Lava_12", "Lava_12.asq");
	m_pResource->CreateAnimationSequence("Lava_13", "Lava_13.asq");
	m_pResource->CreateAnimationSequence("Lava_14", "Lava_14.asq");
	m_pResource->CreateAnimationSequence("Lava_15", "Lava_15.asq");

	// down 다운은 프레임 순서를 임의로 바꿀것이므로 직접 프레임을 지정한다.
	m_pResource->CreateAnimationSequence("Baba_Down_Normal", "Sprite", ANIM_TYPE::ATLAS, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, fLoopTime);
	m_pResource->CreateAnimationSequence("Baba_Down_Open", "Sprite", ANIM_TYPE::ATLAS, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, fLoopTime);
	m_pResource->CreateAnimationSequence("Baba_Down_Close", "Sprite", ANIM_TYPE::ATLAS, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, fLoopTime);

	static bool bAddFrame = false;
	if (!bAddFrame)
	{
		for (int i = 0; i < 3; ++i)
		{
			int j = 0;
			if (i == 2)
				j = -3;

			m_pResource->AddAnimationFrame("Baba_Down_Normal",
				Vector2(fSize * 16.f, (float)(i + 1 + j) * fSize),
				Vector2(fSize * 17.f, (float)(i + 2 + j) * fSize));
		}

		for (int i = 0; i < 3; ++i)
		{
			int j = 0;
			if (i == 2)
				j = -3;

			m_pResource->AddAnimationFrame("Baba_Down_Open",
				Vector2(fSize * 17.f, (float)(i + 1 + j) * fSize),
				Vector2(fSize * 18.f, (float)(i + 2 + j) * fSize));
		}

		for (int i = 0; i < 3; ++i)
		{
			int j = 0;
			if (i == 2)
				j = -3;

			m_pResource->AddAnimationFrame("Baba_Down_Close",
				Vector2(fSize * 19.f, (float)(i + 1 + j) * fSize),
				Vector2(fSize * 20.f, (float)(i + 2 + j) * fSize));
		}
	}
	
	bAddFrame = true;
}

CBlockObj* CScene::CreateBlockObj(const char* cName)
{
	string strName = cName;

	// character

	if (strName == "Baba")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CBaba>("Baba");
		return pBlockObj;
	}
	else if (strName == "Wall")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CWall>("Wall");
		return pBlockObj;
	}
	else if (strName == "Rock")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CRock>("Rock");
		return pBlockObj;
	}
	else if (strName == "Flag")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CFlag>("Flag");
		return pBlockObj;
	}
	else if (strName == "Grass")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CGrass>("Grass");
		return pBlockObj;
	}
	else if (strName == "GroundTile")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CGroundTile>("GroundTile");
		return pBlockObj;
	}
	else if (strName == "Water")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CWater>("Water");
		return pBlockObj;
	}
	else if (strName == "Skull")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CSkull>("Skull");
		return pBlockObj;
	}
	else if (strName == "Flower")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CFlower>("Flower");
		return pBlockObj;
	}
	else if (strName == "Brick")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CBrick>("Brick");
		return pBlockObj;
	}
	else if (strName == "Lava")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CLava>("Lava");
		return pBlockObj;
	}
	// word

	else if (strName == "BabaName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CBabaName>("BabaName");
		return pBlockObj;
	}
	else if (strName == "WallName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CWallName>("WallName");
		return pBlockObj;
	}
	else if (strName == "RockName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CRockName>("RockName");
		return pBlockObj;
	}
	else if (strName == "FlagName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CFlagName>("FlagName");
		return pBlockObj;
	}
	else if (strName == "WaterName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CWaterName>("WaterName");
		return pBlockObj;
	}
	else if (strName == "SkullName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CSkullName>("SkullName");
		return pBlockObj;
	}
	else if (strName == "GrassName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CGrassName>("GrassName");
		return pBlockObj;
	}
	else if (strName == "LavaName")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CLavaName>("LavaName");
		return pBlockObj;
	}
	else if (strName == "LavaName2")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CLavaName2>("LavaName2");
		return pBlockObj;
	}

	else if (strName == "Is")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CIs>("Is");
		return pBlockObj;
	}
	//else if (cName == "And")
	//{
	//	//CBlockObj* pBlockObj = CreateCloneBlockObj<CAnd>("And");
	//	//return pBlockObj;
	//}

	else if (strName == "Push")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CPush>("Push");
		return pBlockObj;
	}
	else if (strName == "Win")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CWin>("Win");
		return pBlockObj;
	}
	else if (strName == "You")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CYou>("You");
		return pBlockObj;
	}
	else if (strName == "Stop")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CStop>("Stop");
		return pBlockObj;
	}
	else if (strName == "Sink")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CSink>("Sink");
		return pBlockObj;
	}
	else if (strName == "Defeat")
	{
		CBlockObj* pBlockObj = CreateCloneBlockObj<CDefeat>("Defeat");
		return pBlockObj;
	}
	else if (strName == "Hot")
	{
	CBlockObj* pBlockObj = CreateCloneBlockObj<CHot>("Hot");
	return pBlockObj;
	}
	else if (strName == "Melt")
	{
	CBlockObj* pBlockObj = CreateCloneBlockObj<CMelt>("Melt");
	return pBlockObj;
	}
	else
		return nullptr;
}

void CScene::AddPrototype()
{
	CObj* pBaba = CreatePrototype<CBaba>("Baba");
	SAFE_RELEASE(pBaba);

	CObj* pFlag = CreatePrototype<CFlag>("Flag");
	SAFE_RELEASE(pFlag);

	CObj* pWall = CreatePrototype<CWall>("Wall");
	SAFE_RELEASE(pWall);

	CObj* pRock = CreatePrototype<CRock>("Rock");
	SAFE_RELEASE(pRock);

	CObj* pGroundTile = CreatePrototype<CGroundTile>("GroundTile");
	SAFE_RELEASE(pGroundTile);

	CObj* pGrass = CreatePrototype<CGrass>("Grass");
	SAFE_RELEASE(pGrass);

	CObj* pWater = CreatePrototype<CWater>("Water");
	SAFE_RELEASE(pWater);

	CObj* pSkull = CreatePrototype<CSkull>("Skull");
	SAFE_RELEASE(pSkull);

	CObj* pFlower = CreatePrototype<CFlower>("Flower");
	SAFE_RELEASE(pFlower);

	CObj* pBrick = CreatePrototype<CBrick>("Brick");
	SAFE_RELEASE(pBrick);

	CObj* pLava = CreatePrototype<CLava>("Lava");
	SAFE_RELEASE(pLava);

	//----
	CObj* pBabaName = CreatePrototype<CBabaName>("BabaName");
	SAFE_RELEASE(pBabaName);

	CObj* pFlagName = CreatePrototype<CFlagName>("FlagName");
	SAFE_RELEASE(pFlagName);

	CObj* pWallName = CreatePrototype<CWallName>("WallName");
	SAFE_RELEASE(pWallName);

	CObj* pRockName = CreatePrototype<CRockName>("RockName");
	SAFE_RELEASE(pRockName);

	CObj* pWaterName = CreatePrototype<CWaterName>("WaterName");
	SAFE_RELEASE(pWaterName);

	CObj* pSkullName = CreatePrototype<CSkullName>("SkullName");
	SAFE_RELEASE(pSkullName);

	CObj* pGrassName = CreatePrototype<CGrassName>("GrassName");
	SAFE_RELEASE(pGrassName);

	CObj* pLavaName = CreatePrototype<CLavaName>("LavaName");
	SAFE_RELEASE(pLavaName);

	CObj* pLavaName2 = CreatePrototype<CLavaName2>("LavaName2");
	SAFE_RELEASE(pLavaName2);

	//---
	CObj* pIs = CreatePrototype<CIs>("Is");
	SAFE_RELEASE(pIs);

	//----
	CObj* pYou = CreatePrototype<CYou>("You");
	SAFE_RELEASE(pYou);

	CObj* pStop = CreatePrototype<CStop>("Stop");
	SAFE_RELEASE(pStop);

	CObj* pPush = CreatePrototype<CPush>("Push");
	SAFE_RELEASE(pPush);

	CObj* pWin = CreatePrototype<CWin>("Win");
	SAFE_RELEASE(pWin);

	CObj* pSink = CreatePrototype<CSink>("Sink");
	SAFE_RELEASE(pSink);

	CObj* pDefeat = CreatePrototype<CDefeat>("Defeat");
	SAFE_RELEASE(pDefeat);

	CObj* pHot = CreatePrototype<CHot>("Hot");
	SAFE_RELEASE(pHot);

	CObj* pMelt = CreatePrototype<CMelt>("Melt");
	SAFE_RELEASE(pMelt);
}


void CScene::SetPlayer(CObj* pPlayer)
{
	SAFE_RELEASE(m_pPlayer);
	m_pPlayer = pPlayer;

	if (m_pPlayer)
		m_pPlayer->AddRef();
}

void CScene::AddObject(CObj* pObj)
{
	pObj->m_pScene = this;
	pObj->AddRef();
	m_ObjList->push_back(pObj);

	if (m_bStart)
		pObj->Start();
}

void CScene::AddUI(CObj* pObj)
{
	pObj->m_pScene = this;
	pObj->AddRef();
	m_UIList.push_back(pObj);

	if (m_bStart)
		pObj->Start();
}

void CScene::AddEnvironment(CObj* pObj)
{
	pObj->m_pScene = this;
	pObj->AddRef();
	m_EnvironmentList.push_back(pObj);

	if (m_bStart)
		pObj->Start();
}

void CScene::AddTileMap(CTileMap* pTileMap)
{
	m_TileMapList.push_back(pTileMap);
}

void CScene::DeleteTileMap(CTileMap* pTileMap)
{
	auto	iter = m_TileMapList.begin();
	auto	iterEnd = m_TileMapList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pTileMap)
		{
			//SAFE_DELETE(*iter);
			m_TileMapList.erase(iter);
			break;
		}
	}
}

CTileMap* CScene::FindTileMap(const Vector2& vPos)
{
	auto	iter = m_TileMapList.begin();
	auto	iterEnd = m_TileMapList.end();

	for (; iter != iterEnd; ++iter)
	{
		Vector2	vStartPos = (*iter)->GetStartPos();
		Vector2	vSize = (*iter)->GetMapSize();

		if (vStartPos.x <= vPos.x && vPos.x <= vStartPos.x + vSize.x &&
			vStartPos.y <= vPos.y && vPos.y <= vStartPos.y + vSize.y)
			return *iter;
	}

	return nullptr;
}

CTile* CScene::FindTile(const Vector2& vMapPos, const Vector2& vRelPos)
{
	CTileMap* pTileMap = FindTileMap(vMapPos);

	if (!pTileMap)
		return nullptr;

	return pTileMap->FindTile(vRelPos);
}

CTile* CScene::FindTile(const Vector2& vMapPos, const int iIndexX, const int iIdexY)
{
	CTileMap* pTileMap = FindTileMap(vMapPos);

	if (!pTileMap)
		return nullptr;

	return pTileMap->FindTile(iIndexX, iIdexY);
}

CTile* CScene::FindTile(const Vector2& vMapPos, const int iIndex)
{
	CTileMap* pTileMap = FindTileMap(vMapPos);

	if (!pTileMap)
		return nullptr;

	return pTileMap->FindTile(iIndex);
}


bool CScene::SortY(CObj* pSrc, CObj* pDest)
{
	// 오브젝트의 Bottom 을 구한다.
	float	fSrcY, fDestY;
	fSrcY = pSrc->GetPos().y - pSrc->GetPivot().y * pSrc->GetSize().y + pSrc->GetSize().y;
	fDestY = pDest->GetPos().y - pDest->GetPivot().y * pDest->GetSize().y + pDest->GetSize().y;

	return fSrcY < fDestY;
}

bool CScene::SortObjZOrder(CObj* pSrc, CObj* pDest)
{
	int	iSrcZ, iDestZ;

	iSrcZ = ((CBlockObj*)pSrc)->GetZOrder();
	iDestZ = ((CBlockObj*)pDest)->GetZOrder();

	return iSrcZ < iDestZ;
}

bool CScene::SortZOrder(CObj* pSrc, CObj* pDest)
{
	int	iSrcZ, iDestZ;

	iSrcZ = ((CUI*)pSrc)->GetZOrder();
	iDestZ = ((CUI*)pDest)->GetZOrder();
	
	return iSrcZ < iDestZ;
}

CObj* CScene::FindPrototype(const string& strName)
{
	auto	iter = m_mapPrototype.find(strName);

	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}


void CScene::LoadStage(const char* pFileName, const string& strPathName)
{
	FILE* pFile = nullptr;

	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultibyte(strPathName);
	char	strFullPath[MAX_PATH] = {};

	if (pPath)
		strcpy_s(strFullPath, pPath);

	strcat_s(strFullPath, pFileName);

	fopen_s(&pFile, strFullPath, "rt");

	if (!pFile)
		return;

	Load(pFile);

	fclose(pFile);
}

void CScene::Load(FILE* pFile)
{
	while (true)
	{
		char charObjName[50] = {};
		fgets(charObjName, 50, pFile);

		int a = strcmp(charObjName, "END");
		if (a == 0)
		{
			break;
		}

		size_t iLength = strlen(charObjName);

		for (size_t i = iLength - 1; i > 0; --i)
		{
			if (charObjName[i] == '_')
			{
				memset(&charObjName[i], 0, 50 - i);
				break;
			}
		}

		CBlockObj* pBlockObj = CreateBlockObj(charObjName);

		char cRelPos[50] = {};
		fgets(cRelPos, 50, pFile);
		char* pContext = nullptr;
		char* pReturn = nullptr;
		pReturn = strtok_s(cRelPos, ", ", &pContext);
		int x = atoi(pReturn);
		int y = atoi(pContext);
		pBlockObj->SetTileIndex(x, y);
		SAFE_RELEASE(pBlockObj);
	}
}