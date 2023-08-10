#include "vanStage1BossEnterScene.h"
#include "vanCamera.h"

#include "vanBackGround.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"

namespace van
{
	Stage1BossEnterScene::Stage1BossEnterScene()
	{
		// nothing
	}

	Stage1BossEnterScene::~Stage1BossEnterScene()
	{
		// nothing
	}

	void Stage1BossEnterScene::Init()
	{
		// 1) BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		//bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, -80.0f));			// ��ġ�� ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Boss_Enter"));				// BackGround ��ü�� texture ����
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));											// Scale ����
		bgsr->SetAffectCamera(true);

		//SetSceneTarget(nullptr);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1BossEnterScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1BossEnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage1BossEnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void Stage1BossEnterScene::SceneIN()
	{
	}
	void Stage1BossEnterScene::SceneOut()
	{
	}
}
