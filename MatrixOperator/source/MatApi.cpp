#include "MatApi.h"
#include "cvtColor.h"
#include "sort.h"
#include "MatOperator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace lzh;


/****************************************************************************
接口类
*****************************************************************************/
void lzh::_InputArray::init(const void * obj, int32 flags, int32 type)
{
	this->flags = flags; this->obj = (void*)obj; this->type = type;
}
void lzh::_InputArray::init(const void * obj, int32 flags, int32 type, Size sz)
{
	this->flags = flags; this->obj = (void*)obj; this->type = type; this->sz = sz;
}
_InputArray::_InputArray(IMat m) {
	init(&m, MAT, m.type());
}
_InputArray::_InputArray(const CvMat &v) {
	init(&v, CVMAT, v.depth());
}
_InputArray::_InputArray(const std::vector<Mat> &v) {
	init(&v, STD_VECTOR_MAT, NONE, Size(1, (int32)v.size()));
}
_InputArray::_InputArray(const std::vector<CvMat> &v) {
	init(&v, STD_VECTOR_CVMAT, NONE, Size(1, (int32)v.size()));
}
CvMat lzh::_InputArray::getCvMat(int32 i) const
{
	if (flags == MAT && i < 0)
		return CvMat(*(Mat*)obj);
	if (flags == MAT_ITER && i < 0) {
		MatCommaInitializer_<uint8> iter = *(MatCommaInitializer_<uint8>*)obj;
		return CvMat(iter.rows() *iter.cols()*iter.channels(), iter.data(), type);
	}
	if (flags == CVMAT && i < 0)
		return *(CvMat*)obj;
	int32 t = depth();
	int32 esz = value_type();
	switch (flags)
	{
	case lzh::_InputArray::VALUE:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return CvMat(esz, sz.h, (const int8*)obj, t);
		case lzh::TP_8U:
			return CvMat(esz, sz.h, (const uint8*)obj, t);
		case lzh::TP_16S:
			return CvMat(esz, sz.h, (const int16*)obj, t);
		case lzh::TP_16U:
			return CvMat(esz, sz.h, (const uint16*)obj, t);
		case lzh::TP_32S:
			return CvMat(esz, sz.h, (const int32*)obj, t);
		case lzh::TP_32U:
			return CvMat(esz, sz.h, (const uint32*)obj, t);
		case lzh::TP_64S:
			return CvMat(esz, sz.h, (const int64*)obj, t);
		case lzh::TP_64U:
			return CvMat(esz, sz.h, (const uint64*)obj, t);
		case lzh::TP_32F:
			return CvMat(esz, sz.h, (const float32*)obj, t);
		case lzh::TP_64F:
			return CvMat(esz, sz.h, (const float64*)obj, t);
		case lzh::TP_64D:
			return CvMat(esz, sz.h, (const float64_*)obj, t);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::STD_VECTOR:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return CvMat(esz, sz.h, &(*(const vec_8s*)obj)[0], t);
		case lzh::TP_8U:
			return CvMat(esz, sz.h, &(*(const vec_8b*)obj)[0], t);
		case lzh::TP_16S:
			return CvMat(esz, sz.h, &(*(const vec_16s*)obj)[0], t);
		case lzh::TP_16U:
			return CvMat(esz, sz.h, &(*(const vec_16u*)obj)[0], t);
		case lzh::TP_32S:
			return CvMat(esz, sz.h, &(*(const vec_32s*)obj)[0], t);
		case lzh::TP_32U:
			return CvMat(esz, sz.h, &(*(const vec_32u*)obj)[0], t);
		case lzh::TP_64S:
			return CvMat(esz, sz.h, &(*(const vec_64s*)obj)[0], t);
		case lzh::TP_64U:
			return CvMat(esz, sz.h, &(*(const vec_64u*)obj)[0], t);
		case lzh::TP_32F:
			return CvMat(esz, sz.h, &(*(const vec_32f*)obj)[0], t);
		case lzh::TP_64F:
			return CvMat(esz, sz.h, &(*(const vec_64f*)obj)[0], t);
		case lzh::TP_64D:
			return CvMat(esz, sz.h, &(*(const vec_64d*)obj)[0], t);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::STD_VECTOR_MAT:
		if (i < 0)THROW_INFO(ERR_INFO_UNLESS);
		return CvMat(((vec_mat*)obj)->at(i));
	case lzh::_InputArray::STD_VECTOR_CVMAT:
		if (i < 0)THROW_INFO(ERR_INFO_UNLESS);
		return ((std::vector<CvMat>*)obj)->at(i);
	case lzh::_InputArray::STD_VECTOR_VECTOR:
		if (i < 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return CvMat(esz, sz.h, &(*(const vecs_8s*)obj)[i][0], t);
		case lzh::TP_8U:
			return CvMat(esz, sz.h, &(*(const vecs_8b*)obj)[i][0], t);
		case lzh::TP_16S:
			return CvMat(esz, sz.h, &(*(const vecs_16s*)obj)[i][0], t);
		case lzh::TP_16U:
			return CvMat(esz, sz.h, &(*(const vecs_16u*)obj)[i][0], t);
		case lzh::TP_32S:
			return CvMat(esz, sz.h, &(*(const vecs_32s*)obj)[i][0], t);
		case lzh::TP_32U:
			return CvMat(esz, sz.h, &(*(const vecs_32u*)obj)[i][0], t);
		case lzh::TP_64S:
			return CvMat(esz, sz.h, &(*(const vecs_64s*)obj)[i][0], t);
		case lzh::TP_64U:
			return CvMat(esz, sz.h, &(*(const vecs_64u*)obj)[i][0], t);
		case lzh::TP_32F:
			return CvMat(esz, sz.h, &(*(const vecs_32f*)obj)[i][0], t);
		case lzh::TP_64F:
			return CvMat(esz, sz.h, &(*(const vecs_64f*)obj)[i][0], t);
		case lzh::TP_64D:
			return CvMat(esz, sz.h, &(*(const vecs_64d*)obj)[i][0], t);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::VECTOR:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return CvMat(esz, sz.h, (const int8*)obj, t);
		case lzh::TP_8U:
			return CvMat(esz, sz.h, (const uint8*)obj, t);
		case lzh::TP_16S:
			return CvMat(esz, sz.h, (const int16*)obj, t);
		case lzh::TP_16U:
			return CvMat(esz, sz.h, (const uint16*)obj, t);
		case lzh::TP_32S:
			return CvMat(esz, sz.h, (const int32*)obj, t);
		case lzh::TP_32U:
			return CvMat(esz, sz.h, (const uint32*)obj, t);
		case lzh::TP_64S:
			return CvMat(esz, sz.h, (const int64*)obj, t);
		case lzh::TP_64U:
			return CvMat(esz, sz.h, (const uint64*)obj, t);
		case lzh::TP_32F:
			return CvMat(esz, sz.h, (const float32*)obj, t);
		case lzh::TP_64F:
			return CvMat(esz, sz.h, (const float64*)obj, t);
		case lzh::TP_64D:
			return CvMat(esz, sz.h, (const float64_*)obj, t);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
	return CvMat();
}
Mat lzh::_InputArray::getMat(int32 i) const
{
	if (flags == MAT && i < 0)
		return *(Mat*)obj;
	if (flags == CVMAT && i < 0)
		return *(CvMat*)obj;
	return getMat_(i);
}
Mat lzh::_InputArray::getMat_(int32 i) const
{
	int32 t = depth();
	int32 esz = value_type();
	switch (flags)
	{
	case lzh::_InputArray::VALUE:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return Mat(esz, sz.h, (const int8*)obj);
		case lzh::TP_8U:
			return Mat(esz, sz.h, (const uint8*)obj);
		case lzh::TP_32S:
			return Mat(esz, sz.h, (const int32*)obj);
		case lzh::TP_32F:
			return Mat(esz, sz.h, (const float32*)obj);
		case lzh::TP_64F:
			return Mat(esz, sz.h, (const float64*)obj);
		case lzh::TP_64D:
			return Mat(esz, sz.h, (const float64_*)obj);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::MAT_ITER:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return Mat(esz, sz.h, &(*(const vec_8s*)obj)[0]);
		case lzh::TP_8U:
			return Mat(esz, sz.h, &(*(const vec_8b*)obj)[0]);
		case lzh::TP_32S:
			return Mat(esz, sz.h, &(*(const vec_32s*)obj)[0]);
		case lzh::TP_32F:
			return Mat(esz, sz.h, &(*(const vec_32f*)obj)[0]);
		case lzh::TP_64F:
			return Mat(esz, sz.h, &(*(const vec_32s*)obj)[0]);
		case lzh::TP_64D:
			return Mat(esz, sz.h, &(*(const vec_64d*)obj)[0]);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::STD_VECTOR:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return Mat(esz, sz.h, &(*(const vec_8s*)obj)[0]);
		case lzh::TP_8U:
			return Mat(esz, sz.h, &(*(const vec_8b*)obj)[0]);
		case lzh::TP_32S:
			return Mat(esz, sz.h, &(*(const vec_32s*)obj)[0]);
		case lzh::TP_32F:
			return Mat(esz, sz.h, &(*(const vec_32f*)obj)[0]);
		case lzh::TP_64F:
			return Mat(esz, sz.h, &(*(const vec_32s*)obj)[0]);
		case lzh::TP_64D:
			return Mat(esz, sz.h, &(*(const vec_64d*)obj)[0]);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::STD_VECTOR_MAT:
		if (i < 0)THROW_INFO(ERR_INFO_UNLESS);
		return (*(const std::vector<Mat>*)obj)[i];
	case lzh::_InputArray::STD_VECTOR_CVMAT:
		if (i < 0)THROW_INFO(ERR_INFO_UNLESS);
		return ((std::vector<CvMat>*)obj)->at(i);
	case lzh::_InputArray::STD_VECTOR_VECTOR:
		if (i < 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return Mat(esz, sz.h, &(*(const vecs_8s*)obj)[i][0]);
		case lzh::TP_8U:
			return Mat(esz, sz.h, &(*(const vecs_8b*)obj)[i][0]);
		case lzh::TP_32S:
			return Mat(esz, sz.h, &(*(const vecs_32s*)obj)[i][0]);
		case lzh::TP_32F:
			return Mat(esz, sz.h, &(*(const vecs_32f*)obj)[i][0]);
		case lzh::TP_64F:
			return Mat(esz, sz.h, &(*(const vecs_32s*)obj)[i][0]);
		case lzh::TP_64D:
			return Mat(esz, sz.h, &(*(const vecs_64d*)obj)[i][0]);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	case lzh::_InputArray::VECTOR:
		if (i >= 0)THROW_INFO(ERR_INFO_UNLESS);
		switch (t)
		{
		case lzh::TP_8S:
			return Mat(esz, sz.h, (const int8*)obj);
		case lzh::TP_8U:
			return Mat(esz, sz.h, (const uint8*)obj);
		case lzh::TP_32S:
			return Mat(esz, sz.h, (const int32*)obj);
		case lzh::TP_32F:
			return Mat(esz, sz.h, (const float32*)obj);
		case lzh::TP_64F:
			return Mat(esz, sz.h, (const float64*)obj);
		case lzh::TP_64D:
			return Mat(esz, sz.h, (const float64_*)obj);
		default:THROW_INFO(ERR_INFO_TYPE); break;
		}
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
	return Mat();
}
void lzh::_InputArray::swap(Mat & dst) const
{
	dst = getMat();
}
bool lzh::_InputArray::empty()const {
	return obj == nullptr;
}
int32 lzh::_InputArray::kind()const
{
	return flags;
}
int32 lzh::_InputArray::depth()const
{
	return MAT_GETVALUE(type);
}
int32 lzh::_InputArray::getTp() const
{
	return type;
}
int32 lzh::_InputArray::size()const
{
	return sz.h;
}
int32 lzh::_InputArray::rows() const
{
	return getCvMat().rows;
}
int32 lzh::_InputArray::cols() const
{
	return getCvMat().cols;
}
int32 lzh::_InputArray::len() const
{
	return getCvMat().len();
}
Size lzh::_InputArray::getSz() const
{
	return sz;
}
Size lzh::_InputArray::getSz_() const
{
	if (flags == MAT)
		return ((Mat*)obj)->size();
	if (flags == MAT_ITER)
		return ((MatCommaInitializer_<uint8>*)obj)->size();
	int32 esz = value_type();
	return Size(esz, sz.h);
}
bool lzh::_InputArray::isStdVector()const {
	return flags == STD_VECTOR;
}
bool lzh::_InputArray::isMat() const
{
	return flags == MAT;
}
int32 lzh::_InputArray::value_type() const
{
	return MAT_GETDEPTH(type);
}

void lzh::_OutputArray::create(Size sz, int32 mtype) const
{
	create(sz.h, sz.w, 1, mtype);
}
void lzh::_OutputArray::create(Size3 sz, int32 mtype) const
{
	create(sz.h, sz.w, sz.c, mtype);
}
void lzh::_OutputArray::create(int32 rows, int32 mtype) const
{
	create(rows, 1, 1, mtype);
}
void lzh::_OutputArray::create(int32 rows, int32 cols, int32 mtype) const
{
	create(rows, cols, 1, mtype);
}
void lzh::_OutputArray::create(int32 rows, int32 cols, int32 channels, int32 mtype) const
{
	switch (flags)
	{
	case lzh::_InputArray::MAT:(*(Mat*)obj).create(cols, rows, channels); break;
	case lzh::_InputArray::CVMAT:(*(CvMat*)obj).create(cols, rows, channels, mtype); break;
	case lzh::_InputArray::STD_VECTOR:
	{
		int32 len = cols * rows* channels*MAT_GETDEPTH(type);
		*(Size*)&sz = Size(cols, rows);
		switch (MAT_GETVALUE(type))
		{
		case lzh::TP_8S:	((vec_8s*)obj)->resize(len);	break;
		case lzh::TP_8U:	((vec_8b*)obj)->resize(len);	break;
		case lzh::TP_32S:	((vec_32s*)obj)->resize(len);	break;
		case lzh::TP_32F:	((vec_32f*)obj)->resize(len);	break;
		case lzh::TP_64F:	((vec_64f*)obj)->resize(len);	break;
		case lzh::TP_64D:	((vec_64d*)obj)->resize(len);	break;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
		break;
	}
	case lzh::_InputArray::STD_VECTOR_MAT: {
		int32 len = cols * rows* channels;
		*(Size*)&sz = Size(cols, rows);
		((vec_mat*)obj)->resize(len);
		break;
	}
	default:
		THROW_INFO(ERR_INFO_TYPE);
	}
}
void lzh::_OutputArray::createSameSize(InputArray arr, int32 mtype) const
{
	if (arr.object() == object())return;
	if (arr.kind() == MAT)
		create(arr.getMat().size3(), MAT_T);
	else if (arr.kind() == CVMAT)
		create(arr.getCvMat().size3(), mtype);
	else if (arr.kind() == STD_VECTOR_VECTOR)
	{
		int32 d = MAT_GETDEPTH(type);
		*(Size*)&sz = arr.getSz();
		int32 len = sz.h;
		switch (MAT_GETVALUE(type))
		{
		case lzh::TP_8S:	((vecs_8s*)obj)->resize(len);	FOR_RANGE(i, 0, len)((vecs_8s*)obj)->at(i).resize(arr.getCvMat(i).len()); break;
		case lzh::TP_8U:	((vecs_8b*)obj)->resize(len);	FOR_RANGE(i, 0, len)((vecs_8b*)obj)->at(i).resize(arr.getCvMat(i).len()); break;
		case lzh::TP_32S:	((vecs_32s*)obj)->resize(len);	FOR_RANGE(i, 0, len)((vecs_32s*)obj)->at(i).resize(arr.getCvMat(i).len()); break;
		case lzh::TP_32F:	((vecs_32f*)obj)->resize(len);	FOR_RANGE(i, 0, len)((vecs_32f*)obj)->at(i).resize(arr.getCvMat(i).len()); break;
		case lzh::TP_64F:	((vecs_64f*)obj)->resize(len);	FOR_RANGE(i, 0, len)((vecs_64f*)obj)->at(i).resize(arr.getCvMat(i).len()); break;
		case lzh::TP_64D:	((vecs_64d*)obj)->resize(len);	FOR_RANGE(i, 0, len)((vecs_64d*)obj)->at(i).resize(arr.getCvMat(i).len()); break;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
	}
	else
		create(arr.getSz(), mtype);
}
void lzh::_OutputArray::release() const
{
}
void lzh::_OutputArray::clear() const
{
}
Mat & lzh::_OutputArray::getMatRef(int32 i) const
{
	if (flags == MAT && i < 0)
		return *(Mat*)obj;
	else if (flags == STD_VECTOR_MAT && i >= 0) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, sz.h);
#endif //MAT_DEBUG
		return (*(vec_mat*)obj)[i];
	}
	else {
		THROW_INFO(ERR_INFO_TYPE);
	}
	return *(Mat*)(0);//为了不警告
}
CvMat & lzh::_OutputArray::getCvMatRef(int32 i) const
{
	if (flags == CVMAT && i < 0)
		return *(CvMat*)obj;
	else if (flags == STD_VECTOR_CVMAT && i >= 0) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, sz.h);
#endif //MAT_DEBUG
		return (*(std::vector<CvMat>*)obj)[i];
	}
	else {
		THROW_INFO(ERR_INFO_TYPE);
	}
	return *(CvMat*)(0);//为了不警告
}
void lzh::_OutputArray::setMatRef(InputArray m, int32 i) const
{
	if (flags == MAT && i < 0)
		*(Mat*)obj = m.getMat().clone();
	else if (flags == STD_VECTOR_MAT && i >= 0) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, sz.h);
#endif //MAT_DEBUG
		(*(vec_mat*)obj)[i] = m.getMat().clone();
	}
	else if (flags == CVMAT && i < 0)
		*(CvMat*)obj = m.getCvMat().clone();
	else if (flags == STD_VECTOR_CVMAT && i >= 0) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, sz.h);
#endif //MAT_DEBUG
		(*(vec_cvmat*)obj)[i] = m.getCvMat().clone();
	}
	else {
		THROW_INFO(ERR_INFO_TYPE);
	}
}
void lzh::_OutputArray::set(InputArray input) const
{
	if (input.object() == object())return;
	if (len() != input.len() && flags != CVMAT && flags != MAT)
		createSameSize(input, input.depth());
	else if (!getCvMat().empty())
		createSameSize(input, input.depth());
	setTo(input);
}
void lzh::_OutputArray::setTo(InputArray input) const
{
	if (input.empty())return;
	if (input.object() == object())return;
	if (flags == MAT) {
		if (!getMat().empty() && !getMat().isDeepCopy()) {
			input.getMat().setTo(getCvMat());
		}
		else
			getMatRef() = input.getCvMat();
	}
	else if (flags == CVMAT) {
		if (!getCvMat().empty() && !getCvMat().isDeepCopy())
			input.getCvMat().setTo(getCvMat());
		else
			getCvMatRef() = input.getCvMat();
	}
	else if (flags == STD_VECTOR || flags == VALUE)
	{
		getCvMat().setTo(input.getCvMat());
	}
	else if (flags == STD_VECTOR_VECTOR)
	{
		FOR_RANGE(i, 0, input.getSz().h)
			getCvMat(i).setTo(input.getCvMat(i));
	}
	else {
		THROW_INFO(ERR_INFO_TYPE);
	}
}
void lzh::_OutputArray::copyTo(InputArray input) const
{
	if (input.empty())return;
	if (flags == MAT || flags == STD_VECTOR) {
		setMatRef(input);
	}
	else {
		THROW_INFO(ERR_INFO_TYPE);
	}
}
void lzh::_OutputArray::operator=(InputArray input)const
{
	set(input);
}

bool lzh::operator>(InputArray a, InputArray b)
{
	return a.getCvMat() > b.getCvMat();
}
bool lzh::operator<(InputArray a, InputArray b)
{
	return a.getCvMat() < b.getCvMat();
}


/****************************************************************************
操作函数
*****************************************************************************/
mat_t lzh::FunOp::angle2radian(mat_t v)
{
	return v * ang2rad_;
}
mat_t lzh::FunOp::radian2angle(mat_t v)
{
	return v * rad2ang_;
}
mat_t lzh::FunOp::EuclideanDistance_2D(mat_t x, mat_t y)
{
	return sqrt(x * x + y * y);
}
mat_t lzh::FunOp::mul(mat_t x, mat_t y)
{
	return x * y;
}
mat_t lzh::FunOp::inv_mul(mat_t x, mat_t y)
{
	return x * -y;
}

/****************************************************************************
矩阵操作
*****************************************************************************/
void lzh::split(IMat src, int32 c, OutputArray dst)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	tools::check(src.cols(), src.rows(), src.channels());
	if (c > src.channels() - 1)
		THROW_INFO(ERR_INFO_MEMOUT);
	if (c < 0)
		THROW_INFO(ERR_INFO_MEMOUT);
#endif //MAT_DEBUG
	Mat mat(src.size());
	Val_ *p = mat;
	for (int32 i = 0; i < src.rows(); i++)
		for (int32 j = 0; j < src.cols(); j++) {
			*p = src(i, j, c);
			++p;
		}
	dst = mat;
}
void lzh::split(InputArray src_, OutputArrayOfArrays dst)
{
	Mat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	dst.create(src.channels(), src.depth());
	for (int32 c = 0; c < src.channels(); ++c) {
		dst.setMatRef(src.channel(c), c);
	}
}
void lzh::split(IMat src, Mat * dst)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	for (int32 c = 0; c < src.channels(); ++c)
		dst[c] = src.channel(c);
}
void lzh::split(const CvMat & src, CvMat * dst)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	for (int32 c = 0; c < src.channels(); ++c)
		dst[c] = src.channel(c);
}
void lzh::Reshape(IMat src, Size3 size, OutputArray dst)
{
	Mat out = src.clone();
	out.reshape(size);
	dst = out;
}
void lzh::merge(const Mat *src, int32 channels, OutputArray dst)
{
#ifdef MAT_DEBUG
	if (channels < 0)
		THROW_INFO(ERR_INFO_MEMOUT);
	if (src == nullptr)
		THROW_INFO(ERR_INFO_PTR);
	CHECK_MATRIX_(src[channels - 1]);
#endif //MAT_DEBUG
	Mat mat(src[0].cols(), src[0].rows(), channels);
	for (int32 z = 0; z < channels; z++)
		src[z].setTo(mat.channel(z));
	dst = mat;
}
void lzh::merge(InputArrayOfArrays src, OutputArray dst)
{
#ifdef MAT_DEBUG
	if (src.size() < 0)
		THROW_INFO(ERR_INFO_MEMOUT);
	if (src.empty())
		THROW_INFO(ERR_INFO_PTR);
#endif //MAT_DEBUG
	CvMat t = src.getCvMat(0);
	CvMat mat(t.cols, t.rows, src.size(), t.depth());
	for (int32 z = 0; z < src.size(); z++) {
		src.getCvMat(z).setTo(mat.channel(z));
	}
	dst.set(mat);
}
void lzh::merge(InputArrayOfArrays src, int32 channels, OutputArray dst)
{

#ifdef MAT_DEBUG
	if (src.size() < 0)
		THROW_INFO(ERR_INFO_MEMOUT);
	if (src.empty())
		THROW_INFO(ERR_INFO_PTR);
#endif //MAT_DEBUG
	CvMat t = src.getCvMat(0);
	CvMat mat(t.cols, t.rows, channels, t.depth());
	for (int32 z = 0; z < channels; z++) {
		src.getCvMat(z).setTo(mat.channel(z));
	}
	dst.set(mat);
}
OMat lzh::reverse(IMat m)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	if (!(m.cols() == 1 || m.rows() == 1))
		THROW_INFO(ERR_INFO_MEMOUT);
