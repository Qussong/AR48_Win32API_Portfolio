#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�
#include "vanTime.h"		// Update���� Time ���� ����ϱ� ���� �߰�

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

		Time::Init();
		Input::Init();			// Init()�Լ��� Input Ŭ������ ���� static ����⿡ ������
								
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
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
		Input::Update();

		// W,S,A,D �� ��,��,��,�� ���� ���� Ȯ���Ѵ�.
		// GetKey()�Լ��� ���ڷ� �� Ű�� �����(state)�� Ȯ���Ͽ� �ش��ϴ� ������ �����Ѵ�.
		if (Input::GetKey(eKeyCode::W))
		{
			//playerPos.y -= 0.02f;
			/*
				�������� �ð��� ���� ������ �����⿡ �����Ӵ� �̵��ؾ��� �Ÿ��� �־�������,
				���� �ð� ������ ���⿡ 1�ʴ� �̵��Ÿ��� �־��ְ� �ȴ�.

				����)
					CPU ���ɿ� ��� ���� ������ �̵��Ÿ�
					= �̵��Ÿ� * ��ŸŸ�� * FPS 
					= �̵��Ÿ� * ��ŸŸ�� * (1 sec / ��ŸŸ��)
					= �̵��Ÿ� * 1 sec
					= ������ �̵��Ÿ� [sec]
			*/
			playerPos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			//playerPos.x -= 0.02f;
			playerPos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//playerPos.y += 0.02f;
			playerPos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			//playerPos.x += 0.02f;
			playerPos.x += 300.0f * Time::DeltaTime();
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Ellipse(mHdc, 100 + playerPos.x, 100 + playerPos.y
			, 200 + playerPos.x, 200 + playerPos.y);
	}
}
