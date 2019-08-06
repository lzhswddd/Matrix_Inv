#pragma once
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Mat.h"

namespace lzh
{
	class Ellipse : public Vec4m
	{
	public:
		explicit Ellipse();
		Ellipse(IMat a);
		Ellipse(const Vec4m & v);
		Ellipse(Val_ x0, Val_ y0, Val_ a, Val_ b);
		Ellipse(std::initializer_list<mat_t> list);
		template<typename _Tp> Ellipse(Point2_<_Tp> center, Val_ a, Val_ b) : Ellipse(center.x, center.y, a, b) {}
		Val_ S()const;
		Val_ C()const;
		Vec2m center()const;
		Vec2m f(Val_ theta)const;
		Vec2m operator ()(Val_ theta)const;
		static Vec4m fit(IMat x, IMat y, Mat* r = nullptr);
	};
	template<> class DataType<Ellipse>
	{
		typedef Ellipse value_type;
		enum { type = DataType<Vec4m>::type };
		const int8 * type_name = DataType<mat_t>().type_name;
	};
	class Circle : public Ellipse
	{
	public:
		explicit Circle() : Ellipse() {}
		Circle(IMat a) : Ellipse(a) {}
		Circle(const Vec3m & v) : Ellipse(Vec4m(v[0], v[1], v[2], v[2])) {}
		Circle(Val_ x0, Val_ y0, Val_ radius = 1) : Ellipse(x0, y0, radius, radius) {}
		Circle(std::initializer_list<mat_t> list) : Ellipse(list) {}
		template<typename _Tp> Circle(Point2_<_Tp> center, Val_ radius = 1) : Ellipse(center, radius, radius) {}
		static Vec3m fit(IMat x, IMat y, Mat* r = nullptr);
	};
	template<> class DataType<Circle>
	{
		typedef Circle value_type;
		enum { type = DataType<Vec4m>::type };
		const int8 * type_name = DataType<mat_t>().type_name;
	};
	class Ellipsoid : public Vec<mat_t, 6>
	{
	public:
		explicit Ellipsoid();
		Ellipsoid(IMat a);
		Ellipsoid(const Vec<mat_t, 6> & v);
		Ellipsoid(Val_ x0, Val_ y0, Val_ z0, Val_ a, Val_ b, Val_ c);
		Ellipsoid(std::initializer_list<mat_t> list);
		template<typename _Tp> Ellipsoid(Point3_<_Tp> center, Val_ a, Val_ b, Val_ c) : Vec<mat_t, 6>(center.x, center.y, center.z, a, b, c) {}
		Val_ V()const;
		Val_ S()const;
		Vec3m center()const;
		Vec3m f(Val_ theta, Val_ fai)const;
		Vec3m operator ()(Val_ theta, Val_ fai)const;
		static Vec<mat_t, 6> fit(IMat x, IMat y, Mat* r = nullptr);
	};
	template<> class DataType<Ellipsoid>
	{
		typedef Ellipsoid value_type;
		enum { type = DataType<Vec<mat_t, 6>>::type };
		const int8 * type_name = DataType<mat_t>().type_name;
	};
	class Sphere : public Ellipsoid
	{
	public:
		explicit Sphere() : Ellipsoid() {}
		Sphere(IMat a) : Ellipsoid(a) {}
		Sphere(const Vec<mat_t, 4> & v) : Ellipsoid(Vec<mat_t, 6>(v[0], v[1], v[2], v[3], v[3], v[3])) {}
		Sphere(Val_ x0, Val_ y0, Val_ z0, Val_ radius = 1) : Ellipsoid(x0, y0, z0, radius, radius, radius) {}
		Sphere(std::initializer_list<mat_t> list) :Ellipsoid(list) {}
		template<typename _Tp> Sphere(Point3_<_Tp> center, Val_ radius = 1) : Vec3m(center, radius, radius, radius) {}
		static Vec<mat_t, 4> fit(IMat x, IMat y, Mat* r = nullptr);
	};
	template<> class DataType<Sphere>
	{
		typedef Sphere value_type;
		enum { type = DataType<Vec<mat_t, 6>>::type };
		const int8 * type_name = DataType<mat_t>().type_name;
	};
	class Polynomial
	{
	public:
		explicit Polynomial();
		Polynomial(IMat a);
		Polynomial(int power);
		Polynomial(std::initializer_list<mat_t> list);
		template <typename ... _Tp> Polynomial(int power, const _Tp & ... args) : param(power, args) {}
		Val_ operator ()(Val_ x)const;
		OMat operator ()(IMat x)const;
		Mat& get();
		operator Mat& () { return param; }
		operator const Mat& ()const { return param; }

		static Polynomial fit(IMat x, IMat y, int32 power, Mat* r = nullptr);
	protected:
		Mat param;
	};
}

#endif //__GEOMETRY_H__
