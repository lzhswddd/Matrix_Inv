#pragma once
#ifndef __MATOPERATOR_H__
#define __MATOPERATOR_H__

#include "MatApi.h"

namespace lzh
{
	/**
	@brief ���ؾ��������ʽ
	@param src	����
	*/
	extern mat_t det(IMat src);
	/**
	@brief ���ؾ���ļ�
	@param src	����
	*/
	extern mat_t trace(IMat src);
	/**
	@brief ���ؾ����Ӧ����������ʽ
	@param src	����
	@param x	������
	@param y	������
	*/
	extern mat_t cof(IMat src, int32 x, int32 y);
	/**
	@brief ���ؾ�����
	@param src ����
	@param num ������
	*/
	extern mat_t Norm(IMat src, int32 num = 1);
	/**
	@brief ���ؾ���İ������
	@param src ����
	*/
	extern void adj(IMat src, OutputArray dst);
	/**
	@brief ���ؾ���������
	@param src ����
	*/
	extern void inv(IMat src, OutputArray dst);
	/**
	@brief ���ضԽ��߾���
	@param src	����
	@param k	��k���Խ���
	*/
	extern void diag(IMat src, OutputArray dst, int32 k = 0);
	/**
	@brief ���ؾ����α�����
	@param src	����
	@param dire α�����ļ��㷽ʽ
	*/
	extern void pinv(IMat src, OutputArray dst, Dire dire = LEFT);
	/**
	@brief ���ؾ����ת�þ���
	@param src ����
	*/
	extern void tran(IMat src, OutputArray dst);
	/**
	@brief ���ؾ���num����
	@param src ����
	@param num ����
	*/
	extern void POW(IMat src, OutputArray dst, int32 num);
	/**
	@brief ���ؾ���ȡ��
	@param src ����
	*/
	extern void Opp(IMat src, OutputArray dst);
	/**
	@brief ���ؾ����л���֮��
	@param src	����
	@param rc	��͵ķ���
	*/
	extern void Sum(IMat src, OutputArray dst, RANK rc);
	/**
	@brief ���ؾ���Ԫ��ȡָ��
	@param src ����
	*/
	extern void Exp(IMat src, OutputArray dst);
	/**
	@brief ���ؾ���Ԫ��ȡ����
	@param src ����
	*/
	extern void Log(IMat src, OutputArray dst);
	/**
	@brief ���ؾ���Ԫ��ȡ����
	@param src ����
	*/
	extern void Sqrt(IMat src, OutputArray dst);
	/**
	@brief ���ؾ���Ԫ��ȡnum����
	@param src ����
	@param num ����
	*/
	extern void Pow(IMat src, OutputArray dst, Val num);
	/**
	@brief ���ؾ���val/src��Ԫ�س�
	@param src ����
	@param val ����
	*/
	extern void Div(IMat src, OutputArray dst, Val val, Dire dire = RIGHT);
	/**
	@brief ���ؾ������
	@param a	��������
	@param b	������
	@param dire ������ʽ
	*/
	extern void Div(IMat a, IMat b, OutputArray dst, Dire dire = RIGHT);
	/**
	@brief ���ع������
	@param a ����
	@param b ����
	*/
	extern void Mult(IMat a, IMat b, OutputArray dst);
	/**
	@brief ���ع������
	@param a ����
	@param b ����
	*/
	extern void Hadamard(IMat a, IMat b, OutputArray dst);
	/**
	@brief ���ؾ���˷�
	@param a ����
	@param b ����
	*/
	extern void Dot(IMat a, IMat b, OutputArray dst);
	/**
	@brief ���ز�ֵ
	@param a ����
	@param b ����
	*/
	extern void Sub(IMat a, IMat b, OutputArray dst);
	/**
	@brief ���غ�ֵ
	@param a ����
	@param b ����
	*/
	extern void Add(IMat a, IMat b, OutputArray dst);
	/**
	�����󻯳ɼ򻯽��ݾ���
	@param src		����
	@param dst		���ݾ���
	*/
	extern void Trapezoidal(IMat src, OutputArray dst, bool normalization = true);
	/**
	����������������
	@param src		����
	@param dst		��������
	@rank			����(ָ��Ϊ�ղ�������
	*/
	extern void RowSimplest(IMat src, OutputArray dst, int32 *rank = nullptr);
	/**
	@brief ��������
	����������������
	@param src		����
	@param dst		��������
	@rank			����(ָ��Ϊ�ղ�������
	*/
	extern void ColSimplest(IMat src, OutputArray dst, int32 *rank = nullptr);
}

#endif // !__MATOPERATOR_H__


