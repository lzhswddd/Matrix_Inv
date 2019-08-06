#pragma once
#ifndef _VARIABLE_H__
#define _VARIABLE_H__

#include "Variable.h"

//#define LMAT_8U		//uint8
//#define LMAT_8S		//char
//#define LMAT_32S		//int32
#define LMAT_32F		//float
//#define LMAT_64F		//double
//#define LMAT_64D		//long double

//#define MAT_LIB

//#ifdef MAT_LIB
//#define 
//#else
//#ifdef MAT_EXPORTS
//#define MAT_API __declspec(dllexport)
//#else 
//#define MAT_API __declspec(dllimport)
//#endif
//#endif

#include <vector>
#include <string>
#include <iostream>
#include <stdarg.h>
//#include <windows.h>

#include "MatType.h"

#ifdef _DEBUG
#ifndef MAT_FAST
#define MAT_DEBUG
#endif // DEBUG
#endif

#ifndef LENGTH
#define LENGTH(x) (sizeof(x)/sizeof(lzh::mat_t))
#endif
#ifndef ILength
#define ILength(x) (sizeof(x)/sizeof(lzh::int32))
#endif

#define MALLOC_ALIGN 16

#ifndef TRUE
enum
{
	TRUE = 0,
	FALSE = ~TRUE
};
#endif

#define MIN(a,b) ((a)<(b)?a:b)
#define MAX(a,b) ((a)>(b)?a:b)

#ifdef max
#undef max
template<typename _Tp> _Tp max(_Tp a, _Tp b) { return MAX(a, b); }
#endif

#ifdef min
#undef min
template<typename _Tp> _Tp min(_Tp a, _Tp b) { return MIN(a, b); }
#endif

#define _NOP do{}while(0)

#define FREE_PTR(data) do{if((data)!=nullptr) {delete (data); (data)=nullptr;}}while(0)
#define FREE_ARRAY(data) do{if((data)!=nullptr) {delete[] (data); (data)=nullptr;}}while(0)

#define ARRAY_LEN(start, end) lzh::int32(((end) - (start)))

#define _RANGE_(low, v, high) ((low)<(v)&&(v)<(high))
#define __RANGE(low, v, high) ((low)<=(v)&&(v)<(high))
#define RANGE__(low, v, high) ((low)<(v)&&(v)<=(high))
#define __RANGE__(low, v, high) ((low)<=(v)&&(v)<=(high))

#define FOR(i, range_) for(int32 i = range_.v1; i < range_.v2; i+=(int32)range_.gap)

#define FOR_RANGE_(start, end) for(lzh::int32 virtual_itereator = (start); virtual_itereator != (end); ++virtual_itereator)
#define FOR_RANGE(i, low, high) for(lzh::int32 i = (low); (i) != (high); ++(i))

#define GET_VALUE(type, v) (*(type*)(v))

#define CHECK_INDEX_IMAGE(v, limit) (MIN((MAX((v), 0)), (limit-1)))
#define FOR_IMAGE(i, img, dire) for(lzh::int32 (i) = 0; (i) < ((dire) == 1?(img).rows():((dire) == 2 ? (img).cols() : (img).channels())); ++i)

#define SHOW_ERRINFO

#define STR1(R)  #R
#define STR2(R)  STR1(R)

extern void print(int colorCode, const char *info, ...);

#ifdef SHOW_ERRINFO
#define THROW_COLOR 0x0004
#define THROW_STR "(位于函数%s中)引发的异常, 第%s行处, @异常信息:"
#define THROW_LOG print(THROW_COLOR, THROW_STR, __FUNCTION__, STR2(__LINE__))
#define THROW_STRING(str) (std::string("ERROR: (位于函数") + __FUNCTION__ + "中)引发的异常, 第" + STR2(__LINE__) + "行处, @异常信息:" + str).c_str()
#define THROW_LOG_END printf("\n")
#define THROW_INFO(info) do{THROW_LOG; print(THROW_COLOR, lzh::errinfo[info]);THROW_LOG_END;throw std::exception(THROW_STRING(lzh::errinfo[(info)]));}while(0)
#define THROW_INFO_STR(info) do{THROW_LOG; print(THROW_COLOR, info);THROW_LOG_END;throw std::exception(THROW_STRING(info));}while(0)
#define CHECK_EXCEPTION(judge, info) do{judge{_NOP;}else{print(THROW_COLOR, "ERROR: 在判断中%s程序不符合要求 @异常位置:",STR2(judge));info;}}while(0)
#else
#define THROW_COLOR 0x0004
#define THROW_STR "ERROR: (位于函数)%s中)引发的异常, @异常信息:"
#define THROW_LOG print(THROW_COLOR, THROW_STR, __FUNCTION__)
#define THROW_STRING(str) (std::string("ERROR: (位于函数") + __FUNCTION__ + "中)引发的异常, @异常信息:" + str).c_str()
#define THROW_LOG_END printf("\n")
#define THROW_INFO(info) do{throw std::exception(THROW_STRING(lzh::errinfo[(info)]));}while(0)
#define THROW_INFO_STR(info) do{throw std::exception(THROW_STRING(info));}while(0)
#define CHECK_EXCEPTION(judge, info) do{judge{_NOP;}else{info;}}while(0)
#endif

#define CHECK_MATRIX(m_) CHECK_EXCEPTION(if((m_) != nullptr), THROW_INFO(ERR_INFO_EMPTY))
#define CHECK_MATRIX_(mat) CHECK_EXCEPTION(if(!(mat).empty()), THROW_INFO(ERR_INFO_EMPTY))
#define CHECK_PTR_ORDER(start, end) CHECK_EXCEPTION(if((end) - (start) >= 0), THROW_INFO(lzh::ERR_INFO_UNLESS))
#define CHECK_PTR(s) CHECK_EXCEPTION(if((s) != nullptr), THROW_INFO(lzh::ERR_INFO_PTR))
#define CHECK_INDEX(i, len) CHECK_EXCEPTION(if((i) >= 0 && i < len), THROW_INFO(lzh::ERR_INFO_UNLESS))

#define CHECK_TYPE(_tp, v) CHECK_EXCEPTION(if((lzh::DataType<_tp>::type & lzh::KIND_SHIFT)==(v)), THROW_INFO(lzh::ERR_INFO_TYPE))
#define CHECK_TYPE_(t1, t2) CHECK_EXCEPTION(if((t1)==(t2)), THROW_INFO(lzh::ERR_INFO_TYPE))

#define MAT_GETPTR(type, data) (((type*)data))
#define MAT_INDEX(type, data ,i) ((((type*)data)) + i)
#define MAT_GETARRAY(type, data ,i) ((((type*)data))[i])
#define MAT_VALUE(_Tp, t, data ,i, out) do{ switch (t){ \
		case lzh::TP_8S:	out = (_Tp)MAT_GETARRAY(int8,		data, i); break; \
		case lzh::TP_8U:	out = (_Tp)MAT_GETARRAY(uint8,	data, i); break; \
		case lzh::TP_16S:	out = (_Tp)MAT_GETARRAY(int16,	data, i); break; \
		case lzh::TP_16U:	out = (_Tp)MAT_GETARRAY(uint16,	data, i); break; \
		case lzh::TP_32S:	out = (_Tp)MAT_GETARRAY(int32,	data, i); break; \
		case lzh::TP_32U:	out = (_Tp)MAT_GETARRAY(uint32,	data, i); break; \
		case lzh::TP_64S:	out = (_Tp)MAT_GETARRAY(int64,	data, i); break; \
		case lzh::TP_64U:	out = (_Tp)MAT_GETARRAY(uint64,	data, i); break; \
		case lzh::TP_32F:	out = (_Tp)MAT_GETARRAY(float32,	data, i); break; \
		case lzh::TP_64F:	out = (_Tp)MAT_GETARRAY(float64,	data, i); break; \
		case lzh::TP_64D:	out = (_Tp)MAT_GETARRAY(float64_, data, i); break; \
		default:THROW_INFO(ERR_INFO_TYPE);}}while(0)
