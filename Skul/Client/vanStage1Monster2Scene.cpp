#include "vanStage1Monster2Scene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollisionManager.h"

#include "vanFloor.h"
#include "vanTransform.h"
#include "vanWall.h"
#include "vanPlayer.h"

// player
// floor
// wall

namespace van
{
	Stage1Monster2Scene::Stage1Monster2Scene()
	{
		// nothing
	}

	Stage1Monster2Scene::~Stage1Monster2Scene()
	{
		// nothing
	}

	void Stage1Monster2Scene::Init()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();					// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster_2"));		// BackGround ��ü�� texture ����
		bgsr->SetAffectCamera(true);
		// ����̹����� ũ�⸦ ������� ī�޶��� �̵����Ѱ� ���
		bg->SetAutoCameraLimit();
		// �ش� Scene�� ī�޶��� �̵����Ѱ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));

		// floor
		Floor* floor_B1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_B1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 511.0f, Window_Y / 2 + 565.0f));
		floor_B1_1->GetComponent<Collider>()->SetSize(math::Vector2(90.0f, 2.0f));

		Floor* floor_B1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_B1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 80.0f, Window_Y / 2 + 565.0f));
		floor_B1_2->GetComponent<Collider>()->SetSize(math::Vector2(90.0f, 2.0f));

		Floor* floor_B2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_B2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 250.0f, Window_Y / 2 + 615.0f));
		floor_B2->GetComponent<Collider>()->SetSize(math::Vector2(1040.0f, 2.0f));

		Floor* floor_1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 990.0f, Window_Y / 2 + 420.0f));
		floor_1_1->GetComponent<Collider>()->SetSize(math::Vector2(440.0f, 2.0f));

		Floor* floor_1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 318.0f, Window_Y / 2 + 420.0f));
		floor_1_2->GetComponent<Collider>()->SetSize(math::Vector2(640.0f, 2.0f));

		Floor* floor_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 +  290.0f, Window_Y / 2 + 265.0f));
		floor_2->GetComponent<Collider>()->SetSize(math::Vector2(150.0f, 2.0f));

		Floor* floor_3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 262.0f, Window_Y / 2 + 60.0f));
		floor_3->GetComponent<Collider>()->SetSize(math::Vector2(500.0f, 2.0f));

		Floor* floor_4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 695.0f, Window_Y / 2 - 100.0f));
		floor_4->GetComponent<Collider>()->SetSize(math::Vector2(1040.0f, 2.0f));
		
		// Wall
		Wall* wall_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 772.0f, Window_Y / 2 + 520.0f));
		wall_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 200.0f));

		Wall* wall_2_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 768.0f, Window_Y / 2 - 216.0f));
		wall_2_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 825.0f));

		Wall* wall_2_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 992.0f, Window_Y / 2 + 196.0f));
		wall_2_2->GetComponent<Collider>()->SetSize(math::Vector2(446.0f, 2.0f));

		Wall* wall_3_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 562.0f, Window_Y / 2 + 590.0f));
		wall_3_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_3_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 463.0f, Window_Y / 2 + 590.0f));
		wall_3_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_3_3 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 130.0f, Window_Y / 2 + 590.0f));
		wall_3_3->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_3_4 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_3_4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 32.0f, Window_Y / 2 + 590.0f));
		wall_3_4->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 46.0f));

		Wall* wall_4_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_4_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 264.0f, Window_Y / 2 + 510.0f));
		wall_4_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 204.0f));



		SetSceneTarget(player);	// �⺻�� nullptr�̶� ���� ����
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1Monster2Scene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
		Scene::Update();
	}

	void Stage1Monster2Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage1Monster2Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1Monster2Scene::SceneIN()
	{
		// �ش� Scene������ ī�޶� �ִ� �̵� ���� �Ÿ��� ī�޶� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶� �ش� Scene�� Ÿ���� ����
		Camera::SetTarget(GetSceneTarget());

		// �ش� Scene������ �浹���� ����
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
	}

	void Stage1Monster2Scene::SceneOut()
	{
		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		// �浹���� ���� �ʱ�ȭ
		CollisionManager::Clear();
	}
}