#pragma once

/*
	[ �Ǽ��� ]
	�Ǽ� Ÿ�Կ� double �� float �� �ִ�.
		- double : 8 Byte
		- float : 4 Byte
	float Ÿ������ �Ǽ� ���� ����ϰ��� �Ѵٸ� �� �ڿ� 'f'�� �ٿ���� �Ѵ�.
*/

namespace van::math
{
	struct Vector2
	{
	public:
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

	public:
		Vector2()
			: x(0.0f)
			, y(0.0f)
		{
		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{
		}
		
		Vector2 operator-(const Vector2 _other)
		{
			Vector2 temp;
			temp.x = x - _other.x;
			temp.y = y - _other.y;
			return temp;
		}

		Vector2 operator/(const float _value)
		{
			Vector2 temp;
			temp.x = x / _value;
			temp.y = y / _value;
			return temp;
		}

		Vector2 operator+(const Vector2 _other)
		{
			Vector2 temp;
			temp.x = x + _other.x;
			temp.y = y + _other.y;
			return temp;
		}

		bool operator==(const Vector2 _other)
		{
			if (x == _other.x && y == _other.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator!=(const Vector2 _other)
		{
			if (x == _other.x && y == _other.y)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	public:
		float x;
		float y;
	};
}