#include "vanEndingScene.h"
#include "vanGhost.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"
van::EndingScene::EndingScene()
{
	// nothing

}

van::EndingScene::~EndingScene()
{
	// nothing

}

void van::EndingScene::Init()
{
	// EndingScene�� �־��� ��ü ���� + �ش� ��ü�� Component ���� & �߰� (Transform ����)

	// Ghost ��ü �߰�
	Ghost* ghost = Object::Instantiate<Ghost>(enums::eLayerType::Monster);
	ghost->AddComponent<SpriteRenderer>();
}

void van::EndingScene::Update()
{
	Scene::Update();
}

void van::EndingScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	// Scene ����
	const wchar_t* str = L"[ EndingScene ]";
	int len = (int)wcslen(str);
	Text::PrintwString(_hdc, 10, 30, str);
}
