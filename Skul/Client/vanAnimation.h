#pragma once
#include "vanResource.h"

namespace van
{
	class Animator;
	class Texture;

	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			/*
				Sprite�� �Ϲ������� 'Atlas Image' ����� ������Ѵ�.
				������ �ش� �����ӿ� ����� ������ Sprite�� ������� �� �ʿ䰡 �ִ�.
				Atlas�� ���� ���� ������ �̹����� ��Ƶ� �Ŵ��� �̹��� �����̴�.
				Atlas�� �����ϴ� ������ '�޸��� ��������' �����̴�.
				�Ϲ������� ��ǻ�� �������� ���� �ӵ��� �Ʒ��� ������ ������.
					1. CPU -> �������� 
					2. �������� -> ��(Memory)
					3. �� -> �ϵ��ũ / SSD
				�̹��� ������ �о���� �۾���
				�ϵ��ũ Ȥ�� SSD�� �����ؼ� ������ �а� �̸� ��(Memory)�� �ø��� ������ �ϱ� ������ 
				Atlas�� ���� ���� ������ �̹����� ���ļ� ����ϴ� ���� ��ȣ�ȴ�.
				�� ���� ���� ������ �̹����� ���� ������ �̷���� �ִٸ� ������ �̹����� �д� �ð��� �䱸�Ǿ�
				���ʿ��ϰ� �ε忡 �ð��� ���� �Ҿ��ϰԵȴ�. 
				�̷��� '���ʿ��� �ð�' Ȥ�� '���'�� '�������'����Ѵ�.
			*/

			math::Vector2 leftTop;					// �»��
			math::Vector2 size;						// �»�ܺ��� ���ϴܱ����� ũ��
			math::Vector2 offset;					// �̹��� ��½� ������ �ʿ��� �ɼ°�(�ɼ�)
			float duration;							// �� �̹����� ȭ�� ��½� �����Ǿ�� �� �ð�(=�����ð�)

			Sprite()
				: leftTop(math::Vector2::Zero)		
				, size(math::Vector2::Zero)
				, offset(math::Vector2::Zero)
				, duration(0.0f)
			{
			}
		};

		Animation();
		//Animation(const Animation& anim);	// ���� ������
		~Animation();

		void init();
		
		void Update();

		void Render(HDC _hdc);

		// �θ� Ŭ������ Resource�� ���� �������� Load �Լ�
		__forceinline virtual HRESULT Load(const std::wstring& _path) override { return S_FALSE; };

		void Create(					// Animation�� �������ش�.
			const std::wstring& _name	// Animation �̸�
			, class Texture* _texture	// �̹���(Atlas)
			, math::Vector2 _leftTop	// �� �������� ������ �»���� ��ġ
			, math::Vector2 _size		// �� �������� ũ��
			, math::Vector2 _offset		// �̹��� ��½� ������ �ʿ��� �ɼ°�(�ɼ�)
			, UINT _spriteLength		// Atals �ؽ�ó���� ������ �������� ����
			, float _duration);			// �� �̹��� ���� �ð�

		void Reset();	// ����� ���õ� ������ ��� �ʱ�ȭ�Ѵ�.
						// ��, Animation�� ����Ǳ� ������ �ǵ�����.
		
		// Animation�� ��� �Ϸ� ���θ� ��ȯ
		__forceinline bool IsComplete() { return mbComplete; }	
		// �ڽ��� �����ϴ� �ִϸ����͸� ����
		// GameObject�� Component�� Transform�� ������ �����Ͽ� ���� ��ġ�� �˾Ƴ���
		// �̸� ���� Animation�� �׷��� ��ġ�� ������ �� �ֱ� ������ 
		// �ش� Animation�� ������ �ִ� Animator�� �������ش�.
		__forceinline void SetAnimator(Animator* _animator) { mAnimator = _animator; }	
		__forceinline void SetScale(math::Vector2 _scale) { mScale = _scale; }
		__forceinline void SetAffectCamera(bool _flag) { mbAffectCamera = _flag; }


	private:
		Animator* mAnimator;	// �ش� Animation�� �����ϴ� Animator ��ü�� ����Ų��.
		Texture* mTexture;		// �ش� Animation�� Render �� �� �����Ͽ� �׷��� Atlas �ؽ�ó
		std::vector<Sprite> mSpriteSheet;	// �� �������� ������ ���� �迭�� ����
		int mIndex;							// ���� �������� ��ȣ
		float mTime;						// ���� ���������� �ǰ� �� �� ����� �ð�
		bool mbComplete;					// �ִϸ��̼��� ��� �Ϸ� ����
		math::Vector2 mScale;				// �� ��µǴ� �ִϸ��̼��� ������ ��
		bool mbAffectCamera;				// �� ��µǴ� �ִϸ��̼��� ī�޶� ���� ����
	};
}

