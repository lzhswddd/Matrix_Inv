#pragma once
#ifndef __BSPLINE_H__
#define __BSPLINE_H__
#include "Mat.h"
namespace lzh
{
	class BSpline
	{
	public:
		/**
		UNIFORM			����B��������
		QUASI_UNIFORM	׼����B��������
		*/
		enum BSplineType
		{
			UNIFORM = 0,
			QUASI_UNIFORM
		};

		explicit BSpline();
		BSpline(BSplineType type, int32 k = 1, IMat p = Mat());
		/**
		@brief ����B����������t�ĵ�
		t�Ķ�������[0,1]
		@param t	���������Ա���
		*/
		void setCtrlPoint(IMat p);
		/**
		ע��B�������߽ڵ�����
		@param node	�ڵ�����
		ȱʡʱ�����������Զ�����
		*/
		void NodeVector(IMat node = Mat());
		/**
		@brief ����B�������߿��Ƶ�
		*/
		const Mat CtrlPoint()const;
		/**
		@brief ����B�������߽ڵ�����
		*/
		const Mat Node()const;
		/**
		@brief ����B�������ߵ㼯
		@param T	���������Ա���
		TΪ��������[0,1]�ĵ�������
		*/
		const Mat BPiont(IMat T)const;
		/**
		@brief ����B�������ߵ㼯
		@param number	[0,1]�ȼ��number�ȷ�
		*/
		const Mat BPoint(int32 number)const;
		/**
		@brief ����B����������t�ĵ�
		t�Ķ�������[0,1]
		@param t	���������Ա���
		*/
		const Mat operator ()(Val t)const;
		/**
		@brief ����B��������
		�㼯���B��������
		@param P	�㼯
		@param n	���Ƶ�����
		@param k	k��B��������
		*/
		static BSpline fit(IMat P, int32 n, int32 k);
	protected:
		mat_t BF(int32 i, int32 k, Val t)const;
		const Mat BaseFunction(Val t)const;
	private:
		int32 k;
		Mat P;
		Mat nodevector;
		BSplineType type;
	};
}
#endif // !__BSPLINE_H__
