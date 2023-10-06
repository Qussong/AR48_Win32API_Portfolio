#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"

namespace van
{
	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)
		, mbAffectedCamera(true)
		, mAlpha(1.0f)
		, mScale(math::Vector2::One)
	{
		// nothing
	}

	Animator::~Animator()
	{
		for (auto iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void Animator::Init()
	{
		// nothing
	}

	void Animator::Update()
	{
		if (mActiveAnimation)	// ����Ű�� Animation ��ü�� �ִٸ�
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && mbLoop)
			{
				mActiveAnimation->Reset();
			}
		}
		else  // ����Ű�� Animation ��ü�� ���ٸ�
		{
			return;
		}
	}

	void Animator::Render(HDC _hdc)
	{
		// ����� �ڵ�)
		//mActiveAnimation->SetAffectCamera(mbAffectedCamera);
		//if (mActiveAnimation)	// ����Ű�� Animation ��ü�� �ִٸ�
		//	mActiveAnimation->Render(_hdc);

		// �����)
		if (mActiveAnimation)	// ����Ű�� Animation ��ü�� �ִٸ�
		{
			mActiveAnimation->SetAffectCamera(mbAffectedCamera);
			mActiveAnimation->Render(_hdc);
		}
		else  // ����Ű�� Animation ��ü�� ���ٸ�
		{
			return;
		}
	}

	Animation* Animator::CreateAnimation(
				const std::wstring& _name
				, Texture* _texture
				, math::Vector2 _leftTop
				, math::Vector2 _size
				, UINT _spriteLength
				, math::Vector2 _offset
				, float _duration)
	{
		Animation* animation = nullptr;
		//animation = ResourceManager::Find<Animation>(_name);
		animation = FindAnimation(_name);

		if (animation != nullptr)
		{
			return animation;
		}

		animation = new Animation();
		animation->Create(
			_name
			, _texture
			, _leftTop
			, _size
			, _offset
			, _spriteLength
			, _duration);
		animation->SetAnimator(this);
		mAnimations.insert(std::make_pair(_name, animation));

		return animation;
	}

	void Animator::CreateAnimationFolder(
		const std::wstring& _name						// �ִϸ��̼� �̸�(Key)
		, const std::wstring& _path						// �ִϸ��̼� ���� ���
		, math::Vector2 _offset							// 
		, float _duration)								// ����ð�
	{
		UINT width = 0;									// �ʺ�
		UINT height = 0;								// ����
		UINT fileCout = 0;								// ������ ����ִ� �̹��� ���� ����

		std::filesystem::path fs(_path);				// �������
		std::vector<Texture*> images = {};				// Texture ��ü�� �����ϴ� ��

		for (auto& p :
			std::filesystem::directory_iterator(_path))	// recursive_directory_iterator
		{
			std::wstring  fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* image =
				ResourceManager::Load<Texture>(fileName, fullName);

			images.push_back(image);

			if (width < image->GetWidth())
			{
				width = image->GetWidth();
			}

			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}

			++fileCout;
		}

		Texture* spriteSheet = Texture::Create(_name, width * fileCout, height);

		eTextureType imgType = images[0]->GetType();	// 0�� �ε����� �ϴ¹�� ���� ����..?
		if (imgType == eTextureType::Bmp)
		{
			spriteSheet->SetType(eTextureType::Bmp);
		}
		if(imgType == eTextureType::AlphaBmp)
		{
			spriteSheet->SetType(eTextureType::AlphaBmp);
		}
		if (imgType == eTextureType::Png)				// �ٵ�... png �ȵǴ°ǰ�?
		{
			spriteSheet->SetType(eTextureType::Png);
			//spriteSheet->SetType(eTextureType::Bmp);
		}

		int idx = 0;
		for (Texture* image : images)
		{
			::BitBlt(											// BitBlt() ???
				// Ÿ��
				spriteSheet->GetHdc()
				, width * idx
				, 0
				, image->GetWidth() /** mScale.x*/
				, image->GetHeight() /** mScale.y*/
				// ����
				, image->GetHdc()
				, 0, 0
				// ����
				, SRCCOPY);
			idx++;
		}

		CreateAnimation(
			_name
			, spriteSheet
			, math::Vector2(0.0f, 0.0f)
			, math::Vector2(width, height)
			, fileCout
			, _offset
			, _duration);
	}

	Animation* Animator::FindAnimation(const std::wstring& _name)
	{
		auto iter = mAnimations.find(_name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& _name, bool _loop)
	{
		Animation* animation = FindAnimation(_name);
		if (animation == nullptr)
			return;

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = _loop;
	}

	void Animator::Reset()
	{
		mActiveAnimation = nullptr;
		mbLoop = false;
		mbAffectedCamera = true;
		mAlpha = 1.0f;
		mScale = math::Vector2::One;
	}
}