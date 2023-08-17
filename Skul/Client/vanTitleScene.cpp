#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"
#include "vanCamera.h"

#include "vanMonster.h"
#include "vanAnimator.h"

namespace van
{
	TitleScene::TitleScene()
	{
		// nothing
	}

	TitleScene::~TitleScene()
	{
		// nothing
	}

	void TitleScene::Init()
	{
		// 1) Title Art
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Title_Art"));
		bgsr->SetScale(math::Vector2(0.67f,0.67f));
		bgsr->SetAffectCamera(false);
		// �ش� Scene������ ī�޶� �ִ� �̵��Ÿ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// 2) Title Logo
		BackGround* logo = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		logo->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 200));
		bgsr = logo->GetComponent<SpriteRenderer>();
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Title_Logo"));
		bgsr->SetScale(math::Vector2(0.67f,0.67f));
		bgsr->SetAffectCamera(false);

		SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
	}

	void TitleScene::Update()
	{
		Scene::Update();						// �θ��� Update �Լ� ȣ��
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
		//  ī�޶� �ִ� �̵� ���� �Ÿ� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶�� �ش� Scene�� Target ���߱�
		Camera::SetTarget(GetSceneTarget());
	}

	void TitleScene::SceneOut()
	{
		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
	}
}