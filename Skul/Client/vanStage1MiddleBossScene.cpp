#include "vanStage1MiddleBossScene.h"
#include "vanCamera.h"

#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanObject.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Stage1MiddleBossScene::Stage1MiddleBossScene()
	{
		// nothing
	}

	Stage1MiddleBossScene::~Stage1MiddleBossScene()
	{
		// nothing
	}

	void Stage1MiddleBossScene::Init()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Middle_Boss"));			// BackGround ��ü�� texture ����
		bgsr->SetAffectCamera(true);
		// ����̹����� ũ�⸦ ������� ī�޶��� �̵����Ѱ� ���
		bg->SetAutoCameraLimit();
		// �ش� Scene�� ī�޶��� �̵����Ѱ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		//SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1MiddleBossScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1MiddleBossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage1MiddleBossScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1MiddleBossScene::SceneIN()
	{
		// �ش� Scene������ ī�޶� �ִ� �̵� ���� �Ÿ��� ī�޶� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶� �ش� Scene�� Ÿ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1MiddleBossScene::SceneOut()
	{

	}
}