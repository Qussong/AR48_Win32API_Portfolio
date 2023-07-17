#include "vanAnimation.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanCamera.h"
#include "vanTexture.h"
#include "vanAnimator.h"

namespace van
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		//, mScale(math::Vector2::One)
	{
	}

	Animation::~Animation()
	{
		// nothing
	}

	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;

			if (mIndex < mSpriteSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}

	void Animation::Render(HDC _hdc)
	{
		if (mTexture == nullptr)
			return;
		
		Sprite sprite = mSpriteSheet[mIndex];
		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		// ĳ���� �̹����� �߽��� ��ǥ�� ������ �ϰ� offset �� ��ŭ ��ǥ���� �̵��ϵ��� �Ѵ�.
		math::Vector2 pos = tr->GetPosition()/* - (sprite.size / 2.0f)*/ + sprite.offset;
		Animator* ani = mAnimator;

		mTexture->Render(
			_hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, sprite.offset
			, ani->GetScale()
			, ani->GetAlpha());

		//Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		//math::Vector2 pos = tr->GetPosition();

		//if (mAnimator->GetAffectedCamera())
		//	pos = Camera::CalculatePosition(pos);

		//// BMP
		//if (mTexture->GetType() == eTextureType::Bmp)
		//{
		//	TransparentBlt(
		//		// Ÿ��
		//		_hdc
		//		, (int)pos.x - (mSpriteSheet[mIndex].size.x / 2.0f) /*+ mSpriteSheet[mIndex].offset.x*/
		//		, (int)pos.y - (mSpriteSheet[mIndex].size.y / 2.0f) /*+ mSpriteSheet[mIndex].offset.y*/
		//		, mSpriteSheet[mIndex].size.x * mScale.x
		//		, mSpriteSheet[mIndex].size.y * mScale.y
		//		// ����
		//		, mTexture->GetHdc()
		//		, mSpriteSheet[mIndex].leftTop.x * mScale.x
		//		, mSpriteSheet[mIndex].leftTop.y * mScale.y
		//		, mSpriteSheet[mIndex].size.x
		//		, mSpriteSheet[mIndex].size.y
		//		// ���� �÷�
		//		, RGB(255, 0, 255));
		//}
		//// AlpaBMP
		//else if (mTexture->GetType() == eTextureType::AlphaBmp)
		//{
		//	// AlphaBlend() ����
		//	BLENDFUNCTION func = {};
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = AC_SRC_ALPHA;
		//	// 0.0f ~ 1.0f -> 0 ~ 255
		//	int alpha = (int)(mAnimator->GetAlpha() * 255.0f);
		//	if (alpha <= 0)
		//		alpha = 0;
		//	func.SourceConstantAlpha = alpha; // 0 ~ 255

		//	AlphaBlend(
		//		// Ÿ��
		//		_hdc
		//		, (int)pos.x - (mSpriteSheet[mIndex].size.x / 2.0f) /*+ mSpriteSheet[mIndex].offset.x*/
		//		, (int)pos.y - (mSpriteSheet[mIndex].size.y / 2.0f) /*+ mSpriteSheet[mIndex].offset.y*/
		//		, mSpriteSheet[mIndex].size.x * mScale.x
		//		, mSpriteSheet[mIndex].size.y * mScale.y
		//		// ����
		//		, mTexture->GetHdc()
		//		, mSpriteSheet[mIndex].leftTop.x
		//		, mSpriteSheet[mIndex].leftTop.y
		//		, mSpriteSheet[mIndex].size.x
		//		, mSpriteSheet[mIndex].size.y
		//		// ����
		//		, func);
		//}
		//// PNG
		//else if (mTexture->GetType() == eTextureType::Png)
		//{
		//	Gdiplus::Graphics graphics(_hdc);
		//	graphics.DrawImage(
		//		mTexture->GetImage()
		//		, (int)(pos.x - (mSpriteSheet[mIndex].size.x / 2.0f))
		//		, (int)(pos.y - (mSpriteSheet[mIndex].size.y / 2.0f))
		//		, (int)(mSpriteSheet[mIndex].size.x * mScale.x)
		//		, (int)(mSpriteSheet[mIndex].size.y * mScale.y));
		//}
		//// �׷��� �̹����� Ȯ���ڰ� *.bmp , *.png �� �ƴҶ�
		//else
		//	__noop;
	}

	void Animation::Create(const std::wstring& _name
		, Texture* _texture
		, math::Vector2 _leftTop
		, math::Vector2 _size
		, math::Vector2 _offset
		, UINT _spriteLength
		, float _duration)
	{
		mTexture = _texture;

		for (size_t i = 0; i < _spriteLength; ++i)
		{
			Sprite sprite = {};

			sprite.leftTop.x = _leftTop.x + (_size.x * i);
			sprite.leftTop.y = _leftTop.y;
			sprite.size = _size;
			sprite.offset = _offset;
			sprite.duration = _duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}