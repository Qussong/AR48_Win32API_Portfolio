#include "vanStageScene.h"
#include "vanMonster.h"
#include "vanObject.h"
#include "vanSpriteRenderer.h"

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
	// StageScene�� �־��� ��ü ���� + �ش� ��ü�� Component ���� & �߰� (Transform ����)

	// Monster ��ü �߰�
	Monster* monster = Object::Instantiate<Monster>(enums::eLayerType::Monster);
	monster->AddComponent<SpriteRenderer>();
}

void van::StageScene::Update()
{
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
