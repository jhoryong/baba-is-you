#pragma once

#include "../Game.h"
#include "../Object/Obj.h"
#include "../Object/Tree.h"

enum class SCENE_TYPE
{
	START,
	MAINMAP,
	STAGE,
	EDIT,
	ANIMEDIT
};

class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0;

protected:
	SCENE_TYPE m_eType;
	class CSceneResource*	m_pResource;
	class CCamera*			m_pMainCamera;
	unordered_map<string, class CCamera*>	m_mapCamera; // 카메라
	class CSceneCollision* m_pCollision;

protected:
	unordered_map<string, class CObj*>	m_mapPrototype; // Obj 프로토타입 맵
	list<class CObj*>*		m_ObjList;
	list<class CObj*>		m_UIList;
	list<class CObj*>		m_EnvironmentList; // Map Obj
	list<class CTileMap*>	m_TileMapList;
	class CBackgroundObj*	m_pBackgroundObj = nullptr;
	vector<list<class CObj*>*> m_vecObjList;

	class CObj* m_pPlayer;
	static bool m_bInitial;
	bool	m_bInitialFrame = true;
	bool	m_bStart;
	bool	m_bMoved = false; // 한칸 이동이 완전히 이루어지면 한번 true 가 된다.
	bool    m_bMoveSoundPlay = false;
	bool	m_bSink = false; // 누군가가 sink 했을 경우 true 된다.
	bool	m_bDefeat = false; // skull 에 닿았을 경우 defeat 된다.
	bool	m_bMelt = false;
	bool m_bLavaMelt = false;
	CHARACTER_TYPE m_eReRegisterKeyChar = CHARACTER_TYPE::END;
	bool m_bUndo = false;
	bool m_bPlayDefeatSound = false;

	vector<int> m_vecCharacterCount;
	vector<int> m_vecNameCount;
	vector<int> m_vecConnectCount;
	vector<int> m_vecStateCount;

