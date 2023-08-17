#include "vanTestScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanCarleonRecruit.h"
#include "vanFloor.h"
#include "vanCollider.h"
#include "vanCarleonRecruit.h"
#include "vanCollisionManager.h"
#include "vanPlayer.h"

#include "vanWall.h"
#include "vanStage1Trap.h"
#include "vanCatSeol.h"
#include "vanGold.h"
#include "vanEnt.h"
#include "vanManAtArms.h"
#include "vanSkull.h"

#define FLOOR_POS_Y			-2880.0f
#define FLOOR_UP_CONDITION	-3.0f

namespace van
{
	TestScene::TestScene()
	{
		// nothing
	}

	TestScene::~TestScene()
	{
		// nothing
	}

	void TestScene::Init()
	{	
		// BackGround 객체
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	
		SpriteRenderer* bgsr = bg->GetComponent<SpriteRenderer>();
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Test"));
		bgsr->SetAffectCamera(true);
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + 400.0f, Window_Y / 2 + FLOOR_UP_CONDITION));
		player->GetComponent<Animator>()->SetAffectedCamera(true);

		//// Wall객체
		//Wall* wall = Object::Instantiate<Wall>(enums::eLayerType::Wall);
		//wall->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 - 50.0f));
		//wall->GetComponent<Collider>()->SetSize(math::Vector2(10, 100));

		// Floor 객체 
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2));
		floor->GetComponent<Collider>()->SetSize(math::Vector2(Window_X, FLOOR_HEIGHT));
		
		//// Trap
		//Stage1Trap* trap = Object::Instantiate<Stage1Trap>(enums::eLayerType::Trap);
		//trap->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 400.0f , Window_Y / 2 - 20.0f));
		
		// Cat_Seol
		CatSeol* catSeol = Object::Instantiate<CatSeol>(enums::eLayerType::NPC);
		catSeol->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2, Window_Y / 2 + FLOOR_UP_CONDITION));
		catSeol->GetComponent<Animator>()->SetAffectedCamera(true);

		// Gold
		for (int i = 0; i < 10; ++i)
		{
			Gold* gold = Object::Instantiate<Gold>(enums::eLayerType::Drop);
			gold->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 + (i*20), Window_Y / 2 + FLOOR_UP_CONDITION - 100.0f));
			gold->GetComponent<Animator>()->SetAffectedCamera(true);
		}

		// Carleon Recruit
		CarleonRecruit* carleon = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
		carleon->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 400.0f, Window_Y / 2 + FLOOR_UP_CONDITION));
		carleon->GetComponent<Animator>()->SetAffectedCamera(true);

		// Ent
		Ent* ent = Object::Instantiate<Ent>(enums::eLayerType::Monster);
		ent->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 200.0f, Window_Y / 2 + FLOOR_UP_CONDITION));
		ent->GetComponent<Animator>()->SetAffectedCamera(true);

		//ManAtArms
		ManAtArms* man = Object::Instantiate<ManAtArms>(enums::eLayerType::Monster);
		man->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 100.0f, Window_Y / 2 + FLOOR_UP_CONDITION));
		man->GetComponent<Animator>()->SetAffectedCamera(true);

		//// Skull
		//Skull* head = Object::Instantiate<Skull>(enums::eLayerType::Player);
		//head->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 100.0f, Window_Y / 2 + FLOOR_UP_CONDITION - 100.0f));

		// 해당 씬의 (카메라)Target 설정
		SetSceneTarget(player);
	}

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ TestScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void TestScene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Trap, true);
		
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Wall, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Trap, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Trace, eLayerType::Player, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Range_Monster_Attack, eLayerType::Player, true);

		CollisionManager::SetCollisionLayerCheck(eLayerType::NPC, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::Drop, eLayerType::Floor, true);
	}

	void TestScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}
}
