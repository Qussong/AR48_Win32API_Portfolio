#include "vanStageScene.h"
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

van::StageScene::StageScene()
{
	// nothing
}

van::StageScene::~StageScene()
{
	// nothing
}

void van::StageScene::Init()
{	
	// BackGround ��ü
	BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	
	bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 0.0f));				
	SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							
	bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Sample"));						
	bgsr->SetScale(math::Vector2(1.5f, 1.5f));											
	bgsr->SetAffectCamera(true);														

	// Player
	Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
	Animator* at = player->GetComponent<Animator>();
	at->SetScale(math::Vector2(2.0f, 2.0f));
	at->SetAffectedCamera(true);

	// Carleon Recruit
	CarleonRecruit* carleon = Object::Instantiate<CarleonRecruit>(enums::eLayerType::Monster);
	at = carleon->GetComponent<Animator>();
	at->SetScale(math::Vector2(2.0f, 2.0f));
	at->SetAffectedCamera(true);

	// Floor ��ü 
	Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
	floor->GetComponent<Collider>()->SetSize(math::Vector2(2200.0f, 1.0f));
	floor->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 180.0f));

	CollisionManager::SetCollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);

	SetSceneTarget(player);	// �⺻�� nullptr�̶� ���� ����
	Camera::SetTarget(GetSceneTarget());
}

void van::StageScene::Update()
{
	Camera::SetTarget(GetSceneTarget());
	Scene::Update();
}

void van::StageScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	// Scene ����
	const wchar_t* str = L"[ StageScene ]";
	int len = (int)wcslen(str);
	Text::PrintwString(_hdc, 10, 30, str);
}