public:
	virtual bool Init() = 0;
	virtual void Start(); // scene 이 시작하면 실행되는 함수
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void PrevRender(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual void PostRender(float fTime);

public:
	virtual void Undo(float fTime);
	void PlayUndoSound();
	virtual void Restart(float fTime);
	void ReRegisterKey(CHARACTER_TYPE eCharacterType);


public:
	virtual void LoadTexture();
	virtual void LoadAnimation();
	virtual void AddPrototype();
	virtual class CBlockObj* CreateBlockObj(const char* cName);

public:
	class CObj* FindObject(const string& strName);
	vector<class CName*> FindName(CHARACTER_TYPE eNameType);
	void SetPlayer(class CObj* pPlayer);
	void AddObject(class CObj* pObj);
	void AddUI(class CObj* pObj);
	void AddEnvironment(class CObj* pObj);

public:
	void AddTileMap(class CTileMap* pTileMap);
	void DeleteTileMap(class CTileMap* pTileMap);
	class CTileMap* FindTileMap(const Vector2& vPos);// 해당 위치에 있는 타일맵을 찾는다.

public:
	class CTile* FindTile(const Vector2& vMapPos, const Vector2& vRelPos);// 해당 위치의 타일을 찾는다.
	class CTile* FindTile(const Vector2& vMapPos, const int iIndexX, const int iIdexY);
	class CTile* FindTile(const Vector2& vMapPos, const int iIndex);

public:
	static bool SortY(class CObj* pSrc, class CObj* pDest);
	static bool SortObjZOrder(class CObj* pSrc, class CObj* pDest);
	static bool SortZOrder(class CObj* pSrc, class CObj* pDest);

private:
	CObj* FindPrototype(const string& strName);

public:
	void LoadStage(const char* pFileName, const string& strPathName = DATA_PATH);
	void Load(FILE* pFile);

public:
	template <typename T>
	T* CreateObject(const string& strName, const Vector2& vPos = Vector2::Zero,
		const Vector2& vSize = Vector2(100.f, 100.f))
	{
		T* pObj = new T;

		pObj->SetName(strName);
		pObj->SetPos(vPos);
		pObj->SetSize(vSize);
		pObj->m_pScene = this;

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		if (pObj->IsUI())
			AddUI(pObj);

		else if (pObj->IsEnvironment())
			AddEnvironment(pObj);

		else if (pObj->IsBackgroundObj())
		{
			m_pBackgroundObj = (CBackgroundObj*)pObj; 
			pObj->AddRef();
		}

		else
			AddObject(pObj);

		return pObj;
	}

	template <typename T>
	T* CreateObject(const string& strName, const char* pFileName,
		const string& strPathName = DATA_PATH)
	{
		T* pObj = new T;

		pObj->SetName(strName);

		if (!pObj->Init(pFileName, strPathName))
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		return pObj;
	}

	template <typename T>
	T* CreatePrototype(const string& strName, const Vector2& vPos = Vector2::Zero,
		const Vector2& vSize = Vector2(100.f, 100.f))
	{
		T* pObj = new T;

		pObj->SetName(strName);
		pObj->SetPos(vPos);
		pObj->SetSize(vSize);
		pObj->m_pScene = this;

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		pObj->AddRef();
		m_mapPrototype.insert(make_pair(strName, pObj));

		return pObj;
	}

	template <typename T>
	T* CreatePrototype(const string& strName, const char* pFileName,
		const string& strPathName = DATA_PATH)
	{
		T* pObj = new T;

		pObj->SetName(strName);

		if (!pObj->Init(pFileName, strPathName))
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		pObj->AddRef();
		m_mapPrototype.insert(make_pair(strName, pObj));

		return pObj;
	}

	template <typename T>
	T* CreateCloneObject(const string& strPrototypeName,
		const string& strName)
	{
		T* pPrototype = (T*)FindPrototype(strPrototypeName);

		if (!pPrototype)
			return nullptr;

		T* pClone = (T*)pPrototype->Clone();

		if (pClone->IsUI())
			AddUI(pClone);

		else
			AddObject(pClone);

		return pClone;
	}

	template <typename T>
	T* CreateCloneBlockObj(const string& strPrototypeName)
	{
		T* pPrototype = (T*)FindPrototype(strPrototypeName);

		if (!pPrototype)
			return nullptr;

		T* pClone = (T*)pPrototype->Clone();
	/*	const char* a = typeid(T).name();
		size_t ab = typeid(T).hash_code();
		size_t bc = typeid(CTree).hash_code();*/
		string strName = pClone->GetName();
		int iCount;

		if (strName == "Baba")
		{
			iCount = GetCount(CHARACTER_TYPE::BABA); 
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::BABA);
		}
		else if (strName == "Rock")
		{
			iCount = GetCount(CHARACTER_TYPE::ROCK);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::ROCK);
		}
		else if (strName == "Flag")
		{
			iCount = GetCount(CHARACTER_TYPE::FLAG);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::FLAG);
		}
		else if (strName == "Wall")
		{
			iCount = GetCount(CHARACTER_TYPE::WALL);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::WALL);
		}
		else if (strName == "GroundTile")
		{
			iCount = GetCount(CHARACTER_TYPE::GROUNDTILE);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::GROUNDTILE);
		}
		else if (strName == "Grass")
		{
			iCount = GetCount(CHARACTER_TYPE::GRASS);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::GRASS);
		}
		else if (strName == "Tree")
		{
			iCount = GetCount(CHARACTER_TYPE::TREE);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::TREE);
		}
		else if (strName == "Flower")
		{
			iCount = GetCount(CHARACTER_TYPE::FLOWER);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::FLOWER);
		}
		else if (strName == "Fungi")
		{
			iCount = GetCount(CHARACTER_TYPE::FUNGI);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::FUNGI);
		}
		else if (strName == "Foliage")
		{
			iCount = GetCount(CHARACTER_TYPE::FOLIAGE);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::FOLIAGE);
		}
		else if (strName == "TPBlock")
		{
			iCount = GetCount(CHARACTER_TYPE::TPBLOCK);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::TPBLOCK);
		}
		else if (strName == "Water")
		{
			iCount = GetCount(CHARACTER_TYPE::WATER);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::WATER);
		}
		else if (strName == "Skull")
		{
			iCount = GetCount(CHARACTER_TYPE::SKULL);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::SKULL);
		}
		else if (strName == "Brick")
		{
			iCount = GetCount(CHARACTER_TYPE::BRICK);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::BRICK);
		}
		else if (strName == "Lava")
		{
			iCount = GetCount(CHARACTER_TYPE::LAVA);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CHARACTER_TYPE::LAVA);
		}
		//--

		else if (strName == "BabaName")
		{
			iCount = GetCount(NAME_TYPE::BABA);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(NAME_TYPE::BABA);
		}
		else if (strName == "RockName")
		{
			iCount = GetCount(NAME_TYPE::ROCK);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(NAME_TYPE::ROCK);
		}
		else if (strName == "WallName")
		{
			iCount = GetCount(NAME_TYPE::WALL);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(NAME_TYPE::WALL);
		}
		else if (strName == "FlagName")
		{
			iCount = GetCount(NAME_TYPE::FLAG);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(NAME_TYPE::FLAG);
		}
		else if (strName == "WaterName")
		{
			iCount = GetCount(NAME_TYPE::WATER);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(NAME_TYPE::WATER);
		}
		else if (strName == "SkullName")
		{
		iCount = GetCount(NAME_TYPE::SKULL);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(NAME_TYPE::SKULL);
		}
		else if (strName == "GrassName")
		{
		iCount = GetCount(NAME_TYPE::GRASS);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(NAME_TYPE::GRASS);
		}
		else if (strName == "LavaName")
		{
		iCount = GetCount(NAME_TYPE::LAVA);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(NAME_TYPE::LAVA);
		}
		else if (strName == "LavaName2")
		{
		iCount = GetCount(NAME_TYPE::LAVA);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(NAME_TYPE::LAVA);
		}
		//--

		else if (strName == "Is")
		{
			iCount = GetCount(CONNECT_TYPE::IS);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CONNECT_TYPE::IS);
		}
		else if (strName == "And")
		{
			iCount = GetCount(CONNECT_TYPE::AND);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(CONNECT_TYPE::AND);
		}

		else if (strName == "Push")
		{
			iCount = GetCount(STATE_TYPE::PUSH);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(STATE_TYPE::PUSH);
		}
		else if (strName == "You")
		{
			iCount = GetCount(STATE_TYPE::YOU);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(STATE_TYPE::YOU);
		}
		else if (strName == "Stop")
		{
			iCount = GetCount(STATE_TYPE::STOP);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(STATE_TYPE::STOP);
		}
		else if (strName == "Win")
		{
			iCount = GetCount(STATE_TYPE::WIN);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(STATE_TYPE::WIN);
		}
		else if (strName == "Sink")
		{
			iCount = GetCount(STATE_TYPE::SINK);
			strName.append("_");
			strName.append(to_string(iCount));
			AddCount(STATE_TYPE::SINK);
		}
		else if (strName == "Defeat")
		{
		iCount = GetCount(STATE_TYPE::DEFEAT);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(STATE_TYPE::DEFEAT);
		}
		else if (strName == "Melt")
		{
		iCount = GetCount(STATE_TYPE::MELT);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(STATE_TYPE::MELT);
		}
		else if (strName == "Hot")
		{
		iCount = GetCount(STATE_TYPE::HOT);
		strName.append("_");
		strName.append(to_string(iCount));
		AddCount(STATE_TYPE::HOT);
		}

		pClone->SetName(strName);

		if (pClone->IsUI())
			AddUI(pClone);

		else
			AddObject(pClone);

		return pClone;
	}

