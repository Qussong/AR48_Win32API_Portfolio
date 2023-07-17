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
		__forceinline void SetType(eTextureType _type) { mType = _type; }

		__forceinline Gdiplus::Image* GetImage() { return mImage; }

		__forceinline void SetHBitmap(HBITMAP _bitmap) { mBitmap = _bitmap; }

	private:
		eTextureType mType;
		Gdiplus::Image* mImage;
		/*
			Gdiplus::Image �ȵ�aus "framework.h" ����
			"#define WIN32_LEAN_AND_MEAN" �ּ�ó���ϱ�
		*/
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

