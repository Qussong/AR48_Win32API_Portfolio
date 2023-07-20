#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�
#include "vanTime.h"		// Update���� Time ���� ����ϱ� ���� �߰�
#include "vanSceneManager.h"
#include "vanCamera.h"
#include "vanCollisionManager.h"

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd) 
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);									// WinUser.h
		mWidth = Window_X;
		mHeight = Window_Y;

		RECT rect = { 0, 0, mWidth, mHeight };					// ���� ������ ũ��(�ش� ũ�Ⱑ Ŭ���̾�Ʈ ������ ũ�Ⱑ �Ǳ� ����)
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// ���� �������� ũ�Ⱑ Ŭ���̾�Ʈ ������ �ǵ��� ũ�⸦ ����

		// rect ������ ������ ������� ������ ������ ����
		SetWindowPos(mHwnd, nullptr,
					0, 0,										// ������ ��ġ (x,y)
					rect.right - rect.left,						// ������ ũ��(����)
					rect.bottom - rect.top,						// ������ ũ��(����)
					0);											// ?
		ShowWindow(mHwnd, true);								// CreateWindow()�Լ��� ���� �Ҵ�� �޸𸮸� ȭ�鿡 ���

		mBackBuffer 
			= CreateCompatibleBitmap(mHdc, mWidth, mHeight);	// ������ �ػ� ������ ��Ʈ�� ����

		mBackHdc = CreateCompatibleDC(mHdc);					// ���� ������ ��Ʈ���� ����Ű�� DC ����

		HBITMAP defaultBitmap									// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);		// �̶� DC�� ������ �ִ� �⺻ ��Ʈ���� ��ȯ�ȴ�.
		DeleteObject(defaultBitmap);							// ��ȯ�� �⺻ ��Ʈ���� ����� ���̾��⿡ �޸� ����

		Time::Init();
		Input::Init();
		Camera::Init();
		CollisionManager::Init();
		SceneManager::Init();
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		Camera::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		/*	
			2��° ��Ʈ�ʿ� ū �簢���� �׷��ش�.
			�翷���� 1�� ���� �簢���� ���� ���� : 
			�׵θ� ���� ���̱� ������ �� ���̰� �Ϸ���
		*/

		HBRUSH newBrush = CreateSolidBrush(RGB(125, 125, 125));		// ���ο� Brush ����
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, newBrush);	// ���ο� Brush�� DC�� �־��ְ� ���� Brush�� oldBrush�� �޾��ش�.
		// �簢���� 2�� ��Ʈ�ʿ� �׸���.
		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);
		SelectObject(mBackHdc, oldBrush);							// ���ο� Brush�� ���ϴ� �۾��� �߱⿡ �ǵ�����.
		DeleteObject(newBrush);										// ���� ������� Brush�� �޸� ����

		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

		// 2�� ��Ʈ��(mBackHdc)�� 1�� ��Ʈ��(mHdc)�� �����Ѵ�.
		BitBlt(mHdc, 0, 0, mWidth, mHeight,
				mBackHdc, 0, 0, SRCCOPY);	
	}
}
