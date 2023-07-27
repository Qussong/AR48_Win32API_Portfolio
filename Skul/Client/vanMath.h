#pragma once
#include <cmath>

/*
	[ �Ǽ��� ]
	�Ǽ� Ÿ�Կ� double �� float �� �ִ�.
		- double : 8 Byte
		- float : 4 Byte
	float Ÿ������ �Ǽ� ���� ����ϰ��� �Ѵٸ� �� �ڿ� 'f'�� �ٿ���� �Ѵ�.
*/

#define PI 3.141592f

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
			// nothing
		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{
			// nothing
		}

		Vector2 operator+(const Vector2 _other)
		{
			Vector2 temp;
			temp.x = x + _other.x;
			temp.y = y + _other.y;
			return temp;
		}

		Vector2 operator -()
		{
			return Vector2(-x, -y);
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

		Vector2 operator*(const float _value)
		{
			Vector2 temp;
			temp.x = x * _value;
			temp.y = y * _value;
			return temp;
		}

		Vector2& operator +=(const Vector2 _other)
		{
			x += _other.x;
			y += _other.y;

			return *this;
		}

		Vector2& operator -=(const Vector2 _other)
		{
			x -= _other.x;
			y -= _other.y;

			return *this;
		}

		bool operator ==(const Vector2 _other)
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

		Vector2& operator *=(const float& _value)
		{
			x *= _value;
			y *= _value;

			return *this;
		}

		//bool operator!=(const Vector2 _other)
		//{
		//	if (x == _other.x && y == _other.y)
		//	{
		//		return false;
		//	}
		//	else
		//	{
		//		return true;
		//	}
		//}

		float length()
		{
			return sqrtf(x * x + y * y);	// sqrtf = ������
		}

		Vector2 normalize()
		{
			float len = length();	// 0,0�� �������� �ش� ��ǥ������ �Ÿ�
			x /= len;	// cos�� = 0
			y /= len;	// sin�� = 1

			return *this;
		}

		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

	public:
		float x;
		float y;
	};

	inline Vector2 Rotate(Vector2 _vector, float _degree)
	{
		float radian = (_degree / 180.0f) * PI;
		_vector.normalize();
		float x = cosf(radian) * _vector.x - sinf(radian) * _vector.y;
		float y = sinf(radian) * _vector.x + cosf(radian) * _vector.y;

		return Vector2(x, y);
	}

	inline float Dot(Vector2& _v1, Vector2& _v2)	// ����(��Į��)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y;
	}

	inline float Cross(Vector2 _v1, Vector2 _v2)	// ����
	{
		return _v1.x * _v2.y - _v1.y * _v2.x;
	}
}