#define MAT_GET(_Tp, t, data, out) do{ switch (t){ \
		case lzh::TP_8S:	out = (_Tp)*GET_VALUE(int8,		data); break; \
		case lzh::TP_8U:	out = (_Tp)*GET_VALUE(uint8,	data); break; \
		case lzh::TP_16S:	out = (_Tp)*GET_VALUE(int16,	data); break; \
		case lzh::TP_16U:	out = (_Tp)*GET_VALUE(uint16,	data); break; \
		case lzh::TP_32S:	out = (_Tp)*GET_VALUE(int32,	data); break; \
		case lzh::TP_32U:	out = (_Tp)*GET_VALUE(uint32,	data); break; \
		case lzh::TP_64S:	out = (_Tp)*GET_VALUE(int64,	data); break; \
		case lzh::TP_64U:	out = (_Tp)*GET_VALUE(uint64,	data); break; \
		case lzh::TP_32F:	out = (_Tp)*GET_VALUE(float32,	data); break; \
		case lzh::TP_64F:	out = (_Tp)*GET_VALUE(float64,	data); break; \
		case lzh::TP_64D:	out = (_Tp)*GET_VALUE(float64_, data); break; \
		default:THROW_INFO(ERR_INFO_TYPE);}}while(0)
#define COMPARE(v1, v2 ,op, out)do{switch (op) {\
		case -2:	out = ((v1) < (v2));break;\
		case -1:	out = ((v1) <= (v2));break;\
		case 0:		out = ((v1) == (v2));break;\
		case 1:		out = ((v1) >= (v2));break;\
		case 2:		out = ((v1) > (v2));break;\
		default:break;}}while(0)

#define PTR_COMPARE(p, op, i1, i2, out) \
		do{switch (op) {\
		case -2:	out = (p[i1] < p[i2]);break;\
		case -1:	out = (p[i1] <= p[i2]);break;\
		case 0:		out = (p[i1] == p[i2]);break;\
		case 1:		out = (p[i1] >= p[i2]);break;\
		case 2:		out = (p[i1] > p[i2]);break;\
		default:break;}}while(0)

#define MAT_CREATEDEPTH(v)		(((v)-1) << lzh::int32(lzh::SHIFT))
#define MAT_CREATETYPE(v)		MAT_CREATEDEPTH(v)
#define MAT_GETVALUE(v)			((v) & KIND_SHIFT)
#define MAT_GETDEPTH(v)			((((v) &~KIND_SHIFT) >> lzh::int32(SHIFT)) + 1)

#define _FOR(index,start,end,stride) for(lzh::varray index=(varray)(start);index<(varray)(end);index+=(stride))
#define FORINT(index,start,end,stride) for(lzh::int32 index=(int32)(start);(stride)<0?index>=(int32)(end):index<(int32)(end);index+=(stride))
#define toVarray(x) (lzh::varray(x))

#define MAT_SWITCH(angle, flag) (((angle)&(flag)) != 0)
#define MAT_TIMER(function) do{\
		lzh::tools::Frequency();\
		lzh::tools::StartCounter();\
		function;\
		print(0x0002, "running function %s -> cast time is %0.4f sec\n", STR2(function),lzh::tools::EndCounter() / 1000);\
		}while(0)


// exchange-add operation for atomic operations on reference counters
#if defined __INTEL_COMPILER && !(defined WIN32 || defined _WIN32)
	// atomic increment on the linux version of the Intel(tm) compiler
#  define MAT_XADD(addr, delta) (int)_InterlockedExchangeAdd(const_cast<void*>(reinterpret_cast<volatile void*>(addr)), delta)
#elif defined __GNUC__
#  if defined __clang__ && __clang_major__ >= 3 && !defined __ANDROID__ && !defined __EMSCRIPTEN__ && !defined(__CUDACC__)
#    ifdef __ATOMIC_ACQ_REL
#      define MAT_XADD(addr, delta) __c11_atomic_fetch_add((_Atomic(int)*)(addr), delta, __ATOMIC_ACQ_REL)
#    else
#      define MAT_XADD(addr, delta) __atomic_fetch_add((_Atomic(int)*)(addr), delta, 4)
#    endif
#  else
#    if defined __ATOMIC_ACQ_REL && !defined __clang__
// version for gcc >= 4.7
#      define MAT_XADD(addr, delta) (int)__atomic_fetch_add((unsigned*)(addr), (unsigned)(delta), __ATOMIC_ACQ_REL)
#    else
#      define MAT_XADD(addr, delta) (int)__sync_fetch_and_add((unsigned*)(addr), (unsigned)(delta))
#    endif
#  endif
#elif defined _MSC_VER && !defined RC_INVOKED
#  include <intrin.h>
#  define MAT_XADD(addr, delta) (int)_InterlockedExchangeAdd((long volatile*)addr, delta)
#else
static inline void MAT_XADD(int* addr, int delta) { int tmp = *addr; *addr += delta; return tmp; }
#endif

namespace lzh {
	template<typename _Tp>
	static inline _Tp *alignPtr(_Tp *data, int32 n = (int32) sizeof(_Tp)) {
		return (_Tp *)(((size_t)data + n - 1) & -n);
	}
	// 将缓冲区大小与指定的字节数对齐
	//函数返回大于或等于sz且可被n整除的最小数
	//要对齐的sz缓冲区大小
	//n对齐大小必须是2的幂
	extern size_t alignSize(size_t sz, int32 n);
	extern void *fastMalloc(size_t size);
	extern void fastFree(void *data);
	template<typename _Tp, typename _T2> inline void addList(_Tp * p, int32 &i, const _T2 & arg)
	{
		p[i++] = _Tp(arg);
	}
	template<typename _Tp, typename _T2, typename ...Types> inline void addList(_Tp * p, int32 &i, const _T2 & arg1, const Types & ...args)
	{
		p[i++] = _Tp(arg1);
		addList(p, i, args...);
	}

