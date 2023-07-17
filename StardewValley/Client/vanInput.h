#pragma once
#include "CommonInclude.h"	// vector 

namespace van
{
	enum class eKeyCode		// english key code
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Up, Down, Left, Right,
		End,
	};
	enum class eKeyState	// english key state
	{
		Down,
		Up,
		Pressed,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode code;
			eKeyState state;
			bool isPressed;
		};

		static void Init();		// eKeys�� �� Key ����ü�� ��ü���� �����Ͽ� �־��ش�.
		static void Update();	// �� �����Ӹ��� Ű ���¸� Ȯ���ϰ� ������Ʈ �����ش�.

		/*
			[����������][����������][   ����	]
			|	 x	   |	x	   |	none	|
			|	 x	   |	o	   |	down	|
			|	 o	   |	o	   |   pressed	|
			|	 o	   | 	x	   |	  up	|
		*/
		__forceinline static bool GetKeyDown(eKeyCode code)
		{
			return eKeys[(int)code].state == eKeyState::Down;
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return eKeys[(int)code].state == eKeyState::Up;
		}
		__forceinline static bool GetKey(eKeyCode code)
		{
			return eKeys[(int)code].state == eKeyState::Pressed;
		}
		
	private:
		static std::vector<Key> eKeys;	// english keys
	};
}