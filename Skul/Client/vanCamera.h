#pragma once
#include "vanGameObject.h"

namespace van
{
	class Camera
	{
	public:
		static void Init();
		static void Update();

		__forceinline static math::Vector2 CalculatePosition(math::Vector2 pos) { return pos - mDistance; }
		__forceinline static GameObject* GetTarget() { return mTarget; }
		__forceinline static void SetTarget(GameObject* _target) { mTarget = _target; }
		__forceinline static void SetLimitDistance(math::Vector2 _widthLimit, math::Vector2 _heightLimit)
		{
			mWidthLimit = _widthLimit;
			mHeightLimit = _heightLimit;
		}

	private:
		
		static math::Vector2 mResolution;	// ȭ�� �ػ�
		static math::Vector2 mLookPosition;	// ī�޶� �ٶ󺸰� �ִ� ��ġ
		static math::Vector2 mDistance;		// ����� �������� �̵��� �Ÿ�
		static GameObject* mTarget;			// ī�޶� �ٶ󺸴� GameObject ��ü

		// ī�޶� �̵� ���Ѱ� ����
		static math::Vector2 mWidthLimit;	// width.x = Left, width.y = Right
		static math::Vector2 mHeightLimit;	// height.x = Up, height.y = Down
	};
}