#endif //MAT_DEBUG
	Mat temp = m.clone();
	std::reverse(temp.begin(), temp.end());
	return temp;
}
void lzh::copyMakeBorder(IMat src, OutputArray dst, int32 top, int32 bottom, int32 left, int32 right, BorderTypes borderType, lzh::Val value)
{
	Size3 size = src.size3();
	size.h += (top + bottom);
	size.w += (left + right);
	Mat mat(size);
	switch (borderType)
	{
	case BORDER_CONSTANT: {
		for (int32 i = 0; i < top; i++) {
			for (int32 j = 0; j < mat.cols(); j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = value;
				}
			}
		}
		for (int32 i = 0; i < mat.rows(); i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = value;
				}
			}
		}
		for (int32 i = top + src.rows(); i < mat.rows(); i++) {
			for (int32 j = 0; j < mat.cols(); j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = value;
				}
			}
		}
		for (int32 i = 0; i < mat.rows(); i++) {
			for (int32 j = left + src.cols(); j < mat.cols(); j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = value;
				}
			}
		}
		break;
	}
	case BORDER_REPLICATE: {
		for (int32 i = 0; i < top; i++) {
			for (int32 j = left; j < mat.cols() - right; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(0, j - left, z);
				}
			}
		}
		for (int32 i = top; i < mat.rows() - bottom; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, 0, z);
				}
			}
		}
		for (int32 i = top + src.rows(); i < mat.rows(); i++) {
			for (int32 j = left; j < mat.cols() - right; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 1, j - left, z);
				}
			}
		}
		for (int32 i = top; i < mat.rows() - bottom; i++) {
			for (int32 j = left + src.cols(); j < mat.cols(); j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, src.cols() - 1, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(0, 0, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = mat.cols() - right; j < mat.cols(); j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(0, src.cols() - 1, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom; i < mat.rows(); i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 1, 0, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom; i < mat.rows(); i++) {
			for (int32 j = mat.cols() - right; j < mat.cols(); j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 1, src.cols() - 1, z);
				}
			}
		}
		break;
	}
	case BORDER_REFLECT: {
		bool more_once = false;
		int32 top_, left_, bottom_, right_;
		if (top >= src.rows())
		{
			more_once = true;
			top_ = top;
			top = src.rows();
		}
		if (bottom >= src.rows())
		{
			more_once = true;
			bottom_ = bottom;
			bottom = src.rows();
		}
		if (left >= src.cols())
		{
			more_once = true;
			left_ = left;
			left = src.cols();
		}
		if (right >= src.cols())
		{
			more_once = true;
			right_ = right;
			right = src.cols();
		}
		if (more_once) {
			size = src.size3();
			size.h += (top + bottom);
			size.w += (left + right);
			mat.create(size);
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = left; j < src.cols() + left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(top - i - 1, j - left, z);
				}
			}
		}
		for (int32 i = top; i < src.rows() + top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, left - j - 1, z);
				}
			}
		}
		for (int32 i = top + src.rows(), x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = left; j < src.cols() + left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 1 - x, j - left, z);
				}
			}
		}
		for (int32 i = top; i < src.rows() + top; i++) {
			for (int32 j = left + src.cols(), y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, src.cols() - 1 - y, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(top - i - 1, left - j - 1, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = mat.cols() - right, y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(top - i - 1, src.cols() - 1 - y, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom, x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 1 - x, left - j - 1, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom, x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = mat.cols() - right, y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 1 - x, src.cols() - 1 - y, z);
				}
			}
		}
		if (more_once) {
			copyMakeBorder(mat, mat, top_ - src.rows(), bottom_ - src.rows(), left_ - src.cols(), right_ - src.cols(), borderType);
			top = top_;
			bottom = bottom_;
			left = left_;
			right = right_;
		}
		break;
	}
	case BORDER_WRAP: {
		bool more_once = false;
		int32 top_, left_, bottom_, right_;
		if (top >= src.rows())
		{
			more_once = true;
			top_ = top;
			top = src.rows();
		}
		if (bottom >= src.rows())
		{
			more_once = true;
			bottom_ = bottom;
			bottom = src.rows();
		}
		if (left >= src.cols())
		{
			more_once = true;
			left_ = left;
			left = src.cols();
		}
		if (right >= src.cols())
		{
			more_once = true;
			right_ = right;
			right = src.cols();
		}
		if (more_once) {
			size = src.size3();
			size.h += (top + bottom);
			size.w += (left + right);
			mat.create(size);
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = left; j < src.cols() + left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i, j - left, z);
				}
			}
		}
		for (int32 i = top; i < src.rows() + top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, j, z);
				}
			}
		}
		for (int32 i = top + src.rows(), x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = left; j < src.cols() + left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(x, j - left, z);
				}
			}
		}
		for (int32 i = top; i < src.rows() + top; i++) {
			for (int32 j = left + src.cols(), y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, y, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i, j, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = mat.cols() - right, y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i, y, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom, x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(x, j, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom, x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = mat.cols() - right, y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(x, y, z);
				}
			}
		}
		if (more_once) {
			copyMakeBorder(mat, mat, top_ - src.rows(), bottom_ - src.rows(), left_ - src.cols(), right_ - src.cols(), borderType);
			top = top_;
			bottom = bottom_;
			left = left_;
			right = right_;
		}
		break;
	}
	case BORDER_REFLECT_101: {
		bool more_once = false;
		int32 top_, left_, bottom_, right_;
		if (top >= src.rows() - 1)
		{
			more_once = true;
			top_ = top;
			top = src.rows() - 1;
		}
		if (bottom >= src.rows() - 1)
		{
			more_once = true;
			bottom_ = bottom;
			bottom = src.rows() - 1;
		}
		if (left >= src.cols() - 1)
		{
			more_once = true;
			left_ = left;
			left = src.cols() - 1;
		}
		if (right >= src.cols() - 1)
		{
			more_once = true;
			right_ = right;
			right = src.cols() - 1;
		}
		if (more_once) {
			size = src.size3();
			size.h += (top + bottom);
			size.w += (left + right);
			mat.create(size);
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = left; j < src.cols() + left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(top - i, j - left, z);
				}
			}
		}
		for (int32 i = top; i < src.rows() + top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, left - j, z);
				}
			}
		}
		for (int32 i = top + src.rows(), x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = left; j < src.cols() + left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 2 - x, j - left, z);
				}
			}
		}
		for (int32 i = top; i < src.rows() + top; i++) {
			for (int32 j = left + src.cols(), y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(i - top, src.cols() - 2 - y, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(top - i, left - j, z);
				}
			}
		}
		for (int32 i = 0; i < top; i++) {
			for (int32 j = mat.cols() - right, y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(top - i, src.cols() - 2 - y, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom, x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = 0; j < left; j++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 2 - x, left - j, z);
				}
			}
		}
		for (int32 i = mat.rows() - bottom, x = 0; i < mat.rows(); i++, x++) {
			for (int32 j = mat.cols() - right, y = 0; j < mat.cols(); j++, y++) {
				for (int32 z = 0; z < mat.channels(); z++) {
					mat(i, j, z) = src(src.rows() - 2 - x, src.cols() - 2 - y, z);
				}
			}
		}
		if (more_once) {
			copyMakeBorder(mat, mat, top_ - src.rows(), bottom_ - src.rows(), left_ - src.cols(), right_ - src.cols(), borderType);
			top = top_;
			bottom = bottom_;
			left = left_;
			right = right_;
		}
		break;
	}
							 //case BORDER_TRANSPARENT:
							 //	break;
							 //case BORDER_ISOLATED:
							 //	break;
	default:
		break;
	}
	for (int32 i = 0; i < src.rows(); i++) {
		for (int32 j = 0; j < src.cols(); j++) {
			for (int32 z = 0; z < src.channels(); z++) {
				mat(i + top, j + left, z) = src(i, j, z);
			}
		}
	}
	dst = mat;
}
void lzh::Block(IMat src, OutputArray dst, int32 Row_Start, int32 Row_End, int32 Col_Start, int32 Col_End, int32 Chennel_Start, int32 Chennel_End)
{
	Mat a = src;
	int32 h = Row_End - Row_Start + 1;
	int32 w = Col_End - Col_Start + 1;
	int32 c = Chennel_End - Chennel_Start + 1;
	tools::check(w, h, c);
	Mat mark(w, h, c);
	int32 i = 0;
	for (int32 y = Row_Start, j = 0; y <= Row_End; y++, j++)
		for (int32 x = Col_Start, i = 0; x <= Col_End; x++, i++)
			for (int32 z = Chennel_Start, k = 0; z <= Chennel_End; z++, k++)
				mark(j, i, k) = a(y, x, z);
	dst = mark;
}


/****************************************************************************
矩阵数学工具
*****************************************************************************/
mat_t lzh::Max(IMat src, bool isAbs)
{
	return src.Max(isAbs);
}
mat_t lzh::Min(IMat src, bool isAbs)
{
	return src.Min(isAbs);
}
mat_t lzh::median(IMat src)
{
	Mat mat = src;
	mat_t *pnData = mat;
	int32 knLength = mat.len();
	int32 nLow = 0;
	int32 nHigh = 0;
	int32 nMiddle = 0;
	int32 nMedian = 0;
	int32 nLTmp = 0;
	int32 nHTmp = 0;
	nMedian = (knLength - 1) >> 1;
	nHigh = knLength - 1;
	while (1)
	{
		if (nHigh == nLow)
		{
			return pnData[nHigh];
		}
		if (nHigh == nLow + 1)
		{
			return pnData[nHigh] > pnData[nLow] ? pnData[nLow] : pnData[nHigh];
		}
		nMiddle = (nHigh + nLow) >> 1;
		if (pnData[nLow] > pnData[nHigh])
		{
			std::swap(pnData[nHigh], pnData[nLow]);
		}
		if (pnData[nMiddle] > pnData[nHigh])
		{
			std::swap(pnData[nMiddle], pnData[nHigh]);
		}
		if (pnData[nMiddle] > pnData[nLow])
		{
			std::swap(pnData[nMiddle], pnData[nLow]);
		}
		std::swap(pnData[nMiddle], pnData[nLow + 1]);
		nLTmp = nLow + 2;
		nHTmp = nHigh - 1;
		while (1)
		{
			while (pnData[nLTmp] < pnData[nLow])
			{
				nLTmp++;
			}
			while (pnData[nHTmp] > pnData[nLow])
			{
				nHTmp--;
			}
			if (nLTmp > nHTmp)
			{
				std::swap(pnData[nHTmp], pnData[nLow]);
				if (nHTmp > nMedian)
				{
					nHigh = nHTmp - 1;
				}
				else
				{
					nLow = nLTmp - 1;
				}
				break;
			}
			else
			{
				std::swap(pnData[nLTmp], pnData[nHTmp]);
				nLTmp++;
				nHTmp--;
			}
		}
	}
}
mat_t lzh::Dist(IMat a, IMat b, int32 num)
{
	return (a - b).norm(num);
}
OMat lzh::Operator(IMat src, mat_t(*op)(mat_t))
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif // MAT_DEBUG
	Mat dst(src.size3());
	Val_* m = dst;
	FOR_RANGE(i, 0, src.rows()) {
		FOR_RANGE(j, 0, src.cols()) {
			FOR_RANGE(k, 0, src.channels()) {
				*m = op(src(i, j, k));
				m++;
			}
		}
	}
	return dst;
}
OMat lzh::Operator(IMat m1, IMat m2, mat_t(*op)(mat_t, mat_t))
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m1);
	CHECK_MATRIX_(m2);
	if (m1.size3() != m2.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	Mat dst(m1.size3());
	Val_* m = dst;
	FOR_RANGE(i, 0, m1.rows()) {
		FOR_RANGE(j, 0, m1.cols()) {
			FOR_RANGE(k, 0, m1.channels()) {
				*m = op(m1(i, j, k), m2(i, j, k));
				m++;
			}
		}
	}
	return dst;
}
void lzh::Bitwise_not(InputOutputArray m, int32 depth)
{
	CvMat mat = m.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif // MAT_DEBUG
	switch (depth)
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, int8(~((int8)Round(mat(i))))); }	break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, uint8(~((uint8)Round(mat(i))))); }	break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, int16(~((int16)Round(mat(i))))); }	break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, uint16(~((uint16)Round(mat(i))))); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, int32(~((int32)Round(mat(i))))); }	break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, uint32(~((uint32)Round(mat(i))))); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, int64(~((int64)Round(mat(i))))); }	break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, mat.len()) { mat.set(i, uint64(~((uint64)Round(mat(i))))); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
OMat lzh::Bitwise_not(IMat mat, int32 depth)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif // MAT_DEBUG
	Mat dst = mat.clone();
	Bitwise_not(dst, depth);
	return dst;
}
void lzh::Bitwise_and(InputOutputArray m, IMat m2, int32 depth)
{
	Mat m1 = m.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_MATRIX_(m2);
	if (m1.size3() != m2.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	switch (depth)
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int8(((int8)Round(m1(i)))	& ((int8)Round(m2(i))))); }	break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint8(((uint8)Round(m1(i)))	& ((uint8)Round(m2(i))))); }	break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int16(((int16)Round(m1(i)))	& ((int16)Round(m2(i))))); }	break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint16(((uint16)Round(m1(i)))& ((uint16)Round(m2(i))))); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int32(((int32)Round(m1(i)))	& ((int32)Round(m2(i))))); }	break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint32(((uint32)Round(m1(i)))& ((uint32)Round(m2(i))))); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int64(((int64)Round(m1(i)))	& ((int64)Round(m2(i))))); }	break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint64(((uint64)Round(m1(i)))& ((uint64)Round(m2(i))))); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
void lzh::Bitwise_and(InputOutputArray m, Val b)
{
	Mat a = m.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	switch (b.type)
	{
	case lzh::TP_8S: {int8		t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int8(((int8)Round(a(i)))	 & t)); }break; }
	case lzh::TP_8U: {uint8	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint8(((uint8)Round(a(i)))	 & t)); }break; }
	case lzh::TP_16S: {int16	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int16(((int16)Round(a(i)))	 & t)); }break; }
	case lzh::TP_16U: {uint16	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint16(((uint16)Round(a(i)))& t)); }break; }
	case lzh::TP_32S: {int32	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int32(((int32)Round(a(i)))	 & t)); }break; }
	case lzh::TP_32U: {uint32	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint32(((uint32)Round(a(i)))& t)); }break; }
	case lzh::TP_64S: {int64	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int64(((int64)Round(a(i)))	 & t)); }break; }
	case lzh::TP_64U: {uint64	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint64(((uint64)Round(a(i)))& t)); }break; }
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
OMat lzh::Bitwise_and(IMat m1, IMat m2, int32 depth)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m1);
	CHECK_MATRIX_(m2);
	if (m1.size3() != m2.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	Mat dst = m1.clone();
	Bitwise_and(dst, m2, depth);
	return dst;
}
OMat lzh::Bitwise_and(IMat a, Val b)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	Mat dst = a.clone();
	Bitwise_and(dst, b);
	return dst;
}
void lzh::Bitwise_or(InputOutputArray m, Val b)
{
	Mat a = m.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	switch (b.type)
	{
	case lzh::TP_8S: {int8		t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int8(((int8)Round(a(i))) | t)); }	break; }
	case lzh::TP_8U: {uint8	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint8(((uint8)Round(a(i))) | t)); }	break; }
	case lzh::TP_16S: {int16	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int16(((int16)Round(a(i))) | t)); }	break; }
	case lzh::TP_16U: {uint16	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint16(((uint16)Round(a(i))) | t)); }	break; }
	case lzh::TP_32S: {int32	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int32(((int32)Round(a(i))) | t)); }	break; }
	case lzh::TP_32U: {uint32	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint32(((uint32)Round(a(i))) | t)); }	break; }
	case lzh::TP_64S: {int64	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(int64(((int64)Round(a(i))) | t)); }	break; }
	case lzh::TP_64U: {uint64	t = Round(b);	FOR_RANGE(i, 0, a.len()) { a(i) = _T(uint64(((uint64)Round(a(i))) | t)); }	break; }
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
void lzh::Bitwise_or(InputOutputArray m, IMat m2, int32 depth)
{
	Mat m1 = m.getMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m1);
	CHECK_MATRIX_(m2);
	if (m1.size3() != m2.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	switch (depth)
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int8(((int8)Round(m1(i))) | ((int8)Round(m2(i))))); }	break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint8(((uint8)Round(m1(i))) | ((uint8)Round(m2(i))))); }	break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int16(((int16)Round(m1(i))) | ((int16)Round(m2(i))))); }	break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint16(((uint16)Round(m1(i))) | ((uint16)Round(m2(i))))); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int32(((int32)Round(m1(i))) | ((int32)Round(m2(i))))); }	break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint32(((uint32)Round(m1(i))) | ((uint32)Round(m2(i))))); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(int64(((int64)Round(m1(i))) | ((int64)Round(m2(i))))); }	break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, m1.len()) { m1(i) = _T(uint64(((uint64)Round(m1(i))) | ((uint64)Round(m2(i))))); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
OMat lzh::Bitwise_or(IMat m1, IMat m2, int32 depth)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m1);
	CHECK_MATRIX_(m2);
	if (m1.size3() != m2.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	Mat dst = m1.clone();
	Bitwise_or(dst, m2, depth);
	return dst;
}
OMat lzh::Bitwise_or(IMat a, Val b)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	Mat dst = a.clone();
	Bitwise_or(dst, b);
	return dst;
}
OMat lzh::Cos(IMat src)
{
	return Operator(src, cos);
}
OMat lzh::Cosh(IMat src)
{
	return Operator(src, cosh);
}
OMat lzh::Sin(IMat src)
{
	return Operator(src, sin);
}
OMat lzh::Sinh(IMat src)
{
	return Operator(src, sinh);
}
OMat lzh::Tan(IMat src)
{
	return Operator(src, tan);
}
OMat lzh::Tanh(IMat src)
{
	return Operator(src, tanh);
}
OMat lzh::arcCos(IMat src)
{
	return Operator(src, acos);
}
OMat lzh::arcCosh(IMat src)
{
	return Operator(src, acosh);
}
OMat lzh::arcSin(IMat src)
{
	return Operator(src, asin);
}
OMat lzh::arcSinh(IMat src)
{
	return Operator(src, asinh);
}
OMat lzh::arcTan(IMat src)
{
	return Operator(src, atan);
}
OMat lzh::arcTanh(IMat src)
{
	return Operator(src, atanh);
}
OMat lzh::arcTan2(IMat y, IMat x)
{
	return Operator(y, x, atan2);
}
OMat lzh::Radian2Angle(IMat radian)
{
	return Operator(radian, FunOp::radian2angle);
}
OMat lzh::Angle2Radian(IMat angle)
{
	return Operator(angle, FunOp::angle2radian);
}
void lzh::Abs(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	dst.set(Operator(mat, abs));
	//Mat m(mat.size3());
	//Val_ *p = m;
	//for (int32 ind = 0; ind < mat.len(); ind++)
	//	p[ind] = std::abs(mat(ind));
	//dst.set(m);
}
void lzh::fftMult(IMat a, IMat b, OutputArray dst)
{
	Mat v1 = a;
	Mat v2 = b;
	Mat a_, a1, a2;
	a1 = fft1D(v1);
	a2 = fft1D(v2);
	complexDot(a1, a2, a_);
	a_ = ifft1D(a_);
	a_ = a_.channel(0).clone();
	int32 top = 0;
	FORINT(i, a_.len() - 1, 0, -1) {
		if (!a_.isZero(i, _T(0.1))) {
			top = i;
			break;
		}
	}
	Mat result(top + 1);
	result(top) = 0;
	a_.colRange(0, top).setTo(result);
	FOR_RANGE(i, 0, top) {
		result(i + 1) += Round(result(i)) / 10;
		result(i) = _T(mod(result(i), 10));
	}
	dst.set(result);
}
const LargeNumber lzh::fftMult(const LargeNumber & a, const LargeNumber & b)
{
	vec_32f vec_a(a.size());
	vec_32f vec_b(b.size());
	FOR_RANGE(i, 0, a.size())
		vec_a[i] = float32(a[a.size() - 1 - i]);
	FOR_RANGE(i, 0, b.size())
		vec_b[i] = float32(b[b.size() - 1 - i]);
	int32 l1 = (int32)vec_a.size(),
		l2 = (int32)vec_b.size(), l;
	l = 1;
	while (l < l1 * 2 || l < l2 * 2)   l <<= 1;
	FOR_RANGE_(l1, l) {
		vec_a.push_back(0);
	}
	FOR_RANGE_(l2, l) {
		vec_b.push_back(0);
	}
	Mat result;
	fftMult(vec_a, vec_b, result);
	int32 top = result.len() - 1;
	LargeNumber val;
	int32 v = (int32)result(top);
	while (v) {
		val.push_back(v % 10);
		v /= 10;
	}
	reverse(val.begin(), val.end());
	FOR_RANGE(i, 1, top + 1) {
		val.push_back((int32)result(top - i));
	}
	return val;
}
void lzh::complexDot(IMat m1, IMat m2, OutputArray dst)
{
	Mat a = m1;
	Mat b = m2;
	Mat m(a.size3());
	Val_* p = m;
	if (a.rows() == 1)
		for (int32 i = 0; i < a.len() / 2; i++) {
			p[0] = a(0, i, 0) * b(0, i, 0) - a(0, i, 1) * b(0, i, 1);
			p[1] = a(0, i, 0) * b(0, i, 1) + a(0, i, 1) * b(0, i, 0);
			p += 2;
		}
	else
		for (int32 i = 0; i < a.len() / 2; i++) {
			p[0] = a(i, 0, 0) * b(i, 0, 0) - a(i, 0, 1) * b(i, 0, 1);
			p[1] = a(i, 0, 0) * b(i, 0, 1) + a(i, 0, 1) * b(i, 0, 0);
			p += 2;
		}
	dst.set(m);
}
void lzh::brc(InputOutputArray src)
{
	Mat y = src.getMat();
	bool dir = y.cols() > y.rows();
	int32 l = dir ? y.cols() : y.rows();
	int32 k;
	Val_ *p = y;
	for (int32 i = 1, j = l / 2; i < l - 1; i++)
	{
		if (i < j) {
			Val_ *vi = p + (dir ? i * y.step()[1] : i * y.step().size());
			Val_ *vj = p + (dir ? j * y.step()[1] : j * y.step().size());
			__swap(vi[0], vj[0]);
			__swap(vi[1], vj[1]);
		}
		// i<j保证只交换一次
		k = l / 2;
		while (j >= k) // 由最高位检索，遇1变0，遇0变1，跳出
		{
			j -= k;
			k >>= 1;
		}
		if (j < k)	j += k;
	}
}
void lzh::phase(IMat x, IMat y, OutputArray angle, bool angleInDegrees)
{
	Mat dst = arcTan2(x, y);
	angle.set(angleInDegrees ? Radian2Angle(dst) : dst);
}
void lzh::magnitude(IMat x, IMat y, OutputArray magnitude)
{
	Mat x1 = x;
	Mat y1 = y;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x1);
	CHECK_MATRIX_(y1);
#endif //MAT_DEBUG
	magnitude.set(Operator(x1, y1, FunOp::EuclideanDistance_2D));
}
void lzh::mulSpectrums(IMat a, IMat b, OutputArray c, bool conjB)
{
	Mat x = a;
	Mat y = b;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x);
	CHECK_MATRIX_(y);
#endif //MAT_DEBUG
	c.set(conjB ? Operator(x, y, FunOp::inv_mul) : Operator(x, y, FunOp::mul));
}
void lzh::Max(Val a, IMat m, OutputArray dst)
{
	Mat b = m;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(b);
#endif //MAT_DEBUG
	Mat mark(b.size3());
	Val_* p = mark;
	for (int32 ind = 0; ind < b.len(); ind++)
		p[ind] = a > b(ind) ? a.v : b(ind);
	dst.set(mark);
}
void lzh::Max(IMat m1, IMat m2, OutputArray dst)
{
	Mat a = m1;
	Mat b = m2;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(b);
	if (a.rows() != b.rows() || a.cols() != b.cols() || a.channels() != b.channels())
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	Mat mark(b.size3());
	Val_* p = mark;
	for (int32 ind = 0; ind < b.len(); ind++)
		p[ind] = a(ind) > b(ind) ? a(ind) : b(ind);
	dst.set(mark);
}
void lzh::Min(Val a, IMat m, OutputArray dst)
{
	Mat b = m;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(b);
#endif //MAT_DEBUG
	Mat mark(b.size3());
	Val_* p = mark;
	for (int32 ind = 0; ind < b.len(); ind++)
		p[ind] = a < b(ind) ? a.v : b(ind);
	dst.set(mark);
}
void lzh::Min(IMat m1, IMat m2, OutputArray dst)
{
	Mat a = m1;
	Mat b = m2;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(b);
	if (a.rows() != b.rows() || a.cols() != b.cols() || a.channels() != b.channels())
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	Mat mark(b.size3());
	Val_* p = mark;
	for (int32 ind = 0; ind < b.len(); ind++)
		p[ind] = a(ind) < b(ind) ? a(ind) : b(ind);
	dst.set(mark);
}


/****************************************************************************
数值运算
*****************************************************************************/
void lzh::LeastSquare(IMat x_, IMat y_, OutputArray out, Mat *r)
{
	Mat x = x_;
	Mat y = y_;
	Mat a = ((x.t()*x).inv()*x.t()*y).t();
	if (r)*r = y - a * x;
	out.set(a);
}
void lzh::regress(IMat x_, IMat y_, OutputArray out, Mat *r)
{
	Mat x = x_;
	Mat y = y_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x);
	CHECK_MATRIX_(y);
	CHECK_EXCEPTION(if (x.rows() != y.rows()), THROW_INFO(ERR_INFO_SIZE));
#endif //MAT_DEBUG
	LeastSquare(x.addones(RIGHT), y, out, r);
}
void lzh::polyfit(IMat x_, IMat y_, uint32 n, OutputArray out, Mat *r)
{
	Mat x = x_;
	Mat y = y_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x);
	CHECK_MATRIX_(y);
	CHECK_EXCEPTION(if (x.rows() != y.rows()), THROW_INFO(ERR_INFO_SIZE));
