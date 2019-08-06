#pragma once
#ifndef __CVTCOLOR_H__
#define __CVTCOLOR_H__

#include "MatApi.h"

namespace lzh
{
	/**
	ɫ��ת����
	*/
	class cvtColor
	{
	public:
		/**
		��ɫ��������ͼ��ɫ��ת��
		@param	src  ����
		@param	dst  ���
		@param	code  ɫ�����
		*/
		static void ConverTo(InputArray src, OutputArray dst, ColorGamut code);
		/**
		labɫ��תrbgɫ��
		*/
		static void Lab2RGB(InputArray src, OutputArray dst);
		/**
		labɫ��תbgrɫ��
		*/
		static void Lab2BGR(InputArray src, OutputArray dst);
		/**
		rbgɫ��תlabɫ��
		*/
		static void RGB2Lab(InputArray src, OutputArray dst);
		/**
		bgrɫ��תlabɫ��
		*/
		static void BGR2Lab(InputArray src, OutputArray dst);
		/**
		labɫ��תxyzɫ��
		*/
		static void Lab2XYZ(InputArray src, OutputArray dst);
		/**
		xyzɫ��תlabɫ��
		*/
		static void XYZ2Lab(InputArray src, OutputArray dst);
		/**
		xyzɫ��תbgrɫ��
		*/
		static void XYZ2BGR(InputArray src, OutputArray dst);
		/**
		xyzɫ��תrbgɫ��
		*/
		static void XYZ2RGB(InputArray src, OutputArray dst);
		/**
		bgrɫ��תxyzɫ��
		*/
		static void BGR2XYZ(InputArray src, OutputArray dst);
		/**
		rgbɫ��תxyzɫ��
		*/
		static void RGB2XYZ(InputArray src, OutputArray dst);
		/**
		hsvɫ��תbgrɫ��
		*/
		static void HSV2BGR(InputArray src, OutputArray dst);
		/**
		hsvɫ��תrbgɫ��
		*/
		static void HSV2RGB(InputArray src, OutputArray dst);
		/**
		bgrɫ��תhsvɫ��
		*/
		static void BGR2HSV(InputArray src, OutputArray dst);
		/**
		rgbɫ��תhsvɫ��
		*/
		static void RGB2HSV(InputArray src, OutputArray dst);
		/**
		bgrɫ��תrbgɫ��
		*/
		static void BGR2RGB(InputArray src, OutputArray dst);
		/**
		rbgɫ��תbgrɫ��
		*/
		static void RGB2BGR(InputArray src, OutputArray dst);
		/**
		bgrɫ��תbgraɫ��
		*/
		static void BGR2BGRA(InputArray src, OutputArray dst);
		/**
		rgbɫ��תrgbaɫ��
		*/
		static void RGB2RGBA(InputArray src, OutputArray dst);
		/**
		�Ҷ�תbgraɫ��
		*/
		static void GRAY2BGRA(InputArray src, OutputArray dst);
		/**
		�Ҷ�תbgrɫ��
		*/
		static void GRAY2BGR(InputArray src, OutputArray dst);
		/**
		�Ҷ�תrgbaɫ��
		*/
		static void GRAY2RGBA(InputArray src, OutputArray dst);
		/**
		�Ҷ�תrgbɫ��
		*/
		static void GRAY2RGB(InputArray src, OutputArray dst);
		/**
		rgbaɫ��תrgbɫ��
		*/
		static void RGBA2RGB(InputArray src, OutputArray dst);
		/**
		bgraɫ��תbgrɫ��
		*/
		static void BGRA2BGR(InputArray src, OutputArray dst);
		/**
		rgbaɫ��תrgbɫ��
		*/
		static void RGBA2BGRA(InputArray src, OutputArray dst);
		/**
		bgraɫ��תbgrɫ��
		*/
		static void BGRA2RGBA(InputArray src, OutputArray dst);
		/**
		rgbaɫ��תrgbɫ��
		*/
		static void RGB2BGRA(InputArray src, OutputArray dst);
		/**
		bgraɫ��תbgrɫ��
		*/
		static void BGR2RGBA(InputArray src, OutputArray dst);
		/**
		rgbaɫ��תrgbɫ��
		*/
		static void RGBA2BGR(InputArray src, OutputArray dst);
		/**
		bgraɫ��תbgrɫ��
		*/
		static void BGRA2RGB(InputArray src, OutputArray dst);
		/**
		rgbɫ��ת�Ҷ�
		*/
		static void RGB2GRAY(InputArray src, OutputArray dst);
		/**
		rgbaɫ��ת�Ҷ�
		*/
		static void RGBA2GRAY(InputArray src, OutputArray dst);
		/**
		bgrɫ��ת�Ҷ�
		*/
		static void BGR2GRAY(InputArray src, OutputArray dst);
		/**
		bgraɫ��ת�Ҷ�
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
