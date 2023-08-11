#include "vanStage1EnterScene.h"
#include "vanTiedSkul.h"
#include "vanPlayer.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanCamera.h"
#include "vanAnimator.h"
#include "vanBackGround.h"
#include "vanCollider.h"
#include "vanCollisionManager.h"
#include "vanRigidBody.h"
#include "vanFloor.h"
#include "vanDoor.h"

#define NPC_TIEDSKUL_POS_X	-500.0f
#define FLOOR_POS_Y			260.0f
#define DOOR_POS_Y			135.0f
#define DOOR_POS_X			-210.0f

namespace van
{
	Stage1EnterScene::Stage1EnterScene()
	{
		// nothing
	}

	Stage1EnterScene::~Stage1EnterScene()
	{
		// nothing
	}

	void Stage1EnterScene::Init()
	{
		// BackGround
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Enter"));				// BackGround ��ü�� texture ����
		bgsr->SetAffectCamera(true);														// ī�޶� ���� ���μ���
		// ����̹����� ũ�⸦ ������� ī�޶��� �̵����Ѱ� ���
		bg->SetAutoCameraLimit();
		// �ش� Scene�� ī�޶��� �̵����Ѱ� ����
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));
		
		// Tied_Skul_NPC
		TiedSkul* tiedSkul = Object::Instantiate<TiedSkul>(enums::eLayerType::NPC);		
		Animator* at = tiedSkul->GetComponent<Animator>();
		tiedSkul->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + NPC_TIEDSKUL_POS_X, Window_Y / 2 + FLOOR_POS_Y));
		at->SetScale(math::Vector2(2.0f, 2.0f));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 , Window_Y / 2 + FLOOR_POS_Y));
		at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));

		// Floor
		Floor* floor = Object::Instantiate<Floor>(eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(2200.0f, 1.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_POS_Y));

		// Door
		Door* door = Object::Instantiate<Door>(eLayerType::Door);
		door->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + DOOR_POS_X, Window_Y / 2 + DOOR_POS_Y));
		at = door->GetComponent<Animator>();
		at->PlayAnimation(L"Stage1_Door_2", true);
		at->SetScale(math::Vector2(2.0f, 2.0f));

		SetSceneTarget(player);
	}

	void Stage1EnterScene::Update()
	{
		Scene::Update();
	}

	void Stage1EnterScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene ����
		const wchar_t* str = L"[ Stage1EnterScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void Stage1EnterScene::SceneIN()
	{
		// �ش� Scene������ ī�޶� �ִ� �̵� ���� �Ÿ��� ī�޶� ����
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// ī�޶� �ش� Scene�� Ÿ���� ����
		Camera::SetTarget(GetSceneTarget());

		// �ش� Scene������ �浹���� ����
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Door, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::NPC, eLayerType::Floor, true);
	}

	void Stage1EnterScene::SceneOut()
	{
		// ī�޶� Ÿ�� ���� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		// �浹���� ���� �ʱ�ȭ
		CollisionManager::Clear();
	}
}