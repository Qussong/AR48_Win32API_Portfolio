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
#include "vanCollisionManager.h"

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
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Home_Scene"));					// BackGround ��ü�� texture ����
		bgsr->SetAffectCamera(true);														// ī�޶� ���� ���μ���
		// ����̹����� ũ�⸦ ������� ī�޶��� �̵����Ѱ� ���
		bg->SetAutoCameraLimit();
		// �ش� Scene�� ī�޶��� �̵����Ѱ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		Animator* at = player->GetComponent<Animator>();
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X - 700.0f, Window_Y - 3240.0f));
		at->SetScale(math::Vector2(2.0f, 2.0f));

		// Floor
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(3860.0f, 2.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X - 1205.0f, Window_Y - 3240.0f));

		// �ش� Scene�� ī�޶� Ÿ�� ����
		SetSceneTarget(player);
	}

	void HomeScene::Update()
	{
		Scene::Update();

		math::Vector2 targetPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		float targetPos_Y = targetPos.y;
		float cameraPosLimit_Y = GetCameraHeightLimit().y;
		float offset_Y = fabs(cameraPosLimit_Y - targetPos_Y);
		if (targetPos.x < 1320.0f)
		{
			Camera::SetCameraOffset(math::Vector2(0.0f, -offset_Y));
		}
		
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
		// �ش� Scene������ ī�޶� �ִ� �̵� ���� �Ÿ��� ī�޶� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶� �ش� Scene�� Ÿ���� ����
		Camera::SetTarget(GetSceneTarget());

		// �ش� Scene������ �浹���� ����
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
	}

	void HomeScene::SceneOut()
	{
		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		// ī�޶� offset ���� �ʱ�ȭ
		Camera::CameraOffsetClear();
		// �浹���� ���� �ʱ�ȭ
		CollisionManager::Clear();
	}
}