#endif //MAT_DEBUG
	Mat param(n + 1, x.rows());
	for (uint32 idx = n, i = 0; idx > 0; idx--, i++)
		x.pow((mat_t)idx).setTo(param.col(i));
	Mat::ones(1, x.rows()).setTo(param.col(n));
	LeastSquare(param, y, out, r);
}
void lzh::fitEllipse(IMat x, IMat y, OutputArray ellipse, Mat * r)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x);
	CHECK_MATRIX_(y);
	CHECK_EXCEPTION(if (x.rows() != y.rows()), THROW_INFO(ERR_INFO_SIZE));
#endif //MAT_DEBUG
	Mat param(4, x.rows());
	Mat out = y.pow(2);
	int32 idx = 0;
	x.pow(2).setTo(param.col(idx++));
	x.setTo(param.col(idx++));
	y.setTo(param.col(idx++));
	Mat::ones(1, x.rows()).setTo(param.col(idx++));
	Mat res;
	LeastSquare(x, y, res, r);
	Mat vec(4, 1);
	vec[0] = -2 * res(1) / res(0); vec[1] = res(2) / _T(2);
	mat_t t = (-res(3) - vec[1] * vec[1] + res(0) * vec[0] * vec[0]) / res(0);
	vec[2] = sqrt(t); vec[3] = -res(0) * t;
	ellipse.set(vec);
}
void lzh::fitCircle(IMat p_, OutputArray circle, Mat *r)
{
	Mat p = p_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(p);
#endif //MAT_DEBUG
	Mat y = Mat::zeros(1, p.rows());
	Mat x = Mat::zeros(p.cols() + 1, p.rows());
	for (int32 w = 0; w < p.cols(); ++w)
	{
		y += p.col(w).pow(2);
		p.col(w).setTo(x.col(w));
	}
	Mat::ones(1, p.rows()).setTo(x.col(p.cols()));
	Mat res;
	LeastSquare(x, y, res, r);
	res(0) /= 2; res(1) /= 2; res(2) = sqrt(res(2) + pow(res(0), 2) + pow(res(1), 2));
	circle.set(res);
}
void lzh::fitCircle(IMat x_, IMat y_, OutputArray circle, Mat * r)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x_);
	CHECK_MATRIX_(y_);
	CHECK_EXCEPTION(if (x_.rows() != y_.rows()), THROW_INFO(ERR_INFO_SIZE));
#endif //MAT_DEBUG
	int32 size = x_.len();
	Mat y = (x_ ^ 2) + (y_ ^ 2);
	Mat x(3, size);
	int32 idx = 0;
	x_.setTo(x.col(idx++));
	y_.setTo(x.col(idx++));
	Mat::ones(1, size).setTo(x.col(idx++));
	Mat res;
	LeastSquare(x, y, res, r);
	res(0) /= 2; res(1) /= 2; res(2) = sqrt(res(2) + pow(res(0), 2) + pow(res(1), 2));
	circle.set(res);
}
void lzh::fitSphere(IMat x, IMat y, IMat z, OutputArray sphere, Mat * r)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(x);
	CHECK_MATRIX_(y);
	CHECK_MATRIX_(z);
	CHECK_EXCEPTION(if (x.size() == y.size() && y.size() == z.size() && x.size() == z.size()), THROW_INFO(ERR_INFO_SIZE));
#endif //MAT_DEBUG
	int32 size = x.len();
	Mat expect = x.pow(2) + y.pow(2) + z.pow(2);
	Mat param(4, size);
	int32 idx = 0;
	x.setTo(param.col(idx++));
	y.setTo(param.col(idx++));
	z.setTo(param.col(idx++));
	Mat::ones(1, size).setTo(param.col(idx++));
	Mat res;
	LeastSquare(param, expect, res, r);
	res(0) /= 2; res(1) /= 2; res(2) /= 2; res(3) = sqrt(res(2) + pow(res(0), 2) + pow(res(1), 2) + pow(res(2), 2));
	sphere.set(res);
}
void lzh::polynomial(IMat a_, IMat x_, OutputArray y_)
{
	Mat a = a_;
	Mat x = x_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(x);
#endif //MAT_DEBUG
	Mat y = Mat::zeros(x.size3());
	for (int32 idx = 0, power = a.len() - 1; idx < a.len(); ++idx, --power)
	{
		y += a(idx)*x.pow(_T(power));
	}
	y_.set(y);
}
void lzh::NonLinearLeastSqures(IMat x_, IMat y_, IMat a0_, OutputArray out, F f, Mat *r, Val stride, Val error)
{
	Mat x = x_;
	Mat y = y_;
	Mat a0 = a0_;
#ifdef MAT_DEBUG
	CHECK_PTR(f);
	CHECK_MATRIX_(x);
	CHECK_MATRIX_(y);
	CHECK_MATRIX_(a0);
#endif //MAT_DEBUG
	Mat a = a0;
	Mat da = a;
	while (da.norm() > error) {
		try {
			Mat p;
			NumericGradient(a, x, f, p, _T(1e-3));
			Mat q = f(a, x) - y;
			Mat deta;
			LeastSquare(p, q, deta);
			da = stride * deta;
			a = a - da;
		}
		catch (std::exception e)
		{
			std::cout << "拟合失败!" << std::endl;
			break;
		}
	}
	if (r)*r = y - f(a, x);
	out.set(a);
}
void lzh::gradient(IMat y_, OutputArray grad, IMat x_)
{
	Mat y = y_;
	Mat x = x_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(y);
#endif //MAT_DEBUG
	int32 dim = y.dims();
	Mat df(y.cols(), y.rows(), dim*y.channels());
	for (int32 c = 0; c < y.channels(); ++c) {
		if (x.empty()) {
			if (y.dims() >= 2) {
				for (int32 row = 0; row < y.rows(); ++row)
					for (int32 col = 0; col < y.cols(); ++col)
						if (col == 0) {
							df(row, col, dim*c) = y(row, col + 1, c) - y(row, col, c);
						}
						else if (col == y.cols() - 1) {
							df(row, col, dim*c) = y(row, col, c) - y(row, col - 1, c);
						}
						else {
							df(row, col, dim*c) = ((y(row, col + 1, c) - y(row, col, c)) + (y(row, col, c) - y(row, col - 1, c))) / _T(2.0);
						}
				for (int32 row = 0; row < y.rows(); ++row)
					for (int32 col = 0; col < y.cols(); ++col)
						if (row == 0) {
							df(row, col, dim*c + 1) = y(row + 1, col, c) - y(row, col, c);
						}
						else if (row == y.rows() - 1) {
							df(row, col, dim*c + 1) = y(row, col, c) - y(row - 1, col, c);
						}
						else {
							df(row, col, dim*c + 1) = ((y(row + 1, col, c) - y(row, col, c)) + (y(row, col, c) - y(row - 1, col, c))) / _T(2.0);
						}
			}
			else {
				for (int32 idx = 0; idx < y.len(); ++idx)
					if (idx == 0) {
						df(idx) = y(idx + 1) - y(idx);
					}
					else if (idx == y.len() - 1) {
						df(idx) = y(idx) - y(idx - 1);
					}
					else {
						df(idx) = ((y(idx + 1) - y(idx)) + (y(idx) - y(idx - 1))) / _T(2.0);
					}
			}
		}
		else {
			if (y.dims() >= 2) {
				for (int32 row = 0; row < y.rows(); ++row)
					for (int32 col = 0; col < y.cols(); ++col)
						if (col == 0) {
							df(row, col, dim*c) = (y(row, col + 1, c) - y(row, col, c)) / (x(row, col + 1, c) - x(row, col, c));
						}
						else if (col == y.cols() - 1) {
							df(row, col, dim*c) = (y(row, col, c) - y(row, col - 1, c)) / (x(row, col, c) - x(row, col - 1, c));
						}
						else {
							df(row, col, dim*c) = ((y(row, col + 1, c) - y(row, col, c)) + (y(row, col, c) - y(row, col - 1, c)) / ((x(row, col + 1, c) - x(row, col, c)) + (x(row, col, c) - x(row, col - 1, c))));
						}
				for (int32 row = 0; row < y.rows(); ++row)
					for (int32 col = 0; col < y.cols(); ++col)
						if (row == 0) {
							df(row, col, dim*c + 1) = (y(row + 1, col, c) - y(row, col, c)) / (x(row + 1, col, c) - x(row, col, c));
						}
						else if (row == y.rows() - 1) {
							df(row, col, dim*c + 1) = (y(row, col, c) - y(row - 1, col, c)) / (x(row, col, c) - x(row - 1, col, c));
						}
						else {
							df(row, col, dim*c + 1) = ((y(row + 1, col, c) - y(row, col, c)) + (y(row, col, c) - y(row - 1, col, c)) / ((x(row, col + 1, c) - x(row, col, c)) + (x(row, col, c) - x(row, col - 1, c))));
						}
			}
			else {
				for (int32 idx = 0; idx < y.len(); ++idx)
					if (idx == 0) {
						df(idx) = (y(idx + 1) - y(idx)) / (x(idx + 1) - x(idx));
					}
					else if (idx == y.len() - 1) {
						df(idx) = (y(idx) - y(idx - 1)) / (x(idx) - x(idx - 1));
					}
					else {
						df(idx) = ((y(idx + 1) - y(idx)) + (y(idx) - y(idx - 1))) / ((x(idx + 1) - x(idx)) + (x(idx) - x(idx - 1)));
					}
			}
		}
	}
	grad.set(df);
}
mat_t lzh::NumericGradient(NF f, Val x, Val epsilon)
{
#ifdef MAT_DEBUG
	CHECK_PTR(f);
#endif //MAT_DEBUG
	mat_t tmp1 = x;
	mat_t tmp2 = x;
	tmp1 = tmp1 + epsilon;
	tmp2 = tmp2 - epsilon;
	return (f(tmp1) - f(tmp2)) / (_T(2) * epsilon);
}
void lzh::NumericGradient(IMat x_, Fun f, OutputArray grad, Val epsilon)
{
	Mat x = x_;
#ifdef MAT_DEBUG
	CHECK_PTR(f);
#endif //MAT_DEBUG
	int32 n = x.len();
	Mat numgrad = Mat::zeros(n, 1);
	for (int32 i = 0; i < n; ++i) {
		Mat tmp1 = x.clone();
		Mat tmp2 = x.clone();
		tmp1(i) += epsilon;
		tmp2(i) -= epsilon;
		numgrad(i) = (f(tmp1) - f(tmp2)) / (_T(2) * epsilon);
	}
	grad.set(numgrad);
}
void lzh::NumericGradient(IMat a_, IMat x_, F f, OutputArray grad, Val epsilon)
{
	Mat x = x_;
	Mat a = x_;
#ifdef MAT_DEBUG
	CHECK_PTR(f);
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(x);
#endif //MAT_DEBUG
	int32 n = a.len();
	Mat numgrad = Mat::zeros(n, x.rows());
	for (int32 i = 0; i < n; ++i) {
		Mat tmp1 = a.clone();
		Mat tmp2 = a.clone();
		tmp1(i) += epsilon;
		tmp2(i) -= epsilon;
		((f(tmp1, x) - f(tmp2, x)) / (_T(2) * epsilon)).setTo(numgrad.col(i));
	}
	grad.set(numgrad);
}
mat_t lzh::EulerInt(NF f, Val low, Val high, Val epsilon)
{
#ifdef MAT_DEBUG
	CHECK_PTR(f);
#endif //MAT_DEBUG
	mat_t y = 0;
	for (mat_t x = low; x <= high; x += epsilon)
	{
		y += f(x) * epsilon;
	}
	return y;
}
mat_t lzh::TrapezoidInt(NF f, Val low, Val high, Val epsilon)
{
#ifdef MAT_DEBUG
	CHECK_PTR(f);
#endif //MAT_DEBUG
	mat_t y = 0;
	for (mat_t x = low; x <= high; x += epsilon)
	{
		y += _T(0.5) * epsilon * (f(x) + f(x + epsilon));
	}
	return y;
}
mat_t lzh::RungeKuttaInt(NF f, Val low, Val high, Val epsilon)
{
#ifdef MAT_DEBUG
	CHECK_PTR(f);
#endif //MAT_DEBUG	
	mat_t y = 0;
	for (mat_t x = low; x <= high; x += epsilon)
	{
		mat_t k1 = f(x);
		mat_t k2 = f(x + _T(0.5)*epsilon);
		mat_t k3 = f(x + _T(0.5)*epsilon);
		mat_t k4 = f(x + epsilon);
		y += epsilon * (k1 + 2 * k2 + 2 * k3 + k4) / _T(6);
	}
	return y;
}
Vec2m lzh::SolveLinear(const Point2m & p1, const Point2m & p2)
{
	Vec2m m;
	m[0] = tools::saveDiv(p1.y - p2.y, p1.x - p2.x);
	m[1] = p1.y - p1.x*m[0];
	return m;
}
Point2m lzh::LinearIntersection(const Vec2m & line1, const Vec2m & line2)
{
	Point2m p;
	p.x = tools::saveDiv(line1[1] - line2[1], line2[0] - line1[0]);
	p.y = p.x*line1[0] + line1[1];
	return p;
}
Point2m lzh::LinearIntersection(Val a1, Val b1, Val a2, Val b2)
{
	Point2m p;
	p.x = tools::saveDiv((b1 - b2), (a2 - a1));
	p.y = p.x*a1 + b1;
	return p;
}


