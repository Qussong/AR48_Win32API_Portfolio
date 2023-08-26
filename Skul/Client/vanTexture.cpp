#include "vanTexture.h"
#include "vanApplication.h"
#include "vanResourceManager.h"
#include "vanCamera.h"
#include "vanSceneManager.h"

extern van::Application application;

namespace van
{
	Texture::Texture()
		: mImage(nullptr)
		, mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mType(eTextureType::None)
	{
		// nothing
	}

	Texture::~Texture()
	{
		delete mImage;	// �޸� �� ����
		mImage = nullptr;

		::DeleteObject(mBitmap);
		mBitmap = NULL;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		// bmp �϶�
		if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)::LoadImageW(
							nullptr
							, path.c_str()
							, IMAGE_BITMAP
							, 0, 0
							, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return E_FAIL;	// ����� "S_FALSE" ���

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
				mType = eTextureType::AlphaBmp;

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(deafultBitmap);
		}
		else if (ext == L"png")
		{
			// [ �߸��� �� ]
			//mType = eTextureType::Png;
			//mImage = Gdiplus::Image::FromFile(path.c_str());	// *.png ������ �̿��Ͽ� Texture ��ü�� ����
			//mWidth = mImage->GetWidth();
			//mHeight = mImage->GetHeight();

			mType = eTextureType::Png;

			ULONG_PTR ptrGdi;                        //Gdi+����� ���� �����Ͱ�ü
			Gdiplus::GdiplusStartupInput inputGdi;         //gdi+�Է°���ü
			Gdiplus::GdiplusStartup(&ptrGdi, &inputGdi, 0);   //����


			// image.png ������ �̿��Ͽ� Texture ��ü�� �����մϴ�.
			mImage = Gdiplus::Image::FromFile(path.c_str());

			//���Ϸκ��� ��Ʈ�ʹޱ�
			mGdiBitMap = Gdiplus::Bitmap::FromFile(path.c_str());

			//��Ʈ�������� HBITMAP m_hBit�� ����
			mGdiBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &mBitmap);

			HDC mainDC = application.GetHdc();

			mHdc = ::CreateCompatibleDC(mainDC);

			// ��Ʈ�ʰ� DC ����
			HBITMAP hPrevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(hPrevBit);

			//assert(mImage);

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		else
			__noop;

		return S_OK;		// == 0L
	}

	Texture* Texture::Create(const std::wstring& _name, UINT _width, UINT _height)
	{
		Texture* image = ResourceManager::Find<Texture>(_name);

		if (image != nullptr)	// �ҷ��� �̹����� �ִٸ� �ش� �̹����� ��ȯ�ϰ� �Լ� ����
			return image;

		image = new Texture();
		image->SetWidth(_width);
		image->SetHeight(_height);
		HDC hdc = application.GetHdc();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, _width, _height);	// CreateCompatibleBitmap() ???
		image->SetHBitmap(bitmap);

		HDC bitmapHdc = CreateCompatibleDC(hdc);						// CreateCompatibleDC() ???
		image->SetHdc(bitmapHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHdc, bitmap);
		DeleteObject(defaultBitmap);

		image->SetName(_name);

		ResourceManager::Insert<Texture>(_name, image);

		return image;
	}

	void Texture::Render(HDC _hdc
		, math::Vector2 _pos
		, math::Vector2 _size
		, math::Vector2 _leftTop
		, math::Vector2 _rightBottom
		, bool mbAffectCamera
		, math::Vector2 _offset
		, math::Vector2 _scale
		, float _alpha)
	{
		if (mBitmap == nullptr && mImage == nullptr)
			return;

		if (mbAffectCamera)
			_pos = Camera::CalculatePosition(_pos);

		if (mType == eTextureType::Bmp)
		{
			TransparentBlt(
				// target
				_hdc
				, (int)(_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x)
				, (int)(_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y)
				, (int)(_size.x * _scale.x)
				, (int)(_size.y * _scale.y)
				// source
				, mHdc
				, (int)_leftTop.x
				, (int)_leftTop.y
				, (int)_rightBottom.x
				, (int)_rightBottom.y
				// option
				, RGB(255, 0, 255));
		}
		else if (mType == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			int alpha = 1;
			alpha = (int)(alpha * 255.0f);	// 0.0f ~ 1.0f -> 0 ~ 255

			if (alpha <= 0)
				alpha = 0;

			func.SourceConstantAlpha = alpha;

			AlphaBlend(
				// target
				_hdc
				, (int)(_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x)
				, (int)(_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y)
				, (int)(_size.x * _scale.x)
				, (int)(_size.y * _scale.y)
				// source
				, mHdc
				, (int)_leftTop.x
				, (int)_leftTop.y
				, (int)_rightBottom.x
				, (int)_rightBottom.y
				// option
				, func);
		}
		else if (mType == eTextureType::Png)
		{
			// [ �߸��� �� ]
			//Gdiplus::Graphics graphics(_hdc);
			//graphics.DrawImage(
			//	mImage
			//	, Gdiplus::Rect(
			//		(int)(_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x)
			//		, (int)(_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y)
			//		, (int)(_size.x * _scale.x)
			//		, (int)(_size.y * _scale.y))
			//	, (int)_leftTop.x
			//	, (int)_leftTop.y
			//	, (int)_rightBottom.x
			//	, (int)_rightBottom.y
			//	, Gdiplus::UnitPixel
			//	, nullptr);

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			GdiAlphaBlend(
					_hdc
					, (int)(_pos.x - (_size.x * _scale.x / 2.0f) + _offset.x)
					, (int)(_pos.y - (_size.y * _scale.y / 2.0f) + _offset.y)
					, (int)(_size.x * _scale.x)
					, (int)(_size.y * _scale.y)
					// source
					, mHdc
					, (int)_leftTop.x
					, (int)_leftTop.y
					, (int)_rightBottom.x
					, (int)_rightBottom.y
					// option
					, func);
		}
		else
		{

			__noop;
		}

		// ColliderVisible Flag ���� �������� Texture�� �߽��� ����� �����Ѵ�.
		if (SceneManager::GetColliderVisibleFlag() == true)
		{
			Rectangle(_hdc
				, (int)_pos.x
				, (int)_pos.y
				, (int)_pos.x + 10
				, (int)_pos.y + 10);
		}
		else
		{
			__noop;
		}
	}

}