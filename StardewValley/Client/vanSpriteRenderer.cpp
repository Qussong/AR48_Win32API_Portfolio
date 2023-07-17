#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanApplication.h"
#include "vanCamera.h"

extern van::Application application;

namespace van
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::Transform)
		, mScale(math::Vector2::One)
		, mTexture(nullptr)
		, mAffectCamera(true)
		, mAlpha(1.0f)
	{
		// nothing
	}

	SpriteRenderer::~SpriteRenderer()
	{
		// nothing
	}

	void SpriteRenderer::Init()
	{
		// nothing
	}

	void SpriteRenderer::Update()
	{
		// nothing
	}

	void SpriteRenderer::Render(HDC _hdc)
	{
		if (mTexture == nullptr)	// �׷��� �̹̰� ���� ��
			return;

		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		mTexture->Render(
			_hdc
			, tr->GetPosition()
			, math::Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, math::Vector2::Zero	// offset
			, mScale				// scale
			, mAlpha);				// alpha

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//math::Vector2 pos = tr->GetPosition();

		//// ī�޶��� �̵��� ������� ȭ��󿡼� �׻� ���� ��ġ�� �־�� �� �� false
		//// ī�޶��� �̵��� ���� ȭ��󿡼� �������� �ʿ��� ��� true
		//if (mAffectCamera == true)
		//	pos = Camera::CalculatePosition(pos);

		//// �׷��� �̹����� Ȯ���ڰ� *.bmp �϶�
		//if (mTexture->GetType() == eTextureType::Bmp)
		//{
		//	TransparentBlt(
		//		// Ÿ��
		//		_hdc
		//		, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)		// �̹����� �߽��� �Էµ� x��ǥ�� ��ġ
		//		, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)	// �̹����� �߽��� �Էµ� y��ǥ�� ��ġ
		//		, mTexture->GetWidth() * mScale.x
		//		, mTexture->GetHeight() * mScale.y
		//		// ����
		//		, mTexture->GetHdc()
		//		, 0, 0
		//		, mTexture->GetWidth()
		//		, mTexture->GetHeight()
		//		// ���� �÷�
		//		, RGB(255, 0, 255));
		//}
		//// �׷��� �̹����� alpha ���� ������ �ִ� *.bmp �϶�
		//else if (mTexture->GetType() == eTextureType::AlphaBmp)
		//{
		//	// AlphaBlend() ����
		//	BLENDFUNCTION func = {};
		//	int alpha = (int)(mAlpha * 255.0f);	// 0.0f ~ 1.0f -> 0 ~ 255
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = AC_SRC_ALPHA;
		//	if (alpha <= 0)
		//		alpha = 0;
		//	func.SourceConstantAlpha = alpha;

		//	AlphaBlend(_hdc
		//		// Ÿ��
		//		, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)
		//		, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)
		//		, mTexture->GetWidth() * mScale.x
		//		, mTexture->GetHeight() * mScale.y
		//		// ����
		//		, mTexture->GetHdc()
		//		, 0, 0
		//		, mTexture->GetWidth()
		//		, mTexture->GetHeight()
		//		// ����
		//		, func);
		//}
		//// �׷��� �̹����� Ȯ���ڰ� *.png �϶�
		//else if (mTexture->GetType() == eTextureType::Png)
		//{
		//	Gdiplus::Graphics graphics(_hdc);
		//	graphics.DrawImage(
		//		mTexture->GetImage()
		//		, (int)(pos.x - (mTexture->GetWidth() * mScale.x / 2.0f))
		//		, (int)(pos.y - (mTexture->GetHeight() * mScale.y / 2.0f))
		//		, (int)(mTexture->GetWidth() * mScale.x)
		//		, (int)(mTexture->GetHeight() * mScale.y));
		//}
		//// �׷��� �̹����� Ȯ���ڰ� *.bmp , *.png �� �ƴҶ�
		//else
		//	__noop;
	}
}