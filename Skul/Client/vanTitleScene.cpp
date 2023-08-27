#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"
#include "vanCamera.h"
#include "vanAnimator.h"
#include "vanSound.h"

namespace van
{
	TitleScene::TitleScene()
		: mBackGround(nullptr)
	{
		// nothing
	}

	TitleScene::~TitleScene()
	{
		// nothing
	}

	void TitleScene::Init()
	{
		mBackGround = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		mBackGround->GetComponent<Animator>()->PlayAnimation(L"BG_Intro", false);
		mBackGround->GetComponent<Animator>()->SetAffectedCamera(false);
		mBackGround->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));

		// �ش� Scene������ ī�޶� �ִ� �̵��Ÿ� ����
		SetCameraWidthLimit(math::Vector2(mBackGround->GetLimitLeft(), mBackGround->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(mBackGround->GetLimitUp(), mBackGround->GetLimitDown()));

		SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
	}

	void TitleScene::Update()
	{
		Animator* at = mBackGround->GetComponent<Animator>();

		Scene::Update();						// �θ��� Update �Լ� ȣ��

		if (at->IsActiveAnimationComplete() == true)
		{
			if(mbPlayAnimation == true)
			{
				at->PlayAnimation(L"BG_Intro_Loop", true);
				mbPlayAnimation = false;
			}
		}
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);					// �θ��� Render �Լ� ȣ��

		// Scene ����
		const wchar_t* str = L"[ TitleScene ]";
		Text::PrintwString(_hdc, 10, 30, str);	// �Ʒ� �θ� �������� �ʴ´�.
	}

	void TitleScene::SceneIN()
	{
		// ��� ����
		SetBgSound(ResourceManager::Load<Sound>(L"TitleSound", L"..\\MyResources\\skul\\Sound\\MainTitle.wav"));
		GetBgSound()->Play(false);

		//  ī�޶� �ִ� �̵� ���� �Ÿ� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶�� �ش� Scene�� Target ���߱�
		Camera::SetTarget(GetSceneTarget());
	}

	void TitleScene::SceneOut()
	{
		// ��� ���� ����
		GetBgSound()->Stop(true);

		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
	}
}