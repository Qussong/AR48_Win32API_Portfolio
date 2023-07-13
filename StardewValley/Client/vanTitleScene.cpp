#include "vanTitleScene.h"
#include "vanPlayer.h"
#include "vanObject.h"
#include "vanTransform.h"
#include "vanSpriteRenderer.h"
#include "vanTexture.h"
#include "vanResourceManager.h"
#include "vanBackGround.h"
#include "vanCamera.h"

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
		//bg->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / (-2), Window_Y / (-2)));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetAffectCamera(false);
		Texture* texture = ResourceManager::Load<Texture>(L"TitleBackGroundTexture", L"..\\MyResources\\DarkMirror_Title_Art_BMP_24.bmp");	// _BMP.bmp
		bgsr->SetTexture(texture);
		//bgsr->SetScale(math::Vector2(1.0f,1.0f));
		//bgsr->SetAlpha(0.2);
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