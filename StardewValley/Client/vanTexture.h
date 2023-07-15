#pragma once
#include "vanResource.h"

namespace van
{
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};

	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;

		static Texture* Create(const std::wstring& _name, UINT _width, UINT _height);

		__forceinline UINT GetWidth() { return mWidth; }
		__forceinline void SetWidth(UINT _width) { mWidth = _width; }

		__forceinline UINT GetHeight() { return mHeight; }
		__forceinline void SetHeight(UINT _height) { mHeight = _height; }

		__forceinline HDC GetHdc() { return mHdc; }
		__forceinline void SetHdc(HDC _hdc) { mHdc = _hdc; }

		__forceinline eTextureType GetType() { return mType; }

		__forceinline Gdiplus::Image* GetImage() { return mImage; }

		__forceinline void SetHBitmap(HBITMAP _bitmap) { mBitmap = _bitmap; }

	private:
		eTextureType mType;
		Gdiplus::Image* mImage;
		/*
			Gdiplus::Image 안되aus "framework.h" 에서
			"#define WIN32_LEAN_AND_MEAN" 주석처리하기
		*/
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

