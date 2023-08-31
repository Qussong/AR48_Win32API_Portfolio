#include "vanCamera.h"
#include "vanApplication.h"
#include "vanTransform.h"
#include "vanTexture.h"

#define CAMERA_SPEED			500.0f
#define CAMERA_OFFSET_SPEED		10.0f	// Camera�� offset ���� 10�� ������ �����Ѵ�.

extern van::Application application;	// Client.cpp�� ����Ǿ� �ִ� ��������������

namespace van
{

	math::Vector2 Camera::mResolution = math::Vector2::Zero;
	math::Vector2 Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2 Camera::mDistance = math::Vector2::Zero;
	math::Vector2 Camera::mCameraOffset = math::Vector2::Zero;

	GameObject* Camera::mTarget = nullptr;

	math::Vector2 Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2 Camera::mHeightLimit = math::Vector2::Zero;

	std::list<tCamEffect>	Camera::m_listCamEffect = {};
	Texture* Camera::mWhiteTex = nullptr;
	Texture* Camera::mBlackTex = nullptr;

	void Camera::Init()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = mResolution / 2.0f;

		// ���ȭ�� ũ���� ī�޶� ȿ���� �ؽ��� ����
		mWhiteTex = Texture::Create(L"WhiteTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(255, 255, 255));
		mBlackTex = Texture::Create(L"BlackTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(0, 0, 0));
	}

	void Camera::Update()
	{
		// ī�޶� �Ĵٺ� Ÿ���� �����ϸ� �ش� Ÿ���� ����ٴѴ�.
		if (mTarget)	
		{
			Transform* tr = mTarget->GetComponent<Transform>();		// Target�� ��ġ���� �����´�
			mLookPosition = (tr->GetPosition()) + mCameraOffset;	// ī�޶� �Ĵٺ�����ġ�� ����
		}
		// ī�޶��� Ÿ���� ���ٸ� ī�޶� ������ �� �ִ�.
		else
		{
			if (Input::GetKey(eKeyCode::Up))
			{
				mLookPosition.y -= CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Left))
			{
				mLookPosition.x -= CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Down))
			{
				mLookPosition.y += CAMERA_SPEED * Time::GetDeltaTime();
			}
			if (Input::GetKey(eKeyCode::Right))
			{
				mLookPosition.x += CAMERA_SPEED * Time::GetDeltaTime();
			}
		}

		// ī�޶� Ÿ���� �߽����� ���� ���� �̵��� �Ÿ�
		mDistance = mLookPosition - (mResolution / 2.0f);		
		
		// [ ī�޶� �̵� ���� ]
		// ī�޶� �̹����� �Ѿ�� ������ ������ �ʰ��Ѵ�.
		// x��
		if (mDistance.x <= mWidthLimit.x)
		{
			mDistance.x = mWidthLimit.x;
		}
		if (mDistance.x >= mWidthLimit.y)
		{
			mDistance.x = mWidthLimit.y;
		}
		// y��
		if (mDistance.y <= mHeightLimit.x)
		{
			mDistance.y = mHeightLimit.x;
		}
		if (mDistance.y >= mHeightLimit.y)
		{
			mDistance.y = mHeightLimit.y;
		}
	}

	void Camera::Render(HDC _hdc)
	{
		// �̺�Ʈ�� ���ٸ� ����
		if (m_listCamEffect.empty())
			return;

		tCamEffect& effect = m_listCamEffect.front();
		//mCurCamEffect = effect.eEffect;

		effect.fCurTime += Time::GetDeltaTime();

		float fRatio = effect.fCurTime / effect.fDuration;

		if (fRatio < 0.f)
			fRatio = 0.f;
		if (fRatio > 1.f)
			fRatio = 1.f;

		int iAlpha = 0;

		// �̺�Ʈ�� ���� ���İ� ����
		if (effect.eEffect == CAM_EFFECT::FADE_OUT)
		{
			iAlpha = (int)(255.f * fRatio);
		}
		else if (effect.eEffect == CAM_EFFECT::FADE_IN)
		{
			iAlpha = (int)(255.f * (1.f - fRatio));
		}
		else if (effect.eEffect == CAM_EFFECT::Pause)
		{
			iAlpha = 255;
		}

		// AlphaBlend ���ð� ����
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER; // ������ ��� �̹����� ��ģ�ٴ� �ǹ�
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = iAlpha; // ���� ���İ� ����

		if (effect.TexColor == RGB(255, 255, 255))
		{
			AlphaBlend(_hdc,
				0, 0
				, (int)mWhiteTex->GetWidth()
				, (int)mWhiteTex->GetHeight()
				, mWhiteTex->GetHdc()
				, 0, 0
				, (int)mWhiteTex->GetWidth()
				, (int)mWhiteTex->GetHeight()
				, bf);
		}
		else if (effect.TexColor == RGB(0, 0, 0))
		{
			AlphaBlend(_hdc,
				0, 0
				, (int)mBlackTex->GetWidth()
				, (int)mBlackTex->GetHeight()
				, mBlackTex->GetHdc()
				, 0, 0
				, (int)mBlackTex->GetWidth()
				, (int)mBlackTex->GetHeight()
				, bf);
		}


		if (effect.fCurTime > effect.fDuration)
		{
			//mCurCamEffect = CAM_EFFECT::NONE;
			m_listCamEffect.pop_front();
		}
	}

	void Camera::SetCameraOffsetSmooth(math::Vector2 _offset, int _doubleSpeed)
	{
		bool flagX = true;
		bool flagY = true;

		// ���� offset ���� ��ǥġ offset ���� ���̰� 10���� ������ Ȯ��
		if (fabs(_offset.x - mCameraOffset.x) < 10.0f)
		{
			flagX = false;
		}
		if (fabs(_offset.y - mCameraOffset.y) < 10.0f)
		{
			flagY = false;
		}

		// offset x�� ����
		if (mCameraOffset.x != _offset.x)
		{
			if (_offset.x > 0 && flagX)
			{
				mCameraOffset.x += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (_offset.x < 0 && flagX)
			{
				mCameraOffset.x -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (!flagX)
			{
				mCameraOffset.x = _offset.x;
			}
		}

		// offset y�� ����
		if (mCameraOffset.y != _offset.y)
		{
			if (_offset.y > 0 && flagY)
			{
				mCameraOffset.y += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (_offset.y < 0 && flagY)
			{
				mCameraOffset.y -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
			}
			else if (!flagY)
			{
				mCameraOffset.y = _offset.y;
			}
		}

	}

	void Camera::ClearCameraOffsetSmooth(int _doubleSpeed)
	{
		bool flagX = true;
		bool flagY = true;

		// offset ���� 10���� ������ Ȯ��
		if (fabs(mCameraOffset.x) < 10.0f)
		{
			flagX = false;
		}
		if (fabs(mCameraOffset.y) < 10.0f)
		{
			flagY = false;
		}

		// offset x�� ����
		if (mCameraOffset.x > 0
			&& flagX)
		{
			mCameraOffset.x -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (mCameraOffset.x < 0
			&& flagX)
		{
			mCameraOffset.x += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (!flagX)
		{
			mCameraOffset.x = 0.0f;
		}

		// offset y�� ����
		if (mCameraOffset.y > 0
			&& flagY)
		{
			mCameraOffset.y -= CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (mCameraOffset.y < 0
			&& flagY)
		{
			mCameraOffset.y += CAMERA_OFFSET_SPEED * (Time::GetDeltaTime() * _doubleSpeed);
		}
		else if (!flagY)
		{
			mCameraOffset.y = 0.0f;
		}
	}

}