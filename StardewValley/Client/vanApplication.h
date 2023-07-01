#pragma once
#include "CommonInclude.h"

#define OBJECT_CNT 3
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
		void Render();		// ȭ�鿡 �׷��ش�

	private:
		HWND mHwnd;
		HDC mHdc;
		math::Vector2 playerPos;	// vanMath.h

		Object obj;					// �����̴� ��ü �ϳ�
		Object objs[OBJECT_CNT];	// �����̴� ���� ��ü
	};
}

