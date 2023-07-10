#pragma once
#include "CommonInclude.h"
//#include "vanScene.h"

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


	private:
		HWND mHwnd;
		HDC mHdc;
		//UINT mWidth;
		//UINT mHeight;

		HDC mBackHdc;
		HBITMAP mBackBuffer;

		//math::Vector2 playerPos;	// vanMath.h
		//Scene* mScene;
	};
}

