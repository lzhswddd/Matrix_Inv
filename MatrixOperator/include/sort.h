#pragma once
#ifndef __SORT_H__
#define __SORT_H__
#include "MatApi.h"

namespace lzh
{
	/**
		ÅÅĞòËã·¨Àà
		Ìá¹©ÁË
		Ã°ÅİÅÅĞò	=> bubble;
		²åÈëÅÅĞò	=> insert;
		Ñ¡ÔñÅÅĞò	=> select;
		ÊáÅÅĞò		=> comb;
		µØ¾«ÅÅĞò	=> gnome;
		¶ÑÅÅĞò		=> heap;
		Ï£¶ûÅÅĞò	=> shell;
		¿ìËÙÅÅĞò	=> quick;
		¹é²¢ÅÅĞò	=> merge;
		*/
	class sort
	{
	public:
		static bool compare_angle(InputArray a, InputArray b);
		static bool compare_min(InputArray a, InputArray b);
		static bool compare_max(InputArray a, InputArray b);
		template<typename _Tp> static bool comp_min(_Tp a, _Tp b);
		template<typename _Tp> static bool comp_max(_Tp a, _Tp b);
		/**
		Ã°ÅİÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void bubble(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		Ã°ÅİÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void bubble(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		²åÈëÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void insert(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		²åÈëÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void insert(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		Ñ¡ÔñÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void select(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		Ñ¡ÔñÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void select(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		ÊáÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void comb(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		ÊáÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void comb(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		µØ¾«ÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void gnome(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		µØ¾«ÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void gnome(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		¶ÑÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void heap(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		¶ÑÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void heap(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		Ï£¶ûÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void shell(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		Ï£¶ûÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void shell(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		¿ìËÙÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void quick(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		¿ìËÙÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void quick(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		/**
		¹é²¢ÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		template<typename _Tp, typename _Ptr> static void merge(_Tp begin, _Tp end, _Ptr compare = comp_min);
		/**
		@brief ·µ»ØÅÅĞò½á¹û
		¹é²¢ÅÅĞò
		@param m		ÅÅĞòÊı¾İ
		@param order	Ë³Ğò
		*/
		static void merge(InputArray src, OutputArray dst, ORDER order = MIN_TO_MAX);
		static void Register(const void*);
		static void* pre;
	protected:
		template<typename _Tp, typename _Ptr> static void heapdown(_Tp m, int32 i, int32 n, _Ptr compare = comp_min);
		template<typename _Tp, typename _Ptr> static void heapup(_Tp m, int32 i, _Ptr compare = comp_min);
		template<typename _Tp, typename _Ptr> static void makeheap(_Tp m, int32 length, _Ptr compare = comp_min);
		template<typename _Tp, typename _Ptr> static void heaparray(_Tp m, int32 i, int32 n, _Ptr compare = comp_min);
		template<typename _Tp, typename _Ptr> static void mergearray(_Tp a, _Tp b, int32 start, int32 mid, int32 end, _Ptr compare = comp_min);
		template<typename _Tp, typename _Ptr> static void _merge(_Tp a, _Tp b, int32 start, int32 end, _Ptr compare = comp_min);
		template<typename _Tp, typename _Ptr> static void _quick(_Tp m, int32 low, int32 high, _Ptr compare = comp_min);
	};


