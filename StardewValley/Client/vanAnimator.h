#pragma once
#include "vanComponent.h"
#include "vanAnimation.h"

namespace van
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		void CreateAnimation(				//
			const std::wstring& _name		//
			, class Texture* _texture		//
			, math::Vector2 _leftTop		//
			, math::Vector2 _size			//
			, math::Vector2 _offset			//
			, UINT _spriteLength			//
			, float _duration);				//									

		/*void CreateAnimationFolder(							
			const std::wstring& _name						
			, const std::wstring& _path						
			, math::Vector2 _offset = math::Vector2::Zero	
			, float _duration = 0.1f);*/													

		Animation* FindAnimation(const std::wstring& _name);								//
		void PlayAnimation(const std::wstring& _name, bool _loop = false);					// 

		__forceinline bool GetAffectedCamera() { return mbAffectedCamera; }					//
		__forceinline void SetAffectedCamera(bool _enable) { mbAffectedCamera = _enable; }	//
		__forceinline float GetAlpha() { return mAlpha; }									//
		__forceinline void SetAlpha(float _alpha) { mAlpha = _alpha; }						//

	private:
		std::map<std::wstring, Animation*> mAnimations;		//
		Animation* mActiveAnimation;						//
		bool mbLoop;										//
		bool mbAffectedCamera;								//
		float mAlpha;										//
	};
}

