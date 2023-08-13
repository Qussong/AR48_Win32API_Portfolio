#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanTransform.h"

namespace van
{
	BackGround::BackGround()
	{
		// nothing
	}

	BackGround::BackGround(math::Vector2 _offset)
	{
		// nothing
	}

	BackGround::~BackGround()
	{
		// nothing
	}

	void BackGround::Init()
	{
		// nothing
	}

	void BackGround::Update()
	{
		GameObject::Update();
	}

	void BackGround::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void BackGround::MakeAnimation()
	{
		// nothing
	}

	void BackGround::SetAutoCameraLimit()
	{
		// SpriteRender�� �ּҰ� ����
		SpriteRenderer* bgsr = this->GetComponent<SpriteRenderer>();
		// SpriteRender ������ �Լ� ����
		if (nullptr == bgsr)
		{
			return;
		}
		// ��� �̹��� �ҷ���
		Texture* image = bgsr->GetTexture();
		// �̹����� ������ �Լ� ����
		if (nullptr == image)
		{
			return;
		}
		// BackGround ��ü�� ��ġ�� ����
		math::Vector2 pos = GetComponent<Transform>()->GetPosition();
		// ��� �̹����� ������ ���ݰ� ����
		math::Vector2 imageSize = image->GetSize() / 2.0f;

		float tempLimitX = std::fabsf(pos.x - imageSize.x);
		float tempLimitY = std::fabsf(pos.y - imageSize.y);

		mCameraLimitLeft	= -tempLimitX;	// ���� �ִ� �̵����� �Ÿ�
		mCameraLimitRight	= tempLimitX;	// ������ �ִ� �̵����� �Ÿ�
		mCameraLimitUp		= -tempLimitY;	// ���� �ִ� �̵����� �Ÿ�
		mCameraLimitDown	= tempLimitY;	// �Ʒ��� �ִ� �̵����� ��
	}
}