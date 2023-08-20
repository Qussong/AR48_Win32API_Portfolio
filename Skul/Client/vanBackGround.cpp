#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanTransform.h"

namespace van
{
	BackGround::BackGround()
	{
		AddComponent<SpriteRenderer>();
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
		math::Vector2 scale = bgsr->GetScale();

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
		// ��� �̹����� ������ ���ݰ� ����(���� ����� �׷����� scale�� ���)
		math::Vector2 imageSize = (image->GetSize() * scale) / 2.0f;

		float tempLimitX = std::fabsf(pos.x - imageSize.x);
		float tempLimitY = std::fabsf(pos.y - imageSize.y);

		mCameraLimitLeft	= -tempLimitX;	// ���� �ִ� �̵����� �Ÿ�
		mCameraLimitRight	= tempLimitX;	// ������ �ִ� �̵����� �Ÿ�
		mCameraLimitUp		= -tempLimitY;	// ���� �ִ� �̵����� �Ÿ�
		mCameraLimitDown	= tempLimitY;	// �Ʒ��� �ִ� �̵����� ��
	}
}