public:
	class CObj* GetPlayer() const
	{
		if (m_pPlayer)
			m_pPlayer->AddRef();

		return m_pPlayer;
	}

	CSceneResource*GetSceneResource() const
	{
		return m_pResource;
	}

	CCamera* GetMainCamera() const
	{
		return m_pMainCamera;
	}

	CSceneCollision* GetSceneCollision() const
	{
		return m_pCollision;
	}

	SCENE_TYPE GetSceneType()
	{
		return m_eType;
	}

	bool GetMoved()
	{
		return m_bMoved;
	}

	void SetMoved(bool bMoved)
	{
		m_bMoved = bMoved;
	}

	bool GetStart()
	{
		return m_bStart;
	}

	int GetCount(CHARACTER_TYPE eCharacterType)
	{
		return m_vecCharacterCount[(int)eCharacterType];
	}

	void AddCount(CHARACTER_TYPE eCharacterType)
	{
		m_vecCharacterCount[(int)eCharacterType] = ++m_vecCharacterCount[(int)eCharacterType];
	}

	int GetCount(NAME_TYPE eNameType)
	{
		return m_vecNameCount[(int)eNameType];
	}

	void AddCount(NAME_TYPE eNameType)
	{
		m_vecNameCount[(int)eNameType] = ++m_vecNameCount[(int)eNameType];
	}

	int GetCount(CONNECT_TYPE eConnectType)
	{
		return m_vecConnectCount[(int)eConnectType];
	}

	void AddCount(CONNECT_TYPE eConnectType)
	{
		m_vecConnectCount[(int)eConnectType] = ++m_vecConnectCount[(int)eConnectType];
	}

	int GetCount(STATE_TYPE eStateType)
	{
		return m_vecStateCount[(int)eStateType];
	}

	void AddCount(STATE_TYPE eStateType)
	{
		m_vecStateCount[(int)eStateType] = ++m_vecStateCount[(int)eStateType];
	}

	bool GetMoveSoundPlay()
	{
		return m_bMoveSoundPlay;
	}

	void SetMoveSoundPlay(bool bMoveSoundPlay)
	{
		m_bMoveSoundPlay = bMoveSoundPlay;
	}

	void SetSink()
	{
		m_bSink = true;
	}

	void SetDefeat()
	{
		m_bDefeat = true;
	}

	void SetMelt()
	{
		m_bMelt = true;
	}

	void SetReRegisterKeyChar(CHARACTER_TYPE eType)
	{
		m_eReRegisterKeyChar = eType;
	}

	bool GetInitialFrame()
	{
		return m_bInitialFrame;
	}

	void SetLavaMelt()
	{
		m_bLavaMelt = true;
	}

	bool GetLavaMelt()
	{
		return m_bLavaMelt;
	}

	bool GetPlayDefeatSound()
	{
		return m_bPlayDefeatSound;
	}

	void SetPlayDefeatSound(bool bSound)
	{
		m_bPlayDefeatSound = bSound;
	}
};