/****************************************************************************
图像运算
*****************************************************************************/
lzh::Size3 lzh::CalSize(Size3 src, Size3 kern, Point anchor, Size strides, int32 & top, int32 & bottom, int32 & left, int32 & right)
{
	int32 kern_row = kern.h;
	int32 kern_col = kern.w;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	top = anchor.x;
	bottom = kern_row - anchor.x - 1;
	left = anchor.y;
	right = kern_col - anchor.y - 1;
	return Size3(Round(_T(src.w - kern_col + 1) / _T(strides.w)), Round(_T(src.h - kern_row + 1) / _T(strides.h)), kern.c / src.c);
}
lzh::Size3 lzh::CalSize(Size3 src, Size3 kern, Point anchor, Size strides)
{
	int32 kern_row = kern.h;
	int32 kern_col = kern.w;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	return Size3(int32(_T(src.w - kern_col + 1) / _T(strides.w) + 0.5f), int32(_T(src.h - kern_row + 1) / _T(strides.h) + 0.5f), kern.c / src.c);
}
lzh::Size3 lzh::CalSize(Size3 src, Size kern, Point anchor, Size strides)
{
	int32 kern_row = kern.h;
	int32 kern_col = kern.w;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	return Size3(int32(_T(src.w - kern_col + 1) / _T(strides.w) + 0.5f), int32(_T(src.h - kern_row + 1) / _T(strides.h) + 0.5f), src.c);
}
OMat lzh::GaussianKernel(Size ksize, Val sigma)
{
	Mat kernel(ksize);
	Val_ *k = kernel;
	FOR_RANGE(i, -ksize.h / 2, ksize.h / 2 + ksize.h % 2) {
		FOR_RANGE(j, -ksize.w / 2, ksize.w / 2 + ksize.w % 2) {
			*k = generateGaussian(_T(i), _T(j), sigma);
			k++;
		}
	}
	normalize(kernel, kernel, 1, 0, NORM_SUM);
	return kernel;
}
OMat lzh::LoGKernel(Size ksize, Val sigma)
{
	Mat kernel(ksize);
	Val_ *k = kernel;
	FOR_RANGE(i, -ksize.h / 2, ksize.h / 2 + ksize.h % 2) {
		FOR_RANGE(j, -ksize.w / 2, ksize.w / 2 + ksize.w % 2) {
			*k = generateLoG(_T(i), _T(j), sigma);
			k++;
		}
	}
	normalize(kernel, kernel, 0, 1, NORM_ZSCORE);
	return kernel;
}
OMat lzh::DoGKernel(Size ksize, Val sigma1, Val sigma2)
{
	Mat kernel(ksize);
	Val_ *k = kernel;
	FOR_RANGE(i, -ksize.h / 2, ksize.h / 2 + ksize.h % 2) {
		FOR_RANGE(j, -ksize.w / 2, ksize.w / 2 + ksize.w % 2) {
			*k = generateDoG(_T(i), _T(j), sigma1, sigma2);
			k++;
		}
	}
	normalize(kernel, kernel, 0, 1, NORM_ZSCORE);
	return kernel;
}
OMat lzh::SharpenKernel(SharpenScale level)
{
	switch (level)
	{
	case lzh::SHARPEN_LEVEL1:
		return (Mat_(3, 3) <<
			0, -1, 0,
			-1, 5, -1,
			0, -1, 0);
	case lzh::SHARPEN_LEVEL2:
		return (Mat_(3, 3) <<
			-1, -1, -1,
			-1, 9, -1,
			-1, -1, -1);
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
}
void lzh::ConvKernel(IMat src, OutputArray dst, OMat(*CreatKernel)(int32), int32 angle)
{
	vec_mat ms;
	Mat m;
	if (MAT_SWITCH(angle, ANGLE0)) {
		Filter2D(src, m, CreatKernel(ANGLE0), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE45)) {
		Filter2D(src, m, CreatKernel(ANGLE45), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE90)) {
		Filter2D(src, m, CreatKernel(ANGLE90), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE135)) {
		Filter2D(src, m, CreatKernel(ANGLE135), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE180)) {
		Filter2D(src, m, CreatKernel(ANGLE180), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE225)) {
		Filter2D(src, m, CreatKernel(ANGLE225), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE270)) {
		Filter2D(src, m, CreatKernel(ANGLE270), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}if (MAT_SWITCH(angle, ANGLE315)) {
		Filter2D(src, m, CreatKernel(ANGLE315), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
		ms.push_back(m);
	}
	if (ms.empty())return;
	if (ms.size() == 1) { dst.set(ms[0]); return; }
	m = ms[0].pow(2);
	FOR_RANGE(i, 1, ms.size())
		m += ms[i].pow(2);
	dst.set(m.sqrt());
}
void lzh::Roberts(IMat src, OutputArray dst, int32 angle)
{
	ConvKernel(src, dst, RobertsKernel, angle);
}
void lzh::Prewitt(IMat src, OutputArray dst, int32 angle)
{
	ConvKernel(src, dst, PrewittKernel, angle);
}
void lzh::Sobel(IMat src, OutputArray dst, int32 angle)
{
	ConvKernel(src, dst, SobelKernel, angle);
}
void lzh::Sharpen(IMat src, OutputArray dst, SharpenScale level)
{
	Filter2D(src, dst, SharpenKernel(level), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
}
void lzh::Lapacian(IMat src, OutputArray dst, LaplaceType laplacetype)
{
	Filter2D(src, dst, LapacianKernel(laplacetype), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
}
void lzh::LoG(IMat src, OutputArray dst, Size ksize, Val sigma)
{
	Filter2D(src, dst, LoGKernel(ksize, sigma), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
}
void lzh::DoG(IMat src, OutputArray dst, Size ksize, Val sigma1, Val sigma2)
{
	Filter2D(src, dst, DoGKernel(ksize, sigma1, sigma2), Point(-1, -1), Size(1, 1), true, BORDER_DEFAULT);
}
void lzh::Roberts(IMat src_, OutputArray dst)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat kernx = RobertsKernel(ANGLE0);
	Mat kerny = RobertsKernel(ANGLE90);

	Mat x, y;
	conv2(src, y, kerny, CONVOLUTION_SAME);
	conv2(src, x, kernx, CONVOLUTION_SAME);
	dst.set((x.pow(2) + y.pow(2)).sqrt());
}
void lzh::Prewitt(IMat src_, OutputArray dst)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat kernx = PrewittKernel(ANGLE0);
	Mat kerny = PrewittKernel(ANGLE90);

	Mat x, y;
	conv2(src, y, kerny, CONVOLUTION_SAME);
	conv2(src, x, kernx, CONVOLUTION_SAME);
	dst.set((x.pow(2) + y.pow(2)).sqrt());
}


void lzh::HomomorphicFilter(IMat src_, OutputArray dst, Val D0, Val n, Val rL, Val rH)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat img;
	Mat imgHls;
	vec_mat vHls;

	if (src.channels() == 3)
	{
		cvtColor::RGB2HSV(src, imgHls);
		split(imgHls, vHls);
		vHls[2].copyTo(img);
	}
	else
		src.copyTo(img);

	//DFT
	//cout<<"DFT "<<endl;
	Mat img_complex;
	Mat fpower = FourierTransform(img, img_complex);
	dftShift(img_complex);
	dftShift(fpower);

	Mat filter_complex;
	filter_complex = ButterworthFilter(img_complex.size(), D0, n, rH, rL);
	//do mulSpectrums on the full dft
	mulSpectrums(img_complex, filter_complex, filter_complex);

	dftShift(filter_complex);

	//IDFT
	Mat result;
	InvFourierTransform(filter_complex, result);

	if (src.channels() == 3)
	{
		vHls[2] = result(Rect(0, 0, src.cols(), src.rows()));
		merge(vHls, imgHls);
		cvtColor::HSV2RGB(imgHls, dst);
	}
	else {
		resize(result, dst, src.size(), ReductionMothed::LocalMean);
	}
}
void lzh::GaussianFilter(IMat src_, OutputArray dst, Size ksize, Val sigma, BorderTypes borderType)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG

}
void lzh::unevenLightCompensate(IMat image_, OutputArray dst, int32 blockSize)
{
	Mat image = image_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(image);
#endif //MAT_DEBUG
	if (image.channels() == 3)
		cvtColor::RGB2GRAY(image, image);
	mat_t average = image.mean();
	int32 rows_new = int32(ceil(mat_t(image.rows()) / mat_t(blockSize)));
	int32 cols_new = int32(ceil(mat_t(image.cols()) / mat_t(blockSize)));
	Mat blockImage;
	blockImage = Mat::zeros(cols_new, rows_new);
	for (int32 i = 0; i < rows_new; i++)
	{
		for (int32 j = 0; j < cols_new; j++)
		{
			int32 rowmin = i * blockSize;
			int32 rowmax = (i + 1)*blockSize;
			if (rowmax > image.rows()) rowmax = image.rows();
			int32 colmin = j * blockSize;
			int32 colmax = (j + 1)*blockSize;
			if (colmax > image.cols()) colmax = image.cols();
			Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
			mat_t temaver = imageROI.mean();
			blockImage(i, j) = temaver;
		}
	}
	blockImage = blockImage - average;
	Mat blockImage2;
	resize(blockImage, blockImage2, image.size(), INTER_LINEAR);
	dst.set(image - blockImage2);
}
void lzh::GaussianBlur(IMat src, OutputArray dst, Size ksize, Val sigma, BorderTypes borderType)
{
	Filter2D(src, dst, GaussianKernel(ksize, sigma), Point(-1, -1), Size(1, 1), true, borderType);
}
void lzh::medianBlur(IMat src_, OutputArray dst, int32 ksize)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
	if (ksize % 2 == 0)THROW_INFO(ERR_INFO_UNLESS);
#endif //MAT_DEBUG
	int32 kern_row = ksize;
	int32 kern_col = ksize;
	Point anchor(-1, -1);
	int32 left, right, top, bottom;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	Size3 size = CalSize(src.size3(), Size(ksize, ksize), anchor, Size(1, 1), top, bottom, left, right);
	Mat in;
	int32 len = ksize * ksize;
	vec_m vec(len);
	copyMakeBorder(src, in, top, bottom, left, right, BORDER_REPLICATE);
	Val_* img = in;
	Mat out(src.size3());
	int32 c = out.channels();
	int32 offset = out.step().size();
	for (int32 z = 0; z < in.channels(); z++) {
		Val_* o = out.begin() + z;
		for (int32 h = top, x = 0; h < in.rows() - bottom; h++, x++) {
			for (int32 w = left, y = 0; w < in.cols() - right; w++, y++) {
				int32 idx = 0;
				int32 vidx = ((h - anchor.x)* in.s() + w - anchor.y) * in.o() + z;
				for (int32 i = 0; i < kern_row; ++i) {
					for (int32 j = 0; j < kern_col; ++j) {
						vec[idx++] = img[vidx + (i * in.s() + j) * in.o()];
					}
				}
				//std::sort(vec.begin(), vec.end());
				o[y * c] = median(vec);
			}
			o += offset;
		}
	}
	dst.set(out);
}
void lzh::blur(IMat src_, OutputArray dst, Size kernel, Point anchor, int32 iteration)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
#endif //MAT_DEBUG
	int32 kern_row = kernel.h;
	int32 kern_col = kernel.w;
	mat_t area = _T(kernel.area());
	int32 left, right, top, bottom;
	Size3 size = CalSize(src.size3(), kernel, anchor, Size(1, 1), top, bottom, left, right);
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	Mat in;
	copyMakeBorder(src, in, top, bottom, left, right, BORDER_DEFAULT);
	Mat out(src.size3());
	Val_* img = in;
	int32 c = out.channels();
	int32 offset = out.step().size();
	while (iteration--) {
		for (int32 z = 0; z < in.channels(); z++) {
			Val_* o = out.begin() + z;
			for (int32 h = top, x = 0; h < in.rows() - bottom; h++, x++) {
				for (int32 w = left, y = 0; w < in.cols() - right; w++, y++) {
					mat_t value = 0;
					int32 idx = ((h - anchor.x)* in.s() + w - anchor.y) * in.o() + z;
					for (int32 i = 0; i < kern_row; ++i) {
						for (int32 j = 0; j < kern_col; ++j) {
							value += img[idx + (i * in.s() + j) * in.o()];
						}
					}
					o[y * c] = value / area;
				}
				o += offset;
			}
		}
		if (iteration == 0)break;
		out.copy(in, top, top + src.rows() - 1, left, left + src.cols() - 1);
	}
	dst.set(out);
}
void lzh::erode(IMat src_, OutputArray dst, IMat kern, int32 iteration, Point anchor)
{
	Mat src = src_;
	Mat kernel = kern;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
#endif //MAT_DEBUG
	int32 kern_row = kernel.rows(), kern_col = kernel.cols();
	int32 left, right, top, bottom;
	Size3 size = CalSize(src.size3(), kernel.size3(), anchor, Size(1, 1), top, bottom, left, right);
	Mat in = src;
	Mat out(src.size3());
	Val_* img = in;
	int32 c1 = in.channels();
	int32 c = out.channels();
	int32 offset = out.step().size();
	while (iteration--) {
		for (int32 z = 0; z < in.channels(); z++) {
			Val_* o = out.begin() + z;
			for (int32 h = top, x = 0; h < in.rows() - bottom; h++, x++) {
				for (int32 w = left, y = 0; w < in.cols() - right; w++, y++) {
					int32 v_idx = ((h - anchor.x)* in.s() + w - anchor.y) * in.o() + z;
					if (img[v_idx] != 0) {
						bool isContain = true;
						Val_ *k = kernel;
						for (int32 i = 0; i < kern_row; ++i) {
							for (int32 j = 0; j < kern_col; ++j) {
								int32 idx = v_idx + (i * in.s() + j) * in.o();
								if (k[j] != 0 && img[idx] == 0) {
									isContain = false; break;
								}
							}
							if (!isContain)break;
							k += kern_col;
						}
						o[y * c] = isContain ? img[v_idx] : Val_(0);
					}
					else {
						o[y * c] = 0;
					}
				}
				o += offset;
			}
		}
		if (iteration == 0)break;
		out.setTo(in);
	}
	dst.set(out);
}
void lzh::dilate(IMat src_, OutputArray dst, IMat kern, int32 iteration, Point anchor)
{
	Mat src = src_;
	Mat kernel = kern;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
#endif //MAT_DEBUG
	int32 kern_row = kernel.rows(), kern_col = kernel.cols();
	int32 left, right, top, bottom;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	Size3 size = CalSize(src.size3(), kernel.size3(), anchor, Size(1, 1), top, bottom, left, right);
	Mat in = src;
	Mat out(src.size3());
	Val_* img = in;
	int32 c1 = in.channels();
	int32 c = out.channels();
	int32 offset = out.step().size();
	while (iteration--) {
		for (int32 z = 0; z < in.channels(); z++) {
			Val_* o = out.begin() + z;
			for (int32 h = top, x = 0; h < in.rows() - bottom; h++, x++) {
				for (int32 w = left, y = 0; w < in.cols() - right; w++, y++) {
					bool isContain = false;
					Val_ *k = kernel;
					int32 v_idx = ((h - anchor.x)* in.s() + w - anchor.y) * in.o() + z;
					//mat_t value = img[((h - anchor.x)* in.s() + w - anchor.y) * in.o() + z];
					for (int32 i = 0; i < kern_row; ++i) {
						for (int32 j = 0; j < kern_col; ++j) {
							int32 idx = v_idx + (i * in.s() + j) * in.o();
							if (k[j] != 0 && img[idx] != 0) {
								isContain = true; v_idx = idx; break;
							}
						}
						if (isContain)break;
						k += kern_col;
					}
					o[y * c] = isContain ? img[v_idx] : Val_(0);
				}
				o += offset;
			}
		}
		if (iteration == 0)break;
		out.setTo(in);
	}
	dst.set(out);
}
OMat lzh::getStructuringElement(MorphShape morphshape, Size elementsize)
{
	Mat element;
	switch (morphshape)
	{
	case lzh::MORPH_RECT:element = Mat::ones(elementsize); break;
	case lzh::MORPH_CROSS: {
		element = Mat::zeros(elementsize);
		Val_ *m = element;
		int32 idx = element.w() / 2;
		FOR_RANGE(i, 0, element.rows())
			m[i*element.w() + idx] = _T(1);
		idx = element.h() / 2 * element.w();
		FOR_RANGE(i, 0, element.cols())
			m[idx + i] = _T(1);
		break;
	}
	case lzh::MORPH_ELLIPSE: {
		vec_p2_32s ps;
		BresenhamCircle(ps, elementsize, Point(elementsize.w % 2 == 0 ? elementsize.w / 2 - 1 : elementsize.w / 2, elementsize.h % 2 == 0 ? elementsize.h / 2 - 1 : elementsize.h / 2), MIN(elementsize.h, elementsize.w) % 2 == 0 ? MIN(elementsize.h, elementsize.w) / 2 - 1 : MIN(elementsize.h, elementsize.w) / 2);
		if (ps.empty())return element;
		element = Mat::zeros(elementsize);
		for (Point &p : ps)if (__RANGE(0, p.x, elementsize.w) && __RANGE(0, p.y, elementsize.h))element(p) = 1;
		break;
	}
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
	return element;
}
void lzh::morphologyEx(IMat src, OutputArray dst, MorphType morphtype, IMat kernel, int32 iteration, Point anchor)
{
	Mat t;
	switch (morphtype)
	{
	case lzh::MORPH_OPEN:
		erode(src, t, kernel, iteration, anchor);
		dilate(t, dst, kernel, iteration, anchor);
		break;
	case lzh::MORPH_CLOSE:
		dilate(src, t, kernel, iteration, anchor);
		erode(t, dst, kernel, iteration, anchor);
		break;
	case lzh::MORPH_GRADIENT: {
		Mat a, b;
		dilate(src, a, kernel, iteration, anchor);
		erode(src, b, kernel, iteration, anchor);
		dst.set(a - b);
		break; }
	case lzh::MORPH_TOPHAT: {
		Mat a;
		morphologyEx(src, a, MORPH_OPEN, kernel, iteration, anchor);
		dst.set(src - a);
		break; }
	case lzh::MORPH_BLACKHAT: {
		Mat a;
		morphologyEx(src, a, MORPH_CLOSE, kernel, iteration, anchor);
		dst.set(a - src);
		break; }
	case lzh::MORPH_ERODE:
		erode(src, dst, kernel, iteration, anchor);
		break;
	case lzh::MORPH_DILATE:
		dilate(src, dst, kernel, iteration, anchor);
		break;
	default:
		THROW_INFO(ERR_INFO_UNLESS);
	}
}
void lzh::reverse(IMat src_, OutputArray dst, Val v)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	dst.set(-(src - v));
}
void lzh::Threshold(IMat src, OutputArray dst, Val boundary, Val lower, Val upper, int32 boundary2upper)
{
	Mat src_ = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
#endif //MAT_DEBUG
	Mat mark;
	src_.swap(mark);
	switch (boundary2upper)
	{
	case -1:
		for (int32 ind = 0; ind < mark.len(); ind++)
			mark(ind) = mark(ind) <= boundary ? lower : upper;
		break;
	case 0:
		for (int32 ind = 0; ind < mark.len(); ind++)
			mark(ind) = mark(ind) >= boundary ? upper : lower;
		break;
	case 1:
		for (int32 ind = 0; ind < mark.len(); ind++)
			mark(ind) = mark(ind) < boundary ? lower : (mark(ind) == boundary ? boundary : upper);
		break;
	default:
		THROW_INFO(ERR_INFO_UNLESS);
	}
	dst.set(mark);
}
mat_t lzh::Threshold(IMat src_, OutputArray dst, Val thresh, Val maxval, ThreshMethod method)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat img(src.size3());
	FOR_RANGE(z, 0, img.channels()) {
		switch (method)
		{
		case lzh::THRESH_BINARY:
			FOR_RANGE(i, 0, img.rows()) {
				FOR_RANGE(j, 0, img.cols()) {
					if (src.compare(i, j, z, thresh, GREATER))
						img(i, j, z) = maxval;
					else
						img(i, j, z) = 0;
				}
			}
			break;
		case lzh::THRESH_BINARY_INV:
			FOR_RANGE(i, 0, img.rows()) {
				FOR_RANGE(j, 0, img.cols()) {
					if (src.compare(i, j, z, thresh, GREATER))
						img(i, j, z) = maxval;
					else
						img(i, j, z) = 0;
				}
			}
			break;
		case lzh::THRESH_TRUNC:
			FOR_RANGE(i, 0, img.rows()) {
				FOR_RANGE(j, 0, img.cols()) {
					if (src.compare(i, j, z, thresh, GREATER))
						img(i, j, z) = thresh;
					else
						img(i, j, z) = src(i, j, z);
				}
			}
			break;
		case lzh::THRESH_TOZERO:
			FOR_RANGE(i, 0, img.rows()) {
				FOR_RANGE(j, 0, img.cols()) {
					if (src.compare(i, j, z, thresh, GREATER))
						img(i, j, z) = src(i, j, z);
					else
						img(i, j, z) = 0;
				}
			}
			break;
		case lzh::THRESH_TOZERO_INV:
			FOR_RANGE(i, 0, img.rows()) {
				FOR_RANGE(j, 0, img.cols()) {
					if (src.compare(i, j, z, thresh, GREATER))
						img(i, j, z) = 0;
					else
						img(i, j, z) = src(i, j, z);
				}
			}
			break;
		case lzh::THRESH_OTSU: {
			thresh = getOtsuThreshold(src.channel(z));
			FOR_RANGE(i, 0, img.rows()) {
				FOR_RANGE(j, 0, img.cols()) {
					if (src.compare(i, j, z, thresh, GREATER))
						img(i, j, z) = maxval;
					else
						img(i, j, z) = 0;
				}
			}
			break;
		}
		default:
			THROW_INFO(ERR_INFO_UNLESS);
		}
	}
	dst.set(img);
	return thresh;
}
mat_t lzh::getOtsuThreshold(IMat src_)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	mat_t pixel_sum = _T(1) / _T(src.len());
	Mat pixel_pro = Mat::zeros(256);
	Mat pixel_counts = Mat::zeros(256);
	FOR_RANGE(i, 0, src.rows())
		FOR_RANGE(j, 0, src.cols())
		pixel_counts((int32)src(i, j) < 0 ? 0 : (int32)src(i, j) > 255 ? 255 : (int32)src(i, j)) += 1;
	FOR_RANGE(i, 0, 256)
		pixel_pro(i) = pixel_counts(i) * pixel_sum;
	Vec2m s_max(0, 0);
	FOR_RANGE(threshold, 0, 256) {
		mat_t w_0 = pixel_pro.colRange(0, threshold).sum();
		mat_t w_1 = pixel_pro.colRange(threshold, 255).sum();
		mat_t u_0 = 0, u_1 = 0;
		mat_t u = 0;
		if (w_0 > 0) {
			FOR_RANGE(i, 0, threshold) {
				u_0 += _T(i * pixel_pro(i));
			}
			u += u_0;
			u_0 /= w_0;
		}
		if (w_1 > 0) {
			FOR_RANGE(i, threshold, 256) {
				u_1 += _T(i * pixel_pro(i));
			}
			u += u_1;
			u_1 /= w_1;
		}
		mat_t g = w_0 * w_1* pow((u_0 - u_1), 2);

		if (g > s_max[1])
			s_max = Vec2m(_T(threshold), g);
	}
	return s_max[0];
}
void lzh::adaptiveThreshold(IMat src_, OutputArray dst_, int32 area_pro, int32 percent)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat dst;
	if (src.channels() != 1)
		cvtColor::RGB2GRAY(src, dst);
	else
		dst = src.clone();
	int32 x1, y1, x2, y2;
	int32 count = 0;
	mat_t sum = 0;
	int32 S = src.rows() >> area_pro;  //划分区域的大小S*S
	int32 T = percent;         /*百分比，用来最后与阈值的比较。原文：If the value of the current pixel is t percent less than this average
						then it is set to black, otherwise it is set to white.*/
	int32 W = dst.cols();
	int32 H = dst.rows();
	mat_t **Argv;
	Argv = new mat_t*[dst.rows()];
	for (int32 ii = 0; ii < dst.rows(); ii++)
	{
		Argv[ii] = new mat_t[dst.cols()];
	}
	for (int32 i = 0; i < W; i++)
	{
		sum = 0;
		for (int32 j = 0; j < H; j++)
		{
			sum += dst(j, i);
			if (i == 0)
				Argv[j][i] = sum;
			else
				Argv[j][i] = Argv[j][i - 1] + sum;
		}
	}
	for (int32 i = 0; i < W; i++)
	{
		for (int32 j = 0; j < H; j++)
		{
			x1 = i - S / 2;
			x2 = i + S / 2;
			y1 = j - S / 2;
			y2 = j + S / 2;
			if (x1 < 0)
				x1 = 0;
			if (x2 >= W)
				x2 = W - 1;
			if (y1 < 0)
				y1 = 0;
			if (y2 >= H)
				y2 = H - 1;
			count = (x2 - x1)*(y2 - y1);
			sum = Argv[y2][x2] - Argv[y1][x2] - Argv[y2][x1] + Argv[y1][x1];
			if (dst(j, i)*count < (sum*(100 - T) / _T(100)))
				dst(j, i) = 0;
			else
				dst(j, i) = 255;
		}
	}
	for (int32 i = 0; i < dst.rows(); ++i) {
		delete[] Argv[i];
	}
	delete[] Argv;
	dst_.set(dst);
}
void lzh::copyMakeBorder(IMat src_, OutputArray dst, Size newSize, BorderTypes borderType, Val value)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	if (newSize.h < src.rows() || newSize.w < src.cols())
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	int32 h = newSize.h - src.rows();
	int32 w = newSize.w - src.cols();
	copyMakeBorder(src, dst, h / 2, Round(_T(h) / 2), w / 2, Round(_T(w) / 2), borderType, value);
}
void lzh::copyMakeBorder(IMat src, OutputArray dst, Size newSize, BorderTypes borderType, const Color & value)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	if (newSize.h < src.rows() || newSize.w < src.cols() || src.channels() > 4)
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	int32 h = newSize.h - src.rows();
	int32 w = newSize.w - src.cols();
	Mat mat(newSize, src.channels());
	FOR_RANGE(i, 0, src.channels()) {
		Mat res;
		copyMakeBorder(src.channel(i), res, h / 2, Round(_T(h) / 2), w / 2, Round(_T(w) / 2), borderType, value[i]);
		res.set(mat.channel(i));
	}
	dst = mat;
}
void lzh::copyMakeBorder(IMat src, OutputArray dst, int32 top, int32 bottom, int32 left, int32 right, BorderTypes borderType, const Color & value)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	if (src.channels() > 4)
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	Mat mat(Size(src.cols() + left + right, src.rows() + top + bottom), src.channels());
	FOR_RANGE(i, 0, src.channels()) {
		Mat res;
		copyMakeBorder(src.channel(i), res, top, bottom, left, right, borderType, value[i]);
		res.set(mat.channel(i));
	}
	dst = mat;
}
void lzh::Filter2D(IMat src, OutputArray dst, IMat kern, Point anchor, Size strides, bool is_copy_border, BorderTypes borderType, Val value)
{
	Mat src_ = src;
	Mat kern_ = kern;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
	CHECK_MATRIX_(kern_);
	if (kern_.dims() > 2)
		THROW_INFO(ERR_INFO_NOT2D);
#endif //MAT_DEBUG
	int32 kern_row = kern_.rows();
	int32 kern_col = kern_.cols();
	int32 left, right, top, bottom;
	Size3 size = CalSize(src_.size3(), kern_.size3(), anchor, strides, top, bottom, left, right);
	size.c = src_.channels();
	Mat out, in;
	if (is_copy_border) {
		copyMakeBorder(src_, in, top, bottom, left, right, borderType, value);
		out.create(src_.cols() / strides.h, src_.rows() / strides.w, size.c);
	}
	else {
		in = src_;
		out.create(size);
	}
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	Val_* img = in;
	int32 c = in.channels();
	int32 offset = out.step().size();
	for (int32 z = 0; z < in.channels(); z++) {
		Val_* o = out.begin() + z;
		for (int32 h = top, x = 0; h < in.rows() - bottom; h += strides.h, x++) {
			for (int32 w = left, y = 0; w < in.cols() - right; w += strides.w, y++) {
				mat_t value = 0;
				Val_* k = kern_;
				int32 idx = ((h - anchor.x)* in.s() + w - anchor.y) * in.o() + z;
				for (int32 i = 0; i < kern_row; ++i) {
					for (int32 j = 0; j < kern_col; ++j) {
						value += img[idx + (i * in.s() + j) * in.o()] * k[j];
					}/*out(h + i - anchor.y, w + j - anchor.x)*/
					k += kern_.step()[0];
				}
				o[y * c] = value;
			}
			o += offset;
		}
	}
	dst.set(out);
}
void lzh::Convolution(IMat src_, OutputArray dst, IMat kernel, Point anchor, Size strides, bool is_copy_border, BorderTypes borderType, Val value)
{
	Mat src = src_;
	Mat kern = kernel;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_MATRIX_(kern);
	if (kern.dims() != 2)
		THROW_INFO(ERR_INFO_NOT2D);
#endif //MAT_DEBUG
	int32 kern_row = kern.rows();
	int32 kern_col = kern.cols();
	int32 left, right, top, bottom;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	Size3 size = CalSize(src.size3(), kern.size3(), anchor, strides, top, bottom, left, right);
	size.c = src.channels();
	Mat out, in;
	if (is_copy_border) {
		copyMakeBorder(src, in, top, bottom, left, right, borderType, value);
		out.create(src.cols() / strides.h, src.rows() / strides.w, size.c);
	}
	else {
		in = src;
		out.create(size);
	}
	Val_* img = in;
	int32 c = in.channels();
	int32 offset = out.step().size();
	for (int32 z = 0; z < in.channels(); z++) {
		Val_* o = out.begin() + z;
		for (int32 h = top, x = 0; h < in.rows() - bottom; h += strides.h, x++) {
			for (int32 w = left, y = 0; w < in.cols() - right; w += strides.w, y++) {
				mat_t value = 0;
				Val_* k = kern;
				for (int32 i = 0; i < kern_row; ++i) {
					for (int32 j = 0; j < kern_col; ++j) {
						value += img[((h + i - anchor.x)* in.step()[0] + w + j - anchor.y) * c + z] * k[j];
					}/*out(h + i - anchor.y, w + j - anchor.x)*/
					k += kern.step()[0];
				}
				o[y * c] = value;
			}
			o += offset;
		}
	}
	dst.set(out);
}
void lzh::img2col(IMat src_, OutputArray dst, Size kernel, Point anchor, Size strides, bool is_copy_border, BorderTypes borderType, Val value)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
#endif //MAT_DEBUG
	int32 kern_row = kernel.h;
	int32 kern_col = kernel.w;
	int32 left, right, top, bottom;
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	Size3 size = CalSize(src.size3(), kernel, anchor, strides, top, bottom, left, right);
	size.c = src.channels();
	Mat out, in;
	if (is_copy_border) {
		copyMakeBorder(src, in, top, bottom, left, right, borderType, value);
		out.create(src.cols() / strides.h, src.rows() / strides.w, size.c);
	}
	else {
		in = src;
		out.create(size);
	}
	int32 conv_count = (in.rows() - bottom - top)*(in.cols() - right - left)*size.c;
	Mat mat(kernel.area(), conv_count);
	Val_* m = mat;
	Val_* img = in;
	int32 c = in.channels();
	int32 offset = out.step().size();
	for (int32 z = 0; z < in.channels(); z++) {
		for (int32 h = top, x = 0; h < in.rows() - bottom; h += strides.h, x++) {
			for (int32 w = left, y = 0; w < in.cols() - right; w += strides.w, y++) {
				for (int32 i = 0; i < kern_row; ++i) {
					for (int32 j = 0; j < kern_col; ++j) {
						*m = img[((h + i - anchor.x)* in.step()[0] + w + j - anchor.y) * c + z];
						m++;
					}
				}
			}
		}
	}
	dst.set(mat);
}


//void lzh::fastFilter2D(IMat src, OutputArray dst, IMat kern, Point anchor, Size strides, bool is_copy_border, BorderTypes borderType, mat_t value)
//{
//	Mat src_ = src;
//	Mat kern_ = kern;
//#ifdef MAT_DEBUG
//	CHECK_MATRIX_(src_);
//	CHECK_MATRIX_(kern_);
//	if (kern_.dims() != 2)
//		THROW_INFO(ERR_INFO_NOT2D);
//#endif //MAT_DEBUG
//	Mat mat;
//	img2col(src, mat, kern_.size(), anchor, strides, is_copy_border, borderType, value);
//	kern_.reshape(1, -1);
//	Dot(mat, kern_, dst);
//}
void lzh::filter2D(IMat src, OutputArray dst, IMat kernel, ConvolutionType type, BorderTypes border_types, Val value)
{
	Mat img, dest;
	img = src;
	Mat source = img.clone();
	if (CONVOLUTION_FULL == type)
	{
		source = Mat();
		const int32 additionalRows = kernel.rows() - 1, additionalCols = kernel.cols() - 1;
		copyMakeBorder(img, source, (additionalRows + 1) / 2, additionalRows / 2, (additionalCols + 1) / 2, additionalCols / 2, border_types, 0);
	}
	Point anchor(kernel.cols() - kernel.cols() / 2 - 1, kernel.rows() - kernel.rows() / 2 - 1);
	Filter2D(source, dest, kernel, anchor, Size(1, 1), true, border_types, value);
	if (CONVOLUTION_VALID == type)
	{
		dest = dest.colRange((kernel.cols() - 1) / 2, dest.cols() - kernel.cols() / 2).rowRange((kernel.rows() - 1) / 2, dest.rows() - kernel.rows() / 2);
	}
	dst.set(dest);
}
void lzh::SumChannel(IMat src_, OutputArray dst)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat m = Mat::zeros(src.size3());
	for (int32 i = 0; i < src.rows(); i++)
		for (int32 j = 0; j < src.cols(); j++) {
			mat_t sum = 0;
			for (int32 z = 0; z < src.channels(); z++)
				sum += src(i, j, z);
			m(i, j) = sum;
		}
	dst.set(m);
}
void lzh::rotate(IMat src_, RotateAngle dice, OutputArray dst_)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat dst;
	switch (dice)
	{
	case lzh::ROTATE_90_ANGLE:
	{
		Mat mat(src.rows(), src.cols(), src.channels());
		for (int32 h = 0; h < src.rows(); ++h)
			for (int32 w = 0; w < src.cols(); ++w)
				for (int32 depth = 0; depth < src.channels(); ++depth)
					mat(w, src.rows() - 1 - h, depth) = src(h, w, depth);
		dst = mat;
	}
	break;
	case lzh::ROTATE_180_ANGLE:
	{
		Mat mat(src.cols(), src.rows(), src.channels());
		for (int32 h = 0, y = src.rows() - 1; h < src.rows() && y >= 0; ++h, --y)
			for (int32 w = 0, x = src.cols() - 1; w < src.cols() && x >= 0; ++w, --x)
				for (int32 depth = 0; depth < src.channels(); ++depth)
					mat(h, w, depth) = src(y, x, depth);
		dst = mat;
	}
	break;
	case lzh::ROTATE_270_ANGLE:
	{
		Mat mat(src.rows(), src.cols(), src.channels());
		for (int32 h = 0; h < src.rows(); ++h)
			for (int32 w = 0; w < src.cols(); ++w)
				for (int32 depth = 0; depth < src.channels(); ++depth)
					mat(src.cols() - 1 - w, h, depth) = src(h, w, depth);
		dst = mat;
	}
	break;
	default:
		break;
	}
	dst_.set(dst);
}
OMat lzh::getRotationMat2D(Point2f center, Val angle)
{
	angle = -angle;
	Mat rot_mat = Mat::zeros(3, 3);
	Mat tran_1_mat = Mat::eye(3);
	Mat tran_2_mat = Mat::eye(3);
	angle = angle * PI / _T(180);
	rot_mat(0, 0) = cos(angle);
	rot_mat(0, 1) = -sin(angle);
	rot_mat(1, 0) = -rot_mat(0, 1);
	rot_mat(1, 1) = rot_mat(0, 0);
	rot_mat(2, 2) = _T(1);
	tran_1_mat(0, 2) = center.x;
	tran_1_mat(1, 2) = center.y;
	tran_2_mat(0, 2) = -center.x;
	tran_2_mat(1, 2) = -center.y;
	rot_mat = tran_1_mat * rot_mat*tran_2_mat;
	return rot_mat(Rect(0, 0, 3, 2)).clone();
}
OMat lzh::getRotationMat3D(Point2f center, Val angle)
{
	Mat rotate_mat = Mat::zeros(3, 3);
	angle = angle * PI / _T(180);
	rotate_mat(0, 0) = cos(angle);
	rotate_mat(0, 1) = -sin(angle);
	rotate_mat(1, 0) = sin(angle);
	rotate_mat(1, 1) = cos(angle);
	rotate_mat(0, 2) = center.x;
	rotate_mat(1, 2) = center.y;
	rotate_mat(2, 2) = _T(1);
	return rotate_mat;
}
void lzh::Conv2D(IMat src, OutputArray dst, IMat kern, Point anchor, const Size & strides, bool is_copy_border)
{
	Mat src_ = src;
	Mat kern_ = kern;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src_);
	CHECK_MATRIX_(kern_);
