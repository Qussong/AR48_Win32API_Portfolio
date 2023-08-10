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

		math::Vector2 tempLimitX = pos.x - imageSize.x;
		math::Vector2 tempLimitY = pos.y - imageSize.y;

		tempLimitX.x = std::fabsf(tempLimitX.x);
		tempLimitX.y = std::fabsf(tempLimitX.y);
		tempLimitY.x = std::fabsf(tempLimitY.x);
		tempLimitY.y = std::fabsf(tempLimitY.y);

		mCameraLimitLeft = -tempLimitX.x;	// ���� �ִ� �̵����� �Ÿ�
		mCameraLimitRight = tempLimitX.y;	// ������ �ִ� �̵����� �Ÿ�
		mCameraLimitUp = -tempLimitY.x;		// ���� �ִ� �̵����� �Ÿ�
		mCameraLimitDown = tempLimitY.y;	// �Ʒ��� �ִ� �̵����� �Ÿ�
	}
}