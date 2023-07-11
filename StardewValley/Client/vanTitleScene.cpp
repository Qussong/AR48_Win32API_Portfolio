#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"

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


		// 1) ���ȭ�� ��ü
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		bg->SetMyType(enums::eGameObjectType::BackGround);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		Texture* texture = ResourceManager::Load<Texture>(L"TitleBackGroundTexture", L"..\\MyResources\\DarkMirror_Title_Art_BMP.bmp");
		bgsr->SetTexture(texture);
		bgsr->SetScale(math::Vector2(1.0f,1.0f));

		// 2) Player ��ü
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);	// Player ����
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();				// Player ��ü�� SpriteRenderer �Ӽ� ����
		texture = ResourceManager::Load<Texture>(L"Skul", L"..\\MyResources\\skul\\skul\\Idle_3_24.bmp");
		sr->SetTexture(texture);
	}

	void TitleScene::Update()
	{
		Scene::Update();						// �θ��� Update �Լ� ȣ��
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);					// �θ��� Render �Լ� ȣ��

		// Scene ����
		const wchar_t* str = L"[ TitleScene ]";
		Text::PrintwString(_hdc, 10, 30, str);	// �Ʒ� �θ� �������� �ʴ´�.
	}
}