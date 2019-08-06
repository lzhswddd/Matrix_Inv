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
		UNIFORM			均匀B样条曲线
		QUASI_UNIFORM	准均匀B样条曲线
		*/
		enum BSplineType
		{
			UNIFORM = 0,
			QUASI_UNIFORM
		};

		explicit BSpline();
		BSpline(BSplineType type, int32 k = 1, IMat p = Mat());
		/**
		@brief 返回B样条曲线在t的点
		t的定义域在[0,1]
		@param t	参数方程自变量
		*/
		void setCtrlPoint(IMat p);
		/**
		注册B样条曲线节点向量
		@param node	节点向量
		缺省时按曲线类型自动生成
		*/
		void NodeVector(IMat node = Mat());
		/**
		@brief 返回B样条曲线控制点
		*/
		const Mat CtrlPoint()const;
		/**
		@brief 返回B样条曲线节点向量
		*/
		const Mat Node()const;
		/**
		@brief 返回B样条曲线点集
		@param T	参数方程自变量
		T为定义域在[0,1]的递增序列
		*/
		const Mat BPiont(IMat T)const;
		/**
		@brief 返回B样条曲线点集
		@param number	[0,1]等间隔number等分
		*/
		const Mat BPoint(int32 number)const;
		/**
		@brief 返回B样条曲线在t的点
		t的定义域在[0,1]
		@param t	参数方程自变量
		*/
		const Mat operator ()(Val t)const;
		/**
		@brief 返回B样条曲线
		点集拟合B样条曲线
		@param P	点集
		@param n	控制点数量
		@param k	k阶B样条曲线
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