	class Val; template<class _Tp> class Range_
	{
	public:
		explicit Range_() : v1(0), v2(0) {}
		Range_(const _Tp& v1, const _Tp& v2, Val gap = 1) : v1(v1), v2(v2), gap(gap) {}
		int32 len()const { return (int32)((v2 - v1) / gap + 1); }
		_Tp dv()const { return v2 - v1; }
		_Tp size()const { return v1 * v2; }
		_Tp v1; _Tp v2; Val gap;
	};
	typedef Range_<int32> Range;
	template<class _Tp> class Rect_
	{
	public:
		explicit Rect_() : x(0), y(0), width(0), height(0) {}
		Rect_(_Tp x, _Tp y, _Tp width, _Tp height) : x(x), y(y), width(width), height(height) {}
		_Tp area()const { return width * height; }
		_Tp x; _Tp y; _Tp width; _Tp height;
	};
	typedef Rect_<int32> Rect;
	typedef Rect_<float32> Rectf;
	template<class _Tp> class Size_
	{
	public:
		explicit Size_() :h(0), w(0) {}
		Size_(_Tp width, _Tp height = 1) :h(height), w(width) {}
		_Tp area()const { return h * w; }
		bool operator == (Size_<_Tp> size)const { return (h == size.h && w == size.w); }
		bool operator != (Size_<_Tp> size)const { return !(*this == size); }
		operator _Tp () const { return area(); }
		_Tp h; _Tp w;
	};
	typedef Size_<int32> Size;
	template<class _Tp> class Size3_
	{
	public:
		explicit Size3_() : h(0), w(0), c(0) {}
		Size3_(_Tp w, _Tp h, _Tp c = 1) : h(h), w(w), c(c) {}
		Size3_(Size_<_Tp> size) : h(size.h), w(size.w), c(1) {}
		int32 area()const { return h * w * c; }
		bool operator == (Size3_<_Tp> size)const { return (h == size.h && w == size.w && c == size.c); }
		bool operator != (Size3_<_Tp> size)const { return !(*this == size); }
		operator _Tp () const { return area(); }
		_Tp h; _Tp w; _Tp c;
	};
	typedef Size3_<int32> Size3;
	class MatStep
	{
	public:
		explicit MatStep() { stride[0] = 1; stride[1] = 1; }
		MatStep(int32 s) { stride[0] = s; stride[1] = s; }
		MatStep(int32 s1, int32 s2) { stride[0] = s1; stride[1] = s2; }
		int32& operator [](int32 i) { return stride[i]; }
		const int32& operator [](int32 i)const { return stride[i]; }
		int32* operator ()()const { return (int32*)&stride[0]; }
		operator int32()const { return stride[0]; }
		int32 size()const { return stride[0] * stride[1]; }
		int32 stride[2];
	};
	class Complex
	{
	public:
		explicit Complex(mat_t real = 0.0, mat_t imaginary = 0.0) { r = real; i = imaginary; }
		void set(mat_t real, mat_t imaginary) { r = real; i = imaginary; }
		// 以下为三种虚数运算的定义
		Complex operator + (const Complex & o) { return Complex(r + o.r, i + o.i); }
		Complex operator - (const Complex & o) { return Complex(r - o.r, i - o.i); }
		Complex operator * (const Complex & o) { return Complex(r*o.r - i * o.i, r*o.i + i * o.r); }
		Complex operator + (mat_t val) { return Complex(r + val, i + val); }
		Complex operator - (mat_t val) { return Complex(r - val, i - val); }
		Complex operator * (mat_t val) { return Complex(r * val, i * val); }
		Complex operator / (mat_t val) { return Complex(r / val, i / val); }
		friend Complex operator + (mat_t val, Complex p) { return p + val; }
		friend Complex operator - (mat_t val, Complex p) { return Complex(val - p.r, val - p.i); }
		friend Complex operator * (mat_t val, Complex p) { return p * val; }
		friend Complex operator / (mat_t val, Complex p) { return Complex(val / p.r, val / p.i); }
		bool operator == (const Complex &o)const { return (r == o.r) && (i == o.i); }
		bool operator != (const Complex &o)const { return !((*this) == o); }
		mat_t r;
		mat_t i;
	};
	/**
	内存管理类
	*/
	template<class _Tp>
	class MatPtr
	{
	public:
		explicit MatPtr();
		MatPtr(int32 size);
		MatPtr(const MatPtr<_Tp> &m);
		MatPtr(const _Tp *p, int32 n);
		template <typename ... Types> MatPtr(int32 size, const Types & ... args);
		~MatPtr();
		void create(uint32 len);
		void addref();
		void release();
		_Tp* begin();
		const _Tp* begin()const;
		_Tp* end();
		const _Tp* end()const;
		_Tp& at(int32 i)const;
		bool operator == (void *m) const;
		bool operator != (void *m) const;
		_Tp& operator [] (int32 i) const;
		bool empty()const;
		int32 size()const;
		int32 &L();
		_Tp* &P();
		_Tp* obj()const;
		void set(const MatPtr<_Tp> &ptr);
		int32* getCount()const;
		void setCount(int32*refcount);
		MatPtr<_Tp> & operator=(const MatPtr<_Tp> & m);
		bool operator==(const MatPtr<_Tp> & m)const;
		bool operator!=(const MatPtr<_Tp> & m)const;
		operator _Tp*();
		operator const _Tp*()const;

		void set(const void* p, int32 len);
		//protected:
		int32 len;
		_Tp *data;
		void init(const _Tp* p, int32 len, const int32 *count);
	private:
		int32 *refcount = 0;
	};

	class Val_
	{
	public:
		explicit Val_() : v(0) {}
		Val_(const int8 v) : v(_T(v)) {}
		Val_(const uint8 &v) : v(_T(v)) {}
		Val_(const int16 v) : v(_T(v)) {}
		Val_(const uint16 v) : v(_T(v)) {}
		Val_(const int32 v) : v(_T(v)) {}
		Val_(const uint32 v) : v(_T(v)) {}
		Val_(const long v) : v(_T(v)) {}
		Val_(const unsigned long v) : v(_T(v)) {}
		Val_(const float32 v) : v(_T(v)) {}
		Val_(const float64 v) : v(_T(v)) {}
		Val_(const float64_ v) : v(_T(v)) {}
		Val_(const int64 v) : v(_T(v)) {}
		Val_(const uint64 v) : v(_T(v)) {}

		operator mat_t&() { return v; }
		operator const mat_t&()const { return v; }
		mat_t& operator () () { return v; }
		const mat_t& operator ()()const { return v; }
		template<typename _Tp> _Tp get()const { return (_Tp)v; }

		mat_t v;
	};
	class Val : public Val_
	{
	public:
		explicit Val();
		Val(Val_ v);
		Val(const int8 v);
		Val(const uint8 &v);
		Val(const int16 v);
		Val(const uint16 v);
		Val(const int32 v);
		Val(const uint32 v);
		Val(const int64 v);
		Val(const uint64 v);
		Val(const float32 v);
		Val(const float64 v);
		Val(const float64_ v);

		int32 type;
	};

	class Value
	{
	public:
		explicit Value();
		template<typename _Tp> Value(const _Tp & data);
		template<typename _Tp> _Tp& at(int32 idx)const;
		template<typename _Tp> _Tp* ptr(int32 idx)const;
		void* index()const;
		int32 depth()const;
		bool empty()const;
		void set(const Value &m);
		template<typename _Tp> _Tp get() const {
#ifdef MAT_DEBUG
			CHECK_PTR(data);
#endif // MAT_DEBUG
			_Tp v;
			//MAT_VALUE(_Tp, depth(), data, i, v);
			return v;
		}
		Val val() const;
		void *data;
		int32 len;
		int32 flag;
		void init(const void* data, int32 flag);
	};
	class Object
	{
	public:
		explicit Object() : pre(nullptr), copy(false) {}
		template<typename _Tp> Object(_Tp &p) : pre((void*)&p), copy(false) {}
		template<typename _Tp> Object(_Tp &&p) : pre(new _Tp(p)), copy(true) {}
		Object(const void* p) : pre((void*)p), copy(false) {}
		~Object() { if (copy) { FREE_PTR(pre); } }
		bool empty()const {
			return pre == nullptr;
		}
		template<typename _Tp> _Tp& as() {
#ifdef MAT_DEBUG
			CHECK_PTR(pre);
#endif // MAT_DEBUG
			return *(_Tp*)pre;
		}
		template<typename _Tp> const _Tp& as() const {
#ifdef MAT_DEBUG
			CHECK_PTR(pre);
#endif // MAT_DEBUG
			return *(_Tp*)pre;
		}
		void* data() { return pre; }
		const void* data()const { return pre; }
		template<typename _Tp> _Tp* ptr() {
			return pre == nullptr ? nullptr : (_Tp*)pre;
		}
		template<typename _Tp> const _Tp* ptr() const {
			return pre == nullptr ? nullptr : (const _Tp*)pre;
		}
		template<typename _Tp> operator _Tp&() {
			return as<_Tp>();
		}
		template<typename _Tp> operator const _Tp&()const {
			return as<_Tp>();
		}
		template<typename _Tp> operator _Tp*() {
			return ptr<_Tp>();
		}
		template<typename _Tp> operator const _Tp*()const {
			return ptr<_Tp>();
		}
	protected:
		void* pre;
		bool copy;
	};
	template<class _Tp>
	class Point2_
	{
	public:
		explicit Point2_();
		Point2_(_Tp x, _Tp y);
		Point2_(const _Tp *m);
		Point2_(MatPtr<_Tp> &&m);
		Point2_(const MatPtr<_Tp> & m);
		template<typename T2_>
		Point2_(const Point2_<T2_> &p);
		bool operator == (const Point2_<_Tp> &P)const;
		bool operator != (const Point2_<_Tp> &P)const;
		_Tp abs()const;
		template<typename T2_>
		static T2_ cross(const Point2_<T2_> &p1, const Point2_<T2_> &p2);
		template<typename T2_>
		static bool Clockwise(const Point2_<T2_> &p0, const Point2_<T2_> &p1, const Point2_<T2_> &p2);
		static bool xsort(const Point2_<_Tp> &p0, const Point2_<_Tp> &p1);
		static bool ysort(const Point2_<_Tp> &p0, const Point2_<_Tp> &p1);
		_Tp x;
		_Tp y;
	};