	template<typename _Tp> inline bool sort::comp_min(_Tp a, _Tp b) {
		return a > b;
	}
	template<typename _Tp> inline bool sort::comp_max(_Tp a, _Tp b)
	{
		return a < b;
	}
	template<typename _Tp, typename _Ptr> inline void sort::bubble(_Tp begin, _Tp end, _Ptr compare) {
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 i, j,
			length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0)
			for (i = 0; i < length - 1; i++)
				for (j = i + 1; j < length; j++) {
					if (compare(m[i], m[j]))
						__swap(m[i], m[j]);
				}
	}
	template<typename _Tp, typename _Ptr> inline void sort::insert(_Tp begin, _Tp end, _Ptr compare) {
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 i, j, k;
		int32 length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0)
			for (i = 0; i < length; i++)
				for (j = 0; j < i; j++) {
					if (compare(m[j], m[i]))
						for (k = i; k > j; k--)
							__swap(m[k], m[k - 1]);
				}
	}
	template<typename _Tp, typename _Ptr> inline void sort::select(_Tp begin, _Tp end, _Ptr compare)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 i, j,
			index = 0,
			length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0)
			for (i = 0; i < length - 1; index = ++i) {
				for (j = i + 1; j < length; j++) {
					if (compare(m[index], m[j]))
						index = j;
				}
				if (i != index)
					__swap(m[i], m[index]);
			}
	}
	template<typename _Tp, typename _Ptr> inline void sort::comb(_Tp begin, _Tp end, _Ptr compare)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 length = ARRAY_LEN(begin, end);
		int32 j, i, k;
		_Tp m = begin;
		if (length > 0)
			for (k = 0, i = (int32)(length / shrink_factor); i > 1 || k; i = (i > 1) ? (int32)(i / shrink_factor) : i) {
				k = 0;
				for (j = 0; j < length - i; j++) {
					if (compare(m[j], m[j + i])) {
						__swap(m[j], m[j + i]);
						k = 1;
					}
				}
			}
	}
	template<typename _Tp, typename _Ptr> inline void sort::gnome(_Tp begin, _Tp end, _Ptr compare)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 i, flag,
			length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0)
			for (i = 0; i < length&&i >= 0; flag ? i++ : i--, flag = 0) {
				if (i == 0 || compare(m[i], m[i - 1]))
					flag = 1;
				else
					__swap(m[i - 1], m[i]);
			}
	}
	template<typename _Tp, typename _Ptr> inline void sort::heap(_Tp begin, _Tp end, _Ptr compare)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 length = ARRAY_LEN(begin, end);
		if (length > 0) {
			makeheap(begin, length, compare);
			for (int32 i = length - 1; i >= 1; i--)
				heaparray(begin, 0, i, compare);
		}
	}
	template<typename _Tp, typename _Ptr> inline void sort::shell(_Tp begin, _Tp end, _Ptr compare)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 j, i, k,
			length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0)
			for (i = length >> 1; i > 0; i >>= 1)
				for (j = i; j < length; j++) {
					for (k = j - i; k >= 0 && compare(m[k], m[k + i]); k -= i)
						__swap(m[k], m[k + i]);
				}
	}
	template<typename _Tp, typename _Ptr> inline void sort::quick(_Tp begin, _Tp end, _Ptr compare)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		int32 length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0)
			_quick(m, 0, length - 1, compare);
	}
	template<typename _Tp, typename _Ptr> inline void sort::merge(_Tp begin, _Tp end, _Ptr compare) {
#ifdef MAT_DEBUG
		CHECK_PTR(begin);
		CHECK_PTR(end);
		CHECK_PTR_ORDER(begin, end);
#endif //MAT_DEBUG
		_Tp p;
		int32 length = ARRAY_LEN(begin, end);
		_Tp m = begin;
		if (length > 0) {
			p = (_Tp)malloc(length * sizeof(_Tp));
			CHECK_PTR(p);
			_merge(m, p, 0, length - 1, compare);
			free(p);
		}
	}
	template<typename _Tp, typename _Ptr> inline void sort::heapdown(_Tp m, int32 i, int32 n, _Ptr compare)
	{
		for (int32 j = 2 * i + 1; j < n; i = j, j = 2 * j + 1) {
			if (j + 1 < n && compare(m[j + 1], m[j]))
				j++;
			if (!compare(m[j], m[i]))
				break;
			__swap(m[j], m[i]);
		}
	}
	template<typename _Tp, typename _Ptr> inline void sort::heapup(_Tp m, int32 i, _Ptr compare) {
		for (int32 j = (i - 1) / 2; j >= 0 && compare(m[i], m[j]); i = j, j = (i - 1) / 2)
			__swap(m[i], m[j]);
	}
	template<typename _Tp, typename _Ptr> inline void sort::makeheap(_Tp m, int32 length, _Ptr compare) {
		for (int32 i = 0; i < length; i++)
			heapup(m, i, compare);
	}
	template<typename _Tp, typename _Ptr> inline void sort::heaparray(_Tp m, int32 i, int32 n, _Ptr compare) {
		__swap(m[i], m[n]);
		heapdown(m, i, n, compare);
	}
	template<typename _Tp, typename _Ptr> inline void sort::mergearray(_Tp a, _Tp b, int32 start, int32 mid, int32 end, _Ptr compare) {
		int32 i = start,
			j = mid + 1,
			k = 0;
		while (i <= mid && j <= end) {
			if (compare(a[j], a[i]))
				b[k++] = a[i++];
			else
				b[k++] = a[j++];
		}
		while (i <= mid)
			b[k++] = a[i++];
		while (j <= end)
			b[k++] = a[j++];
		for (i = 0; i < k; i++)
			a[start + i] = b[i];
	}
	template<typename _Tp, typename _Ptr> inline void sort::_merge(_Tp a, _Tp b, int32 start, int32 end, _Ptr compare) {
		int32 mid;
		if (start < end) {
			mid = (start + end) / 2;
			_merge(a, b, start, mid, compare);
			_merge(a, b, mid + 1, end, compare);
			mergearray(a, b, start, mid, end, compare);
		}
	}
	template<typename _Tp, typename _Ptr> inline void sort::_quick(_Tp m, int32 low, int32 high, _Ptr compare) {
		int32 start, end;
		_Tp mark;
		if (low >= high)return;
		start = low;
		end = high;
		mark = &m[start];
		while (start < end) {
			while (start < end && !compare(*mark, m[end])) {
				end -= 1;
			}
			m[start] = m[end];
			while (start < end && !compare(m[start], *mark)) {
				start += 1;
			}
			m[end] = m[start];
		}
		m[start] = *mark;
		_quick(m, low, start - 1, compare);
		_quick(m, start + 1, high, compare);
	}

}
#endif //__SORT_H__