#include "vanAnimation.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanCamera.h"
#include "vanTexture.h"
#include "vanAnimator.h"

namespace van
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		, mScale(math::Vector2::One)
		, mAffectCamera(true)
	{
	}

	Animation::~Animation()
	{
		// nothing
	}

	void Animation::init()
	{
		// nothing
	}

	void Animation::Update()
	{
		if (mbComplete)
		{
			return;
		}

		mTime += Time::GetDeltaTime();					// �������� �帧�� ���� mTime�� �ð� ����
		if (mSpriteSheet[mIndex].duration < mTime)	// mIndex�� �ش��ϴ� �̹����� �����ð��� �����ð��� ��
		{
			// �����ð� < �����ð�
			mTime = 0.0f;							// ���� �̹����� ��µ� ���̹Ƿ� mTime �ʱ�ȭ

			if (mIndex < mSpriteSheet.size() - 1)	// mIndex�� 0���� �����ϹǷ� (ũ�� - 1)���� �۴ٸ� �ε��� ����
			{
				mIndex++;
			}
			else
			{
				// mIndex�� ���� (mSpriteSheetũ�� - 1) ���� ũ�ų� ���ٴ� �ǹ�
				mbComplete = true;	// �ִϸ��̼��� ��� �Ϸ�
			}
		}
	}

	void Animation::Render(HDC _hdc)
	{
		if (mTexture == nullptr)
		{
			// �׷��� �� ������ Atlas �ؽ�ó�� nullptr �̶��
			// ������ �̹����� ���ٴ� ���̱⿡ ����ó���� ���ؼ� return
			return;
		}
		
		Sprite sprite = mSpriteSheet[mIndex];	// ���� �ε���(mIndex)�� Sprite �̹����� �����´�.

		Transform* tr = 
			mAnimator->GetOwner()->GetComponent<Transform>();	// �ش� Animation ��ü�� �����ϴ� Animator�� ���� 
																// GameObject ��ü�� �����Ͽ� Transform ���� ���´�.
		
		math::Vector2 pos = 
			tr->GetPosition() + sprite.offset;	// Transform ������ Animation �� �׷��� ��ġ�� ���´�.
												// �ش� ��ǥ���� offset(�⺻�� : 0) �� ��ŭ �̵��ϵ��� �Ѵ�.

		//Animator* ani = mAnimator;
		mTexture->Render(
			_hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, mAffectCamera
			, sprite.offset
			, mAnimator->GetScale()
			, mAnimator->GetAlpha());
	}

	// ���޹��� ���ڸ� �̿��ؼ� m_SpriteSheet�� ���� ������ ������ �־��ش�.
	// �ش� �Լ��� �ִϸ��̼��� ���� ��, �� �ٷ� �������� ã�Ƴ��� �־��ش�.
	void Animation::Create(
		const std::wstring& _name
		, Texture* _texture
		, math::Vector2 _leftTop
		, math::Vector2 _size
		, math::Vector2 _offset
		, UINT _spriteLength	// Atals �ؽ�ó���� ������ �������� ����
		, float _duration)
	{
		mTexture = _texture;

		for (size_t i = 0; i < _spriteLength; ++i)
		{
			Sprite sprite = {};

			sprite.leftTop.x = _leftTop.x + (_size.x * i);	// loop�� ����ɼ��� �̹����� x�� ���̸�ŭ ��� �����
			sprite.leftTop.y = _leftTop.y;					// �����ϰ� ����

			if (sprite.leftTop.x >= _texture->GetWidth())	// �����ٿ� ������ �̹����� ���� ���
			{
				sprite.leftTop.x = sprite.leftTop.x - _texture->GetWidth();
				sprite.leftTop.y = _leftTop.y + _size.y;
			}

			sprite.size = _size;							// �� �������� ũ��
			sprite.offset = _offset;						// �̹��� ��½� ������ �ʿ��� �ɼ°�(�ɼ�)
			sprite.duration = _duration;					// �ش� ��������Ʈ�� ȭ�鿡 ������ �ð�

			mSpriteSheet.push_back(sprite);					// Texture���� �� �����ӿ����� �ִϸ��̼� ����� ���õ� ������ 
															// Sprite�� �����Ͽ� mSpriteSheet�� ����
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}