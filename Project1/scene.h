#pragma once
#include <list>
#include <typeinfo>
#include <vector>
#include "main.h"
#include "polygon.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "camera.h"
#include "game_object.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "wall.h"
#include "wall2.h"
#include "map.h"
#include "effect.h"

class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[3];

public:
	CScene(){}
	virtual ~CScene(){}

	virtual void Init()
	{
		CBullet::Load();
		CExplosion::Load();
		CEffect::Load();


		CMap::Load();
		CWall::Load();
		CWall2::Load();

		AddGameObject<CCamera>(0);
		AddGameObject<CField>(1);
		AddGameObject<CPlayer>(1);
	
	/*	AddGameObject<CWall>(1);
		AddGameObject<CWall>(1)->SetPosision(D3DXVECTOR3( 1.0f, 0.0f, 0.0f));
		AddGameObject<CWall>(1)->SetPosision(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));*/

		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(-5.0f, 0.0f, 5.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(5.0f, 0.0f, 5.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(-10.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(8.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(-4.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(9.0f, 0.0f, 15.0f));

//		AddGameObject<CPolygon>(2);
	}

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}

		CBullet::Unload();
		CExplosion::Unload();
		CEffect::Unload();
		CWall::Unload();
		CWall2::Unload();
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](CGameObject* object) {return object->Destory(); });

		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	template<typename T>
	T* AddGameObject(int Layer) 
	{

		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}


	template <typename T>
	T* GetGameObject(int Layer)
	{		
			for (CGameObject* object : m_GameObject[Layer])
			{
				if (typeid(*object) == typeid(T))
				{
					return (T*)object;
				}
			}
		
		return NULL;
	}


	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects;
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

};
