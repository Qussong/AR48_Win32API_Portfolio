#pragma once
#include "CommonInclude.h"	// <windows.h>_HDC

namespace van
{
	class Time
	{
	public:
		static void Init();
		static void Update();					// ���� �������� ��Ÿ Ÿ���� ���ؼ� mDeltaTime�� ����
		static void Render(HDC hdc);
		__forceinline static float DeltaTime() { return mDeltaTime; }

	private:
		static LARGE_INTEGER mCpuFrequency;		// CPU�� ���������� ����
		static LARGE_INTEGER mPrevFrequency;	// ���α׷� ����� ������, ���� ������
		static LARGE_INTEGER mCurFrequency;		// ���� ������
		static float mDeltaTime;				// ��ŸŸ��(deltaTime) = �� �����ӿ� �ɸ� �ð� = (Cur-Prev)/Cpu 
	};
}

