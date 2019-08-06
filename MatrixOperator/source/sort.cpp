#include "sort.h"
using namespace lzh;


/****************************************************************************
≈≈–Ú
*****************************************************************************/
#define SORT_FUN(fun, dst, order)\
do{\
	fun(dst.begin(), dst.end(), order == MIN_TO_MAX ? comp_min<mat_t> : comp_max<mat_t>);	break;\
}while(0)
bool lzh::sort::compare_angle(InputArray a_, InputArray b_)
{
	CvMat a = a_.getCvMat();
	CvMat b = b_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_PTR(sort::pre);
#endif //MAT_DEBUG
	CvMat &p = *(CvMat*)sort::pre;
	mat_t xx = p(1);
	mat_t yy = p(0);
	mat_t v1 = std::atan2(a(0) - yy, a(1) - xx);
	mat_t v2 = std::atan2(b(0) - yy, b(1) - xx);
	if (v1 != v2)
		return v1 < v2;
	return a(1) < b(1);
}
bool lzh::sort::compare_min(InputArray a, InputArray b)
{
	return a < b;
}
bool lzh::sort::compare_max(InputArray a, InputArray b)
{
	return a > b;
}
void lzh::sort::bubble(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(bubble, dst, order);
	dst_.set(dst);
}
void lzh::sort::insert(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(insert, dst, order);
	dst_.set(dst);
}
void lzh::sort::select(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(select, dst, order);
	dst_.set(dst);
}
void lzh::sort::comb(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(comb, dst, order);
	dst_.set(dst);
}
void lzh::sort::gnome(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(gnome, dst, order);
	dst_.set(dst);
}
void lzh::sort::heap(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(heap, dst, order);
	dst_.set(dst);
}
void lzh::sort::shell(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(shell, dst, order);
	dst_.set(dst);
}
void lzh::sort::quick(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(quick, dst, order);
	dst_.set(dst);
}
void lzh::sort::merge(InputArray src, OutputArray dst_, ORDER order)
{
	Mat m = src.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.clone();
	SORT_FUN(merge, dst, order);
	dst_.set(dst);
}

void lzh::sort::Register(const void * p)
{
	sort::pre = (void*)p;
}