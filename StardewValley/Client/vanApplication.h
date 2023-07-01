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
		void Proc();		// ��ü���� �۾� (Update, Render)
		void Update();		// Ű �Է��� �޾� ������ ����
		void Update2();
		void Render();		// ȭ�鿡 �׷��ش�

	private:
		HWND mHwnd;
		HDC mHdc;
		math::Vector2 playerPos;	// vanMath.h
		Object obj;
	};
}

