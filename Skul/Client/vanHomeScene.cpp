#include "vanHomeScene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanFloor.h"
#include "vanObject.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanPlayer.h"
#include "vanAnimator.h"

namespace van
{
	HomeScene::HomeScene()
	{
		// nothing
	}

	HomeScene::~HomeScene()
	{
		// nothing
	}

	void HomeScene::Init()
	{
		// BG
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 2880.0f));			// ��ġ�� ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Home_Scene"));					// BackGround ��ü�� texture ����
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));											// Scale ����
		bgsr->SetAffectCamera(true);														// ī�޶� ���� ���μ���
		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		Animator* at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		// Floor
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(5000.0f, 2.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 0.0f));

		SetSceneTarget(player);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void HomeScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}
	void HomeScene::SceneIN()
	{
	}
	void HomeScene::SceneOut()
	{
	}
}