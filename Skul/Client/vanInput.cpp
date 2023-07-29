#include "vanInput.h"

namespace van
{
	int hASCII[(int)eKeyCode::End] =					// hash ASCII
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,
	};

	void Input::Init()
	{
		for (int i = 0
			; i < (int)eKeyCode::End
			; ++i)
		{
			Key key = {};								// Question) �׳� Key key; �� ���θ� �ȵǴ°�?? -> ����ü�⿡ {}���� �ʱ�ȭ�Ѵ�.
			key.code = (eKeyCode)i;						// i=0 �� eKeyCode ���� 'Q'
			key.state = eKeyState::None;				// �ƹ��� �Է��� ���� ����
			key.isPressed = false;						// ������ ���� ����

			eKeys.push_back(key);
		}
	}

	/*
		[����������][����������][   ����	]
		|	 x	   |	x	   |	none	|
		|	 x	   |	o	   |	down	|
		|	 o	   |	o	   |   pressed	|
		|	 o	   | 	x	   |	  up	|
	*/
	void Input::Update()
	{
		for (int i = 0
			; i < (int)eKeyCode::End
			; ++i)
		{
			// ���� �����ӿ� i �� �ش��ϴ� Ű�� �������°�?
			if (GetAsyncKeyState(hASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� �������°�?
				if (eKeys[i].isPressed == true)
					eKeys[i].state = eKeyState::Pressed;	// ���� �����ӿ� �������� ���� �����ӿ��� ��������. = Pressed
				else
					eKeys[i].state = eKeyState::Down;		// ���� �����ӿ� �������� ���� �����ӿ��� �� ��������. = Down

				eKeys[i].isPressed = true;					// ���� �����ӿ� ���������� ǥ���صд�
			}
			else											// ���� �����ӿ� i �� �ش��ϴ� Ű�� �������� �ʾ�����
			{
				// ���� �����ӿ� �������°�?
				if (eKeys[i].isPressed == true)
					eKeys[i].state = eKeyState::Up;			// ���� �����ӿ� �� ��������, ���� �����ӿ� ��������. = Up
				else
					eKeys[i].state = eKeyState::None;		// ���� �����ӿ� �� ��������, ���� �����ӿ��� �� ��������. = None

				eKeys[i].isPressed = false;					// ���� �����ӿ� �ȴ��������� ǥ���صд�
			}
		}
	}

	bool Input::CheckGetKey()
	{
		bool upKey = GetKey(eKeyCode::Up);
		bool downKey = GetKey(eKeyCode::Down);
		bool leftKey = GetKey(eKeyCode::Left);
		bool rightKey = GetKey(eKeyCode::Right);

		bool zKey = GetKey(eKeyCode::Z);
		bool xKey = GetKey(eKeyCode::X);
		bool cKey = GetKey(eKeyCode::C);
	
		if (upKey || downKey || leftKey || rightKey ||
			zKey || xKey || cKey)
		{
			return true;
		}

		return false;
	}

	bool Input::CheckGetDirectionKey()
	{
		//bool upKey = GetKey(eKeyCode::Up);
		//bool downKey = GetKey(eKeyCode::Down);
		bool leftKey = GetKey(eKeyCode::Left);
		bool rightKey = GetKey(eKeyCode::Right);

		if (leftKey || rightKey)
		{
			return true;
		}

		return false;
	}
	
	// [ �������� namespace ]
	// public �� ���� ���� ������ ���������� ���� ������ �ϱ������� 
	// input Ŭ���� �Ҽ��̱⿡ ������ eKeys �տ� namespace �ٿ�����Ѵ�. 
	//	-> Input::eKeys
	std::vector<Input::Key> Input::eKeys = {};	
}