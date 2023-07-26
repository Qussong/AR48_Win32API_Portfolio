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
		Layer& GetLayer(enums::eLayerType _type) { return mLayers[(UINT)_type]; }	// �ش� Scene�� �����ϴ� Layer���� �Ķ���Ϳ� �ش��ϴ� ������ �����´�.
																					// CommonInclude.h �� ���ǵǾ� �ִ� enums::eLayerType�� ���� 
		__forceinline void SetSceneTarget(GameObject* _target = nullptr) { target = _target; }	// �ش� Scene ������ Ÿ�� ����
		__forceinline GameObject* GetSceneTarget() { return target; }	// �ش� Scene ������ Ÿ�� ���� �޾ƿ���

	private:
		std::vector<Layer> mLayers;	// �ش� Scene�� �����ϴ� Layer ��ü���� ����
		GameObject* target;	// �ش� Scene���� Camera�� Target
	};
}

