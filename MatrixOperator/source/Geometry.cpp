#include "Geometry.h"
#include "MatApi.h"
using namespace lzh;

Ellipse::Ellipse() : Vec4m() {}
Ellipse::Ellipse(IMat a) : Vec4m(a) {}
Ellipse::Ellipse(const Vec4m & v) : Vec4m(v) {}
Ellipse::Ellipse(Val_ x0, Val_ y0, Val_ a, Val_ b) : Vec4m(x0, y0, a, b) {}
Ellipse::Ellipse(std::initializer_list<mat_t> list) : Vec4m() {
	int32 size = int32(list.end() - list.begin());
	CHECK_EXCEPTION(if (size == 3 || size == 4), THROW_INFO_STR("椭圆只需要中心点坐标和半径, 3-4个参数!"));
	if (size == 4)memcpy(data, list.begin(), M_SIZE * 4);
	else { memcpy(data, list.begin(), M_SIZE * 3); data[3] = data[2]; }
}
Val_ Ellipse::S() const {
	return data[2] * data[3] * PI;
}
Val_ Ellipse::C() const {
	return PI * data[2] * data[3];
}
Vec2m Ellipse::center() const {
	return Vec2m(data[0], data[1]);
}
Vec2m lzh::Ellipse::f(Val_ theta) const {
	CHECK_EXCEPTION(if (0 <= theta && theta <= 2 * PI), THROW_INFO_STR("椭圆参数方程的输入theta不在定义域[0, 2pi]内!"));
	return Vec2m(data[0] + data[2] * cos(theta), data[1] + data[3] * sin(theta));
}
Vec2m Ellipse::operator()(Val_ theta) const {
	return f(theta);
}
Vec4m Ellipse::fit(IMat x, IMat y, Mat * r)
{
	Mat a;
	fitEllipse(x, y, a, r);
	return Vec4m(a);
}
Vec3m lzh::Circle::fit(IMat x, IMat y, Mat * r)
{
	Mat a;
	fitCircle(x, y, a, r);
	return Vec3m(a);
}

Ellipsoid::Ellipsoid() : Vec<mat_t, 6>() {}
Ellipsoid::Ellipsoid(IMat a) : Vec<mat_t, 6>(a) {}
Ellipsoid::Ellipsoid(const Vec<mat_t, 6> & v) : Vec<mat_t, 6>(v) {}
Ellipsoid::Ellipsoid(Val_ x0, Val_ y0, Val_ z0, Val_ a, Val_ b, Val_ c) : Vec<mat_t, 6>(x0, y0, z0, a, b, c) {}
Ellipsoid::Ellipsoid(std::initializer_list<mat_t> list) : Vec<mat_t, 6>() {
	int32 size = int32(list.end() - list.begin());
	CHECK_EXCEPTION(if (size >= 4 && size <= 6), THROW_INFO_STR("椭球只需要中心点坐标与半径, 4-6个参数!"));
	if (size == 6) memcpy(data, list.begin(), M_SIZE * 6);
	else if (size == 5) { memcpy(data, list.begin(), M_SIZE * 5); data[5] = data[4]; }
	else { memcpy(data, list.begin(), M_SIZE * 4); data[5] = data[4] = data[3]; }
}
Val_ Ellipsoid::V() const {
	return Val_(4.0 / 3.0) * PI * data[3] * data[4] * data[5];
}
Val_ Ellipsoid::S() const {
	return Val_(4.0 / 3.0) * (data[3] * data[4] + data[4] * data[5] + data[3] * data[5]) * PI;
}
Vec3m Ellipsoid::center() const {
	return Vec3m(data[0], data[1], data[2]);
}
Vec3m lzh::Ellipsoid::f(Val_ theta, Val_ fai) const
{
	CHECK_EXCEPTION(if (0 <= theta && theta <= 2 * PI), THROW_INFO_STR("球参数方程的输入theta不在定义域[0, 2pi]内!"));
	CHECK_EXCEPTION(if (0 <= fai && fai <= PI), THROW_INFO_STR("球参数方程的输入t不在定义域[0, pi]内!"));
	return Vec3m(data[0] + data[3] * sin(fai)* cos(theta), data[1] + data[4] * sin(fai)* sin(theta), data[2] + data[5] * cos(fai));
}
Vec3m Ellipsoid::operator()(Val_ theta, Val_ fai)const {
	return f(theta, fai);
}
Vec<mat_t, 6> Ellipsoid::fit(IMat x, IMat y, Mat * r)
{
	return Vec<mat_t, 6>();
}

Vec<mat_t, 4> Sphere::fit(IMat x, IMat y, Mat * r)
{
	return Vec<mat_t, 4>();
}

Polynomial::Polynomial() : param() {}
Polynomial::Polynomial(IMat a) : param(a) {}
Polynomial::Polynomial(int power) : param(power, 1) {}
Polynomial::Polynomial(std::initializer_list<mat_t> list) : param(list) {}
Val_ Polynomial::operator()(Val_ x) const {
	CHECK_EXCEPTION(if (param.empty()), THROW_INFO_STR("多项式参数为空!"));
	mat_t y = 0;
	int32 power = (int32)param.len() - 1;
	for (const mat_t &a : param) {
		y += a * pow(x, power--);
	}
	return y;
}
OMat Polynomial::operator()(IMat x) const
{
	CHECK_EXCEPTION(if (!param.empty()), THROW_INFO_STR("多项式参数为空!"));
	Mat y = Mat::zeros(x.size3());
	int32 power = (int32)param.len() - 1;
	for (const mat_t &a : param) {
		y += a * x.pow(power--);
	}
	return y;
}
Mat & Polynomial::get()
{
	return param;
}
Polynomial Polynomial::fit(IMat x, IMat y, int32 power, Mat * r)
{
	Polynomial poly;
	polyfit(x, y, power, poly.get(), r);
	return poly;
}