	template<class _Tp>
	class Point3_
	{
	public:
		explicit Point3_();
		Point3_(_Tp x, _Tp y, _Tp z);
		Point3_(const _Tp *m);
		Point3_(MatPtr<_Tp> &&m);
		Point3_(const MatPtr<_Tp> & m);
		template<typename T2_>
		Point3_(const Point3_<T2_> &p);
		~Point3_() {}
		bool operator == (Point3_<_Tp> &P)const;
		bool operator != (Point3_<_Tp> &P)const;
		_Tp x;
		_Tp y;
		_Tp z;
	};

	class Mat; class CvMat;
	template<class _Tp, int32 N>
	class Vec
	{
	public:
		explicit Vec();
		Vec(_Tp *v);
		Vec(const Mat & m);
		Vec(const CvMat & m);
		Vec(const MatPtr<_Tp> & m);
		template<typename T2_> Vec(const Vec<T2_, N> & m);
		template <typename ... Types> Vec(const Types & ... args);
		_Tp & at(int32 i);
		const _Tp & at(int32 i)const;
		_Tp & operator [](int32 i);
		const _Tp & operator [](int32 i)const;
		int32 size()const;
		_Tp *begin();
		const _Tp *begin() const;
		_Tp *end();
		const _Tp *end() const;
		Vec<_Tp, N> t()const;
		//Vec<_Tp, N> operator = (const Vec<_Tp, N> &vec);
		Vec<_Tp, N> operator = (int32 tab);
		template<class _T2, int32 N1> Vec<_Tp, N> operator = (const Vec<_T2, N1> &vec);

		template <typename T> void addvalue(int32 i, const T & arg);
		template <typename T, typename ... Types> void addvalue(int32 i, const T & arg1, const Types & ... args);
		_Tp data[N];
		int32 h = 1;
		int32 w = N;
	};

