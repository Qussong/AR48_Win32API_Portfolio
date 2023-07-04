#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�
#include "vanTime.h"		// Update���� Time ���� ����ϱ� ���� �߰�

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, clientArea{}
		, curObjectCnt(0)
	{
		
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);			// WinUser.h

		randomize();

		Time::Init();
		Input::Init();					// Init()�Լ��� Input Ŭ������ ���� static ����⿡ ������
		GetClientRect(mHwnd, &clientArea);
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		// objs
		ObjectGenerator(300.0f, 100, 2.0f);
		for (int i = 0; i < curObjectCnt; ++i)
		{
			objectContainer.at(i).Update();
			objectContainer.at(i).setDelta(Time::DeltaTime());
		}
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
		if (Input::GetKey(eKeyCode::W))	// ��
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
			if (playerPos.y > 0)
				playerPos.y -= 300.0f * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// ��
		{
			//playerPos.y += 0.02f;
			if (playerPos.y < /*FHD_Y*/clientArea.bottom - 100)
				playerPos.y += 300.0f * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// ��
		{
			//playerPos.x -= 0.02f;
			if (playerPos.x > 0)
				playerPos.x -= 300.0f * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// ��
		{
			//playerPos.x += 0.02f;
			if (playerPos.x < /*FHD_X*/clientArea.right - 100)
				playerPos.x += 300.0f * Time::DeltaTime();
			else
				__noop;
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Ellipse(mHdc, playerPos.x, playerPos.y,
				playerPos.x + 100.0f, playerPos.y + 100.0f);

		// objs
		for (int i = 0; i < curObjectCnt; ++i)
			objectContainer.at(i).Render(mHdc);		// ���� ������ ��ü�� ȭ�� ���
	}

	void Application::ObjectGenerator(float speed, int diameter, float timeGap)
	{
		static float timeCheck = 0.0f;					// ��ŸŸ�� �״� ��
		timeCheck += Time::DeltaTime();
		int posX = random(clientArea.right - diameter);			// ��ü�� ������ ���� x��ǥ
		int posY = random(clientArea.bottom - diameter);			// ��ü�� ������ ���� y��ǥ
		int cnt = curObjectCnt;							// ���� ������ �����̴� ��ü�� ����
		int totalCnt = OBJECT_CNT;

		while (cnt < totalCnt && timeCheck >= timeGap)
		{
			Object obj = 
				Object(mHwnd, posX, posY, posX + diameter, posY + diameter);	// ���� ������ ��ü�� ũ�� ����
			obj.setDirNum2(random(DIRECTION_CNT));						// ���� ������ ��ü�� ù �̵� ���� ����
			obj.setSpeed(speed);										// ���� ������ ��ü�� �ӵ� ����
			objectContainer.push_back(obj);

			++curObjectCnt;
			timeCheck = 0.0f;
		}
	}
}
