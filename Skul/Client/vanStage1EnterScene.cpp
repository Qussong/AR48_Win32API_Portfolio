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
		// 1) BackGround ��ü
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround ��ü ����
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, -80.0f));			// ��ġ�� ����
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer �߰�
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Stage1_Enter"));						// BackGround ��ü�� texture ����
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));											// Scale ����
		bgsr->SetAffectCamera(true);														// ī�޶� ���� ���μ���
		
		// 2) Tied_Skul_NPC
		TiedSkul* tiedSkul = Object::Instantiate<TiedSkul>(enums::eLayerType::Monster);		
		Animator* at = tiedSkul->GetComponent<Animator>();
		tiedSkul->GetComponent<Transform>()->SetPosition(math::Vector2(-500.0f, 125.0f));
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		// 3) Player ��ü
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		at = player->GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->SetAffectedCamera(true);

		// 4) Floor ��ü 
		Floor* floor = Object::Instantiate<Floor>(eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(2200.0f, 1.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(0.0f, 180.0f));

		SetSceneTarget(player);
		Camera::SetTarget(GetSceneTarget());
	}

	void Stage1EnterScene::Update()
	{
		Camera::SetTarget(GetSceneTarget());
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
}