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

	virtual void Init() = 0;

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