#endif //MAT_DEBUG
	Mat in, out;
	int32 kern_row = kern_.rows();
	int32 kern_col = kern_.cols();
	int32 left, right, top, bottom;
	Size3 size = CalSize(src_.size3(), kern_.size3(), anchor, strides, top, bottom, left, right);
	if (is_copy_border) {
		copyMakeBorder(src_, in, top, bottom, left, right);
		out = Mat::zeros(src_.cols() / strides.w, src_.rows() / strides.h, size.c);
	}
	else {
		in = src_;
		out = Mat::zeros(size);
	}
	if (anchor == Point(-1, -1)) {
		anchor.x = kern_row / 2;
		anchor.y = kern_col / 2;
	}
	for (int32 kern_c = 0; kern_c < size.c; kern_c++) {
		for (int32 in_c = 0; in_c < src_.channels(); in_c++) {
			int32 c = kern_c * src_.channels() + in_c;
			for (int32 h = top, x = 0; h < in.rows() - bottom; h += strides.h, x++)
				for (int32 w = left, y = 0; w < in.cols() - right; w += strides.w, y++) {
					int32 px = w - anchor.y;
					int32 py = h - anchor.x;
					mat_t value = 0;
					for (int32 i = 0; i < kern_row; ++i) {
						for (int32 j = 0; j < kern_col; ++j) {
							value += in(py + i, px + j, in_c)*kern_(i, j, c);
						}
					}
					out(x, y, kern_c) += value;
				}
		}
	}
	dst = out;
}
void lzh::conv2(IMat src, OutputArray dst, IMat kern, ConvolutionType type, BorderTypes border_types, const Color & value)
{
	Mat kernel, img, dest;
	flip(kern, kernel, -1);
	img = src;
	Mat source = src.clone();
	if (CONVOLUTION_FULL == type)
	{
		source = Mat();
		const int32 additionalRows = kernel.rows() - 1, additionalCols = kernel.cols() - 1;
		copyMakeBorder(img, source, (additionalRows + 1) / 2, additionalRows / 2, (additionalCols + 1) / 2, additionalCols / 2, border_types, value);
	}
	Point anchor(kernel.cols() - kernel.cols() / 2 - 1, kernel.rows() - kernel.rows() / 2 - 1);
	Filter2D(source, dest, kernel, anchor);
	if (CONVOLUTION_VALID == type)
	{
		dest = dest.colRange((kernel.cols() - 1) / 2, dest.cols() - kernel.cols() / 2).rowRange((kernel.rows() - 1) / 2, dest.rows() - kernel.rows() / 2);
	}
	dst.set(dest);
}
void lzh::flip(InputArray src_, OutputArray dst, int32 flipCode)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	CvMat v(src.size3(), src.depth());
	if (flipCode > 0)
		FOR_RANGE(row, 0, v.rows)
		FOR_RANGE(col, 0, v.cols)
		FOR_RANGE(z, 0, v.channels())
		v.set(v.rows - row - 1, col, z, src(row, col, z));
	else if (flipCode == 0)
		FOR_RANGE(row, 0, v.rows)
		FOR_RANGE(col, 0, v.cols)
		FOR_RANGE(z, 0, v.channels())
		v.set(row, v.cols - col - 1, z, src(row, col, z));
	else
		FOR_RANGE(row, 0, v.rows)
		FOR_RANGE(col, 0, v.cols)
		FOR_RANGE(z, 0, v.channels())
		v.set(v.rows - row - 1, v.cols - col - 1, z, src(row, col, z));
	dst.set(v);
}
void lzh::HighPass(IMat src, OutputArray dst, Val r, Size ksize, Val sigma)
{
	Mat img = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	Mat result;
	GaussianBlur(img, result, ksize, sigma);
	dst.set(img + r * (img - result)); //高反差保留算法
}
OMat lzh::ButterworthFilter(Size sz, Val D, Val n, Val high_h_v_TB, Val low_h_v_TB)
{
	Mat single(sz.w, sz.h);
	Point centre = Point(sz.w / 2, sz.h / 2);
	mat_t radius;
	mat_t upper = high_h_v_TB;
	mat_t lower = low_h_v_TB;
	mat_t dpow = D * D;
	mat_t W = (upper - lower);
	Val_ *p = single;
	for (int32 i = 0; i < sz.h; i++) {
		for (int32 j = 0; j < sz.w; j++) {
			radius = pow(_T(i - centre.x), 2) + pow(_T(j - centre.y), 2);
			mat_t r = exp(-n * radius / dpow);
			if (radius < 0)
				*p = upper;
			else
				*p = W * (1 - r) + lower;
			p++;
		}
	}
	Mat butterworth_complex;
	//make two channels to match complex
	Mat butterworth_channels[] = { single, single/*Mat::zeros(sz)*/ };
	merge(butterworth_channels, 2, butterworth_complex);
	return butterworth_complex;
}
OMat lzh::FourierTransform(IMat frame_bw, OutputArray image_complex, Mat *image_phase, Mat *image_mag)
{
	Mat frame_log = frame_bw;
	frame_log = frame_log / _T(255);
	/*Take the natural log of the input (compute log(1 + Mag)*/
	frame_log += 1;
	frame_log = frame_log.log();

	Mat padded;
	int32 M = getOptimalDFTSize(frame_log.rows());
	int32 N = getOptimalDFTSize(frame_log.cols());
	copyMakeBorder(frame_log, padded, 0, M - frame_log.rows(), 0, N - frame_log.cols(), BORDER_CONSTANT, 0);

	Mat image_planes[] = { padded, Mat::zeros(padded.size()) };
	merge(image_planes, 2, image_complex);

	dft(image_complex.getMat(), image_complex);

	split(image_complex.getMat(), image_planes);

	if (image_phase) phase(image_planes[0], image_planes[1], *image_phase);
	if (image_mag) magnitude(image_planes[0], image_planes[1], *image_mag);

	//Power
	image_planes[0] = image_planes[0].pow(2);
	image_planes[1] = image_planes[1].pow(2);

	Mat Power = image_planes[0] + image_planes[1];

	return Power;
}
void lzh::InvFourierTransform(IMat input, OutputArray inverseTransform)
{
	Mat result;
	idft(input, result);
	/*Take the exponential*/
	result = result.exp();

	vec_mat planes;
	split(result, planes);
	magnitude(planes[0], planes[1], planes[0]);
	planes[0] = planes[0] - 1.0;
	normalize(planes[0], inverseTransform, 0, 255, NORM_MINMAX);
}
OMat lzh::RobertsKernel(int32 angle)
{
	switch (angle)
	{
	case lzh::ANGLE0:	return (Mat_(2, 1) << -1, 1);
	case lzh::ANGLE45:	return (Mat_(2, 2) << -1, 0, 0, 1);
	case lzh::ANGLE90:	return (Mat_(1, 2) << -1, 1);
	case lzh::ANGLE135:	return (Mat_(2, 2) << 0, -1, 1, 0);
	case lzh::ANGLE180:	return (Mat_(2, 1) << 1, -1);
	case lzh::ANGLE225:	return (Mat_(2, 2) << 1, 0, 0, -1);
	case lzh::ANGLE270:	return (Mat_(2, 1) << 1, -1);
	case lzh::ANGLE315:	return (Mat_(2, 1) << 0, 1, -1, 0);
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
	return Mat();
}
OMat lzh::PrewittKernel(int32 angle)
{
	switch (angle)
	{
	case lzh::ANGLE0:
		return (Mat_(3, 3) <<
			-1, 0, 1,
			-1, 0, 1,
			-1, 0, 1);
	case lzh::ANGLE45:
		return (Mat_(3, 3) <<
			-1, -1, 0,
			-1, 0, 1,
			0, 1, 1);
	case lzh::ANGLE90:
		return (Mat_(3, 3) <<
			-1, -1, -1,
			0, 0, 0,
			1, 1, 1);
	case lzh::ANGLE135:
		return (Mat_(3, 3) <<
			0, -1, -1,
			1, 0, -1,
			1, 1, 0);
	case lzh::ANGLE180:
		return (Mat_(3, 3) <<
			1, 0, -1,
			1, 0, -1,
			1, 0, -1);
	case lzh::ANGLE225:
		return (Mat_(3, 3) <<
			1, 1, 0,
			1, 0, -1,
			0, -1, -1);
	case lzh::ANGLE270:
		return (Mat_(3, 3) <<
			1, 1, 1,
			0, 0, 0,
			-1, -1, -1);
	case lzh::ANGLE315:
		return (Mat_(3, 3) <<
			0, 1, 1,
			-1, 0, 1,
			-1, -1, 0);
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
	return Mat();
}
OMat lzh::SobelKernel(int32 angle)
{
	switch (angle)
	{
	case lzh::ANGLE0:
		return (Mat_(3, 3) <<
			-1, 0, 1,
			-2, 0, 2,
			-1, 0, 1);
	case lzh::ANGLE45:
		return (Mat_(3, 3) <<
			-2, -1, 0,
			-1, 0, 1,
			0, 1, 2);
	case lzh::ANGLE90:
		return (Mat_(3, 3) <<
			-1, -2, -1,
			0, 0, 0,
			1, 2, 1);
	case lzh::ANGLE135:
		return (Mat_(3, 3) <<
			0, -1, -2,
			1, 0, -1,
			2, 1, 0);
	case lzh::ANGLE180:
		return (Mat_(3, 3) <<
			1, 0, -1,
			2, 0, -2,
			1, 0, -1);
	case lzh::ANGLE225:
		return (Mat_(3, 3) <<
			2, 1, 0,
			1, 0, -1,
			0, -1, -2);
	case lzh::ANGLE270:
		return (Mat_(3, 3) <<
			1, 2, 1,
			0, 0, 0,
			-1, -2, -1);
	case lzh::ANGLE315:
		return (Mat_(3, 3) <<
			0, 1, 2,
			-1, 0, 1,
			-2, -1, 0);
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
	return Mat();
}
OMat lzh::LapacianKernel(LaplaceType neighbourhood)
{
	switch (neighbourhood)
	{
	case lzh::Four_Dire:
		return (Mat_(3, 3) <<
			0, 1, 0,
			1, -4, 1,
			0, 1, 0);
	case lzh::Eight_Dire:
		return (Mat_(3, 3) <<
			1, 1, 1,
			1, -8, 1,
			1, 1, 1);
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
	return Mat();
}
void lzh::Sobel(IMat src_, OutputArray dst)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat kernx = SobelKernel(ANGLE0);
	Mat kerny = SobelKernel(ANGLE90);

	Mat x, y;
	conv2(src, y, kerny, CONVOLUTION_SAME, BORDER_DEFAULT);
	conv2(src, x, kernx, CONVOLUTION_SAME, BORDER_DEFAULT);
	dst.set((x.pow(2) + y.pow(2)).sqrt());
}
bool CannyMark(InputOutputArray img, Point point, Object *p)
{
	if (p == nullptr)return false;
	CvMat image = img.getCvMat();
	if (image(point) == p[0].as<mat_t>() || image(point) == p[1].as<mat_t>()) {
		image.set(point, p[2].as<mat_t>());
		return true;
	}
	else {
		//img(y, x) = 50;
		return false;
	}
}
void lzh::Canny(IMat image, OutputArray edges, Val threshold1, Val threshold2, bool L2gradient, int32 ksize, Val sigma)
{
	Mat img, grad[2], theta, G;
	if (image.channels() == 3)
		cvtColor::RGB2GRAY(image, img);
	else
		img = image.clone();
	GaussianBlur(img, img, Size(ksize, ksize), sigma);
	Sobel(img, grad[0], ANGLE0); Sobel(img, grad[1], ANGLE270);
	Canny(grad[0], grad[1], edges, threshold1, threshold2, L2gradient);
}
void lzh::Canny(IMat dx, IMat dy, OutputArray edges, Val threshold1, Val threshold2, bool L2gradient)
{
	Mat G = L2gradient ? (dx.pow(2) + dy.pow(2)).sqrt() : dx.abs() + dy.abs();
	Mat flag = Mat::zeros(G.size3());
	mat_t Gp1, Gp2, angle, t, Gp;
	FOR_RANGE(i, 0, G.rows()) {
		FOR_RANGE(j, 0, G.cols()) {
			Gp1 = Gp2 = 0;
			Gp = G(i, j);
			if (Gp <= 0)continue;
			t = atan2(dy(i, j), dx(i, j));
			angle = t * rad2ang_;
			angle = angle < 0 ? 180 + angle : angle;
			if (0 < angle && angle < 45) {
				t = tan(t);
				if (!__RANGE(0, i - 1, G.rows()) || !__RANGE(0, j + 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i, j + 1) + (G(i - 1, j + 1) - G(i, j + 1)) * t;
				if (!__RANGE(0, i + 1, G.rows()) || !__RANGE(0, j - 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i, j - 1) + (G(i + 1, j - 1) - G(i, j - 1)) * t;
			}
			else if (45 < angle && angle < 90) {
				t = tan(PI_ / 2 - t);
				if (!__RANGE(0, i - 1, G.rows()) || !__RANGE(0, j + 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i - 1, j) + (G(i - 1, j + 1) - G(i - 1, j)) * t;
				if (!__RANGE(0, i + 1, G.rows()) || !__RANGE(0, j - 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i + 1, j) + (G(i + 1, j - 1) - G(i + 1, j)) * t;
			}
			else if (90 < angle && angle < 135) {
				t = tan(t - PI_ / 2);
				if (!__RANGE(0, i - 1, G.rows()) || !__RANGE(0, j - 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i - 1, j) + (G(i - 1, j - 1) - G(i - 1, j))*t;
				if (!__RANGE(0, i + 1, G.rows()) || !__RANGE(0, j + 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i + 1, j) + (G(i + 1, j + 1) - G(i + 1, j))*t;
			}
			else if (135 < angle && angle < 180) {
				t = tan(PI_ - t);
				if (!__RANGE(0, i - 1, G.rows()) || !__RANGE(0, j - 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i, j - 1) + (G(i - 1, j - 1) - G(i, j - 1)) * t;
				if (!__RANGE(0, i + 1, G.rows()) || !__RANGE(0, j + 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i, j + 1) + (G(i + 1, j + 1) - G(i, j + 1)) * t;
			}
			else if (angle == 0 || angle == 180) {
				if (!__RANGE(0, j + 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i, j + 1);
				if (!__RANGE(0, j - 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i, j - 1);
			}
			else if (angle == 45) {
				if (!__RANGE(0, i - 1, G.rows()) || !__RANGE(0, j + 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i - 1, j + 1);
				if (!__RANGE(0, i + 1, G.rows()) || !__RANGE(0, j - 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i + 1, j - 1);
			}
			else if (angle == 135) {
				if (!__RANGE(0, i - 1, G.rows()) || !__RANGE(0, j - 1, G.cols()))Gp1 = 0;
				else Gp1 = G(i - 1, j - 1);
				if (!__RANGE(0, i + 1, G.rows()) || !__RANGE(0, j + 1, G.cols()))Gp2 = 0;
				else Gp2 = G(i + 1, j + 1);
			}
			else if (angle == 90) {
				if (!__RANGE(0, i - 1, G.rows()))Gp1 = 0;
				else Gp1 = G(i - 1, j);
				if (!__RANGE(0, i + 1, G.rows()))Gp2 = 0;
				else Gp2 = G(i + 1, j);
			}
			if (Gp <= Gp1 || Gp <= Gp2) {
				flag(i, j) = 0;
			}
			else {
				if (Gp >= threshold1 && Gp < threshold2) {
					flag(i, j) = 1;
				}
				else if (Gp >= threshold2) {
					flag(i, j) = 2;
				}
				else if (Gp < threshold1) {
					flag(i, j) = 0;
				}
			}
		}
	}
	Object obj[3] = { _T(255), _T(128), _T(200) };
	FOR_RANGE(i, 0, G.rows()) {
		FOR_RANGE(j, 0, G.cols()) {
			if (flag(i, j) == 0) {
				G(i, j) = 0;
			}
			else if (flag(i, j) == 1) {
				G(i, j) = obj[1];
			}
			else if (flag(i, j) == 2) {
				G(i, j) = obj[0];
			}
		}
	}
	Dfs::DfsMark(G, 255, CannyMark, Dfs::Iteration, obj);
	FOR_RANGE(i, 0, G.rows()) {
		FOR_RANGE(j, 0, G.cols()) {
			if (G(i, j) == obj[2].as<mat_t>()) {
				G(i, j) = obj[0];
			}
			else {
				G(i, j) = 0;
			}
		}
	}
	edges = G;
}
void Dfs::DfsMark(InputOutputArray image, Val thresh, DfsOperator op, int32 method, Object * pre, DfsCallBack callback)
{
	switch (method)
	{
	case lzh::Dfs::Recursion:
		DfsMarkRecursion(image, thresh, op, pre, callback);
		break;
	case lzh::Dfs::Iteration:
		DfsMarkIteration(image, thresh, op, pre, callback);
		break;
	default:
		break;
	}
}
void Dfs::DfsMark(InputOutputArray image, Point seedpoint, DfsOperator op, int32 method, Object * pre, DfsCallBack callback)
{
	switch (method)
	{
	case lzh::Dfs::Recursion:
		DfsMarkRecursion(image, seedpoint, op, pre, callback);
		break;
	case lzh::Dfs::Iteration:
		DfsMarkIteration(image, seedpoint, op, pre, callback);
		break;
	default:
		break;
	}
}
void Dfs::DfsMarkRecursion(InputOutputArray image, Val thresh, DfsOperator op, Object*pre, DfsCallBack callback)
{
	CvMat img = image.getCvMat();
	FOR_RANGE(i, 0, img.rows) {
		FOR_RANGE(j, 0, img.cols) {
			if (img(i, j) >= thresh) {
				if (callback)callback(pre);
				DfsMarkRecursion(image, j, i, op, pre);
			}
		}
	}
}
void Dfs::DfsMarkRecursion(InputOutputArray image, Point seedpoint, DfsOperator op, Object*pre, DfsCallBack callback)
{
	if (callback)callback(pre);
	DfsMarkRecursion(image, seedpoint.x, seedpoint.y, op, pre);
}
void Dfs::DfsMarkRecursion(InputOutputArray image, int32 col, int32 row, DfsOperator op, Object*pre, int32 angle)
{
	if (row >= image.rows() || col >= image.cols() || col < 0 || row < 0)
		return;
	tools::output(Point(col, row));
	if (op(image, Point(col, row), pre)) {
		if (!MAT_SWITCH(angle, ANGLE0))		DfsMarkRecursion(image, col + 1, row, op, pre, angle | ANGLE180);
		if (!MAT_SWITCH(angle, ANGLE45))	DfsMarkRecursion(image, col + 1, row - 1, op, pre, angle | ANGLE225);
		if (!MAT_SWITCH(angle, ANGLE90))	DfsMarkRecursion(image, col, row - 1, op, pre, angle | ANGLE270);
		if (!MAT_SWITCH(angle, ANGLE135))	DfsMarkRecursion(image, col - 1, row - 1, op, pre, angle | ANGLE315);
		if (!MAT_SWITCH(angle, ANGLE180))	DfsMarkRecursion(image, col + 1, row, op, pre, angle | ANGLE0);
		if (!MAT_SWITCH(angle, ANGLE225))	DfsMarkRecursion(image, col - 1, row + 1, op, pre, angle | ANGLE45);
		if (!MAT_SWITCH(angle, ANGLE270))	DfsMarkRecursion(image, col, row + 1, op, pre, angle | ANGLE90);
		if (!MAT_SWITCH(angle, ANGLE315))	DfsMarkRecursion(image, col + 1, row + 1, op, pre, angle | ANGLE135);
	}
}
bool Dfs::DfsBackDirection(Point &p, int32 &state, int32 &angle)
{
	if (angle >> 8 == NO_ANGLE)
		return false;
	int32 s = angle >> 8;
	int32 off = 0;
	int32 idx = 0;
	while (s) {
		if ((s & 0x01) == 0x01)
			idx++;
		s >>= 1;
	}
	off = state >> 2 >> ((idx - 1) * 3); //获取最高3位的回退方向(栈顶)
	switch (off)
	{
	case lzh::ANGLE0_OFFSET:	p = Point(p.x + 1, p.y);		break;//往右退
	case lzh::ANGLE45_OFFSET:	p = Point(p.x + 1, p.y - 1);	break;//往右上退
	case lzh::ANGLE90_OFFSET:	p = Point(p.x, p.y - 1);		break;//往上退
	case lzh::ANGLE135_OFFSET:	p = Point(p.x - 1, p.y - 1);	break;//往左上退
	case lzh::ANGLE180_OFFSET:	p = Point(p.x - 1, p.y);		break;//往左退
	case lzh::ANGLE225_OFFSET:	p = Point(p.x - 1, p.y + 1);	break;//往左下退
	case lzh::ANGLE270_OFFSET:	p = Point(p.x, p.y + 1);		break;//往下退
	case lzh::ANGLE315_OFFSET:	p = Point(p.x + 1, p.y + 1);	break;//往右下退
	default:break;
	}
	state = (state & ~(0x07 << ((idx - 1) * 3 + 2)) & (~0x03)) | (state & 0x03); //消去最高3位回退方向(弹出栈顶)
	return true;
}
int32 Dfs::DfsCalDirection(int32 &angle, int32 angle_offset)
{
	int32 idx = 0;
	int32 state = angle >> 8; //回退方向
	while (state) { //获取回退方向的个数
		if ((state & 0x01) == 0x01)
			idx++;
		state >>= 1;
	}
	angle |= 1 << _I(angle_offset);	//记录前进方向
	angle |= (1 << _I(angle_offset)) << 8;	//记录回退方向
	return angle_offset << (idx * 3); //低2位表示状态, 高位每3位表示后退方向优先级
}
bool Dfs::DfsForwardDirection(int32 *stateArr, Point &p, int32 &angle, int32 angle_flag, int32 rows, int32 cols, int32 dy, int32 dx)
{
	Point pos;
	angle = angle | angle_flag;
	if (!((dx >= 0 ? p.x + dx >= cols : p.x + dx < 0) || (dy >= 0 ? p.y + dy >= rows : p.y + dy < 0))) {
		pos = Point(p.x + dx, p.y + dy);
		if ((stateArr[pos.y*cols + pos.x] & 0x03) != 0x01) {
			p = pos;
			return true;
		}
	}
	return false;
}
bool Dfs::DfsForwardDirection(int32 *angleArr, int32 *stateArr, Point &p, int32 &angle, int32 rows, int32 cols)
{
	int32 angle_offset = -1;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE0))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE0, rows, cols, 0, 1))
			angle_offset = ANGLE180_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE45))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE45, rows, cols, -1, 1))
			angle_offset = ANGLE225_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE90))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE90, rows, cols, -1, 0))
			angle_offset = ANGLE270_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE135))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE135, rows, cols, -1, -1))
			angle_offset = ANGLE315_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE180))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE180, rows, cols, 0, -1))
			angle_offset = ANGLE0_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE225))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE225, rows, cols, 1, -1))
			angle_offset = ANGLE45_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE270))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE270, rows, cols, 1, 0))
			angle_offset = ANGLE90_OFFSET;
	if (angle_offset == -1 && !MAT_SWITCH(angle, ANGLE315))
		if (DfsForwardDirection(stateArr, p, angle, ANGLE315, rows, cols, 1, 1))
			angle_offset = ANGLE135_OFFSET;
	if (angle_offset == -1)
		return false;
	else
		stateArr[p.y*cols + p.x] |= DfsCalDirection(angleArr[p.y*cols + p.x], angle_offset) << 2; //回退方向压入堆栈
	return true;
}
void Dfs::DfsMarkIteration(InputOutputArray image, Val thresh, DfsOperator op, Object* pre, DfsCallBack callback)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	int32 *angleArr = (int32*)fastMalloc(img.size().area() * sizeof(int32));
	int32 *stateArr = (int32*)fastMalloc(img.size().area() * sizeof(int32));
#ifdef MAT_DEBUG
	CHECK_PTR(angleArr);
	CHECK_PTR(stateArr);
