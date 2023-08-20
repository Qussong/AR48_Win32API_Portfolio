#include "vanHomeScene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanObject.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanFloor.h"
#include "vanSceneManager.h"
#include "vanPlayer.h"
#include "vanWitch.h"
#include "vanFoxHunter.h"
#include "vanOrge.h"
#include "vanDeathKnight.h"
#include "vanDruid.h"
#include "vanWall.h"

#define OFFSET1						400.0f
#define OFFSET2						900.0f
#define FLOOR_POS_Y					-2860.0f
#define FLOOR_UP_CONDITION			-10.0f
#define CAMERA_CONTROL_POS_X		1320.0f
#define CAMERA_OFFSET_Y				-150.0f
#define CAMERA_OFFSET_X				0.0f
#define CAMERA_OFFSET_DOUBLESPEED	5

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
		Scene::Init();

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 60.0f, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// DeathKnight
		DeathKnight* deathKnight = Object::Instantiate<DeathKnight>(enums::eLayerType::NPC);
		deathKnight->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 5 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Witch
		Witch* witch = Object::Instantiate<Witch>(enums::eLayerType::NPC);
		witch->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 4 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// FoxHunter
		FoxHunter* foxHunter = Object::Instantiate<FoxHunter>(enums::eLayerType::NPC);
		foxHunter->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 3 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Orge
		Orge* orge = Object::Instantiate<Orge>(enums::eLayerType::NPC);
		orge->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 2 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Druid
		Druid* druid = Object::Instantiate<Druid>(enums::eLayerType::NPC);
		druid->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 1 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// ī�޶� ���� offset ��
		Camera::SetCameraOffset(math::Vector2(CAMERA_OFFSET_X, CAMERA_OFFSET_Y));

		// �ش� Scene�� ī�޶� Ÿ�� ����
		SetSceneTarget(player);
	}

	void HomeScene::Update()
	{
		Scene::Update();
		NextScene();
		CameraMove();
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
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::NPC, eLayerType::Floor, true);
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

	void HomeScene::CameraMove()
	{
		math::Vector2 playerPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		float cameraPosLimit_Y = GetCameraHeightLimit().y;
		float offset_Y = fabs(cameraPosLimit_Y - playerPos.y);

		if (playerPos.x < CAMERA_CONTROL_POS_X)
		{
			Camera::SetCameraOffsetSmooth(math::Vector2(CAMERA_OFFSET_X, CAMERA_OFFSET_Y), CAMERA_OFFSET_DOUBLESPEED);
		}
		else
		{
			Camera::ClearCameraOffsetSmooth(CAMERA_OFFSET_DOUBLESPEED);
		}
	}

	void HomeScene::MakeWorld()
	{
		// BG
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Home_Scene"));					// BackGround ��ü�� texture ����
		bgsr->SetAffectCamera(true);														// ī�޶� ���� ���μ���
		// ����̹����� ũ�⸦ ������� ī�޶��� �̵����Ѱ� ���
		bg->SetAutoCameraLimit();
		// �ش� Scene�� ī�޶��� �̵����Ѱ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// [ World_Wall ]
		Texture* image = bgsr->GetTexture();
		math::Vector2 size = image->GetSize();
		// Left
		Wall* worldWall_L = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		worldWall_L->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		worldWall_L->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - size.x / 2 - 1.0f, Window_Y / 2));
		// Right
		Wall* worldWall_R = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		worldWall_R->GetComponent<Collider>()->SetSize(math::Vector2(WALL_WIDTH, size.y));
		worldWall_R->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + size.x / 2 + 1.0f, Window_Y / 2));
	}

	void HomeScene::MakeFloor()
	{
		// Floor
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(3860.0f, 50.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 565.0f, Window_Y / 2 + FLOOR_POS_Y));
	}

	void HomeScene::MakeWall()
	{
		// nothing
	}

	void HomeScene::MakeDoor()
	{
		// nothing
	}

	void HomeScene::NextScene()
	{
		math::Vector2 playerPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		if (playerPos.y > 5000.0f)
		{
			SceneManager::Next(GetName());
		}
	}
}