#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

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
		MakeAnimation();
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
		Animator* at = GetComponent<Animator>();

		at->CreateAnimation(L"BG_Intro", ResourceManager::Find<Texture>(L"BG_Intro"), math::Vector2(0.0f, 0.0f), math::Vector2(1920.0f, 1080.0f), 40);
		at->CreateAnimation(L"BG_Intro_Loop", ResourceManager::Find<Texture>(L"BG_Intro_Loop"), math::Vector2(0.0f, 0.0f), math::Vector2(1920.0f, 1080.0f), 11);
		at->SetScale(math::Vector2(0.67f, 0.67f));
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