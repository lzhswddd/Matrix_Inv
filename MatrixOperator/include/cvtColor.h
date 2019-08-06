#pragma once
#ifndef __CVTCOLOR_H__
#define __CVTCOLOR_H__

#include "MatApi.h"

namespace lzh
{
	/**
	色域转换类
	*/
	class cvtColor
	{
	public:
		/**
		按色域编码进行图像色域转换
		@param	src  输入
		@param	dst  输出
		@param	code  色域编码
		*/
		static void ConverTo(InputArray src, OutputArray dst, ColorGamut code);
		/**
		lab色域转rbg色域
		*/
		static void Lab2RGB(InputArray src, OutputArray dst);
		/**
		lab色域转bgr色域
		*/
		static void Lab2BGR(InputArray src, OutputArray dst);
		/**
		rbg色域转lab色域
		*/
		static void RGB2Lab(InputArray src, OutputArray dst);
		/**
		bgr色域转lab色域
		*/
		static void BGR2Lab(InputArray src, OutputArray dst);
		/**
		lab色域转xyz色域
		*/
		static void Lab2XYZ(InputArray src, OutputArray dst);
		/**
		xyz色域转lab色域
		*/
		static void XYZ2Lab(InputArray src, OutputArray dst);
		/**
		xyz色域转bgr色域
		*/
		static void XYZ2BGR(InputArray src, OutputArray dst);
		/**
		xyz色域转rbg色域
		*/
		static void XYZ2RGB(InputArray src, OutputArray dst);
		/**
		bgr色域转xyz色域
		*/
		static void BGR2XYZ(InputArray src, OutputArray dst);
		/**
		rgb色域转xyz色域
		*/
		static void RGB2XYZ(InputArray src, OutputArray dst);
		/**
		hsv色域转bgr色域
		*/
		static void HSV2BGR(InputArray src, OutputArray dst);
		/**
		hsv色域转rbg色域
		*/
		static void HSV2RGB(InputArray src, OutputArray dst);
		/**
		bgr色域转hsv色域
		*/
		static void BGR2HSV(InputArray src, OutputArray dst);
		/**
		rgb色域转hsv色域
		*/
		static void RGB2HSV(InputArray src, OutputArray dst);
		/**
		bgr色域转rbg色域
		*/
		static void BGR2RGB(InputArray src, OutputArray dst);
		/**
		rbg色域转bgr色域
		*/
		static void RGB2BGR(InputArray src, OutputArray dst);
		/**
		bgr色域转bgra色域
		*/
		static void BGR2BGRA(InputArray src, OutputArray dst);
		/**
		rgb色域转rgba色域
		*/
		static void RGB2RGBA(InputArray src, OutputArray dst);
		/**
		灰度转bgra色域
		*/
		static void GRAY2BGRA(InputArray src, OutputArray dst);
		/**
		灰度转bgr色域
		*/
		static void GRAY2BGR(InputArray src, OutputArray dst);
		/**
		灰度转rgba色域
		*/
		static void GRAY2RGBA(InputArray src, OutputArray dst);
		/**
		灰度转rgb色域
		*/
		static void GRAY2RGB(InputArray src, OutputArray dst);
		/**
		rgba色域转rgb色域
		*/
		static void RGBA2RGB(InputArray src, OutputArray dst);
		/**
		bgra色域转bgr色域
		*/
		static void BGRA2BGR(InputArray src, OutputArray dst);
		/**
		rgba色域转rgb色域
		*/
		static void RGBA2BGRA(InputArray src, OutputArray dst);
		/**
		bgra色域转bgr色域
		*/
		static void BGRA2RGBA(InputArray src, OutputArray dst);
		/**
		rgba色域转rgb色域
		*/
		static void RGB2BGRA(InputArray src, OutputArray dst);
		/**
		bgra色域转bgr色域
		*/
		static void BGR2RGBA(InputArray src, OutputArray dst);
		/**
		rgba色域转rgb色域
		*/
		static void RGBA2BGR(InputArray src, OutputArray dst);
		/**
		bgra色域转bgr色域
		*/
		static void BGRA2RGB(InputArray src, OutputArray dst);
		/**
		rgb色域转灰度
		*/
		static void RGB2GRAY(InputArray src, OutputArray dst);
		/**
		rgba色域转灰度
		*/
		static void RGBA2GRAY(InputArray src, OutputArray dst);
		/**
		bgr色域转灰度
		*/
		static void BGR2GRAY(InputArray src, OutputArray dst);
		/**
		bgra色域转灰度
		*/
		static void BGRA2GRAY(InputArray src, OutputArray dst);
	protected:
		static const mat_t XYZ_Xn;
		static const mat_t XYZ_Yn;
		static const mat_t XYZ_Zn;
		static const Mat xyz2rgb;
		static const Mat rgb2xyz;
	};
}

#endif //__CVTCOLOR_H__
