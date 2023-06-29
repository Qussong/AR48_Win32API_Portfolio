#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);	// WinUser.h

		Input::Init();			// Input::eKeys�� �� Key ����ü�� ��ü���� �����Ͽ� �־��ش�.
								// Init()�Լ��� Input Ŭ������ ���� static ����⿡ ������
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		// Ű �Է� �ޱ�_ver1
		/*if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			playerPos.x -= 0.02f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			playerPos.x += 0.02f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			playerPos.y -= 0.02f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			playerPos.y += 0.02f;
		}*/
		// Ű �Է� �ޱ�_ver2
		Input::Update();	// �� �����Ӹ��� Ű ���¸� Ȯ���ϰ� ������Ʈ �����ش�.

		// W,S,A,D �� ��,��,��,�� ���� ���� Ȯ���Ѵ�.
		// GetKey()�Լ��� ���ڷ� �� Ű�� �����(state)�� Ȯ���Ͽ� �ش��ϴ� ������ �����Ѵ�.
		if (Input::GetKey(eKeyCode::W))
		{
			playerPos.y -= 0.02f;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			playerPos.x -= 0.02f;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			playerPos.y += 0.02f;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			playerPos.x += 0.02f;
		}
	}

	void Application::Render()
	{
		Ellipse(mHdc, 100 + playerPos.x, 100 + playerPos.y
			, 200 + playerPos.x, 200 + playerPos.y);
	}
}
