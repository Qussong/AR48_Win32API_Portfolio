#pragma once
#include "vanEntity.h"	// Entity Ŭ���� ���
#include "vanLayer.h"	// mLayers ������ Layer��ü�� ����
#include "vanPlayerFrame.h"
#include "vanHpBar.h"

namespace van
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void SceneIN();
		virtual void SceneOut();
		virtual void CameraMove();
		virtual void MakeWorld();
		virtual void MakeFloor();
		virtual void MakeWall();
		virtual void MakeDoor();
		virtual void MakeUI();

		__forceinline void AddGameObject(enums::eLayerType type, GameObject* gameObj) { mLayers[(int)type].AddGameObject(gameObj); }
		__forceinline Layer& GetLayer(enums::eLayerType _type) { return mLayers[(UINT)_type]; }	// �ش� Scene�� �����ϴ� Layer���� �Ķ���Ϳ� �ش��ϴ� ������ �����´�.
		__forceinline void SetSceneTarget(GameObject* _target = nullptr) { target = _target; }	// �ش� Scene ������ Ÿ�� ����
		__forceinline GameObject* GetSceneTarget() { return target; }							// �ش� Scene ������ Ÿ�� ���� �޾ƿ���
		__forceinline math::Vector2 GetCameraWidthLimit() { return mCameraWidthLimit; }
		__forceinline void SetCameraWidthLimit(math::Vector2 _limit) { mCameraWidthLimit = _limit; }
		__forceinline math::Vector2 GetCameraHeightLimit() { return mCameraHeightLimit; }
		__forceinline void SetCameraHeightLimit(math::Vector2 _limit) { mCameraHeightLimit = _limit; }

		__forceinline int GetMonsterCnt() { return mMonsterCnt; }
		__forceinline void AddMonsterCnt(int _cnt = 1) { mMonsterCnt += _cnt; }
		__forceinline void LoseMonsterCnt(int _cnt = 1) { mMonsterCnt -= _cnt; }

	private:
		std::vector<Layer> mLayers;			// �ش� Scene�� �����ϴ� Layer ��ü���� ����
		GameObject* target;					// �ش� Scene���� Camera�� Target
		math::Vector2 mCameraWidthLimit;	// �ش� Scene���� Camera�� �¿� �ִ� �̵� ���ɰŸ�
		math::Vector2 mCameraHeightLimit;	// �ش� Scene���� Camera�� ���� �ִ� �̵� ���ɰŸ�

		int mMonsterCnt = 0;					// �ش� Scene������ ���� ����
		PlayerFrame* mPlayerFrame = nullptr;
		HpBar* mHpBar = nullptr;
	};
}

