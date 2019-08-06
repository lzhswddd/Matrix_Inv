#pragma once
#ifndef __MATOPERATOR_H__
#define __MATOPERATOR_H__

#include "MatApi.h"

namespace lzh
{
	/**
	@brief 返回矩阵的行列式
	@param src	矩阵
	*/
	extern mat_t det(IMat src);
	/**
	@brief 返回矩阵的迹
	@param src	矩阵
	*/
	extern mat_t trace(IMat src);
	/**
	@brief 返回矩阵对应索引的余子式
	@param src	矩阵
	@param x	列索引
	@param y	行索引
	*/
	extern mat_t cof(IMat src, int32 x, int32 y);
	/**
	@brief 返回矩阵范数
	@param src 矩阵
	@param num 几范数
	*/
	extern mat_t Norm(IMat src, int32 num = 1);
	/**
	@brief 返回矩阵的伴随矩阵
	@param src 矩阵
	*/
	extern void adj(IMat src, OutputArray dst);
	/**
	@brief 返回矩阵的逆矩阵
	@param src 矩阵
	*/
	extern void inv(IMat src, OutputArray dst);
	/**
	@brief 返回对角线矩阵
	@param src	向量
	@param k	第k条对角线
	*/
	extern void diag(IMat src, OutputArray dst, int32 k = 0);
	/**
	@brief 返回矩阵的伪逆矩阵
	@param src	矩阵
	@param dire 伪逆矩阵的计算方式
	*/
	extern void pinv(IMat src, OutputArray dst, Dire dire = LEFT);
	/**
	@brief 返回矩阵的转置矩阵
	@param src 矩阵
	*/
	extern void tran(IMat src, OutputArray dst);
	/**
	@brief 返回矩阵num次幂
	@param src 矩阵
	@param num 次幂
	*/
	extern void POW(IMat src, OutputArray dst, int32 num);
	/**
	@brief 返回矩阵取反
	@param src 矩阵
	*/
	extern void Opp(IMat src, OutputArray dst);
	/**
	@brief 返回矩阵按行或列之和
	@param src	矩阵
	@param rc	求和的方向
	*/
	extern void Sum(IMat src, OutputArray dst, RANK rc);
	/**
	@brief 返回矩阵按元素取指数
	@param src 矩阵
	*/
	extern void Exp(IMat src, OutputArray dst);
	/**
	@brief 返回矩阵按元素取对数
	@param src 矩阵
	*/
	extern void Log(IMat src, OutputArray dst);
	/**
	@brief 返回矩阵按元素取开方
	@param src 矩阵
	*/
	extern void Sqrt(IMat src, OutputArray dst);
	/**
	@brief 返回矩阵按元素取num次幂
	@param src 矩阵
	@param num 次幂
	*/
	extern void Pow(IMat src, OutputArray dst, Val num);
	/**
	@brief 返回矩阵val/src按元素除
	@param src 矩阵
	@param val 除数
	*/
	extern void Div(IMat src, OutputArray dst, Val val, Dire dire = RIGHT);
	/**
	@brief 返回矩阵除法
	@param a	被除矩阵
	@param b	除矩阵
	@param dire 除法方式
	*/
	extern void Div(IMat a, IMat b, OutputArray dst, Dire dire = RIGHT);
	/**
	@brief 返回哈达玛积
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Mult(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回哈达玛积
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Hadamard(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回矩阵乘法
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Dot(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回差值
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Sub(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回和值
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Add(IMat a, IMat b, OutputArray dst);
	/**
	将矩阵化成简化阶梯矩阵
	@param src		输入
	@param dst		阶梯矩阵
	*/
	extern void Trapezoidal(IMat src, OutputArray dst, bool normalization = true);
	/**
	计算矩阵的行最简矩阵
	@param src		输入
	@param dst		行最简矩阵
	@rank			行秩(指针为空不做操作
	*/
	extern void RowSimplest(IMat src, OutputArray dst, int32 *rank = nullptr);
	/**
	@brief 返回列秩
	计算矩阵的列最简矩阵
	@param src		输入
	@param dst		列最简矩阵
	@rank			列秩(指针为空不做操作
	*/
	extern void ColSimplest(IMat src, OutputArray dst, int32 *rank = nullptr);
}

#endif // !__MATOPERATOR_H__


