#pragma once
#ifndef __LARGENUMBER_H__
#define __LARGENUMBER_H__

#include "Variable.h"

namespace lzh
{
	class LargeNumber : public vec_8s
	{
	public:
		LargeNumber();
		LargeNumber(int8 ch);
		LargeNumber(uint8 val);
		LargeNumber(int32 val);
		LargeNumber(int64 val);
		LargeNumber(uint32 val);
		LargeNumber(uint64 val);
		LargeNumber(const int8 *str);
		LargeNumber(std::string str);
		LargeNumber(int32 *ptr, int32 n);

		static int32 SubStract(int32 *p1, int32 *p2, int32 len1, int32 len2);
		void show()const;
		void show(std::ostream &)const;
	};
	typedef LargeNumber LargeN;

	template<typename type> void reverse(type &array_point, varray pos, varray index)
	{
		_FOR(i, 0, (index - pos) / 2 + (index - pos) % 2, 1)
			__swap(array_point[pos + i], array_point[index - i]);
	}
	template<typename type> void Reverse(type &array_point, varray pos, varray index)
	{
		reverse<type>(array_point, pos, pos + (index - pos) / 2 - 1);
		reverse<type>(array_point, pos + (index - pos) / 2, index);
		reverse<type>(array_point, pos, index);
	}

	static inline std::ostream & operator << (std::ostream &out, const LargeNumber &LN)
	{
		LN.show(out);
		return out;
	}

	extern const LargeNumber operator -(const LargeNumber& a);

	extern bool operator <(const LargeNumber& a, const LargeNumber& b);
	extern bool operator >(const LargeNumber& a, const LargeNumber& b);
	extern bool operator <=(const LargeNumber& a, const LargeNumber& b);
	extern bool operator >=(const LargeNumber& a, const LargeNumber& b);
	extern bool operator ==(const LargeNumber& a, const LargeNumber& b);

	extern void operator += (LargeNumber& a, const LargeNumber& b);
	extern void operator -= (LargeNumber& a, const LargeNumber& b);
	extern void operator *= (LargeNumber& a, const LargeNumber& b);
	extern void operator /= (LargeNumber& a, const LargeNumber& b);

	extern const LargeNumber operator +(const LargeNumber& a, const LargeNumber& b);
	extern const LargeNumber operator -(const LargeNumber& a, const LargeNumber& b);
	extern const LargeNumber operator *(const LargeNumber& a, const LargeNumber& b);
	extern const LargeNumber operator /(const LargeNumber& a, const LargeNumber& b);

}
#endif // !__LARGENUMBER_H__