#endif //MAT_DEBUG
	memset(angleArr, 0, img.size().area() * sizeof(int32));
	memset(stateArr, 0, img.size().area() * sizeof(int32));
	FOR_RANGE(i, 0, img.rows) {
		FOR_RANGE(j, 0, img.cols) {
			if (img(i, j) >= thresh && (stateArr[i*img.cols + j] & 0x03) == 0x00) { //状态为0 => 未经过该点
				DfsMarkIteration(image, angleArr, stateArr, Point(j, i), op, pre, callback);
			}
		}
	}
	fastFree(angleArr); angleArr = 0;
	fastFree(stateArr); stateArr = 0;
}
void Dfs::DfsMarkIteration(InputOutputArray image, Point seedpoint, DfsOperator op, Object * pre, DfsCallBack callback)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(image);
#endif //MAT_DEBUG
	int32 *angleArr = (int32*)fastMalloc(img.size().area() * sizeof(int32));
	int32 *stateArr = (int32*)fastMalloc(img.size().area() * sizeof(int32));
#ifdef MAT_DEBUG
	CHECK_PTR(angleArr);
	CHECK_PTR(stateArr);
#endif //MAT_DEBUG
	memset(angleArr, 0, img.size().area() * sizeof(int32));
	memset(stateArr, 0, img.size().area() * sizeof(int32));
	DfsMarkIteration(image, angleArr, stateArr, seedpoint, op, pre, callback);
	fastFree(angleArr); angleArr = 0;
	fastFree(stateArr); stateArr = 0;
}
void Dfs::DfsMarkIteration(InputOutputArray image, int32 *angleArr, int32 *stateArr, Point seedpoint, DfsOperator op, Object * pre, DfsCallBack callback)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(image);
	CHECK_PTR(angleArr);
	CHECK_PTR(stateArr);
#endif //MAT_DEBUG
	if (callback)callback(pre);
	Point p = seedpoint;
	while (1) {
		int32 &state = stateArr[p.y*image.cols() + p.x];//当前状态
		int32 &angle = angleArr[p.y*image.cols() + p.x];//当前方向累计
		if ((state & 0x03) != 0x01) { //状态为1 => 经过该区域
			//tools::print(p);
			//imshow(image); waitKey(30);
			if ((state & 0x03) == 0x02 || op(image, p, pre)) { //状态为-1 => 递归返回该点 || 调用回调确认是否符合条件
				state = (state & (~0x03)) | 0x01; //标记区域为已经过状态
				if (!DfsForwardDirection(angleArr, stateArr, p, angle, image.rows(), image.cols())) {//前进方向
					if (!DfsBackDirection(p, state, angle)) //后退方向
						break;
					stateArr[p.y*image.cols() + p.x] = (stateArr[p.y*image.cols() + p.x] & (~0x03)) | 0x02;//递归返回
				}
			}
			else {
				state = (state & (~0x03)) | 0x01; //标记区域为已经过状态
				if (!DfsBackDirection(p, state, angle))//后退方向
					break;
				stateArr[p.y*image.cols() + p.x] = (stateArr[p.y*image.cols() + p.x] & (~0x03)) | 0x02;//递归返回
			}
		}
		else {
			if (!DfsBackDirection(p, state, angle))//后退方向
				break;
			stateArr[p.y*image.cols() + p.x] = (stateArr[p.y*image.cols() + p.x] & (~0x03)) | 0x02;//递归返回
		}
	}
}


void lzh::MarkMainArea(InputOutputArray image, int32 col, int32 row, int32 dire)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	if (row >= img.rows || col >= img.cols || col < 0 || row < 0)
		return;
	if (img.isValue(img.toidx(row, col), 255)) {
		img.set(row, col, 127);
		if ((dire & 1) != 1)
			MarkMainArea(image, col, row + 1, (dire | 2));
		if ((dire & 8) != 8)
			MarkMainArea(image, col + 1, row, (dire | 4));
		if ((dire & 2) != 2)
			MarkMainArea(image, col, row - 1, (dire | 1));
		if ((dire & 4) != 4)
			MarkMainArea(image, col - 1, row, (dire | 8));
	}
}
void lzh::SearchMainArea(InputOutputArray image)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	for (int32 i = 0; i < img.rows; i++) {
		for (int32 j = 0; j < img.cols; j++) {
			if (img.isValue(img.toidx(i, j), 127))
				img.set(i, j, 0);
			else img.set(i, j, 255);
		}
	}
}
bool floodFillMark(InputOutputArray img, Point point, Object* p)
{
	if (p == nullptr)return false;
	if (p[2].data() != nullptr) {
		if (p[2].as<CvMat>().isZero(point))return false;
	}
	if (img.getCvMat().isValue(point, p[0].as<mat_t>())) {
		img.getCvMat().set(point.y, point.x, p[1].as<mat_t>());
		return true;
	}
	return false;
}
void lzh::floodFill(InputOutputArray image, Point seedPoint, Val newVal)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	Object obj[3] = { _T(0), newVal };
	Dfs::DfsMark(img, seedPoint, floodFillMark, Dfs::Iteration, obj);
}
void lzh::floodFill(InputOutputArray image, InputOutputArray mark, Point seedPoint, Val newVal)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	Object obj[] = { _T(0), newVal, mark.getCvMat() };
	Dfs::DfsMark(img, seedPoint, floodFillMark, Dfs::Iteration, obj);
}
void lzh::floodHole(IMat src, OutputArray dst, Val newVal)
{
	Mat mark = src.clone();
	floodFill(mark, Point(0, 0), newVal);
	dst = src | ~mark;
}
bool ContoursMark(InputOutputArray img, Point point, Object* p)
{
	if (p == nullptr)return false;
	if (img.getCvMat().isValue(point, p[1].as<mat_t>())) {
		//v = 128;
		vecs_p2_32s* vec = (vecs_p2_32s*)p[0];
		if (vec->empty())
			vec->push_back(vec_p2_32s());
		vec->at(vec->size() - 1).push_back(point);
		return true;
	}
	return false;
}
void ContoursUpdate(Object* p)
{
	if (p == nullptr)return;
	((vecs_p2_32s*)p[0])->push_back(vec_p2_32s());
}
void lzh::findContours(IMat image, OutputArrayOfArrays contours, Val threshold1, Val threshold2, bool L2gradient)
{
	Mat img = image;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	Canny(img, img, threshold1, threshold2, L2gradient);
	vecs_p2_32s vecs;
	Object obj[2] = { vecs, _T(255) };
	Dfs::DfsMark(img, 255, ContoursMark, Dfs::Iteration, obj, ContoursUpdate);
	contours.createSameSize(vecs, contours.depth());
	contours.setTo(vecs);
}
Rect lzh::bouningRect(InputArray contour)
{
	CvMat points = contour.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(points);
#endif //MAT_DEBUG
	Point p(points.get<int32>(0), points.get<int32>(1));
	Point pos[2] = { p, p };
	FOR_RANGE(i, 1, points.len() / 2) {
		p = Point(points.get<int32>(i * 2), points.get<int32>(i * 2 + 1));
		if (p.x < pos[0].x)pos[0].x = p.x;
		if (p.y < pos[0].y)pos[0].y = p.y;
		if (p.x > pos[1].x)pos[1].x = p.x;
		if (p.y > pos[1].y)pos[1].y = p.y;
	}
	return Rect(pos[0].x, pos[0].y, pos[1].x - pos[0].x, pos[1].y - pos[0].y);
}
Rectf lzh::bouningRectf(InputArray contour)
{
	CvMat points = contour.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(points);
#endif //MAT_DEBUG
	Point2f p(points.get<float32>(0), points.get<float32>(1));
	Point2f pos[2] = { p, p };
	FOR_RANGE(i, 1, points.len() / 2) {
		p = Point2f(points.get<float32>(i * 2), points.get<float32>(i * 2 + 1));
		if (p.x < pos[0].x)pos[0].x = p.x;
		if (p.y < pos[0].y)pos[0].y = p.y;
		if (p.x > pos[1].x)pos[1].x = p.x;
		if (p.y > pos[1].y)pos[1].y = p.y;
	}
	return Rectf(pos[0].x, pos[0].y, pos[1].x - pos[0].x, pos[1].y - pos[0].y);
}
int32 lzh::mod(Val x, int32 val)
{
	return Round(x) % val;
}
template<>int32 lzh::Round(float32 x)
{
	return (int32)(x + 0.5f);
}
template<>int32 lzh::Round(float64 x)
{
	return (int32)(x + 0.5);
}
template<>int32 lzh::Round(float64_ x)
{
	return (int32)(x + 0.5);
}
void lzh::SetPixel(InputOutputArray src_, Point point, int32 x, int32 y, const Color & color)
{
	CvMat src = src_.getCvMat();
	if (src.channels() == 3) {
		src.set(CHECK_INDEX_IMAGE(point.y + y, src.rows), CHECK_INDEX_IMAGE(point.x + x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -y, src.rows), CHECK_INDEX_IMAGE(point.x + x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + y, src.rows), CHECK_INDEX_IMAGE(point.x + -x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -y, src.rows), CHECK_INDEX_IMAGE(point.x + -x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + x, src.rows), CHECK_INDEX_IMAGE(point.x + y, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -x, src.rows), CHECK_INDEX_IMAGE(point.x + y, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + x, src.rows), CHECK_INDEX_IMAGE(point.x + -y, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -x, src.rows), CHECK_INDEX_IMAGE(point.x + -y, src.cols), color);
	}
	else {
		src.set(CHECK_INDEX_IMAGE(point.y + y, src.rows), CHECK_INDEX_IMAGE(point.x + x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -y, src.rows), CHECK_INDEX_IMAGE(point.x + x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + y, src.rows), CHECK_INDEX_IMAGE(point.x + -x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -y, src.rows), CHECK_INDEX_IMAGE(point.x + -x, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + x, src.rows), CHECK_INDEX_IMAGE(point.x + y, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -x, src.rows), CHECK_INDEX_IMAGE(point.x + y, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + x, src.rows), CHECK_INDEX_IMAGE(point.x + -y, src.cols), color);
		src.set(CHECK_INDEX_IMAGE(point.y + -x, src.rows), CHECK_INDEX_IMAGE(point.x + -y, src.cols), color);
	}
}
void lzh::BresenhamCircle(InputOutputArray circlePoints, Size size, Point point, int32 radius, int32 lineWidth)
{
	vec_p2_32s contour;
	if (radius > 1) {
		for (int32 wid = -lineWidth / 2; wid <= lineWidth / 2; ++wid)
			for (int32 x = 0, y = radius + wid, p = 3 - 2 * (radius + wid); x <= y; x++) {
				addContour(contour, point, x, y, size.h, size.w);
				if (p >= 0) {
					p += 4 * (x - y) + 10;
					y--;
				}
				else {
					p += 4 * x + 6;
				}
			}
	}
	else {
		contour.push_back(point);
	}
	circlePoints.createSameSize(contour, circlePoints.depth());
	circlePoints.setTo(contour);
}
void lzh::BresenhamCircle(InputOutputArray src_, Point point, int32 radius, const Color & color, int32 lineWidth, bool fill)
{
	CvMat src = src_.getCvMat();
	if (radius > 1) {
		radius -= 1;
		//vec_p2_32s contour;
		for (int32 wid = -lineWidth / 2; wid <= lineWidth / 2; ++wid)
			for (int32 x = 0, y = radius + wid, p = 3 - 2 * (radius + wid); x <= y; x++) {
				SetPixel(src, point, x, y, color);
				if (fill)SetPixel(src, point, x, y, color);
				//addContour(contour, point, x, y, src.rows(), src.cols());
				if (p >= 0) {
					p += 4 * (x - y) + 10;
					y--;
				}
				else {
					p += 4 * x + 6;
				}
			}
	}
	else {
		if (src.channels() == 3) src.set(CHECK_INDEX_IMAGE(point.y, src.rows), CHECK_INDEX_IMAGE(point.x, src.cols), color);
		else src.set(CHECK_INDEX_IMAGE(point.y, src.rows), CHECK_INDEX_IMAGE(point.x, src.cols), color);
	}
}
void lzh::drawPoint(InputOutputArray src_, Point point, const Color & color)
{
	CvMat src = src_.getCvMat();
	if (src.channels() == 3) {
		src.set(CHECK_INDEX_IMAGE(point.y, src.rows), CHECK_INDEX_IMAGE(point.x, src.cols), color);
	}
	else {
		src.set(CHECK_INDEX_IMAGE(point.y, src.rows), CHECK_INDEX_IMAGE(point.x, src.cols), color);
	}
}
void lzh::circle(InputOutputArray src, Point p, int32 radius, const Color & color, int32 lineWidth, bool fill)
{
	BresenhamCircle(src, p, radius, color, lineWidth, fill);
}
void lzh::circle(InputOutputArray src, int32 x, int32 y, int32 radius, const Color & color, int32 lineWidth, bool fill)
{
	BresenhamCircle(src, Point(x, y), radius, color, lineWidth, fill);
}
void lzh::drawFill(InputOutputArray src, vec_p2_32s & contour, const Color & color)
{
}


void lzh::lines(OutputArray src, Point p1, Point p2)
{
	if (!src.empty())
		src.clear();
	int32 x1 = p1.x;
	int32 x2 = p2.x;
	int32 y1 = p1.y;
	int32 y2 = p2.y;
	int32 dx, dy;//横轴纵轴差量
	int32 e;
	int32 x, y;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	y = y1;
	x = x1;
	int32 cx, cy;//表明x、y方向的增量  
	vec_p2_32s vec;
	if (x1 > x2) {
		cx = -1;//x递减方向  
	}
	else {
		cx = 1;//x递增方向  
	}
	if (y1 > y2) {
		cy = -1;//y递减方向  
	}
	else {
		cy = 1;//y递增方向  
	}
	if (dx == 0 && dy == 0) {
		//return; src.at<Vec3b>(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x, col)) = color;
	}
	else if (dy == 0) {
		for (x = x1; (cx == 1 ? x <= x2 : x >= x2); x += cx) {
			vec.push_back(Point(x, y));
		}
	}
	else if (dx == 0) {
		for (y = y1; (cy == 1 ? y <= y2 : y >= y2); y += cy) {
			vec.push_back(Point(x, y));
		}
	}
	else if (dx >= dy) {
		e = -dx;
		for (x = x1; (cx == 1 ? x <= x2 : x >= x2); x += cx) {
			vec.push_back(Point(x, y));
			e += dy << 1;
			if (e > 0) {
				y += cy;
				e -= dx << 1;
			}
		}
	}
	else {
		e = -dy;
		for (y = y1; (cy >= 0 ? y <= y2 : y >= y2); y += cy) {
			vec.push_back(Point(x, y));
			e += dx << 1;
			if (e > 0) {
				x += cx;
				e -= dy << 1;
			}

		}
	}
	src.set(vec);
}
void lzh::lines(InputOutputArray src_, Point p1, Point p2, const Color & color, int32 lineWidth, bool fill)
{
	CvMat src = src_.getCvMat();
	int32 row = src.rows;
	int32 col = src.cols;
	int32 thickness = lineWidth;
	int32 x1 = p1.x;
	int32 x2 = p2.x;
	int32 y1 = p1.y;
	int32 y2 = p2.y;
	int32 dx, dy;//横轴纵轴差量
	int32 e;
	int32 x, y;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	y = y1;
	x = x1;
	int32 cx, cy;//表明x、y方向的增量  
	if (x1 > x2) {
		cx = -1;//x递减方向  
	}
	else {
		cx = 1;//x递增方向  
	}
	if (y1 > y2) {
		cy = -1;//y递减方向  
	}
	else {
		cy = 1;//y递增方向  
	}
	if (dx == 0 && dy == 0) {
		//return; src.set(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x, col), color);
	}
	else if (dy == 0) {
		for (x = x1; (cx == 1 ? x <= x2 : x >= x2); x += cx) {
			src.set(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x, col), color);
			for (int32 i = 1; i <= thickness; i++)
				src.set(CHECK_INDEX_IMAGE(y + i, row), CHECK_INDEX_IMAGE(x, col), color);
		}
	}
	else if (dx == 0) {
		for (y = y1; (cy == 1 ? y <= y2 : y >= y2); y += cy) {
			src.set(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x, col), color);
			for (int32 i = 1; i <= thickness; i++)
				src.set(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x + i, col), color);
		}
	}
	else if (dx >= dy) {
		e = -dx;
		for (x = x1; (cx == 1 ? x <= x2 : x >= x2); x += cx) {
			src.set(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x, col), color);
			e += dy << 1;
			if (e > 0) {
				y += cy;
				e -= dx << 1;
			}
		}
	}
	else {
		e = -dy;
		for (y = y1; (cy >= 0 ? y <= y2 : y >= y2); y += cy) {
			src.set(CHECK_INDEX_IMAGE(y, row), CHECK_INDEX_IMAGE(x, col), color);
			e += dx << 1;
			if (e > 0) {
				x += cx;
				e -= dy << 1;
			}

		}
	}
}
void lzh::lines(InputOutputArray src, IMat points, const Color & color, int32 lineWidth, bool fill)
{
	Mat contours = points;
	FOR_RANGE(i, 0, contours.rows() - 1)
		lines(src, contours.row(i).toPoint(), contours.row(i + 1).toPoint(), color, lineWidth, fill);
	lines(src, contours.row(contours.rows() - 1).toPoint(), contours.row(0).toPoint(), color, lineWidth, fill);
}
void lzh::rectangle(InputOutputArray src_, int32 x1, int32 y1, int32 x2, int32 y2, const Color & color, int32 lineWidth, bool fill)
{
	CvMat src = src_.getCvMat();
	int32 xmin = MIN(x1, x2);
	int32 ymin = MIN(y1, y2);
	int32 xmax = MAX(x1, x2);
	int32 ymax = MAX(y1, y2);
	x1 = xmin;
	x2 = xmax;
	y1 = ymin;
	y2 = ymax;
	for (int32 col = MAX(x1, 0); col <= MIN(src.cols - 1, x2); ++col)
		for (int32 wid = -lineWidth / 2; wid <= lineWidth / 2; ++wid)
			src.set(CHECK_INDEX_IMAGE(y1 + wid, src.rows - 1), CHECK_INDEX_IMAGE(col, src.cols - 1), color);
	for (int32 col = MAX(x1, 0); col <= MIN(src.cols - 1, x2); ++col)
		for (int32 wid = -lineWidth / 2; wid <= lineWidth / 2; ++wid)
			src.set(CHECK_INDEX_IMAGE(y2 + wid, src.rows - 1), CHECK_INDEX_IMAGE(col, src.cols - 1), color);
	for (int32 row = MAX(y1, 0); row <= MIN(src.rows - 1, y2); ++row)
		for (int32 wid = -lineWidth / 2; wid <= lineWidth / 2; ++wid)
			src.set(CHECK_INDEX_IMAGE(row + wid, src.rows - 1), CHECK_INDEX_IMAGE(x1 + wid, src.cols - 1), color);
	for (int32 row = MAX(y1, 0); row <= MIN(src.rows - 1, y2); ++row)
		for (int32 wid = -lineWidth / 2; wid <= lineWidth / 2; ++wid)
			src.set(CHECK_INDEX_IMAGE(row + wid, src.rows - 1), CHECK_INDEX_IMAGE(x2 + wid, src.cols - 1), color);
	if (fill)
	{
		for (int32 col = MAX(x1, 0); col <= MIN(src.cols - 1, x2); ++col)
			for (int32 row = MAX(y1, 0); row <= MIN(src.rows - 1, y2); ++row)
				src.set(row, col, color);
	}
}
void lzh::rectangle(InputOutputArray src, Rect rect, const Color & color, int32 lineWidth, bool fill)
{
	rectangle(src, rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, color, lineWidth, fill);
}
void lzh::drawContours(InputOutputArray src, IMat contours_, const Color & color, int32 radius, int32 lineWidth, bool fill)
{
	Mat contours = contours_;
	FOR_RANGE(i, 0, contours.rows())
		circle(src, contours.row(i).toPoint(), radius, color, fill);
}
void lzh::drawContours(InputOutputArray src_, const vecs_p2_32s& contours, int32 index, int32 radius, const Color & color, int32 lineWidth, bool fill)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	if (index == -1) {
		for (const std::vector<Point> &contour : contours)
			for (const Point &p : contour)
				circle(src, p, radius, color, lineWidth, fill);
	}
	else {
		for (const Point &p : contours[index])
			circle(src, p, radius, color, lineWidth, fill);
	}
}
void lzh::drawContour(InputOutputArray src, const vec_p2_32s & contours, const Color & color, int32 radius, int32 lineWidth, bool fill)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	for (const Point &p : contours)
		circle(src, p, radius, color, lineWidth, fill);
}
void lzh::projection(IMat src_, OutputArray vertical_, OutputArray horizontal_)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	if (src.empty())return;
	Mat horizontal = Mat::zeros(src.cols(), 1, src.channels());
	Mat vertical = Mat::zeros(1, src.rows(), src.channels());
	FOR_IMAGE(i, src, 1) {
		FOR_IMAGE(j, src, 2) {
			FOR_IMAGE(k, src, 3) {
				horizontal(0, j, k) += src(i, j, k);
				vertical(i, 0, k) += src(i, j, k);
			}
		}
	}
	vertical_.set(vertical);
	horizontal_.set(horizontal);
}
void lzh::verticalProjection(IMat src_, OutputArray vertical_)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	Mat vertical = Mat::zeros(1, src.rows(), src.channels());
	FOR_IMAGE(i, src, 1) {
		FOR_IMAGE(k, src, 3) {
			mat_t sum = 0;
			FOR_IMAGE(j, src, 2) {
				sum += src(i, j, k);
			}
			vertical(i, 0, k) = sum;
		}
	}
	vertical_.set(vertical);
}
void lzh::horizontalProjection(IMat src_, OutputArray horizontal_)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	Mat horizontal = Mat::zeros(src.cols(), 1, src.channels());
	FOR_IMAGE(i, src, 2) {
		FOR_IMAGE(k, src, 3) {
			mat_t sum = 0;
			FOR_IMAGE(j, src, 1) {
				sum += src(j, i, k);
			}
			horizontal(0, i, k) = sum;
		}
	}
	horizontal_.set(horizontal);
}
void lzh::mosaic(IMat src, OutputArray dst, Rect mosaicRange, int32 ksize, MosaicMethod method)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat out = src.clone();
	for (int32 h = mosaicRange.y; h < mosaicRange.y + mosaicRange.height; h += ksize)
		for (int32 w = mosaicRange.x; w < mosaicRange.x + mosaicRange.width; w += ksize)
			mosaic(out, Point(w, h), ksize, method);
	dst = out;
}
void lzh::mosaic(InputOutputArray image, Point mosaicRange, int32 ksize, MosaicMethod method)
{
	CvMat img = image.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif //MAT_DEBUG
	int32 i, j;
	switch (MosaicAngle0)
	{
	case lzh::MosaicRandom:i = rand() % ksize; j = rand() % ksize; break;
	case lzh::MosaicAngle0:i = ksize / 2; j = ksize - 1; break;
	case lzh::MosaicAngle45:i = 0; j = ksize - 1; break;
	case lzh::MosaicAngle90:i = 0; j = ksize / 2; break;
	case lzh::MosaicAngle135:i = 0; j = 0; break;
	case lzh::MosaicAngle180:i = ksize / 2; j = 0; break;
	case lzh::MosaicAngle225:i = ksize - 1; j = 0; break;
	case lzh::MosaicAngle270:i = ksize - 1; j = ksize / 2; break;
	case lzh::MosaicAngle315:i = ksize - 1; j = ksize - 1; break;
	default:break;
	}
	for (int32 z = 0; z < img.channels(); z++) {
		mat_t v = img(mosaicRange.y + i, mosaicRange.x + j, z);
		for (int32 py = 0; py < ksize; ++py) {
			for (int32 px = 0; px < ksize; ++px) {
				img.set(mosaicRange.y + py, mosaicRange.x + px, z, v);
			}
		}
	}
}
void lzh::mosaic(IMat src, OutputArray dst, vec_p2_32s mosaicRange, int32 ksize, MosaicMethod method)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	Mat out = src.clone();
	for (Point &p : mosaicRange)
		mosaic(out, p, ksize, method);
	dst = out;
}

void lzh::warpAffine(IMat src_, OutputArray dst, IMat M)
{
	Mat src = src_;
	Mat m = M;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	int32 ymax = src.rows() - 1;
	int32 xmax = src.cols() - 1;
	Mat mat(src.size3())/* + 255*/;
	//Mat mark = Mat::zeros(src.size3(), MAT_32S);
	Val_ *s = src;
	Val_ *d = mat;
	Val_ *m_ = m;
	MatStep step_1 = src.step();
	MatStep step_2 = mat.step();
	FOR_RANGE(i, 0, mat.rows()) {
		FOR_RANGE(j, 0, mat.cols()) {
			Point pos;
			pos.x = Round(m_[0] * j + m_[1] * i + m_[2]);
			pos.y = Round(m_[3] * j + m_[4] * i + m_[5]);
			if (_RANGE_(-1, pos.y, src.rows()) && _RANGE_(-1, pos.x, src.cols())) {
				Val_ *p1 = d + i * step_2[0] * step_2[1] + j * step_2[1];
				Val_ *p2 = s + pos.y * step_1[0] * step_1[1] + pos.x * step_1[1];
				//mark.set(pos.y, pos.x, 1);
				FOR_RANGE(k, 0, mat.channels())
					p1[k] = p2[k];
			}
			else {
				Val_ *p1 = d + i * step_2[0] * step_2[1] + j * step_2[1];
				FOR_RANGE(k, 0, mat.channels())
					p1[k] = 0;
			}
		}
	}
	dst.set(mat);
}


