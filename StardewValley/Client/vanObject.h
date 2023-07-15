#pragma once
#include "vanScene.h"
#include "vanGameObject.h"
#include "vanSceneManager.h"


namespace van::Object
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();	// SceneManger�� ���� ���� ȭ�鿡 ���̰� �ִ� Scene�� �ּҸ� �����´�.
		scene->AddGameObject(type, gameObject);			// ���� Scene�� AddGameObject �Լ��� ȣ���Ͽ� 
														// ���ϴ� Layer�� ���ϴ� TŸ�� ��ü(=GameObject��ü) �߰����ش�.
		return gameObject;
	}
}
 