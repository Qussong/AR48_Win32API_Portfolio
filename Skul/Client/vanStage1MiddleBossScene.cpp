#include "vanStage1MiddleBossScene.h"
#include "vanCamera.h"

#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanObject.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanAnimator.h"
#include "vanTransform.h"
#include "vanCollider.h"
#include "vanFloor.h"
#include "vanWall.h"
#include "vanPlayer.h"
#include "vanCollisionManager.h"

#define PLAYER_INIT_POS_Y	55
#define PLAYER_INIT_POS_X	-1480

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

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + PLAYER_INIT_POS_X, Window_Y / 2 + PLAYER_INIT_POS_Y));
		player->GetComponent<Animator>()->SetAffectedCamera(true);

		// Floor
		Floor* floor_1 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 1244.0f, Window_Y / 2 + 85.0f));
		floor_1->GetComponent<Collider>()->SetSize(math::Vector2(575.0f, 2.0f));

		Floor* floor_2 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 280.0f, Window_Y / 2 + 280.0f));
		floor_2->GetComponent<Collider>()->SetSize(math::Vector2(1350.0f, 2.0f));

		Floor* floor_3 = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor_3->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 964.0f, Window_Y / 2 + 85.0f));
		floor_3->GetComponent<Collider>()->SetSize(math::Vector2(1130.0f, 2.0f));

		// Wall
		Wall* wall_1 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_1->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 954.0f, Window_Y / 2 + 180.0f));
		wall_1->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 190.0f));

		Wall* wall_2 = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		wall_2->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 395.0f, Window_Y / 2 + 180.0f));
		wall_2->GetComponent<Collider>()->SetSize(math::Vector2(2.0f, 190.0f));


		SetSceneTarget(player);
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

		// �ش� Scene������ �浹���� ����
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Wall, true);
	}

	void Stage1MiddleBossScene::SceneOut()
	{
		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		// �浹���� ���� �ʱ�ȭ
		CollisionManager::Clear();
	}
}