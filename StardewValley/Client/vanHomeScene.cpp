#include "vanHomeScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"

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
		// 1) Player ��ü
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		Texture* texture = ResourceManager::Load<Texture>(L"Cat", L"..\\MyResources\\skul\\cat_1\\Walk_1_24.bmp");
		sr->SetTexture(texture);
	}

	void HomeScene::Update()
	{
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
}