void lzh::dft(IMat src, OutputArray dst)
{
	Mat m = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif
	bool dim = m.dims() >= 2;
	bool canfast = isOptimalDFTSize(m.size());
	dst = dim ? (canfast ? fft2D(src) : dft2D(src)) : (canfast ? fft1D(src) : dft1D(src));
}
void lzh::idft(IMat src, OutputArray dst)
{
	Mat m = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif
	bool dim = m.dims() >= 2;
	bool canfast = isOptimalDFTSize(m.size());
	dst = dim ? (canfast ? ifft2D(src) : idft2D(src)) : (canfast ? ifft1D(src) : idft1D(src));
}
OMat lzh::fft1D(InputOutputArray src)
{
	Mat y = src.getMat();
	bool dir = y.cols() > y.rows() ? true : false;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(y);
	CHECK_EXCEPTION(if (y.channels() == 2 || y.channels() == 1), THROW_INFO(ERR_INFO_CHANNEL););
#endif
	int32 l = dir ? y.cols() : y.rows();
	Complex u, t;
	brc(y); // 调用反转置换
	Val_* p = y;
	int32 stride = y.step()[1];
	//int32 stride = dir ? y.step()[1] : y.step().size();
	for (int32 h = 2; h <= l; h <<= 1) // 控制层数
	{
		// 初始化单位复根
		Complex wn(cos(-D_PI_ / h), sin(-D_PI_ / h));
		for (int32 j = 0; j < l; j += h) // 控制起始下标
		{
			Complex w(1, 0); // 初始化螺旋因子
			for (int32 k = j; k < j + h / 2; k++) // 配对
			{
				Val_ *val_k = p + k * stride;
				Val_ *val_h = p + (k + h / 2) * stride;
				u = Complex(val_k[0], val_k[1]);
				t = w * Complex(val_h[0], val_h[1]);
				Complex x = u + t;
				val_k[0] = x.r;
				val_k[1] = x.i;
				x = u - t;
				val_h[0] = x.r;
				val_h[1] = x.i;
				w = w * wn;
			} // 据说上面的操作叫蝴蝶操作…
		}
	}
	return y;
}
OMat lzh::fft1D(IMat src)
{
	Mat in = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(in);
	CHECK_EXCEPTION(if (in.channels() == 2 || in.channels() == 1), THROW_INFO(ERR_INFO_CHANNEL););
#endif
	Mat y;
	if (in.channels() == 2) {
		y = in.clone();
	}
	else {
		y = Mat::zeros(in.cols(), in.rows(), 2);
		in.setTo(y.channel(0));
	}
	if (y.rows() != 1)
		y.reshape(-1, 1, 0);
	int32 l = y.cols();
	Complex u, t;
	brc(y); // 调用反转置换
	int32 stride = y.step()[1];
	Val_ *p = y;
	for (int32 h = 2; h <= l; h <<= 1) // 控制层数
	{
		// 初始化单位复根
		Complex wn(cos(-D_PI_ / h), sin(-D_PI_ / h));
		for (int32 j = 0; j < l; j += h) // 控制起始下标
		{
			Complex w(1, 0); // 初始化螺旋因子
			for (int32 k = j; k < j + h / 2; k++) // 配对
			{
				Val_ *val_k = p + k * stride;
				Val_ *val_h = p + (k + h / 2) * stride;
				u = Complex(val_k[0], val_k[1]);
				t = w * Complex(val_h[0], val_h[1]);
				Complex x = u + t;
				val_k[0] = x.r;
				val_k[1] = x.i;
				x = u - t;
				val_h[0] = x.r;
				val_h[1] = x.i;
				w = w * wn;
			} // 据说上面的操作叫蝴蝶操作…
		}
	}
	return y;
}
OMat lzh::ifft1D(IMat src)
{
	Mat in = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(in);
	CHECK_EXCEPTION(if (in.channels() == 2), THROW_INFO(ERR_INFO_CHANNEL););
#endif
	//Mat y = y.rows() != 1 ? out.t() : out.clone();
	Mat y = in.clone();
	if (y.rows() != 1)
		y.reshape(-1, 1, 0);
	int32 l = y.cols();
	Complex u, t;
	brc(y); // 调用反转置换
	int32 stride = y.step()[1];
	Val_ *p = y;
	for (int32 h = 2; h <= l; h <<= 1) // 控制层数
	{
		// 初始化单位复根
		Complex wn(cos(D_PI_ / h), sin(D_PI_ / h));
		for (int32 j = 0; j < l; j += h) // 控制起始下标
		{
			Complex w(1, 0); // 初始化螺旋因子
			for (int32 k = j; k < j + h / 2; k++) // 配对
			{
				Val_ *val_k = p + k * stride;
				Val_ *val_h = p + (k + h / 2) * stride;
				u = Complex(val_k[0], val_k[1]);
				t = w * Complex(val_h[0], val_h[1]);
				Complex x = u + t;
				val_k[0] = x.r;
				val_k[1] = x.i;
				x = u - t;
				val_h[0] = x.r;
				val_h[1] = x.i;
				w = w * wn;
			} // 据说上面的操作叫蝴蝶操作…
		}
	}
	//y /= l;
	for (int32 i = 0; i < l * 2; i++)
		p[i] /= l;
	return y;
}
OMat lzh::dft1D(IMat src)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_EXCEPTION(if (src.channels() == 2 || src.channels() == 1), THROW_INFO(ERR_INFO_CHANNEL););
#endif
	int32 width = src.rows() != 1 ? src.rows() : src.cols();
	Mat mat = Mat::zeros(width, 1, 2);
	int32 stride = src.rows() != 1 ? src.step().size() : src.step()[1];
	Val_ *y = mat;
	const Val_ *s = src;
	Complex cplTemp;
	mat_t fixed_factor = -D_PI_ / width;                   // evaluate -i2π/N of -i2πux/N, and store the value for computing efficiency
	if (src.channels() == 2)
	{
		for (int32 v = 0; v < width; v++) {
			const Val_ *c = s;
			for (int32 w = 0; w < width; w++) {
				mat_t power = v * w * fixed_factor;         // evaluate -i2πux/N
				Complex val(cos(power), sin(power));
				cplTemp = Complex(c[0], c[1]) * val;
				y[0] += cplTemp.r;
				y[1] += cplTemp.i;
				c += stride;
			}
			y += 2;
		}
	}
	else
	{
		for (int32 v = 0; v < width; v++) {
			const Val_ *c = s;
			for (int32 w = 0; w < width; w++) {
				mat_t power = v * w * fixed_factor;         // evaluate -i2πux/N
				Complex val(cos(power), sin(power));
				cplTemp = Complex(c[0] * val.r, c[0] * val.i);
				y[0] += cplTemp.r;
				y[1] += cplTemp.i;
				c += stride;
			}
			y += 2;
		}
	}
	// now we have the transformed vector, keep the info
	return mat;
}
OMat lzh::idft1D(IMat src)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_EXCEPTION(if (src.channels() == 2), THROW_INFO(ERR_INFO_CHANNEL););
#endif	
	int32 width = src.rows() != 1 ? src.rows() : src.cols();
	Mat mat(width, 1, 2);
	int32 stride = src.rows() != 1 ? src.step().size() : src.step()[1];
	Val_ *y = mat;
	const Val_ *s = src;
	Complex cplTemp;
	mat_t fixed_factor = D_PI_ / width;
	for (int32 w = 0; w < width; w++) {
		Complex cplResult;
		const Val_ *c = s;
		for (int32 v = 0; v < width; v++) {
			mat_t power = v * w * fixed_factor;         // evaluate -i2πux/N
			cplResult = cplResult + Complex(c[0], c[1]) * Complex(cos(power), sin(power));
			c += stride;
		}
		y[0] = cplResult.r / width;
		y[1] = cplResult.i / width;
		y += 2;
	}
	// now we have the inverse transformed matrix, keep the info
	return mat;
}
OMat lzh::dft2D(IMat src)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_EXCEPTION(if (src.channels() == 2 || src.channels() == 1), THROW_INFO(ERR_INFO_CHANNEL););
#endif
	int32 height = src.rows(), width = src.cols();
	Mat mat(width, height, 2);
	for (int32 v = 0; v < width; v++)
		dft1D(src.col(v)).setTo(mat.col(v));
	for (int32 v = 0; v < height; v++)
		dft1D(mat.row(v)).setTo(mat.row(v));
	// now we have the transformed vector, keep the info
	return mat;
}
OMat lzh::idft2D(IMat src)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_EXCEPTION(if (src.channels() == 2), THROW_INFO(ERR_INFO_CHANNEL));
#endif
	int32 height = src.rows(), width = src.cols();
	Mat mat(width, height, 2);
	for (int32 v = 0; v < width; v++)
		idft1D(src.col(v)).setTo(mat.col(v));
	for (int32 v = 0; v < height; v++)
		idft1D(mat.row(v)).setTo(mat.row(v));
	// now we have the inverse transformed matrix, keep the info
	return mat;
}
OMat lzh::fft2D(IMat src)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_EXCEPTION(if (src.channels() == 2 || src.channels() == 1), THROW_INFO(ERR_INFO_CHANNEL););
#endif
	int32 height = src.rows(), width = src.cols();
	if ((height & height - 1) != 0 || (width & width - 1))
		THROW_INFO(ERR_INFO_FFT);
	Mat mat(width, height, 2);
	for (int32 v = 0; v < width; v++)
		fft1D(src.col(v)).setTo(mat.col(v));
	for (int32 v = 0; v < height; v++)
		ifft1D(mat.row(v)).setTo(mat.row(v));
	// now we have the transformed vector, keep the info
	return mat;
}
OMat lzh::ifft2D(IMat src)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	CHECK_EXCEPTION(if (src.channels() == 2), THROW_INFO(ERR_INFO_CHANNEL));
#endif
	int32 height = src.rows(), width = src.cols();
	if ((height & height - 1) != 0 || (width & width - 1))
		THROW_INFO(ERR_INFO_FFT);
	Mat mat(width, height, 2);
	for (int32 v = 0; v < width; v++)
		ifft1D(src.col(v)).setTo(mat.col(v));
	for (int32 v = 0; v < height; v++)
		ifft1D(mat.row(v)).setTo(mat.row(v));
	// now we have the inverse transformed matrix, keep the info
	return mat;
}
void lzh::dftShift(InputOutputArray src)
{
	CvMat v = src.getCvMat();
	int32 w = v.cols / 2;
	int32 h = v.rows / 2;

	CvMat a = v(Rect(0, 0, w, h)).clone();
	CvMat b = v(Rect(w, 0, w, h)).clone();
	CvMat c = v(Rect(w, h, w, h)).clone();
	CvMat d = v(Rect(0, h, w, h)).clone();

	a.setTo(v(Rect(w, h, w, h)));
	b.setTo(v(Rect(0, h, w, h)));
	c.setTo(v(Rect(0, 0, w, h)));
	d.setTo(v(Rect(w, 0, w, h)));
}
void lzh::idftShift(InputOutputArray src)
{
	dftShift(src);
}
void lzh::dftShift(IMat src, OutputArray dst)
{
	Mat s = src;
	Mat v(s.size3());
	int32 w = v.cols() / 2;
	int32 h = v.rows() / 2;

	Mat a = s(Rect(0, 0, w, h));
	Mat b = s(Rect(w, 0, w, h));
	Mat c = s(Rect(w, h, w, h));
	Mat d = s(Rect(0, h, w, h));

	a.setTo(v(Rect(w, h, w, h)));
	b.setTo(v(Rect(0, h, w, h)));
	c.setTo(v(Rect(0, 0, w, h)));
	d.setTo(v(Rect(w, 0, w, h)));

	dst.set(v);
}
void lzh::ifftShift(IMat src, OutputArray dst)
{
	dftShift(src, dst);
}
bool lzh::isOptimalDFTSize(int32 size)
{
	return ((size&(size - 1)) == 0);
}
bool lzh::isOptimalDFTSize(Size size)
{
	return (isOptimalDFTSize(size.h) && isOptimalDFTSize(size.w));
}
int32 lzh::getOptimalDFTSize(int32 size)
{
	if ((size&(size - 1)) == 0)return size;
	int32 l = 1;
	while (l < size) l <<= 1;
	return (size - (l >> 1)) > (l - size) ? l : l >> 1;
}
Size lzh::getOptimalDFTSize(Size size)
{
	return Size(getOptimalDFTSize(size.w), getOptimalDFTSize(size.h));
}
void lzh::copyBorderDFTSize(IMat src, OutputArray dst)
{
	Size sz = src.size();
	Size newSz = getOptimalDFTSize(sz);
	if (sz != newSz)
		if (sz.h < newSz.h &&sz.w < newSz.w)
			copyMakeBorder(src, dst, newSz, BORDER_CONSTANT, 0);
		else if (sz.h > newSz.h &&sz.w > newSz.w)
			resize(src, dst, newSz, LocalMean);
		else {
			Mat img;
			copyMakeBorder(src, img, Size(MAX(newSz.w, sz.w), MAX(newSz.h, sz.h)), BORDER_CONSTANT, 0);
			resize(img, dst, newSz, LocalMean);
		}
	else
		dst.set(src);
}
void lzh::normalize(IMat src, OutputArray dst, Val alpha, Val beta, NormType norm_type)
{
	Mat s = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(s);
#endif // MAT_DEBUG
	Mat norm = s.clone();
	mat_t a = alpha;
	mat_t b = beta;
	FOR_RANGE(i, 0, norm.channels()) {
		Mat in = norm.channel(i);
		switch (norm_type)
		{
		case lzh::NORM_SUM:		(in * a / in.sum()).setTo(in); break;
		case lzh::NORM_L1:		(in * a / in.sum(1, true)).setTo(in); break;
		case lzh::NORM_L2:		(in * a / in.norm(2)).setTo(in); break;
		case lzh::NORM_INF:		(in * a / in.Max(true)).setTo(in); break;
		case lzh::NORM_MINMAX: {
			mat_t min_v = in.Min(), max_v = in.Max();
			if (max_v - min_v != 0)
				((in - min_v) / (max_v - min_v) * (b - a) + a).setTo(in);
			else
				((in - min_v) + a).setTo(in);
			break;
		}
		case lzh::NORM_IMAGE: {
			mat_t max_v = in.Max();
			Mat t;
			Max(a, in, t);
			if (max_v == 0) {
				t.setTo(in);
				break;
			}
			if (max_v < b) {
				t /= max_v;
				t *= b;
			}
			else {
				Min(b, in, t);
			}
			t.setTo(in);
			break;
		}
		case lzh::NORM_ZSCORE: {
			Mat x = in;
			x -= in.mean();
			x /= in.std();
			x.setTo(in);
			break; }
		default:THROW_INFO(ERR_INFO_UNLESS);
		}
	}
	dst.set(norm);
}
OMat lzh::getPerspectiveTransform(const Point2f * src, const Point2f * dst)
{
	Mat a = Mat::ones(3, 3);
	Mat b = Mat::ones(3, 3);
	FOR_RANGE(i, 0, 3) {
		a(0, i) = src[i].x;
		a(1, i) = src[i].y;
		b(0, i) = dst[i].x;
		b(1, i) = dst[i].y;
	}
	return b * a.inv();
}
void lzh::getPerspectiveTransform(IMat src, IMat dst, OutputArray transform)
{
	Mat a = src;
	Mat b = dst;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(b);
#endif // MAT_DEBUG
	if (a.rows() != 3 || b.rows() != 3)
		THROW_INFO(ERR_INFO_SIZE);
	if (a.cols() != 3 && b.cols() != 3)
		THROW_INFO(ERR_INFO_SIZE);
	Mat m = b * a.inv();
	transform.set(m);
}

