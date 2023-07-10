#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
#include "vanImage.h"
#include "vanResourceManager.h"

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
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		Image* image = ResourceManager::Load<Image>(L"TitleBackGroundImage", L"..\\Resources\\Image\\Fighter.bmp");
		sr->SetImage(image);

		std::wstring name = player->GetName();
	}

	void TitleScene::Update()
	{
		Scene::Update();	// �θ��� Update �Լ� ȣ��
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);								// �θ��� Render �Լ� ȣ��

		// Scene ����
		const wchar_t* str = L"[ TitleScene ]";
		Text::PrintwString(_hdc, 10, 30, str);				// �Ʒ� �θ� �������� �ʴ´�.
	}
}