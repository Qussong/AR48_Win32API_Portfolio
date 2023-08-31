#pragma once
#include "vanGameObject.h"

namespace van
{
	enum class CAM_EFFECT
	{
		FADE_IN,
		FADE_OUT,
		Pause,
		NONE,
	};

	struct tCamEffect
	{
		CAM_EFFECT	eEffect;
		float		fDuration;
		float		fCurTime;
		COLORREF	TexColor;
	};

	class Camera
	{
	public:
		static void Init();
		static void Update();
		static void Render(HDC _hdc);


		__forceinline static math::Vector2 CalculatePosition(math::Vector2 pos) { return pos - mDistance; }
		__forceinline static GameObject* GetTarget() { return mTarget; }
		__forceinline static void SetTarget(GameObject* _target) { mTarget = _target; }
		__forceinline static void SetLimitDistance(math::Vector2 _widthLimit, math::Vector2 _heightLimit)
		{
			mWidthLimit = _widthLimit;
			mHeightLimit = _heightLimit;
		}
		__forceinline static void SetCameraOffset(math::Vector2 _offset) { mCameraOffset = _offset; }
		__forceinline static math::Vector2 GetCameraOffset() { return mCameraOffset; }
		__forceinline static void CameraOffsetClear() { mCameraOffset = math::Vector2::Zero; }
		static void SetCameraOffsetSmooth(math::Vector2 _offset, int _doubleSpeed);
		static void ClearCameraOffsetSmooth(int _doubleSpeed = 1);

		static math::Vector2 GetLookPosition() { return mLookPosition; }
		static void SetLookPosition(math::Vector2 _pos) { mLookPosition = _pos; }

	public:
		static void fadeIn(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::FADE_IN;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

		static void fadeOut(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::FADE_OUT;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

		static void Pause(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::Pause;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

	private:
		static math::Vector2 mResolution;	// ȭ�� �ػ�
		static math::Vector2 mLookPosition;	// ī�޶� �ٶ󺸰� �ִ� ��ġ
		static math::Vector2 mDistance;		// ����� �������� �̵��� �Ÿ�
		static GameObject* mTarget;			// ī�޶� �ٶ󺸴� GameObject ��ü
		static math::Vector2 mCameraOffset;	// ī�޶� offset
		// ī�޶� �̵� ���Ѱ� ����
		static math::Vector2 mWidthLimit;	// width.x = Left, width.y = Right
		static math::Vector2 mHeightLimit;	// height.x = Up, height.y = Down

	private:
		static std::list<tCamEffect>  m_listCamEffect;	// ī�޶� ȿ�� �̺�Ʈ ����Ʈ
		static class Texture* mWhiteTex;				// ī�޶� ȿ���� �ؽ���
		static class Texture* mBlackTex;				// ī�޶� ȿ���� �ؽ���
	};
}

