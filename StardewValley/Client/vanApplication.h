#pragma once
#include "CommonInclude.h"

namespace van
{
	//using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();				// ��ü���� �۾� (Update, Render)
		void Update();				// Ű �Է��� �޾� ������ ����
		void Render();				// ȭ�鿡 �׷��ش�

		__forceinline HWND GetHwnd() { return mHwnd; }
		__forceinline HDC GetHdc() { return mHdc; }
		__forceinline UINT GetWidth() { return mWidth; }
		__forceinline UINT GetHeight() { return mHeight; }

	private:
		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;				// Ŭ���̾�Ʈ ���� �ʺ�
		UINT mHeight;				// Ŭ���̾�Ʈ ���� ����

		HDC mBackHdc;
		HBITMAP mBackBuffer;
	};
}