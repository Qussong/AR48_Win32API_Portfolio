#pragma once
#include "CommonInclude.h"
#include "vanCollider.h"

namespace van
{
#define LAYER_MAX (UINT)eLayerType::End	// �� Layer ����

	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	using namespace enums;

	class CollisionManager
	{
	public:
		static void Init();				// �ʱ�ȭ
		static void Update();			// �� ����
		static void Render(HDC hdc);	// ���
		static void Release();			// ???

		static void Clear();	// mCollisionMap, mLayerMasks �� ���� �ʱ�ȭ�Ѵ�.
		static void SetCollisionLayerCheck(eLayerType _left, eLayerType _right, bool _enable);	// �Ķ���ͷ� ������ �� ���̾�(_left, _right)���� �浹üũ ���� ����
		static bool Intersect(Collider* _left, Collider* _right);							// �浹���� Ȯ�� (�浹�� true ��ȯ)
		static void ColliderCollision(Collider* _left, Collider* _right);					// �� ��ü�� �浹������(enter, stay, exit)���� ���� ���
		static void LayerCollision(class Scene* _scene, eLayerType _left, eLayerType _right);	// ���̾�鰣�� �浹 üũ���� ����

		static bool ColliderCollisionCheck();

	private:
		static std::map<UINT64, bool> mCollisionMap;			// �浹 ���� ����
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];	// ���̾�鰣�� �浹 üũ���� ������ ����
	};
}