void lzh::Sort(InputArray src, OutputArray dst, ORDER flag, RANK r)
{
	CvMat in = src.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(in);
#endif // MAT_DEBUG
	int32 size = in.rankSize(r);
	if (size == 1)
		dst.set(in);
	else {
		vec_cvmat vec(size);
		FOR_RANGE(i, 0, size) {
			vec[i] = in.cut(i, r).clone();
		}
		std::sort(vec.begin(), vec.end(), flag == MIN_TO_MAX ? sort::compare_min : sort::compare_max);
		CvMat m(in.size3(), in.depth());
		FOR_RANGE(i, 0, size) {
			vec[i].setTo(m.cut(i, r));
		}
		dst.set(m);
	}
}
void lzh::Sort(InputArray src, OutputArray dst, bool(*comp)(const CvMat &a, const CvMat &b), RANK r)
{
	CvMat in = src.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(in);
#endif // MAT_DEBUG
	int32 size = in.rankSize(r);
	if (size == 1)
		dst.set(in);
	else {
		vec_cvmat vec(size);
		FOR_RANGE(i, 0, size) {
			vec[i] = in.cut(i, r).clone();
		}
		std::sort(vec.begin(), vec.end(), comp);
		CvMat m(in.size3(), in.depth());
		FOR_RANGE(i, 0, size) {
			vec[i].setTo(m.cut(i, r));
		}
		dst.set(m);
	}
}
void lzh::Sort(InputArray src, OutputArray dst, bool(*comp)(InputArray a, InputArray b), RANK r)
{
	CvMat in = src.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(in);
#endif // MAT_DEBUG
	int32 size = in.rankSize(r);
	if (size == 1)
		dst.set(in);
	else {
		vec_cvmat vec(size);
		FOR_RANGE(i, 0, size) {
			vec[i] = in.cut(i, r).clone();
		}
		std::sort(vec.begin(), vec.end(), comp);
		CvMat m(in.size3(), in.depth());
		FOR_RANGE(i, 0, size) {
			vec[i].setTo(m.cut(i, r));
		}
		dst.set(m);
	}
}
mat_t lzh::Cross(IMat a, IMat b)
{
	return a(0) * b(1) - a(1) * b(0);
}
bool lzh::Clockwise(IMat p0, IMat p1, IMat p2)
{
	Mat a = p1 - p0;
	Mat b = p2 - p0;
	return Cross(a, b) < 0;
}
void lzh::ConvexHull(IMat in, OutputArray convexhull)
{
	Mat src = in;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif // MAT_DEBUG
	int32 min_idx = src.col(0).minAt();
	Mat p = src.row(min_idx).clone();
	CvMat data(p.len(), p.data(), MAT_T);
	sort::Register(&data);
	Mat s = src.rowRange(1, src.rows() - 1).clone();
	src.row(0).setTo(s.row(min_idx - 1));
	Sort(s, s, sort::compare_angle);
	sort::Register(nullptr);
	vec_mat u(2, p);
	u[1] = s.row(0);
	int32 idx = 1;
	FOR_RANGE(i, 2, s.rows() + 1) {
		for (int32 n = (int32)u.size(); n >= 2 && Clockwise(u[n - 2], u[n - 1], s.row(idx)) != true; n--)
			u.pop_back();
		u.push_back(s.row(idx++));
	}
	Mat hull(2, (int32)u.size());
	FOR_RANGE(i, 0, u.size())
		u[i].setTo(hull.row(i));
	convexhull.set(hull);
}
void lzh::resize(IMat src_, OutputArray dst, Val xRatio, Val yRatio, ReductionMothed mothed)
{
	Mat src = src_;
	if (src.empty())return;
	int32 rows = static_cast<int32>(src.rows() * yRatio);
	int32 cols = static_cast<int32>(src.cols() * xRatio);
	Mat img(cols, rows, src.channels());
	switch (mothed)
	{
	case lzh::EqualIntervalSampling:
		for (int32 i = 0; i < rows; i++) {
			int32 h = static_cast<int32>((i + 1) / yRatio + _T(0.5)) - 1;
			for (int32 j = 0; j < cols; j++) {
				int32 w = static_cast<int32>((j + 1) / xRatio + _T(0.5)) - 1;
				for (int32 z = 0; z < src.channels(); z++) {
					img(i, j, z) = src(h, w, z); //取得采样像素
				}
			}
		}
		break;
	case lzh::LocalMean:
	{
		int32 lastRow = 0;
		int32 lastCol = 0;

		for (int32 i = 0; i < rows; i++) {
			int32 h = static_cast<int32>((i + 1) / yRatio + _T(0.5)) - 1;
			for (int32 j = 0; j < cols; j++) {
				int32 w = static_cast<int32>((j + 1) / xRatio + _T(0.5)) - 1;
				Mat temp = Mat::zeros(src.channels());
				for (int32 idx = lastCol; idx <= w; idx++) {
					for (int32 jdx = lastRow; jdx <= h; jdx++) {
						FOR_RANGE(z, 0, src.channels())
							temp(z) += src(jdx, idx, z);
					}
				}

				int32 count = (w - lastCol + 1) * (h - lastRow + 1);
				FOR_RANGE(z, 0, src.channels())
					img(i, j, z) = temp(z) / count;

				lastCol = w + 1; //下一个子块左上角的列坐标，行坐标不变
			}
			lastCol = 0; //子块的左上角列坐标，从0开始
			lastRow = h + 1; //子块的左上角行坐标
		}
	}
	break;
	case lzh::INTER_NEARLY:
		yRatio = 1 / yRatio;
		xRatio = 1 / xRatio;
		img.fill(0);
		for (int32 i = 0; i < rows; i++)
		{
			Val_* p = img.begin() + i * img.total();
			for (int32 j = 0; j < cols; j++)
			{
				int32 i_scale = _I(yRatio * i);   //依照高的比例计算原图相应坐标中的x，这里采用的是向下取整，当然四舍五入也可以
				int32 j_scale = _I(xRatio * j);  //依照宽的比例计算原图相应坐标中的y
				//cout << "i_scale: " << i_scale <<" j_scale: "<< j_scale << endl;
				for (int32 k = 0; k < img.channels(); k++)
					p[j*img.channels() + k] = src(i_scale, j_scale, k);
			}
		}
		break;
	case lzh::INTER_LINEAR: {
		mat_t h_scale_rate = 1 / yRatio;
		mat_t w_scale_rate = 1 / xRatio;
		img.fill(0);
		copyMakeBorder(src, src, 0, Round(yRatio), 0, Round(xRatio), BORDER_DEFAULT);
		int32 c = img.channels();
		for (int32 i = 0; i < rows; i++)
		{
			Val_* p = img.begin() + i * img.total();
			mat_t i_scale = h_scale_rate * i;
			int32 raw_i = _I(i_scale);
			mat_t u = i_scale - raw_i;
			for (int32 j = 0; j < cols; j++)
			{
				mat_t j_scale = w_scale_rate * j;

				int32 raw_j = _I(j_scale);
				mat_t v = j_scale - raw_j;

				//注意处理边界问题，容易越界
				if (raw_i + 1 >= src.rows() || raw_j + 1 >= src.cols())
				{
					for (int32 k = 0; k < img.channels(); k++)
						p[j*c + k] = src(raw_i, raw_j, k);
				}
				else {
					for (int32 k = 0; k < img.channels(); k++) {
						Val_* p1 = src.begin() + raw_i * src.total();
						mat_t x1 = p1[raw_j*c + k];  //f(i,j)
						mat_t x2 = p1[(raw_j + 1)*c + k];  //f(i,j+1)
						p1 = p1 + src.total();
						mat_t x3 = p1[raw_j*c + k];    //(i+1,j)
						mat_t x4 = p1[(raw_j + 1)*c + k];  //f(i+1,j+1) 

						p[j*c + k] = ((1 - u)*(1 - v)*x1 + (1 - u)*v*x2 + u * (1 - v)*x3 + u * v*x4);
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
	dst.set(img);
}
void lzh::resize(IMat src, OutputArray dst, Size newSize, ReductionMothed mothed)
{
	resize(src, dst, newSize.w / _T(src.cols()), newSize.h / _T(src.rows()), mothed);
}

/****************************************************************************
随机数
*****************************************************************************/
void lzh::Srandom()
{
	srand(uint32(time(NULL)));
}
mat_t lzh::generateGaussianNoise(Val mu, Val sigma)
{
	const mat_t epsilon = std::numeric_limits<mat_t>::min();
	const mat_t two_pi = _T(2.0*PI);


	static mat_t z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
		return z1 * sigma + mu;

	mat_t u1, u2;
	do
	{
		u1 = rand() * (_T(1.0) / RAND_MAX);
		u2 = rand() * (_T(1.0) / RAND_MAX);
	} while (u1 <= epsilon);

	z0 = sqrt(_T(-2.0) * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(_T(-2.0) * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}
OMat lzh::randSample(IMat src, int32 w, int32 h, int32 c)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif //MAT_DEBUG
	tools::check(w, h, c);
	Mat dst(w, h, c);
	for (int32 ind = 0; ind < src.size(); ind++)
		dst(ind) = randSample(src);
	return dst;
}
OMat lzh::randSample(IMat m, RANK rc, int32 num)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif //MAT_DEBUG
	Mat dst = m.cut(rand() % m.rows(), rc);
	for (int32 i = 1; i < num; i++) {
		dst = Mat(dst, m.cut(rand() % m.rows(), rc), rc);
	}
	return dst;
}
OMat lzh::Rand(int32 low, int32 top, Size3 size, bool isdouble)
{
#ifdef MAT_DEBUG
	tools::check(size.w, size.h, size.c);
	if (low >= top)
		THROW_INFO(ERR_INFO_VALUE);
#endif //MAT_DEBUG
	Mat m(size);
	for (int32 index = 0; index < m.len(); index++)
		m(index) = getRandData(low, top, isdouble);
	return m;
}
mat_t lzh::getRandData(int32 min, int32 max, bool isdouble)
{
#ifdef MAT_DEBUG
	if (min > max)
		THROW_INFO(ERR_INFO_VALUE);
#endif //MAT_DEBUG
	if (isdouble) {
		mat_t m1 = (mat_t)(rand() % 101) / 101;
		min++;
		mat_t m2 = (mat_t)((rand() % (max - min + 1)) + min);
		m2 = m2 - 1;
		return m1 + m2;
	}
	else {
		int32 m = rand() % (max - min) + 1 + min;
		return (mat_t)m;
	}
}
mat_t lzh::randSample(IMat src)
{
	Mat m = src;
	int32 h = rand() % m.rows();
	int32 w = rand() % m.cols();
	int32 depth = rand() % m.channels();
	return m(h, w, depth);
}
OMat lzh::mRange(Val low, Val top, Val gap)
{
#ifdef MAT_DEBUG
	if (low >= top)
		THROW_INFO(ERR_INFO_VALUE);
#endif //MAT_DEBUG
	int32 len = (int32)((top - low) / gap);
	return low + linspace(0, len - 1, len)*gap;
}
OMat lzh::linspace(Val low, Val top, int32 len)
{
#ifdef MAT_DEBUG
	if (low >= top)
		THROW_INFO(ERR_INFO_VALUE);
#endif //MAT_DEBUG
	tools::check(len, len);
	Mat mark(len);
	mark(0) = (mat_t)low;
	mat_t gap = _T(top - low) / (len - 1);
	for (int32 ind = 1; ind < len; ind++)
		mark(ind) = mark(ind - 1) + gap;
	return mark;
}
OMat lzh::Xavier(Size3 size, int32 n1, int32 n2)
{
	Mat m(size);
	Val_ *p = m;
	for (int32 i = 0; i < m.len(); ++i)
	{
		*p = generateGaussianNoise() * _T(1.0) / std::sqrt(_T(n1 + n2));
		//*p = generateGaussianNoise(0, 1) * sqrt(6.0f / (w_ + h_));
		p++;
	}
	return m;
}
OMat lzh::Xavier(int32 w, int32 h, int32 c, int32 n1, int32 n2)
{
	Mat m(w, h, c);
	Val_ *p = m;
	for (int32 i = 0; i < m.len(); ++i)
	{
		*p = generateGaussianNoise() * _T(1.0) / std::sqrt(_T(n1 + n2));
		//*p = generateGaussianNoise(0, 1) * sqrt(6.0f / (w_ + h_));
		p++;
	}
	return m;
}
OMat lzh::Random(Size3 size)
{
	Mat m(size);
	Val_ *p = m;
	for (int32 i = 0; i < m.len(); ++i)
	{
		*p = generateGaussianNoise();
		p++;
	}
	return m;
}
OMat lzh::Random(int32 w, int32 h, int32 c)
{
	Mat m(w, h, c);
	Val_ *p = m;
	for (int32 i = 0; i < m.len(); ++i)
	{
		*p = generateGaussianNoise();
		p++;
	}
	return m;
}
mat_t lzh::generateGaussian(Val x, Val sigma)
{
	return gauss_factor_1D_ * exp(-(x*x) / (2 * sigma*sigma))*(1 / sigma);
}
mat_t lzh::generateGaussian(Val x, Val y, Val sigma)
{
	mat_t sigma2 = sigma * sigma;
	return gauss_factor_1D_ / sigma2 * exp(-_T(0.5)*(x*x + y * y) / sigma2);
}
mat_t lzh::generateLoG(Val x, Val sigma)
{
	mat_t sigma2 = sigma * sigma;
	mat_t a = gauss_factor_1D_ / (sigma*sigma2);
	mat_t ex = exp(-(x*x) / (2 * sigma2));
	return a * ex + a * ex*(1 / sigma2)*x;
}
mat_t lzh::generateLoG(Val x, Val y, Val sigma)
{
	mat_t xx = x * x; mat_t yy = y * y; mat_t sigma2 = sigma * sigma;
	mat_t a = (-2 * sigma2 + xx + yy) / (sigma2* sigma2);
	mat_t b = exp(-((xx + yy) / (2 * sigma2)));
	return a * b;
}
mat_t lzh::generateDoG(Val x, Val sigma1, Val sigma2)
{
	return generateGaussian(x, sigma2) - generateGaussian(x, sigma1);
}
mat_t lzh::generateDoG(Val x, Val y, Val sigma1, Val sigma2)
{
	return generateGaussian(x, y, sigma2) - generateGaussian(x, y, sigma1);
}

/****************************************************************************
k均值聚类
*****************************************************************************/
void lzh::kmeans(IMat P_, InputOutputArray k, OutputArray classifier, int32 K, const uint32 iteration, const Val error)
{
	Mat P = P_;
	uint32 iterate = 0;
	Mat center(P.cols(), K);
	Mat group = P;
	Mat dist(P.rows(), K);
	Mat kclass(1, P.rows());

	//随机生成聚点
	for (int32 i = 0; i < K; ++i) {
		Mat p = P.row(rand() % P.rows());
		p.copy(center, i, i, 0, P.cols() - 1);
		for (int32 j = i; j != 0; j--)
			if (center.row(i) == center.row(i - 1)) {
				i--;
				break;
			}
	}

	mat_t error_ = _T(1);
	Mat point = center;
	Mat a0 = Mat::zeros(1, K);

	while (iterate++ != iteration && error_ > error) {
		//计算聚点与所有点的距离
		for (int32 i = 0; i < K; ++i) {
			for (int32 j = 0; j < P.rows(); ++j) {
				dist(i, j) = (center.cut(i, ROW) - group.cut(j, ROW)).norm(2);
			}
		}
		//数据点按最小距离分组
		for (int32 j = 0; j < P.rows(); ++j) {
			int32 min = 0;
			for (int32 i = 1; i < K; ++i) {
				if (dist(i, j) < dist(min, j)) {
					min = i;
				}
			}
			kclass(j) = _T(min);
		}
		//计算聚点与所属数据点的距离
		Mat a = Mat::zeros(1, K);
		for (int32 i = 0; i < K; ++i) {
			for (int32 j = 0; j < P.rows(); ++j) {
				if (kclass(j) == i)
					a(i) += dist(i, j);
			}
		}
		//计算与上一次距离的二范数
		error_ = (a0 - a).norm(2);
		if (error_ < error) {
			break;
		}
		a0 = a;
		Mat sum = Mat::zeros(K);
		Mat p = Mat::zeros(P.cols(), K);
		//计算聚点所属数据点坐标平均值作为新的聚点
		for (int32 i = 0; i < P.rows(); ++i) {
			sum((int32)kclass(i)) += 1;
			p((int32)kclass(i), ROW) += group(i, ROW);
		}
		for (int32 i = 0; i < K; ++i) {
			p(i, ROW) /= sum(i);
		}
		center = p;
	}
	tools::output(error_);
	k.set(kclass);
	classifier.set(center);
}

/****************************************************************************
求解方程
*****************************************************************************/
lzh::EQUATION lzh::SolveLinearEquation(IMat src, OutputArray dst_, Mat *simplest, Mat *mark)
{
	Mat answer, dst;
	RowSimplest(src, answer);
	int32 height = answer.rows();
	int32 width = answer.cols();
	int32 rank = height;
	int32 augmentedRank = rank;
	for (int32 i = 0; i < height; i++) {
		int32 augmented_count = 0;
		int32 rank_count = 0;
		for (int32 j = 0; j < width; j++) {
			if (j < width - 1) {
				if (answer.isZero(j + i * width)) {
					rank_count++;
					augmented_count++;
				}
			}
			else {
				if (answer.isZero(j + i * width)) {
					augmented_count++;
				}
			}
		}
		if (rank_count == width - 1)
			rank--;
		if (augmented_count == width)
			augmentedRank--;
	}
	EQUATION state;
	if (rank >= augmentedRank) {
		if (rank == height) {
			answer.col(width - 1).copyTo(dst);
			if (mark != nullptr)
				*mark = Mat::ones(height);
			state = SPECIAL_SOLUTION;
		}
		else {
			int32 freeparam = height - rank;
			int32 *concer = new int32[rank];
			int32 *markfree = new int32[freeparam];
			for (int32 h = 0; h < rank; h++) {
				for (int32 w = h; w < width; w++) {
					if (answer(h, w) == 1)
					{
						concer[h] = w; break;
					}
				}
			}
			int32 count = 0;
			for (int32 i = 0; i < height; i++) {
				bool flag = false;
				for (int32 j = 0; j < rank; j++)
					if (i == concer[j]) {
						flag = true;
						break;
					}
				if (flag)continue;
				markfree[count++] = i;
			}
			dst = Mat::zeros(freeparam, height);
			Mat param = Mat::eye(freeparam);
			for (int32 h = 0; h < param.rows(); h++) {
				for (int32 i = 0; i < rank; i++) {
					mat_t v = answer(i, width - 1);
					for (int32 j = 0; j < freeparam; j++) {
						v -= answer(i, markfree[j])*param(h, j);
					}
					dst(concer[i], h) = v;
				}
				for (int32 i = 0; i < freeparam; i++) {
					dst(markfree[i], h) = param(h, i);
				}
			}
			if (mark != nullptr) {
				*mark = Mat::ones(height);
				for (int32 i = 0; i < freeparam; i++) {
					mark->operator()(markfree[i]) = _T(0);
				}
			}
			FREE_ARRAY(concer);
			FREE_ARRAY(markfree);
			state = GENERAL_SOLUTION;
		}
	}
	else {
		state = NO_SOLUTION;
	}
	if (simplest != nullptr)
		*simplest = answer;
	dst_.set(dst);
	return state;
}

/****************************************************************************
激活函数/损失函数
*****************************************************************************/
OMat nn::Softmax(IMat x)
{
	Mat out;
	if (x.dims() == 3) {
		out = x.clone();
		for (int32 i = 0; i < x.rows(); ++i)
		{
			for (int32 j = 0; j < x.cols(); ++j)
			{
				Mat y_ = out.cut(i, j, CHANNEL);
				y_ -= Max(y_);
				Mat y_exp;
				Exp(y_, y_exp);
				mat_t y_sum = y_exp.sum();
				(y_exp / y_sum).copyTo(y_);
			}
		}
	}
	else
	{
		Mat y_ = x.clone();
		y_ -= Max(y_);
		Mat y_exp;
		Exp(y_, y_exp);
		mat_t y_sum = y_exp.sum();
		out = y_exp / y_sum;
	}
	return out;
}
OMat nn::L1(IMat y, IMat y0)
{
	return (y - y0).abs();
}
OMat nn::L2(IMat y, IMat y0)
{
	return (y - y0).pow(2);
}
OMat nn::Quadratic(IMat y, IMat y0)
{
	return _T(0.5) *(y - y0).pow(2);
}
OMat nn::CrossEntropy(IMat y, IMat y0)
{
	return -(y.mul(y0.log()));
}
OMat nn::SoftmaxCrossEntropy(IMat y, IMat y0)
{
	return CrossEntropy(y, Softmax(y0));
}
OMat nn::Sigmoid(IMat x)
{
	return (1.0 / (1.0 + (-x).exp()));
}
OMat nn::Tanh(IMat x)
{
	Mat dst = Sigmoid(_T(2) * x);
	return _T(2) * dst - _T(1);
}
OMat nn::ReLU(IMat x)
{
	Mat dst;
	Max(0, x, dst);
	return dst;
}
OMat nn::ELU(IMat x)
{
	Mat x1(x.size3());
	Val_ *p = x1;
	const Val_ *mat = x;
	for (int32 i = 0; i < x.len(); ++i) {
		if (*mat <= 0)
			*p = ELU_alpha * (exp(*mat) - 1);
		else
			*p = *mat;
		p++;
		mat++;
	}
	return x1;
}
OMat nn::SeLU(IMat x)
{
	return SELU_scale * ELU(x);
}
OMat nn::LReLU(IMat x)
{
	Mat x1(x.size3());
	Val_ *p = x1;
	const Val_ *mat = x;
	for (int32 i = 0; i < x.len(); ++i) {
		if (*mat <= 0)
			*p = *mat*LReLU_alpha;
		else
			*p = *mat;
		p++;
		mat++;
	}
	return x1;
}
OMat nn::D_Softmax(IMat y)
{
	return y.mul(1 - y);
}
OMat nn::D_L2(IMat y, IMat y0)
{
	return 2 * (y0 - y);
}
OMat nn::D_Quadratic(IMat y, IMat y0)
{
	return (y0 - y);
}
OMat nn::D_CrossEntropy(IMat y, IMat y0)
{
	return (y0 - y);
}
OMat nn::D_SoftmaxCrossEntropy(IMat y, IMat y0)
{
	return Softmax(y0) - y;
}
OMat nn::D_Sigmoid(IMat x)
{
	Mat s = Sigmoid(x);
	return s.mul(1 - s);
}
OMat nn::D_Tanh(IMat x)
{
	return 4 * D_Sigmoid(x);
}
OMat nn::D_ReLU(IMat x)
{
	Mat x1(x.size3());
	Val_ *p = x1;
	const Val_ *mat = x;
	for (int32 i = 0; i < x.len(); ++i) {
		if (*mat > 0)
			*p = 1;
		else
			*p = 0;
		p++;
		mat++;
	}
	return x1;
}
OMat nn::D_ELU(IMat x)
{
	Mat x1(x.size3());
	Val_ *p = x1;
	const Val_ *mat = x;
	for (int32 i = 0; i < x.len(); ++i) {
		if (*mat > 0)
			*p = 1;
		else if (*mat < 0)
			*p = ELU_alpha * exp(*mat);
		else
			*p = 0;
		p++;
		mat++;
	}
	return x1;
}
OMat nn::D_SELU(IMat x)
{
	return SELU_scale * D_ELU(x);
}
OMat nn::D_LReLU(IMat x)
{
	Mat x1(x.size3());
	Val_ *p = x1;
	const Val_ *mat = x;
	for (int32 i = 0; i < x.len(); ++i) {
		if (*mat > 0)
			*p = 1;
		else if (*mat < 0)
			*p = LReLU_alpha;
		else
			*p = 0;
		p++;
		mat++;
	}
	return x1;
}


/****************************************************************************
其他工具
*****************************************************************************/
std::string lzh::tools::createfile(std::string filename)
{
	return filename.substr(filename.rfind('\\') + 1);
}
std::string lzh::tools::createtype(std::string filename)
{
	return filename.substr(filename.rfind('.') + 1);
}
void lzh::tools::pause()
{
	fprintf(stderr, "waitting press enter key...\n");
	while (getchar() != '\n');
}
int32 lzh::tools::console(const std::string & str)
{
	return system(str.c_str());
}
void lzh::tools::binaryPrint(int32 value, int32 space)
{
	vec_8b p;
	while (value)
	{
		p.push_back((value & 0x01));
		value >>= 1;
	}if (p.empty()) { printf("0\n"); return; }
	reverse(p.begin(), p.end());
	int32 count = space == 0 ? 0 : p.size() % space == 0 ? space : p.size() % space;
	int32 cnt = 1;
	for (uint8 v : p) {
		printf("%u", v);
		if (space > 0) {
			if (cnt / count <= 1 ? cnt % count == 0 : (cnt - count) % space == 0) {
				printf(" ");
			}
			cnt += 1;
		}
	}
	printf("\n");
}
mat_t lzh::tools::saveDiv(mat_t div, mat_t v)
{
	return v == 0 ? (std::numeric_limits<mat_t>::max)() : div / v;
}
void lzh::tools::check(int32 w, int32 h, int32 c)
{
	if (w <= 0 || h <= 0 || c <= 0)
		THROW_INFO(ERR_INFO_VALUE);
}
std::vector<std::string> lzh::tools::strsplit(const std::string &str, int8 ch)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(str);
#endif //MAT_DEBUG
	size_t idx = 0;
	size_t offset = 0;
	std::vector<std::string> spl;
	while (true) {
		offset = str.find(ch, idx);
		if (offset == std::string::npos)break;
		spl.push_back(str.substr(idx, offset - idx));
		idx = offset + 1;
	}
	std::string v = str.substr(idx);
	if (v != "")
		spl.push_back(v);
	return spl;
}
void tools::readcsv(std::string filename, IOMat dst)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(filename);
#endif //MAT_DEBUG
	std::ifstream in(filename);
	CHECK_EXCEPTION(if (in.is_open()), THROW_INFO(ERR_INFO_FILE));
	std::vector<std::vector<mat_t>> vec;
	std::string str;
	while (std::getline(in, str))
	{
		vec.push_back(str2data<mat_t>(strsplit(str, ',')));
	}
	in.close();
	if (vec.empty())return;
	dst = Vec2Mat(vec);
}
void lzh::tools::readcsv(std::string filename, std::vector<std::vector<std::string>>& csv)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(filename);
#endif //MAT_DEBUG
	std::ifstream in(filename);
	CHECK_EXCEPTION(if (in.is_open()), THROW_INFO(ERR_INFO_FILE));
	std::vector<std::vector<std::string>> vec;
	std::string str;
	while (std::getline(in, str))
	{
		vec.push_back(strsplit(str, ','));
	}
	in.close();
	csv = vec;
}
std::string tools::Enum2String(PrintType type)
{
	std::string str;
	switch (type)
	{
	case lzh::MAT_FIXED:
		str = "FIXED INFO:以小数形式格式化输出";
		break;
	case lzh::MAT_SCIENTIFIC:
		str = "SCIENTIFIC INFO:以科学记数法形式格式化输出";
		break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(BorderTypes type)
{
	std::string str;
	switch (type)
	{
	case lzh::BORDER_CONSTANT:
		str = "BORDER_CONSTANT //!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`";
		break;
	case lzh::BORDER_REPLICATE:
		str = "BORDER_CONSTANT INFO://!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`";
		break;
	case lzh::BORDER_REFLECT:
		str = "BORDER_REPLICATE INFO://!< `aaaaaa|abcdefgh|hhhhhhh`";
		break;
	case lzh::BORDER_WRAP:
		str = "BORDER_REFLECT INFO://!< `fedcba|abcdefgh|hgfedcb`";
		break;
	case lzh::BORDER_REFLECT_101:
		str = "BORDER_REFLECT_101 INFO://!< `gfedcb|abcdefgh|gfedcba`";
		break;
		//case lzh::BORDER_TRANSPARENT:
		//	str = "BORDER_TRANSPARENT INFO://!< `uvwxyz|abcdefgh|ijklmno`";
		//	break;
		//case lzh::BORDER_ISOLATED:
		//	str = "BORDER_ISOLATED INFO://!< do not look outside of ROI";
		//	break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(MatErrorInfo type)
{
	return errinfo[type];
}
std::string lzh::tools::Enum2String(EQUATION type)
{
	std::string str;
	switch (type)
	{
	case lzh::SPECIAL_SOLUTION:
		str = "SPECIAL_SOLUTION INFO:方程有特解";
		break;
	case lzh::GENERAL_SOLUTION:
		str = "GENERAL_SOLUTION INFO:方程有通解";
		break;
	case lzh::NO_SOLUTION:
		str = "NO_SOLUTION INFO:方程无解";
		break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(ORDER type)
{
	std::string str;
	switch (type)
	{
	case lzh::MIN_TO_MAX:
		str = "MIN_TO_MAX INFO:从小到大";
		break;
	case lzh::MAX_TO_MIN:
		str = "MAX_TO_MIN INFO:从大到小";
		break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(RANK type)
{
	std::string str;
	switch (type)
	{
	case lzh::ROW:
		str = "ROW INFO:行方向";
		break;
	case lzh::COL:
		str = "COL INFO:列方向";
		break;
	case lzh::CHANNEL:
		str = "CHANNEL INFO:通道方向";
		break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(Dire type)
{
	std::string str;
	switch (type)
	{
	case lzh::LEFT:
		str = "LEFT INFO:左";
		break;
	case lzh::RIGHT:
		str = "RIGHT INFO:右";
		break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(ReductionMothed type)
{
	std::string str;
	switch (type)
	{
	case lzh::EqualIntervalSampling:
		str = "EqualIntervalSampling INFO:等间隔采样";
		break;
	case lzh::LocalMean:
		str = "LocalMean INFO:局部均值";
		break;
	default:
		break;
	}
	return str;
}
std::string lzh::tools::Enum2String(RotateAngle type)
{
	std::string str;
	switch (type)
	{
	case lzh::ROTATE_90_ANGLE:
		str = "ROTATE_90_ANGLE INFO:顺时针旋转90度";
		break;
	case lzh::ROTATE_180_ANGLE:
		str = "ROTATE_180_ANGLE INFO:顺时针旋转180度";
		break;
	case lzh::ROTATE_270_ANGLE:
		str = "ROTATE_270_ANGLE INFO:顺时针旋转270度";
		break;
	default:
		break;
	}
	return str;
}
//std::string lzh::tools::Enum2String(BSpline::BSplineType type)
//{
//	std::string str;
//	switch (type)
//	{
//	case BSpline::UNIFORM:
//		str = "UNIFORM INFO:均匀B样条曲线90度"; break;
//	case BSpline::QUASI_UNIFORM:
//		str = "QUASI_UNIFORM INFO:准均匀B样条曲线90度"; break;
//	default:
//		break;
//	}
//	return std::string();
//}



/****************************************************************************
计时器
*****************************************************************************/
#if defined(__linux__)
#include <sys/time.h>
#include <unistd.h>
Timer::Timer()
{
	start = (struct timeval*)malloc(sizeof(struct timeval));
	end = (struct timeval*)malloc(sizeof(struct timeval));
}
Timer::~Timer()
{
	FREE_PTR(start);
	FREE_PTR(end);
}
void Timer::Start()
{
	gettimeofday((struct timeval*)start, NULL);
}
mat_t Timer::End()
{
	gettimeofday((struct timeval*)end, NULL);
	return _T(((struct timeval*)end->tv_sec - (struct timeval*)start->tv_sec) * 1000.0 + (struct timeval*)end->tv_usec - (struct timeval*)start->tv_usec);
}
static struct timeval t1, t2;
void lzh::tools::StartCounter()
{
	gettimeofday(&t1, NULL);
}
mat_t lzh::tools::EndCounter()
{
	gettimeofday(&t2, NULL);
	return _T((t2.tv_sec - t1.tv_sec) * 1000.0 + t2.tv_usec - t1.tv_usec);
}
void lzh::tools::Wait(uint ms)
{
	sleep(ms);
}
#elif defined(_WIN32)
#include <windows.h>  
#include <io.h>
#include <direct.h>  
Timer::Timer()
{
	start = new LARGE_INTEGER();
	end = new LARGE_INTEGER();
	fc = new LARGE_INTEGER();
	QueryPerformanceFrequency((LARGE_INTEGER*)fc);
}
Timer::~Timer()
{
	FREE_PTR(start);
	FREE_PTR(end);
	FREE_PTR(fc);
}
void Timer::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)start);
}
mat_t Timer::End()
{
	QueryPerformanceCounter((LARGE_INTEGER*)end);
	return _T(((((LARGE_INTEGER*)end)->QuadPart - ((LARGE_INTEGER*)start)->QuadPart) * 1000.0) / ((LARGE_INTEGER*)fc)->QuadPart);
}

static LARGE_INTEGER cpuFreq;
static LARGE_INTEGER startTime;
static LARGE_INTEGER endTime;

void lzh::tools::Frequency()
{
	if (cpuFreq.QuadPart == 0)
		QueryPerformanceFrequency(&cpuFreq);
}
void lzh::tools::StartCounter()
{
	QueryPerformanceCounter(&startTime);
}
mat_t lzh::tools::EndCounter()
{
	QueryPerformanceCounter(&endTime);
	return _T(((endTime.QuadPart - startTime.QuadPart) * 1000.0) / cpuFreq.QuadPart);
}
/**
@brief getFiles 得到路径下所有文件的路径
@param path 文件夹路径
@param files 保存path下的所有文件路径
*/
void lzh::tools::getFiles(std::string path, std::vector<std::string>& files)
{
	//文件句柄  
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
std::string lzh::tools::show_path()
{
	int8 buffer[260];
	_getcwd(buffer, 260);
	return std::string(buffer);
}
void lzh::tools::Wait(uint32 ms)
{
	Sleep(ms);
}
void print(int colorCode, const char * info, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
	va_list _ArgList;
	__crt_va_start(_ArgList, info);
	_vfprintf_l(stdout, info, NULL, _ArgList);
	__crt_va_end(_ArgList);
}
#endif