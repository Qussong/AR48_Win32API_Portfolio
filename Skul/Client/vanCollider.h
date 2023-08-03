#pragma once
#include "vanComponent.h"

namespace van
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* _other);	// �浹 ����
		void OnCollisionStay(Collider* _other);		// �浹���� ����
		void OnCollisionExit(Collider* _other);		// �浹���� Ż��

		__forceinline math::Vector2 GetSize() { return mSize; }
		__forceinline void SetSize(math::Vector2 _size) { mSize = _size; }

		__forceinline math::Vector2 GetOffset() { return mOffset; }
		__forceinline void SetOffset(math::Vector2 _offset) { mOffset = _offset; }

		__forceinline math::Vector2 GetPos() { return mPos; }
		__forceinline UINT GetCollisionNum() { return mCollisionNum; }

		__forceinline void SetLineColor(COLORREF _color) { lineColor = _color; }
		__forceinline void SetCollisionLineColor(COLORREF _color) { collisionLineColor = _color; }

		__forceinline BOOL GetActive() { return mbActive; }
		__forceinline void SetActive(BOOL _active) { mbActive = _active; }

	private:
		static UINT mCollisionCount;

		math::Vector2 mSize;		// �׷��� ����(�簢��)�� ũ��
		math::Vector2 mOffset;		// �׷��� ����(�簢��)�� ��ġ���� ��
		math::Vector2 mPos;			// �׷��� ������ �߽���ǥ

		UINT mCollisionNum;
		BOOL mbIsCollision;			// �浹 ���� (�浹�� true)

		COLORREF lineColor;
		COLORREF collisionLineColor;
		COLORREF inActiveLineColor;

		BOOL mbActive;				// �浹ó�� Ȱ��ȭ ����
	};
}

