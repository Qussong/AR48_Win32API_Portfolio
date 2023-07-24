#pragma once
#include "vanEntity.h"	// Entity Ŭ���� ���
#include "vanLayer.h"	// mLayers ������ Layer��ü�� ����

namespace van
{
	//using namespace van::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);

		__forceinline void AddGameObject(enums::eLayerType type, GameObject* gameObj) 
													{ mLayers[(int)type].AddGameObject(gameObj); }

		Layer& GetLayer(enums::eLayerType _type) { return mLayers[(UINT)_type]; }

		__forceinline void SetSceneTarget(GameObject* _target = nullptr) { target = _target; }
		__forceinline GameObject* GetSceneTarget() { return target; }
			
	private:
		std::vector<Layer> mLayers;
		// Scene Ŭ�������� Layer ��ü�� ������ ������ �����ֱ⸸ �� ���̱⿡ ���� �ּҷ� �������� �ʴ´�.

		GameObject* target;	// �ش� Scene�� Target
	};
}

