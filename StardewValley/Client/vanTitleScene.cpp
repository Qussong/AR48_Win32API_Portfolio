#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"

namespace van
{
	TitleScene::TitleScene()
	{
		// nothing
	}

	TitleScene::~TitleScene()
	{
		// nothing
	}

	void TitleScene::Init()
	{
		// TitleScene�� �־��� ��ü ���� + �ش� ��ü�� Component ���� & �߰� (Transform ����)
		// Transform �� GameObject�� �⺻�����ڰ� ȣ��� �� �ڵ����� �����ȴ�.
		
		// 1) Player ��ü
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->AddComponent<SpriteRenderer>();
	}

	void TitleScene::Update()
	{
		Scene::Update();	// �θ��� Update �Լ� ȣ��
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);	// �θ��� Render �Լ� ȣ��
	}
}