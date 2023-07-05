#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�
#include "vanTime.h"		// Update���� Time ���� ����ϱ� ���� �߰�

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		//, mWidth(0)
		//, mHeight(0)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
		, mScene(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);				// WinUser.h

		//mWidth = 1600;					// FHD_X �� ��ü
		//mHeight = 900;					// FHD_Y �� ��ü

		RECT rect = { 0,0, FHD_X, FHD_Y };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, 
					nullptr,0, 0,
					rect.right - rect.left,
					rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);

		// ������ �ػ� ������ ��Ʈ�� ����
		mBackBuffer = CreateCompatibleBitmap(mHdc, FHD_X, FHD_Y);

		// ���� ������ ��Ʈ���� ����Ű�� DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);	// �̶� DC�� ������ �ִ� �⺻ ��Ʈ���� ��ȯ�ȴ�.
		DeleteObject(defaultBitmap);						// ��ȯ�� �⺻ ��Ʈ���� ����� ���̾��⿡ �޸� ����

		Time::Init();
		Input::Init();						// Init()�Լ��� Input Ŭ������ ���� static ����⿡ ������

		mScene = new Scene();				//
		mScene->Init();						//
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
		/*
			//W,S,A,D �� ��,��,��,�� ���� ���� Ȯ���Ѵ�.
			//GetKey()�Լ��� ���ڷ� �� Ű�� �����(state)�� Ȯ���Ͽ� �ش��ϴ� ������ �����Ѵ�.
		if (Input::GetKey(eKeyCode::W))	// ��
		{
			
			//�������� �ð��� ���� ������ �����⿡ �����Ӵ� �̵��ؾ��� �Ÿ��� �־�������,
			//���� �ð� ������ ���⿡ 1�ʴ� �̵��Ÿ��� �־��ְ� �ȴ�.
			//
			//����)
			//	CPU ���ɿ� ��� ���� ������ �̵��Ÿ�
			//	= �̵��Ÿ� * ��ŸŸ�� * FPS 
			//	= �̵��Ÿ� * ��ŸŸ�� * (1 sec / ��ŸŸ��)
			//	= �̵��Ÿ� * 1 sec
			//	= ������ �̵��Ÿ� [sec]
			
			if (playerPos.y > 0)
				playerPos.y -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// ��
		{
			if (playerPos.y < mHeight - DIAMETER)
				playerPos.y += SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// ��
		{
			if (playerPos.x > 0)
				playerPos.x -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// ��
		{
			if (playerPos.x < mWidth - DIAMETER)
				playerPos.x += SPEED * Time::DeltaTime();
			else
				__noop;
		}*/
		// Ű �Է� �ޱ�_ver3 + �� ��ü�� ���� ������Ʈ
		mScene->Update();
	}

	void Application::Render()
	{
		Time::Render(mBackHdc);

		Rectangle(mBackHdc, -1, -1, FHD_X + 1, FHD_Y + 1);			// 2��° ��Ʈ�ʿ� ū �簢���� �׷��ش�.
																	// �翷���� 1�� ���� �簢���� ���� ���� : 
																	//		�׵θ� ���� ���̱� ������ �� ���̰� �Ϸ���
		// ��ü ȭ�� ���_ver1
				/*Ellipse(mBackHdc, playerPos.x, playerPos.y,
				playerPos.x + DIAMETER, playerPos.y + DIAMETER);*/
		// �� ��ü�� ���� ȭ�� ���_ver2
		mScene->Render(mBackHdc);	

		BitBlt(mHdc, 0, 0, FHD_X, FHD_Y, mBackHdc, 0, 0, SRCCOPY);	// 2�� ��Ʈ��(mBackHdc)�� 1�� ��Ʈ��(mHdc)�� �����Ѵ�.
	}
}
