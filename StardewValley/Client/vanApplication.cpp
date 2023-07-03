#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�
#include "vanTime.h"		// Update���� Time ���� ����ϱ� ���� �߰�

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, obj{}
		, objs{}
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);										// WinUser.h

		Time::Init();
		Input::Init();												// Init()�Լ��� Input Ŭ������ ���� static ����⿡ ������

		// obj
		obj = Object(300, 300, 500, 500);							// �����̴� ��ü�� ũ�� ����
		obj.setDirNum();											// �����̴� ��ü�� ù �̵� ���� ����
		obj.setSpeed(200.0f);										// �����̴� ��ü�� �ӵ� ����

		// objs
		randomize();												// ���� ������ ���� �غ�
		for (int i = 0; i < OBJECT_CNT; ++i)
		{
			int size = (i+1) * 100;			
			objs[i] = Object(size, size, size + 100, size + 100);	// ���� ������ ��ü�� ũ�� ����
			objs[i].setDirNum2(random(DIRECTION_CNT));				// ���� ������ ��ü�� ù �̵� ���� ����
			objs[i].setSpeed(250.0f);								// ���� ������ ��ü�� �ӵ� ����
		}
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

		// obj
		obj.setDelta(Time::DeltaTime());			// ������ ��ü�� ��ŸŸ�� ����
		obj.Update();								// �� �����Ӵ� ������ ��ü�� ��ǥ ����

		// objs
		for (int i = 0; i < OBJECT_CNT; ++i)
		{
			objs[i].setDelta(Time::DeltaTime());	// ���� ������ ��ü�� ��ŸŸ�� ����
			objs[i].Update();						// �� �����Ӵ� ���� ������ ��ü�� ��ǥ ����
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Ellipse(mHdc, 100.0f + playerPos.x, 100.0f + playerPos.y
			, 200.0f + playerPos.x, 200.0f + playerPos.y);

		// obj
		obj.Render(mHdc);							// ������ ��ü�� ȭ�� ���

		// objs
		for (int i = 0; i < OBJECT_CNT; ++i)
			objs[i].Render(mHdc);					// ���� ������ ��ü�� ȭ�� ���
	}
}
