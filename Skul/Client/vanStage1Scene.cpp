#include "vanStage1Scene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanDoor.h"

#define PLAYER_INIT_POS_X	-1200.0f
#define PLAYER_INIT_POS_Y	795.0f

#define FLOOR_B1_Y	1050.0f

#define DOOR1_POS_X	-300.0f
#define DOOR2_POS_X	300.0f
#define DOOR_POS_Y	930.0f

namespace van
{
	Stage1Scene::Stage1Scene()
	{
		// nothing
	}

	Stage1Scene::~Stage1Scene()
	{
		// nothing
	}

	void Stage1Scene::Init()
	{
		// BackGround_Tile
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Monster"));				// BackGround ��ü�� texture ����
		bgsr->SetAffectCamera(true);
		// ����̹����� ũ�⸦ ������� ī�޶��� �̵����Ѱ� ���
		bg->SetAutoCameraLimit();
		// �ش� Scene�� ī�޶��� �̵����Ѱ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));
		player->GetComponent<Animator>()->SetAffectedCamera(true);

		// -----
		
		// Floor_B1
		Floor* floorB1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floorB1->GetComponent<Collider>()->SetSize(math::Vector2(1520.0f, FLOOR_HEIGHT));
		floorB1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X/2, Window_Y / 2 + FLOOR_B1_Y));
		
		// Door_1
		Door* door1 = Object::Instantiate<Door>(eLayerType::Door);
		door1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR1_POS_X, Window_Y / 2 + DOOR_POS_Y));
		door1->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_Boss", true);;
		// Door_2
		Door* door2 = Object::Instantiate<Door>(eLayerType::Door);
		door2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR2_POS_X, Window_Y / 2 + DOOR_POS_Y));
		door2->GetComponent<Animator>()->PlayAnimation(L"Stage1_Door_Middle_Boss", true);
		
		// -----

		// Floor_1_1
		Floor* floor1_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_1->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, FLOOR_HEIGHT));
		floor1_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 -1015.0f, Window_Y / 2 + 830.0f));

		// Floor_1_2
		Floor* floor1_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1_2->GetComponent<Collider>()->SetSize(math::Vector2(490.0f, FLOOR_HEIGHT));
		floor1_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 1015.0f, Window_Y / 2 + 830.0f));

		// -----

		// Floor_2_1
		Floor* floor2_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_1->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, FLOOR_HEIGHT));
		floor2_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 470.0f, Window_Y / 2 + 610.0f));

		// Floor_2_2
		Floor* floor2_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2_2->GetComponent<Collider>()->SetSize(math::Vector2(420.0f, FLOOR_HEIGHT));
		floor2_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 470.0f, Window_Y / 2 + 610.0f));

		// -----

		// Floor_3
		Floor* floor3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Collider>()->SetSize(math::Vector2(1800.0f, FLOOR_HEIGHT));
		floor3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 320.0f));

		// -----

		// Floor_4
		Floor* floor4 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Collider>()->SetSize(math::Vector2(350.0f, FLOOR_HEIGHT));
		floor4->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + 35.0f));

		SetSceneTarget(player);
	}

	void Stage1Scene::Update()
	{
		Scene::Update();
	}

	void Stage1Scene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage1Scene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1Scene::SceneIN()
	{
		// �ش� Scene������ ī�޶� �ִ� �̵� ���� �Ÿ��� ī�޶� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶� �ش� Scene�� Ÿ���� ����
		Camera::SetTarget(GetSceneTarget());

		// �ش� Scene������ �浹���� ����
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Floor, true);

	}

	void Stage1Scene::SceneOut()
	{
		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		// �浹���� ���� �ʱ�ȭ
		CollisionManager::Clear();
	}
}