	template<typename _Tp> class DataType
	{
	public:
		typedef _Tp value_type;
		enum { type = NONE };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<int8>
	{
	public:
		typedef int8 value_type;
		enum { type = TP_8S };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<uint8>
	{
	public:
		typedef uint8 value_type;
		enum { type = TP_8U };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<int16>
	{
	public:
		typedef int32 value_type;
		enum { type = TP_16S };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<uint16>
	{
	public:
		typedef int32 value_type;
		enum { type = TP_16U };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<int32>
	{
	public:
		typedef int32 value_type;
		enum { type = TP_32S };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<uint32>
	{
	public:
		typedef int32 value_type;
		enum { type = TP_32S };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<float32>
	{
	public:
		typedef float32 value_type;
		enum { type = TP_32F };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<float64>
	{
	public:
		typedef float64 value_type;
		enum { type = TP_64F };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<float64_>
	{
	public:
		typedef float64_ value_type;
		enum { type = TP_64D };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<int64>
	{
	public:
		typedef float64 value_type;
		enum { type = TP_64S };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<uint64>
	{
	public:
		typedef float64_ value_type;
		enum { type = TP_64U };
		const int8 * type_name = TypeString[type];
	};
	template<> class DataType<Val_>
	{
	public:
		typedef Val_ value_type;
		enum { type = MAT_T };
		const int8 * type_name = "Val_";
	};
	template<> class DataType<Val>
	{
	public:
		typedef Val value_type;
		enum { type = MAT_T };
		const int8 * type_name = "Val";
	};
	template<> class DataType<Complex>
	{
	public:
		typedef Complex value_type;
		enum { type = MAT_CREATETYPE(2) + DataType<mat_t>::type };
		const int8 * type_name = "Complex";
	};
	template<typename _Tp> class DataType<Size_<_Tp>>
	{
	public:
		typedef Size_<_Tp> value_type;
		enum { type = MAT_CREATETYPE(2) + DataType<_Tp>::type };
		const int8 * type_name = ("Size<" + std::string(DataType<_Tp>().type_name + ">")).c_str();
	};
	template<typename _Tp> class DataType<Rect_<_Tp>>
	{
	public:
		typedef Rect_<_Tp> value_type;
		enum { type = MAT_CREATETYPE(4) + DataType<_Tp>::type };
		const int8 * type_name = ("Rect<" + std::string(DataType<_Tp>().type_name + ">")).c_str();
	};
	template<typename _Tp> class DataType<Point2_<_Tp>>
	{
	public:
		typedef Point2_<_Tp> value_type;
		enum { type = MAT_CREATETYPE(2) + DataType<_Tp>::type };
		const int8 * type_name = ("Point2<" + std::string(DataType<_Tp>().type_name + ">")).c_str();
	};
	template<typename _Tp> class DataType<Point3_<_Tp>>
	{
	public:
		typedef Point3_<_Tp> value_type;
		enum { type = MAT_CREATETYPE(3) + DataType<_Tp>::type };
		const int8 * type_name = ("Point3<" + std::string(DataType<_Tp>().type_name + ">")).c_str();
	};
	template<typename _Tp, int32 N> class DataType<Vec<_Tp, N>>
	{
	public:
		typedef Vec<_Tp, N> value_type;
		enum { type = MAT_CREATETYPE(N) + DataType<_Tp>::type };
		const int8 * type_name = ("Vec<" + std::string(DataType<_Tp>().type_name) + std::to_string(N) + ">").c_str();
	};

	//extern std::string DataTypeName(int32 flags);

	typedef Point2_<int8>		Point2c;
	typedef Point2_<uint8>		Point2b;
	typedef Point2_<int32>		Point2i;
	typedef Point2_<float32>	Point2f;
	typedef Point2_<float64>	Point2d;
	typedef Point2_<mat_t>		Point2m;
	typedef Point2_<float64_>	Point2lf;
	typedef Point2i				Point;
	typedef Point3_<int8>		Point3c;
	typedef Point3_<uint8>		Point3b;
	typedef Point3_<int32>		Point3i;
	typedef Point3_<float32>	Point3f;
	typedef Point3_<float64>	Point3d;
	typedef Point3_<mat_t>		Point3m;
	typedef Point3_<float64_>	Point3lf;
	typedef Point3i				Point3;
	typedef Vec<int8, 2>		Vec2c;
	typedef Vec<uint8, 2>		Vec2b;
	typedef Vec<int32, 2>		Vec2i;
	typedef Vec<float32, 2>		Vec2f;
	typedef Vec<float64, 2>		Vec2d;
	typedef Vec<mat_t, 2>		Vec2m;
	typedef Vec<float64_, 2>	Vec2ld;
	typedef Vec<int8, 3>		Vec3c;
	typedef Vec<uint8, 3>		Vec3b;
	typedef Vec<int32, 3>		Vec3i;
	typedef Vec<float32, 3>		Vec3f;
	typedef Vec<float64, 3>		Vec3d;
	typedef Vec<mat_t, 3>		Vec3m;
	typedef Vec<float64_, 3>	Vec3ld;
	typedef Vec<int8, 4>		Vec4c;
	typedef Vec<uint8, 4>		Vec4b;
	typedef Vec<int32, 4>		Vec4i;
	typedef Vec<float32, 4>		Vec4f;
	typedef Vec<float64, 4>		Vec4d;
	typedef Vec<mat_t, 4>		Vec4m;
	typedef Vec<float64_, 4>	Vec4ld;

	class Color : public Vec4m
	{
	public:
		enum ColorTab
		{
			Amber = 0,  //琥珀色
			//AntiqueViolet,  //古紫色
			AntiqueWhite,  //古董白
			Aqua,  //浅绿色
			AquaMarine,  //海蓝宝石色
			AquaMarineBlue,  //蓝绿色
			Azure,  //天蓝色
			AliceBlue, //爱丽丝蓝
			BabyPink,  //浅粉红色
			Beige,  //米色
			Bisque,  //橘黄色
			Black,  //黑色
			BlancheDalmond,  //白杏色
			Blue,  //蓝色
			BlueViolet,  //紫罗兰色
			Brown,  //棕色
			BurlyWood,  //实木色
			CobaltBlue,  //钴蓝色\艳蓝色
			CadetBlue,  //军蓝色
			Camel,  //驼色
			CharcoalGray,  //炭灰色
			Chartreuse,  //黄绿色
			Chocolate,  //巧克力色
			CobaltVlue,  //艳蓝色
			Coral,  //珊瑚色
			CornflowerBlue,  //菊蓝色
			Cornsilk,  //米绸色
			Crimson,  //暗深红色
			Cyan,  //青色
			DarkBlue,  //暗蓝色
			DarkCyan,  //暗青色
			DarkGoldenrod,  //暗金黄色
			DarkGray,  //暗灰色
			DarkGreen,  //暗绿色
			DarkKhaki,  //暗卡其色
			DarkMagenta,  //暗洋红色
			DarkOliveGreen,  //暗橄榄绿色
			DarkOrange,  //暗桔色
			DarkOrchid,  //暗紫色
			DarkRed,  //暗红色
			DarkSalmon,  //暗肉色
			DarkSeaGreen,  //暗海蓝色
			DarkSlateBlue,  //暗灰蓝色
			DarkSlateGray,  //墨绿色
			DarkTurquoise,  //暗宝石绿
			DarkViolet,  //暗紫色
			DeepPink,  //深粉色
			DeepSkyBlue,  //深天蓝色
			DimGray,  //暗灰色
			DoderBlue,  //道奇蓝
			DodgerBlue,  //闪蓝色
			EmeraldGreen,  //艳绿色
			FireBrick,  //火砖色
			FloralWhite,  //花白色
			ForestGreen,  //森林绿
			Fuchsia,  //紫红色
			Gainsboro,  //淡灰色
			GhostWhite,  //幽灵白
			Gold,  //金黄色
			Goldenrod,  //金麒麟色
			Gray,  //灰色
			Green,  //绿色
			GreenYellow,  //黄绿色
			HoneyDew,  //蜜色
			HotPink,  //艳粉色
			IndianRed,  //印第安红
			Indigo,  //靛蓝色
			Ivory,  //象牙色
			Khaki,  //卡其色
			Lavender,  //熏衣草花的淡紫色
			LavenderBlush,  //淡紫红
			LawnGreen,  //草绿色
			Lemonchiffon,  //柠檬绸色
			LightBlue,  //浅蓝色
			LightCoral,  //浅珊瑚色
			LightCyan,  //浅青色
			LightGoldenrodYellow,  //浅金黄色
			LightGreen,  //浅绿色
			LightGrey,  //浅灰色
			LightPink,  //浅粉色
			LightSalmon,  //浅肉色
			LightSeaGreen,  //浅海蓝色
			LightSkyBlue,  //浅天蓝色
			LightSlateGray,  //浅蓝灰色
			LightSteelBlue,  //浅钢蓝色
			LightYellow,  //浅黄色
			Lilac,  //浅紫色
			Lime,  //酸橙色
			LimeGreen,  //橙绿色
			Linen,  //亚麻色
			Magenta,  //洋红色
			Maroon,  //栗色
			Mauve,  //紫红
			MediumAquamarine,  //间绿色
			MediumBlue,  //间蓝色
			MediumOrchid,  //间紫色
			MediumPurple,  //间紫色
			MediumSeaGreen,  //间海蓝色
			MediumSlateBlue,  //间暗蓝色
			MediumSpringGreen,  //间春绿色
			MediumTurquoise,  //间绿宝石色
			MediumVioletRed,  //间紫罗兰色
			MidNightBlue,  //中灰蓝色
			Mintcream,  //薄荷色
			MistyGray,  //雾灰色
			MistyRose,  //浅玫瑰色
			Moccasin,  //鹿皮色
			MossGreen, //苔绿色
			NavajoWhite,  //纳瓦白
			NavyBlue,  //藏青色\深蓝色\天蓝色
			OffWhite,  //灰白
			Oldlace,  //老花色
			Olive,  //橄榄色
			Olivedrab,  //深绿褐色
			Orange,  //橙色
			OrangeRed,  //橙红色
			Orchid,  //淡紫色
			OysterWhite,  //乳白色
			OliveGreen,  //橄榄绿
			PaleGoldenrod,  //苍麒麟色
			PaleGreen,  //苍绿色
			PaleTurquoise,  //苍绿色
			PaleVioletRed,  //苍紫罗蓝色
			Pansy,  //紫罗兰色
			Papayawhip,  //番木色
			Peachpuff,  //桃色
			Peru,  //秘鲁色
			Pink,  //粉红
			Plum,  //杨李色
			PowderBlue,  //粉蓝色
			Purple,  //紫色
			Red,  //红色
			RosyBrown,  //褐玫瑰红
			RoyalBlue,  //宝蓝色
			Rubine,  //宝石红
			SaddleBrown,  //重褐色
			Salmon,  //鲜肉色
			SalmonPink,  //橙红色
			SandyBeige,  //浅褐色
			SandyBrown,  //沙褐色
			Sapphire,  //宝石蓝
			Scarlet,  //猩红色
			SeaGreen,  //海绿色
			Seashell,  //海贝色
			Sienna,  //赭色
			Silver,  //银白色
			SkyBlue,  //天蓝色
			SlateBlue,  //石蓝色
			SlateGray,  //灰石色
			SmokyGray,  //烟灰色
			Snow,  //雪白色
			SpringGreen,  //春绿色
			SteelBlue,  //钢蓝色
			Stone,  //石色
			SnowyWhite,  //雪白色
			Tan,  //茶色
			Teal,  //水鸭色
			Thistle,  //蓟色
			Tomato,  //番茄色
			Turquoise,  //青绿色
			TurquoiseBlue,  //翠蓝色
			Violet,  //紫色
			Wheat,  //浅黄色
			White,  //白色
			SmokeWhite,  //烟白色
			WineRed,  //葡萄酒红
			Yellow,  //黄色
			YellowGreen  //黄绿色
		};
		explicit Color() : Vec4m() {}
		Color(ColorTab ColorTableIdx) : Vec4m() { *this = Tab(ColorTableIdx); }
		Color(Val_ v) : Vec4m(v) {}
		Color(Val_ v1, Val_ v2) : Vec4m(v1, v2) {}
		Color(Val_ v1, Val_ v2, Val_ v3) : Vec4m(v1, v2, v3) {}
		Color(Val_ v1, Val_ v2, Val_ v3, Val_ v4) : Vec4m(v1, v2, v3, v4) {}

		operator mat_t &() { return data[0]; }
		operator const mat_t &()const { return data[0]; }

		static Color Random();
		static Color Tab(ColorTab index);
	};


	template<class _Tp> template<typename T2_> inline Point2_<_Tp>::Point2_(const Point2_<T2_>& p) : x(_Tp(p.x)), y(_Tp(p.y)) {}
	template<class _Tp> template<typename T2_> inline T2_ Point2_<_Tp>::cross(const Point2_<T2_>& p1, const Point2_<T2_>& p2)
	{
		return p1.x *p2.y - p1.y *p2.x;
	}
	template<class _Tp> template<typename T2_> inline bool Point2_<_Tp>::Clockwise(const Point2_<T2_>& p0, const Point2_<T2_>& p1, const Point2_<T2_>& p2)
	{
		Point2_<T2_> a = p1 - p0;
		Point2_<T2_> b = p2 - p0;
		return cross(a, b) < 0;
	}
	template<class _Tp> inline bool Point2_<_Tp>::ysort(const Point2_<_Tp>& p0, const Point2_<_Tp>& p1)
	{
		if (p0.y != p1.y)
			return p0.y < p1.y;
		return p0.x < p1.x;
	}
	template<class _Tp> inline Point2_<_Tp>::Point2_() :x(), y() {}
	template<class _Tp> inline Point2_<_Tp>::Point2_(_Tp x, _Tp y) : x(x), y(y) {}
	template<class _Tp> inline Point2_<_Tp>::Point2_(const _Tp * m)
	{
		x = m[0];
		y = m[1];
	}
	template<class _Tp> inline Point2_<_Tp>::Point2_(MatPtr<_Tp> && m)
	{
		if (m.len >= 2) {
			if (DataType<_Tp>::type == m.depth()) {
				x = m.at<_Tp>(0);
				y = m.at<_Tp>(1);
			}
			else {
				x = m.get<_Tp>(0);
				y = m.get<_Tp>(1);
			}
		}
	}
	template<class _Tp> inline Point2_<_Tp>::Point2_(const MatPtr<_Tp> & m)
	{
		if (m.size() >= 2) {
			x = m[0];
			y = m[1];
		}
	}
	template<class _Tp> inline bool Point2_<_Tp>::operator==(const Point2_<_Tp>& P) const
	{
		return (x == P.x) && (y == P.y);
	}
	template<class _Tp> inline bool Point2_<_Tp>::operator!=(const Point2_<_Tp>& P) const
	{
		return !((*this) == P);
	}
	template<class _Tp> inline _Tp Point2_<_Tp>::abs() const
	{
		return sqrt(x*x + y * y);
	}
	template<class _Tp> inline bool Point2_<_Tp>::xsort(const Point2_<_Tp>& p0, const Point2_<_Tp>& p1)
	{
		if (p0.x != p1.x)
			return p0.x < p1.x;
		return p0.y < p1.y;
	}
	template<typename _Tp> inline const Point2_<_Tp> operator + (const _Tp& v, const Point2_<_Tp> &P)
	{
		return Point2_<_Tp>(P.x + v, P.y + v);
	}
	template<typename _Tp> inline const Point2_<_Tp> operator + (const Point2_<_Tp> &P1, const Point2_<_Tp>& P2)
	{
		return Point2_<_Tp>(P1.x + P2.x, P1.y + P2.y);
	}
	template<typename _Tp> inline const Point2_<_Tp> operator - (const _Tp& v, const Point2_<_Tp> &P)
	{
		return Point2_<_Tp>(v - P.x, v - P.y);
	}
	template<typename _Tp> inline const Point2_<_Tp> operator - (const Point2_<_Tp> &P1, const Point2_<_Tp>& P2)
	{
		return Point2_<_Tp>(P1.x - P2.x, P1.y - P2.y);
	}
	template<typename _Tp> inline const Point2_<_Tp> operator * (const _Tp& v, const Point2_<_Tp> &P)
	{
		return Point2_<_Tp>(P.x * v, P.y * v);
	}
	template<typename _Tp> inline const _Tp operator * (const Point2_<_Tp> &P1, const Point2_<_Tp>& P2)
	{
		return P1.x * P2.x + P1.y * P2.y;
	}

	template<class _Tp> inline Point3_<_Tp>::Point3_() :x(), y(), z() {}
	template<class _Tp> inline Point3_<_Tp>::Point3_(_Tp x, _Tp y, _Tp z) : x(x), y(y), z(z) {}
	template<class _Tp> inline Point3_<_Tp>::Point3_(const _Tp * m)
	{
		x = m[0];
		y = m[1];
		z = m[2];
	}
	template<class _Tp> inline Point3_<_Tp>::Point3_(MatPtr<_Tp> && m)
	{
		if (m.len >= 3) {
			if (DataType<_Tp>::type == m.depth()) {
				x = m.at<_Tp>(0);
				y = m.at<_Tp>(1);
				z = m.at<_Tp>(2);
			}
			else {
				x = m.get<_Tp>(0);
				y = m.get<_Tp>(1);
				z = m.get<_Tp>(2);
			}
		}
	}
	template<class _Tp> inline Point3_<_Tp>::Point3_(const MatPtr<_Tp> & m)
	{
		if (m.size() >= 3) {
			x = m[0];
			y = m[1];
			z = m[2];
		}
	}
	template<class _Tp> inline bool Point3_<_Tp>::operator==(Point3_<_Tp>& P) const
	{
		return (x == P.x) && (y == P.y) && (z == P.z);
	}
	template<class _Tp> inline bool Point3_<_Tp>::operator!=(Point3_<_Tp>& P) const
	{
		return !((*this) == P);
	}
	template<class _Tp>template<typename T2_> inline Point3_<_Tp>::Point3_(const Point3_<T2_>& p) : x(_Tp(p.x)), y(_Tp(p.y)), z(_Tp(p.z)) {}
	template<typename _Tp> inline const Point3_<_Tp> operator + (const _Tp& v, const Point3_<_Tp> &P)
	{
		return Point3_<_Tp>(P.x + v, P.y + v, P.z + v);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator + (const Point3_<_Tp> &P, const _Tp& v)
	{
		return Point3_<_Tp>(P.x + v, P.y + v, P.z + v);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator + (const Point3_<_Tp> &P1, const Point3_<_Tp>& P2)
	{
		return Point3_<_Tp>(P1.x + P2.x, P1.y + P2.y, P1.z + P2.z);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator - (const _Tp& v, const Point3_<_Tp> &P)
	{
		return Point3_<_Tp>(v - P.x, v - P.y, v - P.z);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator - (const Point3_<_Tp> &P, const _Tp& v)
	{
		return Point3_<_Tp>(P.x - v, P.y - v, P.z - v);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator - (const Point3_<_Tp> &P1, const Point3_<_Tp>& P2)
	{
		return Point2_<_Tp>(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator * (const _Tp& v, const Point3_<_Tp> &P)
	{
		return Point3_<_Tp>(P.x * v, P.y * v, P.z * v);
	}
	template<typename _Tp> inline const Point3_<_Tp> operator * (const Point3_<_Tp> &P, const _Tp& v)
	{
		return Point3_<_Tp>(P.x * v, P.y * v, P.z * v);
	}
	template<typename _Tp> inline const _Tp operator * (const Point3_<_Tp> &P1, const Point3_<_Tp>& P2)
	{
		return P1.x * P2.x + P1.y * P2.y + P1.z * P2.z;
	}

	template<class _Tp, int32 N> inline Vec<_Tp, N>::Vec() {
		memset(data, 0, sizeof(_Tp) * N);
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N>::Vec(_Tp * v)
	{
		memcpy(data, v, sizeof(_Tp)*N);
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N>::Vec(const MatPtr<_Tp> & m)
	{
		if (m.size() >= N) {
			memcpy(data, m, N * sizeof(_Tp));
		}
	}
	template<class _Tp, int32 N> template<typename ...Types> inline Vec<_Tp, N>::Vec(const Types & ...args) {
		int32 i = 0;
		addList(&data[0], i, args...);
		if (i != N) {
			FOR_RANGE(idx, i, N)
				data[i] = 0;
		}
	}
	template<class _Tp, int32 N> template<typename T2_> inline Vec<_Tp, N>::Vec(const Vec<T2_, N>& m)
	{
		for (int32 i = 0; i < N; i++)
			data[i] = _Tp(m[i]);
	}
	template<class _Tp, int32 N> template<typename T> inline void Vec<_Tp, N>::addvalue(int32 i, const T & arg)
	{
		data[i] = (_Tp)arg;
	}
	template<class _Tp, int32 N> template<typename T, typename ...Types> inline void Vec<_Tp, N>::addvalue(int32 i, const T & arg1, const Types & ...args)
	{
		if (i >= N)return;
		data[i] = (_Tp)arg1;
		addvalue(i + 1, args...);
	}
	template<class _Tp, int32 N> inline _Tp & Vec<_Tp, N>::at(int32 i) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, N);
#endif // MAT_DEBUG
		return data[i];
	}
	template<class _Tp, int32 N> inline const _Tp & Vec<_Tp, N>::at(int32 i) const {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, N);
#endif // MAT_DEBUG
		return data[i];
	}
	template<class _Tp, int32 N> inline _Tp & Vec<_Tp, N>::operator[](int32 i) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, N);
#endif // MAT_DEBUG
		return data[i];
	}
	template<class _Tp, int32 N> inline const _Tp & Vec<_Tp, N>::operator[](int32 i) const {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, N);
#endif // MAT_DEBUG
		return data[i];
	}
	template<class _Tp, int32 N> inline int32 Vec<_Tp, N>::size() const { return N; }
	template<class _Tp, int32 N> inline _Tp * Vec<_Tp, N>::begin() {
		return data;
	}
	template<class _Tp, int32 N> inline const _Tp * Vec<_Tp, N>::begin() const {
		return data;
	}
	template<class _Tp, int32 N> inline _Tp * Vec<_Tp, N>::end() {
		return data + N;
	}
	template<class _Tp, int32 N> inline const _Tp * Vec<_Tp, N>::end() const {
		return data + N;
	}
	template<class _Tp, int32 N>
	inline Vec<_Tp, N> Vec<_Tp, N>::t() const
	{
		Vec<_Tp, N> vec = *this;
		if (h == 1) {
			vec.w = N;
			vec.h = 1;
		}
		else {
			vec.h = N;
			vec.w = 1;
		}
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> Vec<_Tp, N>::operator=(int32 tab)
	{
		Color color = Color(tab);
		if (DataType<_Tp>::type == DataType<mat_t>::type && N >= 4)
			memcpy(data, color.data, sizeof(_Tp) * 4);
		else if (DataType<_Tp>::type != DataType<mat_t>::type && N >= 4)
			FOR_RANGE(i, 0, N)data[i] = (_Tp)color[i];
		else THROW_INFO_STR("向量尺寸不符!");
		return *this;
	}
	template<class _Tp, int32 N> template<typename _T2, int32 N1> inline Vec<_Tp, N> Vec<_Tp, N>::operator=(const Vec<_T2, N1>& vec)
	{
		if (data == vec.data)return *this;
		if (DataType<_Tp>::type == DataType<_T2>::type && N <= N1)
			memcpy(data, vec.data, sizeof(_Tp)*N);
		else if (DataType<_Tp>::type != DataType<_T2>::type && N <= N1)
			FOR_RANGE(i, 0, N)data[i] = (_Tp)vec[i];
		else THROW_INFO_STR("向量尺寸不符!");
		return *this;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator+(const Vec<_Tp, N> &vector, Val_ v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] + v;
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator-(const Vec<_Tp, N> &vector, Val_ v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] - v;
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator*(const Vec<_Tp, N> &vector, Val_ v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] * v;
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator/(const Vec<_Tp, N> &vector, Val_ v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] / v;
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator+(const Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] + v[i];
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator-(const Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] - v[i];
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator*(const Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] * v[i];
		return vec;
	}
	template<class _Tp, int32 N> inline Vec<_Tp, N> operator/(const Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		Vec<_Tp, N> vec;
		FOR_RANGE(i, 0, N)
			vec[i] = vector[i] / v[i];
		return vec;
	}
	template<class _Tp, int32 N> inline void operator+=(Vec<_Tp, N> &vector, Val_ v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] += v;
	}
	template<class _Tp, int32 N> inline void operator-=(Vec<_Tp, N> &vector, Val_ v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] -= v;
	}
	template<class _Tp, int32 N> inline void operator*=(Vec<_Tp, N> &vector, Val_ v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] *= v;
	}
	template<class _Tp, int32 N> inline void operator/=(Vec<_Tp, N> &vector, Val_ v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] /= v;
	}
	template<class _Tp, int32 N> inline void operator+=(Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] += v[i];
	}
	template<class _Tp, int32 N> inline void operator-=(Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] -= v[i];
	}
	template<class _Tp, int32 N> inline void operator*=(Vec<_Tp, N> &vector, const Vec<_Tp, N> &v)
	{
		FOR_RANGE(i, 0, N)
			vector[i] *= v[i];
	}
	template<class _Tp, int32 N> inline void operator/=(Vec<_Tp, N> &vector, const Vec<_Tp, N> &v) {
		FOR_RANGE(i, 0, N)
			vector[i] /= v[i];
	}

	static inline std::ostream & operator << (std::ostream & out, const Val_ & t)
	{
		out << "Val_(" << t.v << ", type=" << DataType<mat_t>().type_name << ")";
		return out;
	}
	static inline std::ostream & operator << (std::ostream & out, const Val & t)
	{
		switch (t.type)
		{
		case lzh::TP_8S:	out << "Val(" << (int16)t.v << ", type=int8)"; break;
		case lzh::TP_8U:	out << "Val(" << (uint16)t.v << ", type=uint8)"; break;
		case lzh::TP_16S:	out << "Val(" << (int16)t.v << ", type=int16)"; break;
		case lzh::TP_16U:	out << "Val(" << (uint16)t.v << ", type=uint16)"; break;
		case lzh::TP_32S:	out << "Val(" << (int32)t.v << ", type=int32)"; break;
		case lzh::TP_32U:	out << "Val(" << (uint32)t.v << ", type=uint32)"; break;
		case lzh::TP_32F:	out << "Val(" << (float32)t.v << ", type=float32)"; break;
		case lzh::TP_64S:	out << "Val(" << (float64)t.v << ", type=float64)"; break;
		case lzh::TP_64U:	out << "Val(" << (float64_)t.v << ", type=float64)"; break;
		case lzh::TP_64F:	out << "Val(" << (int64)t.v << ", type=int64)"; break;
		case lzh::TP_64D:	out << "Val(" << (uint64)t.v << ", type=uint64)"; break;
		default:
			break;
		}
		return out;
	}
	template<class _Tp> static inline std::ostream & operator << (std::ostream & out, const Range_<_Tp> & t)
	{
		out << "Range(" << t.v1 << "," << t.v2 << ", type=" << DataType<_Tp>().type_name << ")";
		return out;
	}
	template<class _Tp> static inline std::ostream & operator << (std::ostream & out, const Rect_<_Tp> & t)
	{
		out << "Rect(" << t.x << "," << t.y << "," << t.width << "," << t.height << ", type=" << DataType<_Tp>().type_name << ")";
		return out;
	}
	template<class _Tp> static inline std::ostream & operator << (std::ostream & out, const Size_<_Tp> & t)
	{
		out << "Size(" << t.h << "," << t.w << ", type=" << DataType<_Tp>().type_name << ")";
		return out;
	}
	template<class _Tp> static inline std::ostream & operator << (std::ostream & out, const Size3_<_Tp> & t)
	{
		out << "Size(" << t.h << "," << t.w << "," << t.c << ", type=" << DataType<_Tp>().type_name << ")";
		return out;
	}
	static inline std::ostream & operator << (std::ostream & out, const Complex & o)
	{
		out << "Complex(" << o.r << "+" << o.i << "i" << ", type=" << DataType<mat_t>().type_name << ")";
		return out;
	}
	template<class _Tp> static inline std::ostream & operator <<(std::ostream & out, const Point2_<_Tp>& t)
	{
		out << "Point(" << t.x << "," << t.y << ", type=" << DataType<_Tp>().type_name << ")";
		return out;
	}
	template<class _Tp> static inline std::ostream & operator << (std::ostream & out, const Point3_<_Tp>& t)
	{
		out << "Point(" << t.x << "," << t.y << "," << t.z << ", type=" << DataType<_Tp>().type_name << ")";
		return out;
	}
	template<class _Tp> static inline std::ostream & operator << (std::ostream &out, const MatPtr<_Tp> &t)
	{
		out << "Ptr([";
		FOR_RANGE(i, 0, t.size())
			if (i == t.size() - 1)
				out << t[i] << "]" << ", type=" << DataType<_Tp>().type_name << ")";
			else
				out << t[i] << ", ";
		return out;
	}
	template<class _Tp, int32 N> static inline std::ostream & operator << (std::ostream &out, const Vec<_Tp, N> &t)
	{
		out << "Vector([";
		FOR_RANGE(i, 0, N)
			if (i == N - 1)
				out << t[i] << "]" << ", type=" << DataType<_Tp>().type_name << ")";
			else
				out << t[i] << ", ";
		return out;
	}

	template<typename _Tp> inline void __swap(_Tp & a, _Tp & b) {
		_Tp temp = a;
		a = b;
		b = temp;
	}

	typedef Vec3m Scalar;
	typedef std::vector<lzh::Point2_<lzh::int8>>					vec_p2_8s;
	typedef std::vector<lzh::Point2_<lzh::uint8>>					vec_p2_8b;
	typedef std::vector<lzh::Point2_<lzh::int16>>					vec_p2_16s;
	typedef std::vector<lzh::Point2_<lzh::uint16>>					vec_p2_16u;
	typedef std::vector<lzh::Point2_<lzh::int32>>					vec_p2_32s;
	typedef std::vector<lzh::Point2_<lzh::uint32>>					vec_p2_32u;
	typedef std::vector<lzh::Point2_<lzh::int64>>					vec_p2_64s;
	typedef std::vector<lzh::Point2_<lzh::uint64>>					vec_p2_64u;
	typedef std::vector<lzh::Point2_<lzh::float32>>					vec_p2_32f;
	typedef std::vector<lzh::Point2_<lzh::float64>>					vec_p2_64f;
	typedef std::vector<lzh::Point2_<lzh::float64_>>				vec_p2_64d;
	typedef std::vector<lzh::Point2_<lzh::mat_t>>					vec_p2_m;
	typedef std::vector<std::vector<lzh::Point2_<lzh::int8>>>		vecs_p2_8s;
	typedef std::vector<std::vector<lzh::Point2_<lzh::uint8>>>		vecs_p2_8b;
	typedef std::vector<std::vector<lzh::Point2_<lzh::int16>>>		vecs_p2_16s;
	typedef std::vector<std::vector<lzh::Point2_<lzh::uint16>>>		vecs_p2_16u;
	typedef std::vector<std::vector<lzh::Point2_<lzh::int32>>>		vecs_p2_32s;
	typedef std::vector<std::vector<lzh::Point2_<lzh::uint32>>>		vecs_p2_32u;
	typedef std::vector<std::vector<lzh::Point2_<lzh::int64>>>		vecs_p2_64s;
	typedef std::vector<std::vector<lzh::Point2_<lzh::uint64>>>		vecs_p2_64u;
	typedef std::vector<std::vector<lzh::Point2_<lzh::float32>>>	vecs_p2_32f;
	typedef std::vector<std::vector<lzh::Point2_<lzh::float64>>>	vecs_p2_64f;
	typedef std::vector<std::vector<lzh::Point2_<lzh::float64_>>>	vecs_p2_64d;
	typedef std::vector<std::vector<lzh::Point2_<lzh::mat_t>>>		vecs_p2_m;
	typedef std::vector<lzh::Point3_<lzh::int8>>					vec_p3_8s;
	typedef std::vector<lzh::Point3_<lzh::uint8>>					vec_p3_8b;
	typedef std::vector<lzh::Point3_<lzh::int16>>					vec_p3_16s;
	typedef std::vector<lzh::Point3_<lzh::uint16>>					vec_p3_16u;
	typedef std::vector<lzh::Point3_<lzh::int32>>					vec_p3_32s;
	typedef std::vector<lzh::Point3_<lzh::uint32>>					vec_p3_32u;
	typedef std::vector<lzh::Point3_<lzh::int64>>					vec_p3_64s;
	typedef std::vector<lzh::Point3_<lzh::uint64>>					vec_p3_64u;
	typedef std::vector<lzh::Point3_<lzh::float32>>					vec_p3_32f;
	typedef std::vector<lzh::Point3_<lzh::float64>>					vec_p3_64f;
	typedef std::vector<lzh::Point3_<lzh::float64_>>				vec_p3_64d;
	typedef std::vector<lzh::Point3_<lzh::mat_t>>					vec_p3_m;
	typedef std::vector<std::vector<lzh::Point3_<lzh::int8>>>		vecs_p3_8s;
	typedef std::vector<std::vector<lzh::Point3_<lzh::uint8>>>		vecs_p3_8b;
	typedef std::vector<std::vector<lzh::Point3_<lzh::int16>>>		vecs_p3_16s;
	typedef std::vector<std::vector<lzh::Point3_<lzh::uint16>>>		vecs_p3_16u;
	typedef std::vector<std::vector<lzh::Point3_<lzh::int32>>>		vecs_p3_32s;
	typedef std::vector<std::vector<lzh::Point3_<lzh::uint32>>>		vecs_p3_32u;
	typedef std::vector<std::vector<lzh::Point3_<lzh::int64>>>		vecs_p3_64s;
	typedef std::vector<std::vector<lzh::Point3_<lzh::uint64>>>		vecs_p3_64u;
	typedef std::vector<std::vector<lzh::Point3_<lzh::float32>>>	vecs_p3_32f;
	typedef std::vector<std::vector<lzh::Point3_<lzh::float64>>>	vecs_p3_64f;
	typedef std::vector<std::vector<lzh::Point3_<lzh::float64_>>>	vecs_p3_64d;
	typedef std::vector<std::vector<lzh::Point3_<lzh::mat_t>>>		vecs_p3_m;
}
#endif