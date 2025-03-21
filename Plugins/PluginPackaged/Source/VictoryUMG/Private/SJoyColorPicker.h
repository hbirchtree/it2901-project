/*
	By Rama for You
	
	You are welcome to use this code anywhere as long as you include this notice.
	
	copyright 2015
*/

#pragma once

//UE4 Color Picker
//		Requires public module in build.cs
//			APPFRAMEWORK 
#include "SColorPicker.h"
  
class SJoyColorPicker
	: public SColorPicker
{ 
	typedef SColorPicker Super;
	
public: //! <~~~~~
	FORCEINLINE void SetColorRGB(const FLinearColor& NewColor)
	{
		//This is protected in SColorPicker 
		//		so can't call it from UMG component
		SetNewTargetColorRGB( NewColor, true ); //Force Update
	}
	

//Animation
public:
 
	FLinearColor InstantColor;
	bool Animation_SkipToFinalForOneTick = false; 
	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override
	{ 
		//Skip to final, then resume normal animation behavior
		if(Animation_SkipToFinalForOneTick)
		{  
			Animation_SkipToFinalForOneTick = false;  
			Super::Tick(AllottedGeometry, InCurrentTime, 10000); //<~~~ because all the required vars like CurrentTime are private :)
			SetNewTargetColorRGB(InstantColor,true);
			return;
			//~~~~
		}
		
		//Animate normally!
		Super::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	}
};
