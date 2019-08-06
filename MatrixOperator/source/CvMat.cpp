#include "CvMat.h"
#include "Mat.h"
#include "MatApi.h"
#include "MatOperator.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace lzh;

lzh::uint32 CvMat::print_width = 6;
lzh::uint32 CvMat::print_precision = 4;
lzh::PrintType CvMat::print_type = lzh::MAT_FIXED;
/****************************************************************************
接口类
*****************************************************************************/
PtrMat::PtrMat()
{
	init(0, 0, 0, 0);
}
PtrMat::PtrMat(int32 size, int32 type)
{
	create(size, type);
}
PtrMat::PtrMat(const PtrMat & m)
{
	init(m.data, m.type, m.len, m.refcount);
	if (refcount)
		MAT_XADD(refcount, 1);
}
PtrMat::PtrMat(int32 n, const void *p, int32 type)
{
	init(p, type, n, 0);
}
PtrMat::~PtrMat() { release(); }
void PtrMat::create(uint32 len, int32 type) {
	release();
	this->len = len;
	this->type = type;
	uint32 totalsize = len * calmemsize(type);
	data = (uint8*)fastMalloc(totalsize + sizeof(int32));
	refcount = (int32*)(((uint8*)data) + totalsize);
	*refcount = 1;
}
void PtrMat::addref() {
	if (refcount)
		MAT_XADD(refcount, 1);
}
void PtrMat::release() {
	if (refcount && MAT_XADD(refcount, -1) == 1)
		fastFree(data);
	init(0, 0, 0, 0);
}
bool PtrMat::operator==(void * m) const {
	return (this->data == m);
}
bool PtrMat::operator!=(void * m) const {
	return (this->data != m);
}
PtrMat & PtrMat::operator=(const PtrMat & m) {
	if (this == &m)
		return *this;

	if (m.refcount)
		MAT_XADD(m.refcount, 1);

	release();
	data = m.data;
	len = m.len;
	type = m.type;
	refcount = m.refcount;
	return *this;
}
uint8 * PtrMat::operator()()
{
	return data;
}
const uint8 * lzh::PtrMat::operator()() const
{
	return data;
}
uint8 * PtrMat::operator+(int32 i) const
{
	return (uint8*)offset(i);
}
uint8 * PtrMat::operator-(int32 i) const
{
	return (uint8*)reduce(i);
}
bool PtrMat::empty() const
{
	return data == nullptr;
}
int32 PtrMat::depth() const {
	return MAT_GETVALUE(type);
}
int32 PtrMat::getTp() const
{
	return type;
}
int32 PtrMat::size() const {
	return len;
}
int32 & PtrMat::T() {
	return type;
}
int32 & PtrMat::L() {
	return len;
}
uint8 *& PtrMat::P() {
	return data;
}
uint8 * PtrMat::obj()const {
	return (uint8*)data;
}
void * PtrMat::index(int32 i) const
{
#ifdef MAT_DEBUG
	CHECK_PTR(data);
	CHECK_INDEX(i, len);
#endif // MAT_DEBUG
	switch (depth()) {
	case lzh::TP_8S:	return MAT_INDEX(int8, data, i);
	case lzh::TP_8U:	return MAT_INDEX(uint8, data, i);
	case lzh::TP_16S:	return MAT_INDEX(int16, data, i);
	case lzh::TP_16U:	return MAT_INDEX(uint16, data, i);
	case lzh::TP_32S:	return MAT_INDEX(int32, data, i);
	case lzh::TP_32U:	return MAT_INDEX(uint32, data, i);
	case lzh::TP_64S:	return MAT_INDEX(int64, data, i);
	case lzh::TP_64U:	return MAT_INDEX(uint64, data, i);
	case lzh::TP_32F:	return MAT_INDEX(float32, data, i);
	case lzh::TP_64F:	return MAT_INDEX(float64, data, i);
	case lzh::TP_64D:	return MAT_INDEX(float64_, data, i);
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
}
void * PtrMat::add(int32 i) const
{
	return index(i);
}
void * PtrMat::reduce(int32 i) const
{
#ifdef MAT_DEBUG
	CHECK_PTR(data);
	CHECK_INDEX(i, len);
#endif // MAT_DEBUG
	switch (depth()) {
	case lzh::TP_8S:	return MAT_GETPTR(int8, data) - i;
	case lzh::TP_8U:	return MAT_GETPTR(uint8, data) - i;
	case lzh::TP_16S:	return MAT_GETPTR(int16, data) - i;
	case lzh::TP_16U:	return MAT_GETPTR(uint16, data) - i;
	case lzh::TP_32S:	return MAT_GETPTR(int32, data) - i;
	case lzh::TP_32U:	return MAT_GETPTR(uint32, data) - i;
	case lzh::TP_64S:	return MAT_GETPTR(int64, data) - i;
	case lzh::TP_64U:	return MAT_GETPTR(uint64, data) - i;
	case lzh::TP_32F:	return MAT_GETPTR(float32, data) - i;
	case lzh::TP_64F:	return MAT_GETPTR(float64, data) - i;
	case lzh::TP_64D:	return MAT_GETPTR(float64_, data) - i;
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
}
void * PtrMat::offset(int32 i) const {
	return add(i);
}
int32 * lzh::PtrMat::memCount() const
{
	return refcount;
}
void PtrMat::set(const void * p, int32 length, int32 data_type) {
	data = (uint8*)p; type = data_type; len = length;
}
void lzh::PtrMat::set(const void * p, int32 length, int32 data_type, const int32 * count) {
	data = (uint8*)p; type = data_type; len = length; refcount = (int32 *)count;
}
void lzh::PtrMat::set(const Mat & mat) {
	if (!empty())
		release();
	set(mat.data(), mat.len(), MAT_T, mat.memCount()); addref();
}
void PtrMat::init(const void* p, int32 type, int32 len, const int32 *count) {
	data = (uint8*)p; this->type = type; this->len = len; refcount = (int32*)count;
}
void PtrMat::set(const PtrMat & ptr) {
	data = ptr.data; type = ptr.type; len = ptr.len;
}


/****************************************************************************
任意类型矩阵类
*****************************************************************************/
CvMat::CvMat()
{
	init();
	checkSquare();
}
CvMat::CvMat(int32 w, int32 flags, ColorGamut cg)
{
	init();
	create(w, flags, cg);
}
CvMat::CvMat(int32 w, int32 h, int32 flags, ColorGamut cg)
{
	init();
	create(w, h, flags, cg);
}
CvMat::CvMat(int32 w, int32 h, int32 c, int32 flags, ColorGamut cg)
{
	init();
	create(w, h, c, flags, cg);
}
CvMat::CvMat(Size size_, int32 flags, ColorGamut cg)
{
	init();
	create(size_.w, size_.h, flags, cg);
}
CvMat::CvMat(Size size_, int32 c, int32 flags, ColorGamut cg)
{
	init();
	create(size_.w, size_.h, c, flags, cg);
}
CvMat::CvMat(Size3 size_, int32 flags, ColorGamut cg)
{
	init();
	create(size_.w, size_.h, size_.c, flags, cg);
}
CvMat::CvMat(ColorGamut colorGamut, Size size, int32 flags)
{
	init();
	createColorGamut(colorGamut, size, flags);
}
CvMat::CvMat(const PtrMat & src, Size3 sz, bool copyData)
{
	init();
	if (copyData)
	{
		create(sz, src.depth());
		memcpy(data, src.obj(), memsize());
	}
	else {
		setsize(sz.w, sz.h, sz.c);
		data = src;
	}
}
CvMat::CvMat(const void * p, Size3 sz, int32 flags)
{
	init();
	create(sz, flags);
	memcpy(data, p, memsize());
}
CvMat::CvMat(int32 w, const void * data, int32 flags, bool copyData)
{
	init();
	*this = CvMat(w, 1, 1, data, flags, copyData);
}
CvMat::CvMat(int32 w, int32 h, const void * data, int32 flags, bool copyData)
{
	init();
	*this = CvMat(w, h, 1, data, flags, copyData);
}
CvMat::CvMat(int32 w, int32 h, int32 c, const void * data, int32 flags, bool copyData)
{
	init();
	if (!copyData) {
		setsize(w, h, c);
		this->data.set(data, len(), flags);
	}
	else {
		create(w, h, c, flags);
		memcpy(this->data, data, memsize());
	}
}
CvMat::CvMat(Size size, const void * data, int32 flags, bool copyData)
{
	init();
	*this = CvMat(size.w, size.h, 1, data, flags, copyData);
}
CvMat::CvMat(Size size, int32 c, const void * data, int32 flags, bool copyData)
{
	init();
	*this = CvMat(size.w, size.h, c, data, flags, copyData);
}
CvMat::CvMat(Size3 size, const void * data, int32 flags, bool copyData)
{
	init();
	*this = CvMat(size.w, size.h, size.c, data, flags, copyData);
}
CvMat::CvMat(int32 w, int32 h, int32 c, MatStep step, const void * data, int32 flags)
{
	init();
	setsize(w, h, c);
	stride = step;
	this->data.set(data, h*total(), flags);
}
CvMat::CvMat(const CvMat &src)
{
	init();
	*this = src;
}
lzh::CvMat::CvMat(const _InputArray & inputarray)
{
	init(); *this = inputarray.getCvMat();
}
CvMat::CvMat(const CvMat &a, const CvMat &b, RANK merge)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(b);
	CHECK_TYPE_(a.depth(), b.depth());
#endif //MAT_DEBUG
	init();
	if (merge == ROW) {
		if (a.cols == b.cols) {
			create(a.cols, a.rows + b.rows, a.c_, a.depth());
			memcpy(data, a.data, a.memsize());
			memcpy(data.offset(a.len()), b.data, b.memsize());
		}
	}
	else if (merge == COL) {
		if (a.rows == b.rows) {
			create(a.cols + b.cols, a.rows, a.c_, a.depth());
			for (int32 i = 0; i < rows; i++) {
				memcpy(data.offset(i * cols*c_),
					a.data.offset(i * a.cols*c_),
					a.cols*c_ * calmemsize(depth()));
				memcpy(data.offset(i * cols*c_ + a.cols*c_),
					b.data.offset(i * b.cols*c_),
					b.cols*c_ * calmemsize(depth()));
			}
		}
	}
}
lzh::CvMat::CvMat(const Mat & src, int32 flags)
{
	init();
	if (flags == MAT_T)*this = src;
	else {
		create(src.size3(), flags);
		FOR_RANGE(i, 0, len())
			set(i, src(i));
	}
}
CvMat::~CvMat()
{
	//release();
	setsize(0, 0, 0);
}
void CvMat::create(int32 w, int32 flags, ColorGamut cg)
{
	create(w, 1, 1, flags, cg);
}
void CvMat::create(int32 w, int32 h, int32 flags, ColorGamut cg)
{
	create(w, h, 1, flags, cg);
}
void CvMat::create(int32 w, int32 h, int32 c, int32 flags, ColorGamut cg)
{
	release();
	lzh::tools::check(w, h, c);
	setsize(w, h, c);
	data.create(len(), flags);
	_type = cg;
#ifdef MAT_DEBUG
	CHECK_PTR(data.obj());
#endif //MAT_DEBUG
}
void CvMat::create(Size size, int32 flags, ColorGamut cg)
{
	create(size.w, size.h, flags, cg);
}
void CvMat::create(Size3 size, int32 flags, ColorGamut cg)
{
	create(size.w, size.h, size.c, flags, cg);
}
void CvMat::createColorGamut(ColorGamut colorGamut, Size sz, int32 flags)
{
	int32 channel_ = 1;
	switch (colorGamut)
	{
	case lzh::ColorGamutCustom: case lzh::ColorGamutGray: channel_ = 1; break;
	case lzh::ColorGamutRGB: case lzh::ColorGamutBGR:
	case lzh::ColorGamutXYZ:case lzh::ColorGamutLab:
	case lzh::ColorGamutHSV: channel_ = 3; break;
	case lzh::ColorGamutRGBA:case lzh::ColorGamutBGRA:channel_ = 4; break;
	default:
		THROW_INFO_STR("不支持的色域!, 请使用->[ColorGamutCustom, ColorGamutGray, ColorGamutRGB, ColorGamutBGR, ColorGamutXYZ, ColorGamutLab, ColorGamutHSV, ColorGamutRGBA ColorGamutBGRA]");
	}
	create(sz.h, sz.w, channel_, flags, colorGamut);
}
mat_t CvMat::First() const
{
	return data.get<mat_t>(0);
}
mat_t CvMat::Last() const
{
	return data.get<mat_t>(data.size() - 1);
}
int32 * CvMat::memCount() const
{
	return data.memCount();
}
PtrMat & CvMat::ptr()
{
	return data;
}
const PtrMat& CvMat::ptr() const
{
	return data;
}
const Mat CvMat::toMat() const
{
	return Mat(*this);
}
bool lzh::CvMat::isDeepCopy() const
{
	return data.memCount() != nullptr;
}
uint32 CvMat::memsize() const
{
	return calmemsize(depth()) * rows*cols*c_;
}
void CvMat::DimCheck()const
{
	if (c_ != 1) {
		THROW_INFO(ERR_INFO_DIM);
	}
}
void CvMat::copy(CvMat &src, int32 Row_Start, int32 Row_End, int32 Col_Start, int32 Col_End)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	CHECK_TYPE_(depth(), src.depth());
#endif // MAT_DEBUG
	int32 hei = Row_End - Row_Start + 1;
	int32 wid = Col_End - Col_Start + 1;
	lzh::tools::check(hei, wid);
	if (src.data == nullptr) {
		src = zeros(wid, hei, c_, depth());
	}
	for (int32 y = Row_Start, j = 0; y <= Row_End; y++, j++)
		for (int32 x = Col_Start, i = 0; x <= Col_End; x++, i++)
			for (int32 z = 0; z < c_; z++)
				src.set(y, x, z, data, toidx(y, x, z));
}
void CvMat::swap(CvMat &src)const
{
	src.setvalue(*this);
}
const CvMat CvMat::addones(Dire dire) const
{
	return addvalue(dire, 1);
}
const CvMat CvMat::addzeros(Dire dire) const
{
	return addvalue(dire, 0);
}
void CvMat::mChannel(const CvMat & src, int32 channels)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	CHECK_MATRIX(src.data);
	CHECK_TYPE_(depth(), src.depth());
	if (rows != src.rows || cols != src.cols || channels >= c_)
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	for (int32 i = 0; i < rows; ++i) {
		for (int32 j = 0; j < cols; ++j) {
			set(i, j, channels, src, src.toidx(i, j));
		}
	}
}
void CvMat::mChannel(const CvMat & src, int32 w, int32 h)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	CHECK_MATRIX(src.data);
	CHECK_TYPE_(depth(), src.depth());
	if (this->rows <= rows || this->cols <= cols || src.channels() != c_)
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	for (int32 i = 0; i < c_; ++i)
		set(rows, cols, i, src, src.toidx(i));
}
void CvMat::reshape(Size3 size)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (len() != size.area())
		THROW_INFO(ERR_INFO_UNLESS);
#endif // MAT_DEBUG
	setsize(size.w, size.h, size.c);
}
void CvMat::reshape(int32 w, int32 h, int32 c)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (len() != h * w*c)
		THROW_INFO(ERR_INFO_UNLESS);
#endif // MAT_DEBUG
	setsize(w, h, c);
}
bool CvMat::setSize(int32 w, int32 h, int32 c)
{
	if (h*w*c > 0) {
		create(w, h, c, depth());
		return true;
	}
	if (len() == h * w * c) {
		setsize(w, h, c);
		return true;
	}
	return false;
}
void CvMat::setvalue(const CvMat &src)
{
	create(src.size3(), src.depth());
	memcpy(data, src.data, src.memsize());
}
void CvMat::setAdj()
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	if (square)
		*this = adj();
	else THROW_INFO(ERR_INFO_ADJ);
}
void CvMat::setTran()
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	*this = t();
}
void lzh::CvMat::setColorGamut(ColorGamut cg)
{
	_type = cg;
}
void CvMat::setInv()
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	if (enable() == 0)
		*this = inv();
	else THROW_INFO(ERR_INFO_INV);
}
void CvMat::setPow(lzh::mat_t num)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	if (enable() == 0)
		*this = pow(num);
	else THROW_INFO(ERR_INFO_POW);
}
void CvMat::setIden()
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	if (enable() == 0)
		*this = eye(cols, depth());
	else THROW_INFO(ERR_INFO_IND);
}

lzh::Size3 CvMat::size3() const
{
	return Size3(cols, rows, c_);
}
int32 CvMat::total() const
{
	return stride.size();
}
int32 lzh::CvMat::total_() const
{
	return cols * c_;
}
int32 CvMat::dims() const
{
	return dim;
}
MatStep CvMat::step() const
{
	return stride;
}
Point lzh::CvMat::center() const
{
	return Point(cols / 2, rows / 2);
}
int32 CvMat::depth() const
{
	return data.depth();
}
int32 CvMat::type() const
{
	return data.getTp();
}
int32 CvMat::channels() const
{
	return c_;
}
int32 CvMat::rank() const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (dim != 2)
		THROW_INFO(ERR_INFO_NOT2D);
#endif //MAT_DEBUG
	int32 rank = rows;
	for (int32 i = 0; i < rows; i++) {
		int32 count = 0;
		for (int32 j = 0; j < cols; j++) {
			if (isValue(toidx(j, i * cols), 0)) {
				count++;
			}
		}
		if (count == rows)
			rank--;
	}
	return rank;
}
ColorGamut lzh::CvMat::colorGamut() const
{
	return _type;
}
lzh::Size CvMat::size()const
{
	return Size(cols, rows);
}

int32 CvMat::toidx(int32 i) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (i >= len())
		THROW_INFO(ERR_INFO_MEMOUT);
#endif //MAT_DEBUG
	int32 i0 = i / total_();
	int32 i1 = (i - i0 * total_()) / c_;
	int32 i2 = i % c_;
	return toidx(i0, i1, i2);
	//return i * stride[1] / c_;
}
int32 CvMat::toidx(int32 i, int32 j) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (i*j >= len() || i > rows || j > cols)
		THROW_INFO(ERR_INFO_MEMOUT);
#endif //MAT_DEBUG
	return (i * stride[0] + j) * stride[1];
}
int32 CvMat::toidx(int32 i, int32 j, int32 k) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (i*j >= len() || i > rows || j > cols || k > c_)
		THROW_INFO(ERR_INFO_MEMOUT);
#endif //MAT_DEBUG
	return (i * stride[0] + j) * stride[1] + k;
}

int32 CvMat::len()const
{
	return rows * cols * c_;
}
int32 lzh::CvMat::elementlen() const
{
	return rows * total();
}
int32 CvMat::enable()const
{
	if (data == nullptr)
		return -1;
	if (!square)
		return -2;
	return 0;
}
bool CvMat::empty()const
{
	return (data == nullptr);
}
bool CvMat::Square()const
{
	return square;
}
void CvMat::set(int32 i, const void * v, int32 addr_offset)
{
	setp(toidx(i), v, addr_offset);
}
void CvMat::set(int32 i0, int32 i1, const void * v, int32 addr_offset)
{
	setp(toidx(i0, i1), v, addr_offset);
}
void CvMat::set(int32 i0, int32 i1, int32 i2, const void * v, int32 addr_offset)
{
	setp(toidx(i0, i1, i2), v, addr_offset);
}
void CvMat::assign(int32 i, int32 j)
{
	switch (depth()) {
	case lzh::TP_8S:	set(i, *MAT_GETPTR(int8, data.index(j))); break;
	case lzh::TP_8U:	set(i, *MAT_GETPTR(uint8, data.index(j))); break;
	case lzh::TP_16S:	set(i, *MAT_GETPTR(int16, data.index(j))); break;
	case lzh::TP_16U:	set(i, *MAT_GETPTR(uint16, data.index(j))); break;
	case lzh::TP_32S:	set(i, *MAT_GETPTR(int32, data.index(j))); break;
	case lzh::TP_32U:	set(i, *MAT_GETPTR(uint32, data.index(j))); break;
	case lzh::TP_64S:	set(i, *MAT_GETPTR(int64, data.index(j))); break;
	case lzh::TP_64U:	set(i, *MAT_GETPTR(uint64, data.index(j))); break;
	case lzh::TP_32F:	set(i, *MAT_GETPTR(float32, data.index(j))); break;
	case lzh::TP_64F:	set(i, *MAT_GETPTR(float64, data.index(j))); break;
	case lzh::TP_64D:	set(i, *MAT_GETPTR(float64_, data.index(j))); break;
	default:THROW_INFO(ERR_INFO_TYPE);
	}
}
void CvMat::swap(int32 i, int32 j)
{
	i = toidx(i); j = toidx(j);
	switch (depth()) {
	case lzh::TP_8S:	lzh::__swap(*MAT_GETPTR(int8, data.index(i)), *MAT_GETPTR(int8, data.index(j))); break;
	case lzh::TP_8U:	lzh::__swap(*MAT_GETPTR(uint8, data.index(i)), *MAT_GETPTR(uint8, data.index(j))); break;
	case lzh::TP_16S:	lzh::__swap(*MAT_GETPTR(int16, data.index(i)), *MAT_GETPTR(int16, data.index(j))); break;
	case lzh::TP_16U:	lzh::__swap(*MAT_GETPTR(uint16, data.index(i)), *MAT_GETPTR(uint16, data.index(j))); break;
	case lzh::TP_32S:	lzh::__swap(*MAT_GETPTR(int32, data.index(i)), *MAT_GETPTR(int32, data.index(j))); break;
	case lzh::TP_32U:	lzh::__swap(*MAT_GETPTR(uint32, data.index(i)), *MAT_GETPTR(uint32, data.index(j))); break;
	case lzh::TP_64S:	lzh::__swap(*MAT_GETPTR(int64, data.index(i)), *MAT_GETPTR(int64, data.index(j))); break;
	case lzh::TP_64U:	lzh::__swap(*MAT_GETPTR(uint64, data.index(i)), *MAT_GETPTR(uint64, data.index(j))); break;
	case lzh::TP_32F:	lzh::__swap(*MAT_GETPTR(float32, data.index(i)), *MAT_GETPTR(float32, data.index(j))); break;
	case lzh::TP_64F:	lzh::__swap(*MAT_GETPTR(float64, data.index(i)), *MAT_GETPTR(float64, data.index(j))); break;
	case lzh::TP_64D:	lzh::__swap(*MAT_GETPTR(float64_, data.index(i)), *MAT_GETPTR(float64_, data.index(j))); break;
	default:THROW_INFO(ERR_INFO_TYPE);
	}
}
const CvMat CvMat::add(const CvMat & m)
{
	return *this + m;
}
const CvMat CvMat::reduce(const CvMat & m)
{
	return *this - m;
}
const CvMat CvMat::mul(const CvMat & b)
{
	CvMat mat;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(data);
	CHECK_MATRIX_(b);
	CHECK_TYPE_(depth(), b.depth());
#endif //MAT_DEBUG
	if (b.rows == 1 && b.cols == 1 && channels() == b.channels()) {
		mat.create(size3(), depth());
		for (int32 z = 0; z < mat.channels(); z++) {
			mat_t v = b(z);
			for (int32 i = 0; i < mat.rows; i++)
				for (int32 j = 0; j < mat.cols; j++)
					mat.set(i, j, z, operator()(i, j, z) * v);
		}
	}
	else if (rows == 1 && cols == 1 && channels() == b.channels())
	{
		mat.create(b.size3(), depth());
		for (int32 z = 0; z < mat.channels(); z++) {
			mat_t v = get_(z);
			for (int32 i = 0; i < mat.rows; i++)
				for (int32 j = 0; j < mat.cols; j++)
					mat.set(i, j, z, b(i, j, z) * v);
		}
	}
#ifdef MAT_DEBUG
	else if (rows != b.rows || cols != b.cols || channels() != b.channels())
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	else {
		mat.create(size3(), depth());
		for (int32 ind = 0; ind < len(); ind++)
			mat.set(ind, get_(ind) * b(ind));
	}
	return mat;
}
const CvMat lzh::CvMat::div(const CvMat & m)
{
	return *this / m;
}
lzh::mat_t CvMat::get_(int32 i) const
{
	return get<mat_t>(i);
}

mat_t CvMat::get_(int32 i0, int32 i1) const
{
	return get<mat_t>(i0, i1);
}

mat_t CvMat::get_(int32 i0, int32 i1, int32 i2) const
{
	return get<mat_t>(i0, i1, i2);
}
int32 CvMat::rankSize(RANK r) const
{
	switch (r)
	{
	case lzh::ROW:return rows;
	case lzh::COL:return cols;
	case lzh::CHANNEL:return c_;
	default:THROW_INFO(ERR_INFO_UNLESS);
	}
	return rows;
}
void CvMat::save(std::string file, bool binary) const
{
	if (binary) {
		FILE *out = fopen((file + ".bin").c_str(), "wb");
		if (out) {
			save(out);
			fclose(out);
		}
		else {
			THROW_INFO(ERR_INFO_FILE);
		}
	}
	else {
		std::ofstream out(file);
		if (out.is_open()) {
			show(out);
			out.close();
		}
		else {
			THROW_INFO(ERR_INFO_FILE);
		}
	}
}
void CvMat::save(FILE * out) const
{
	if (out) {
		int32 param[4] = { cols, rows, c_, data.depth() };
		fwrite(param, sizeof(int32) * 4, 1, out);
		fwrite(data, memsize(), 1, out);
	}
	else {
		THROW_INFO(ERR_INFO_FILE);
	}
}
void CvMat::load(std::string file)
{
	FILE *in = fopen((file + ".bin").c_str(), "rb");
	if (in) {
		load(in);
		fclose(in);
	}
	else {
		THROW_INFO(ERR_INFO_FILE);
	}
}
void CvMat::load(FILE * in)
{
	if (in) {
		int32 param[4] = { 0 };
		fread(param, sizeof(int32) * 4, 1, in);
		create(param[0], param[1], param[2], param[3]);
		fread(data, memsize(), 1, in);
	}
	else {
		THROW_INFO(ERR_INFO_FILE);
	}
}
void CvMat::copyTo(CvMat & mat) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	mat.create(size3(), depth());
	memcpy(mat, data, memsize());
}
void CvMat::setTo(CvMat mat) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	FOR_RANGE(i, 0, len()) {
		mat.set(i, get_(i));
	}
}
void CvMat::convertTo(CvMat & m, int32 type) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	m.create(size3(), type);
	if (type == depth())
		memcpy(m, data, memsize());
	else
		FOR_RANGE(i, 0, len())
		m.set(i, get_(i));
}
const CvMat CvMat::convert(int32 type) const
{
	CvMat cv;
	convertTo(cv, type);
	return cv;
}
void CvMat::setAddOnes(Dire dire)
{
	*this = addones(dire);
}
void CvMat::setAddZeros(Dire dire)
{
	*this = addzeros(dire);
}
void CvMat::release()
{
	data.release();
}
int32 CvMat::toX(int32 index)const
{
	return (index / c_) % cols;
}
int32 CvMat::toY(int32 index)const
{
	return (index / c_) / cols;
}
int32 CvMat::toZ(int32 index) const
{
	return index % c_;
}
bool CvMat::isZero(int32 i) const
{
	switch (depth()) {
	case lzh::TP_8S:	return MAT_GETARRAY(int8, data.obj(), i) == (int8)0;
	case lzh::TP_8U:	return MAT_GETARRAY(uint8, data.obj(), i) == (uint8)0;
	case lzh::TP_16S:	return MAT_GETARRAY(int16, data.obj(), i) == (int16)0;
	case lzh::TP_16U:	return MAT_GETARRAY(uint16, data.obj(), i) == (uint16)0;
	case lzh::TP_32S:	return MAT_GETARRAY(int32, data.obj(), i) == (int32)0;
	case lzh::TP_32U:	return MAT_GETARRAY(uint32, data.obj(), i) == (uint32)0;
	case lzh::TP_64S:	return MAT_GETARRAY(int64, data.obj(), i) == (int64)0;
	case lzh::TP_64U:	return MAT_GETARRAY(uint64, data.obj(), i) == (uint64)0;
	case lzh::TP_32F:	return MAT_GETARRAY(float32, data.obj(), i) == (float32)0;
	case lzh::TP_64F:	return MAT_GETARRAY(float64, data.obj(), i) == (float64)0;
	case lzh::TP_64D:	return MAT_GETARRAY(float64_, data.obj(), i) == (float64_)0;
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
}
bool lzh::CvMat::isZero(Point p) const
{
	return isZero(toidx(p.y, p.x));
}
bool CvMat::isOne(int32 i) const
{
	switch (depth()) {
	case lzh::TP_8S:	return MAT_GETARRAY(int8, data.obj(), i) == (int8)1;
	case lzh::TP_8U:	return MAT_GETARRAY(uint8, data.obj(), i) == (uint8)1;
	case lzh::TP_16S:	return MAT_GETARRAY(int16, data.obj(), i) == (int16)1;
	case lzh::TP_16U:	return MAT_GETARRAY(uint16, data.obj(), i) == (uint16)1;
	case lzh::TP_32S:	return MAT_GETARRAY(int32, data.obj(), i) == (int32)1;
	case lzh::TP_32U:	return MAT_GETARRAY(uint32, data.obj(), i) == (uint32)1;
	case lzh::TP_64S:	return MAT_GETARRAY(int64, data.obj(), i) == (int64)1;
	case lzh::TP_64U:	return MAT_GETARRAY(uint64, data.obj(), i) == (uint64)1;
	case lzh::TP_32F:	return MAT_GETARRAY(float32, data.obj(), i) == (float32)1;
	case lzh::TP_64F:	return MAT_GETARRAY(float64, data.obj(), i) == (float64)1;
	case lzh::TP_64D:	return MAT_GETARRAY(float64_, data.obj(), i) == (float64_)1;
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
}
bool lzh::CvMat::isOne(Point p) const
{
	return isOne(toidx(p.y, p.x));
}
bool CvMat::compare(int32 i1, int32 i2, int32 op) const
{
	bool state = false;
	switch (depth()) {
	case lzh::TP_8S: {
		const int8* p = (const int8*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_8U: {
		const uint8* p = (const uint8*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_16S: {
		const int16* p = (const int16*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_16U: {
		const uint16* p = (const uint16*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_32S: {
		const int32* p = (const int32*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_32U: {
		const uint32* p = (const uint32*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_64S: {
		const int64* p = (const int64*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_64U: {
		const uint64* p = (const uint64*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_32F: {
		const float32* p = (const float32*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_64F: {
		const float64* p = (const float64*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	case lzh::TP_64D: {
		const float64_* p = (const float64_*)data.obj();
		PTR_COMPARE(p, op, i1, i2, state);
		break; }
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
	return state;
}
void lzh::CvMat::BitNot(int32 i)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	switch (depth())
	{
	case lzh::TP_8S:	at<int8>(i) = int8(~at<int8>(i));		break;
	case lzh::TP_8U:	at<uint8>(i) = uint8(~at<uint8>(i));	break;
	case lzh::TP_16S:	at<int16>(i) = int16(~at<int16>(i)); 	break;
	case lzh::TP_16U:	at<uint16>(i) = uint16(~at<uint16>(i)); break;
	case lzh::TP_32S:	at<int32>(i) = int32(~at<int32>(i)); 	break;
	case lzh::TP_32U:	at<uint32>(i) = uint32(~at<uint32>(i)); break;
	case lzh::TP_64S:	at<int64>(i) = int64(~at<int64>(i)); 	break;
	case lzh::TP_64U:	at<uint64>(i) = uint64(~at<uint64>(i));	break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
void lzh::CvMat::BitAnd(int32 i, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	switch (depth())
	{
	case lzh::TP_8S:	at<int8>(i) &= val.get<int8>(); 	break;
	case lzh::TP_8U:	at<uint8>(i) &= val.get<uint8>(); 	break;
	case lzh::TP_16S:	at<int16>(i) &= val.get<int16>(); 	break;
	case lzh::TP_16U:	at<uint16>(i) &= val.get<uint16>(); break;
	case lzh::TP_32S:	at<int32>(i) &= val.get<int32>(); 	break;
	case lzh::TP_32U:	at<uint32>(i) &= val.get<uint32>(); break;
	case lzh::TP_64S:	at<int64>(i) &= val.get<int64>(); 	break;
	case lzh::TP_64U:	at<uint64>(i) &= val.get<uint64>(); break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
void lzh::CvMat::BitOr(int32 i, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	switch (depth())
	{
	case lzh::TP_8S:	at<int8>(i) |= val.get<int8>(); 	break;
	case lzh::TP_8U:	at<uint8>(i) |= val.get<uint8>(); 	break;
	case lzh::TP_16S:	at<int16>(i) |= val.get<int16>(); 	break;
	case lzh::TP_16U:	at<uint16>(i) |= val.get<uint16>(); break;
	case lzh::TP_32S:	at<int32>(i) |= val.get<int32>(); 	break;
	case lzh::TP_32U:	at<uint32>(i) |= val.get<uint32>(); break;
	case lzh::TP_64S:	at<int64>(i) |= val.get<int64>();	break;
	case lzh::TP_64U:	at<uint64>(i) |= val.get<uint64>(); break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
}
const CvMat lzh::CvMat::BitNot() const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	CvMat m = clone();
	FOR_RANGE(i, 0, len())m.BitNot(i);
	return m;
}
const CvMat lzh::CvMat::BitAnd(Val val) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	CvMat m = clone();
	switch (val.type)
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<int8>()); }break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<uint8>()); }break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<int16>()); }break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<uint16>()); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<int32>()); }break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<uint32>()); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<int64>()); }break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, val.get<uint64>()); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
	return m;
}
const CvMat lzh::CvMat::BitAnd(const CvMat & a) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	CvMat m = clone();
	switch (a.depth())
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<int8>(i)); }	break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<uint8>(i)); }	break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<int16>(i)); }	break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<uint16>(i)); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<int32>(i)); }	break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<uint32>(i)); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<int64>(i)); }	break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, len()) { m.BitAnd(i, a.at<uint64>(i)); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
	return m;
}
const CvMat lzh::CvMat::BitOr(Val val) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	CvMat m = clone();
	switch (val.type)
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<int8>()); }break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<uint8>()); }break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<int16>()); }break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<uint16>()); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<int32>()); }break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<uint32>()); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<int64>()); }break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, val.get<uint64>()); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
	return m;
}
const CvMat lzh::CvMat::BitOr(const CvMat & a) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	CvMat m = clone();
	switch (a.depth())
	{
	case lzh::TP_8S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<int8>(i)); }	break;
	case lzh::TP_8U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<uint8>(i)); }	break;
	case lzh::TP_16S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<int16>(i)); }	break;
	case lzh::TP_16U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<uint16>(i)); }break;
	case lzh::TP_32S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<int32>(i)); }	break;
	case lzh::TP_32U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<uint32>(i)); }break;
	case lzh::TP_64S:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<int64>(i)); }	break;
	case lzh::TP_64U:	FOR_RANGE(i, 0, len()) { m.BitOr(i, a.at<uint64>(i)); }break;
	default:THROW_INFO_STR("位运算不支持浮点类型!");
	}
	return m;
}
lzh::mat_t CvMat::Max(bool is_abs) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	lzh::mat_t maxdata = is_abs ? std::abs(data.get<mat_t>(0)) : data.get<mat_t>(0);
	for (int32 ind = 1; ind < len(); ind++) {
		lzh::mat_t v = is_abs ? std::abs(data.get<mat_t>(ind)) : data.get<mat_t>(ind);
		if (maxdata < v)
			maxdata = v;
	}
	return maxdata;
}
lzh::mat_t CvMat::Min(bool is_abs) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	lzh::mat_t mindata = is_abs ? std::abs(data.get<mat_t>(0)) : data.get<mat_t>(0);
	for (int32 ind = 1; ind < len(); ind++) {
		lzh::mat_t v = is_abs ? std::abs(data.get<mat_t>(ind)) : data.get<mat_t>(ind);
		if (mindata > v)
			mindata = v;
	}
	return mindata;
}
int32 CvMat::maxAt()const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	int32 max_adr = 0;
	for (int32 ind = 1; ind < len(); ind++)
		if (compare(max_adr, ind, -2))
			max_adr = ind;
	return max_adr;
}
int32 CvMat::minAt()const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	int32 min_adr = 0;
	for (int32 ind = 1; ind < len(); ind++)
		if (compare(min_adr, ind, 2))
			min_adr = ind;
	return min_adr;
}

void CvMat::show()const
{
	show(std::cout);
	std::cout << std::endl;
}
std::ostream & CvMat::show(std::ostream & out) const
{
	if (data == nullptr)return out;
	switch (print_type)
	{
	case lzh::MAT_FIXED:
		out.unsetf(std::ios::fixed);
		break;
	case lzh::MAT_SCIENTIFIC:
		out.setf(std::ios::scientific);
		break;
	default:
		break;
	}
	out.setf(std::ios::showpos);
	out.setf(std::ios::left);
	out << "CvMat([";
	for (int32 i = 0; i < rows; i++) {
		if (i != 0) out << "      [";
		for (int32 j = 0; j < cols; j++) {
			out << "[";
			for (int32 k = 0; k < c_; k++) {
				switch (depth())
				{
				case lzh::TP_8S:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << (int16)at<int8>(i, j, k); break;
				case lzh::TP_8U:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<uint8>(i, j, k); break;
				case lzh::TP_16S:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<int16>(i, j, k); break;
				case lzh::TP_16U:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<uint16>(i, j, k); break;
				case lzh::TP_32S:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<int32>(i, j, k); break;
				case lzh::TP_32U:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<uint32>(i, j, k); break;
				case lzh::TP_32F:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<int64>(i, j, k); break;
				case lzh::TP_64S:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<uint64>(i, j, k); break;
				case lzh::TP_64U:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<float32>(i, j, k); break;
				case lzh::TP_64F:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<float64>(i, j, k); break;
				case lzh::TP_64D:	out << std::setw(print_width) << std::setprecision(print_precision) << std::setfill(' ') << at<float64_>(i, j, k); break;
				default:
					break;
				}
				if (j == cols - 1 && k == c_ - 1)
				{
					out << "]]";
				}
				else if (k == c_ - 1)
				{
					out << "]";
				}
				else {
					out << ", ";
				}
			}
		}
		if (i != rows - 1)
			out << std::endl;
	}
	out << ", type=" << TypeString[data.depth()] << ")";
	switch (print_type)
	{
	case lzh::MAT_FIXED:
		out.unsetf(std::ios::fixed);
		break;
	case lzh::MAT_SCIENTIFIC:
		out.unsetf(std::ios::scientific);
		break;
	default:
		break;
	}
	out.unsetf(std::ios::showpos);
	out.unsetf(std::ios::left);
	out << std::defaultfloat << std::setprecision(6);
	return out;
}

CvMat CvMat::row(int32 h)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (h < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (h >= rows) THROW_INFO(ERR_INFO_MEMOUT);
#endif // DEBUG_MAT
	return CvMat(cols, 1, c_, stride, data.offset(h * cols * c_), depth());
}
const CvMat CvMat::row(int32 h) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (h < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (h >= rows) THROW_INFO(ERR_INFO_MEMOUT);
#endif // DEBUG_MAT
	return CvMat(cols, 1, c_, stride, data.offset(h * cols * c_), depth());
}
CvMat CvMat::col(int32 w)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (w < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (w >= cols) THROW_INFO(ERR_INFO_MEMOUT);
#endif // DEBUG_MAT
	return CvMat(1, rows, c_, stride, data.offset(w * c_), depth());
}
const CvMat CvMat::col(int32 w) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (w < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (w >= cols) THROW_INFO(ERR_INFO_MEMOUT);
#endif // DEBUG_MAT
	return CvMat(1, rows, c_, stride, data.offset(w * c_), depth());
}
CvMat CvMat::channel(int32 c)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (c < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (c >= c_) THROW_INFO(ERR_INFO_MEMOUT);
#endif // DEBUG_MAT
	return CvMat(cols, rows, 1, stride, data.offset(c), depth());
}
const CvMat CvMat::channel(int32 c) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (c < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (c >= c_) THROW_INFO(ERR_INFO_MEMOUT);
#endif // DEBUG_MAT
	return CvMat(cols, rows, 1, stride, data.offset(c), depth());
}
const CvMat CvMat::range(int32 start, int32 end)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (start < 0 || end < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (start >= rows || end >= rows) THROW_INFO(ERR_INFO_MEMOUT);
	if (start >= end) THROW_INFO(ERR_INFO_UNLESS);
#endif // DEBUG_MAT
	return CvMat(end - start, 1, stride, data, depth());
}
const CvMat lzh::CvMat::range(Rect roi) const
{
	return CvMat(roi.width, roi.height, c_, stride, data + toidx(roi.y, roi.x), depth());
}
const CvMat lzh::CvMat::range(int32 h_start, int32 h_end, int32 w_start, int32 w_end) const
{
	return CvMat(w_end - w_start + 1, h_end - h_start + 1, c_, stride, (const void*)(data + toidx(h_start, w_start)), depth());
}
const CvMat CvMat::rowRange(int32 h_start, int32 h_end)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (h_start < 0 || h_end < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (h_start >= rows || h_end >= rows) THROW_INFO(ERR_INFO_MEMOUT);
	if (h_start >= h_end) THROW_INFO(ERR_INFO_UNLESS);
#endif // DEBUG_MAT
	return CvMat(cols, h_end - h_start + 1, c_, stride, data.offset(h_start * stride[0] * stride[1]), depth());
}
const CvMat CvMat::colRange(int32 w_start, int32 w_end)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (w_start < 0 || w_end < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (w_start >= cols || w_end >= cols) THROW_INFO(ERR_INFO_MEMOUT);
	if (w_start > w_end) THROW_INFO(ERR_INFO_UNLESS);
#endif // DEBUG_MAT
	return CvMat(w_end - w_start + 1, rows, c_, stride, data.offset(w_start * stride[1]), depth());
}
const CvMat CvMat::channelRange(int32 c_start, int32 c_end)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (c_start < 0 || c_end < 0) THROW_INFO(ERR_INFO_UNLESS);
	if (c_start >= c_ || c_end >= c_) THROW_INFO(ERR_INFO_MEMOUT);
	if (c_start >= c_end) THROW_INFO(ERR_INFO_UNLESS);
#endif // DEBUG_MAT
	return CvMat(cols, rows, c_end - c_start + 1, stride, data + c_start, depth());
}
const CvMat CvMat::clone() const
{
	CvMat dst;
	dst.setvalue(*this);
	return dst;
}
const CvMat CvMat::opp()const
{
	Mat dst;
	lzh::Opp(*this, dst);
	return CvMat(dst, depth());
}
const CvMat CvMat::adj()const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	CHECK_TYPE_(depth(), MAT_T);
#endif //MAT_DEBUG
	if (square) {
		Mat dst;
		lzh::adj(*this, dst);
		return CvMat(dst, depth());
	}
	else THROW_INFO(ERR_INFO_ADJ);
	return Mat();
}
const CvMat CvMat::t()const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	Mat dst;
	lzh::tran(*this, dst);
	return CvMat(dst, depth());
}
const CvMat CvMat::inv()const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	if (!square)
		THROW_INFO(ERR_INFO_INV);
	Mat dst;
	lzh::inv(*this, dst);
	return CvMat(dst, depth());
}
const CvMat CvMat::diag(int32 k) const
{
	Mat dst;
	lzh::diag(*this, dst, k);
	return CvMat(dst, depth());
}
const CvMat CvMat::abs()const
{
	Mat dst;
	lzh::Abs(*this, dst);
	return CvMat(dst, depth());
}
const CvMat CvMat::mPow(int32 num) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	if (square) {
		Mat dst;
		lzh::POW(*this, dst, num);
		return CvMat(dst, depth());
	}
	else THROW_INFO(ERR_INFO_POW);
	return CvMat();
}
const CvMat CvMat::pow(lzh::mat_t num)const
{
	Mat dst;
	lzh::Pow(*this, dst, num);
	return CvMat(dst, depth());
}
const CvMat CvMat::reverse()const
{
	return CvMat(lzh::reverse(*this), depth());
}
lzh::mat_t CvMat::sum(int32 num, bool _abs)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	lzh::mat_t sum = 0;
	if (num == 0) {
		return (lzh::mat_t)len();
	}
	else if (num == 1) {
		for (int32 ind = 0; ind < len(); ind++)
			if (_abs)
				sum += std::abs(data.get<mat_t>(toidx(ind)));
			else
				sum += data.get<mat_t>(toidx(ind));
	}
	else
		for (int32 ind = 0; ind < len(); ind++)
			if (_abs)
				sum += std::pow(std::abs(data.get<mat_t>(toidx(ind))), num);
			else
				sum += std::pow(data.get<mat_t>(toidx(ind)), num);
	return sum;
}
lzh::mat_t CvMat::mean() const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	lzh::mat_t sum = 0;
	for (int32 ind = 0; ind < len(); ind++)
		sum += data.get<mat_t>(toidx(ind));
	return sum / (lzh::mat_t)len();
}
lzh::mat_t CvMat::std() const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	return std::sqrt(D());
}
lzh::mat_t CvMat::D() const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif //MAT_DEBUG
	lzh::mat_t m = mean();
	lzh::mat_t d = 0;
	lzh::mat_t n = (lzh::mat_t)len();
	FOR_RANGE(i, 0, len())
	{
		d += std::pow(data.at<mat_t>(i) - m, 2.0f);
	}
	return d / n;
}
lzh::mat_t CvMat::Det()
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	if (square)
		return lzh::det(*this);
	else
		return NAN;
}
lzh::mat_t CvMat::norm(int32 num)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (cols != 1 && rows != 1) THROW_INFO(ERR_INFO_NORM);
	if (num < 0) THROW_INFO(ERR_INFO_VALUE);
#endif // MAT_DEBUG
	if (num == 0)
		return sum();
	else if (num == 1)
		return sum(1, true);
	else if (num == 2)
		return std::sqrt(sum(2, true));
	//else if (isinf(num) == 1)
	//	return abs(matrix[find(findmax())]);
	//else if (isinf(num) == -1)
	//	return abs(matrix[find(findmin())]);
	else
		return std::pow(sum(num, true), 1 / _T(num));
}
lzh::mat_t CvMat::Cof(int32 x, int32 y)
{
	return lzh::cof(*this, x, y);
}
lzh::mat_t CvMat::EigenvalueMax(lzh::mat_t offset)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	if (square) {
		int32 count = 0;
		lzh::mat_t err = 100 * offset;
		CvMat v;
		CvMat u0 = CvMat::ones(cols, 1, depth());
		while (err > offset) {
			v = *this*u0;
			CvMat u1 = v * (1 / v.Max());
			err = (u1 - u0).abs().Max();
			u0 = u1; count += 1;
			if (count >= 1e+3) THROW_INFO(ERR_INFO_EIGEN);
		}
		return v.Max();
	}
	else THROW_INFO(ERR_INFO_SQUARE);
	return _T(NAN);
}
const CvMat CvMat::EigenvectorsMax(lzh::mat_t offset)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
#endif // MAT_DEBUG
	if (square) {
		int32 count = 0;
		lzh::mat_t err = 100 * offset;
		CvMat v;
		CvMat u0 = CvMat::ones(rows, 1, depth());
		while (err > offset) {
			v = *this*u0;
			CvMat u1 = v * (1 / v.Max());
			err = (u1 - u0).abs().Max();
			u0 = u1; count += 1;
			if (count >= 1e+3) THROW_INFO(ERR_INFO_EIGEN);
		}
		return u0;
	}
	else THROW_INFO(ERR_INFO_SQUARE);
	return CvMat();
}

const CvMat CvMat::sigmoid() const
{
	return nn::Sigmoid(*this);
}
const CvMat CvMat::tanh() const
{
	return nn::Tanh(*this);
}
const CvMat CvMat::relu() const
{
	return nn::ReLU(*this);
}
const CvMat CvMat::elu() const
{
	return nn::ELU(*this);
}
const CvMat CvMat::selu() const
{
	return nn::SeLU(*this);
}
const CvMat CvMat::leaky_relu() const
{
	return nn::LReLU(*this);
}
const CvMat CvMat::softmax() const
{
	return nn::Softmax(*this);
}
const CvMat CvMat::exp()const
{
	Mat m;
	lzh::Exp(*this, m);
	return m;
}
const CvMat CvMat::log()const
{
	Mat m;
	lzh::Log(*this, m);
	return m;
}
const CvMat CvMat::sqrt()const
{
	Mat m;
	lzh::Sqrt(*this, m);
	return m;
}

void CvMat::setp(int32 i, const void * v, int32 addr_offset)
{
	switch (depth()) {
	case lzh::TP_8S:	set(i, MAT_GETARRAY(const int8, v, addr_offset));		break;
	case lzh::TP_8U:	set(i, MAT_GETARRAY(const uint8, v, addr_offset));		break;
	case lzh::TP_16S:	set(i, MAT_GETARRAY(const int16, v, addr_offset));		break;
	case lzh::TP_16U:	set(i, MAT_GETARRAY(const uint16, v, addr_offset));		break;
	case lzh::TP_32S:	set(i, MAT_GETARRAY(const int32, v, addr_offset));		break;
	case lzh::TP_32U:	set(i, MAT_GETARRAY(const uint32, v, addr_offset));		break;
	case lzh::TP_64S:	set(i, MAT_GETARRAY(const int64, v, addr_offset));		break;
	case lzh::TP_64U:	set(i, MAT_GETARRAY(const uint64, v, addr_offset));		break;
	case lzh::TP_32F:	set(i, MAT_GETARRAY(const float32, v, addr_offset));	break;
	case lzh::TP_64F:	set(i, MAT_GETARRAY(const float64, v, addr_offset));	break;
	case lzh::TP_64D:	set(i, MAT_GETARRAY(const float64_, v, addr_offset));	break;
	default:return;
	}
}

void CvMat::init()
{
	dim = 0;
	rows = 0;
	cols = 0;
	c_ = 0;
	_type = ColorGamutCustom;
}

void CvMat::checkSquare()
{
	if (rows == cols)
		square = true;
	else
		square = false;
}
#ifdef MAT_DEBUG
void CvMat::checkindex(int32 index)
{
	if (rows == 0 || cols == 0) THROW_INFO(ERR_INFO_LEN);
	if (index > len() - 1) THROW_INFO(ERR_INFO_MEMOUT);
	if (index < 0) THROW_INFO(ERR_INFO_VALUE);
	if (!data()) THROW_INFO(ERR_INFO_EMPTY);
}
void CvMat::checkindex(int32 index_x, int32 index_y)
{
	if (rows == 0 || cols == 0)THROW_INFO(ERR_INFO_LEN);
	if (index_x < 0 || index_y < 0) THROW_INFO(ERR_INFO_MEMOUT);
	if (index_x*cols + index_y > rows*cols - 1 || index_x >= rows || index_y >= cols) THROW_INFO(ERR_INFO_VALUE);
	if (!data()) THROW_INFO(ERR_INFO_EMPTY);
}
#endif // MAT_DEBUG
void CvMat::setsize(int32 w, int32 h, int32 c)
{
	cols = w;
	rows = h;
	c_ = c;
	stride[0] = w;
	stride[1] = c;
	if (w == 0 && h == 0 && c == 0)dim = 0;
	else if (w == 1 && h == 1 && c == 1)dim = 0;
	else if (w != 1 && h == 1 && c == 1)dim = 1;
	else if (w == 1 && h != 1 && c == 1)dim = 1;
	else if (w != 1 && h != 1 && c == 1)dim = 2;
	else if (w != 1 && h == 1 && c != 1)dim = 2;
	else if (w == 1 && h != 1 && c != 1)dim = 2;
	else dim = 3;
	square = (h == w);
}

CvMat& CvMat::operator = (const CvMat &temp)
{
	if (this == &temp)
		return *this;
	data = temp.data;
	rows = temp.rows;
	cols = temp.cols;
	c_ = temp.c_;
	stride = temp.stride;
	dim = temp.dim;
	square = temp.square;
	_type = temp._type;
	return *this;
}
CvMat & lzh::CvMat::operator=(const Mat & temp)
{
	if ((int64)data.obj() == (int64)temp.data())
		return *this;
	data.set(temp);
	rows = temp.rows();
	cols = temp.cols();
	c_ = temp.channels();
	stride = temp.step();
	dim = temp.dims();
	_type = temp.colorGamut();
	return *this;
}
bool CvMat::operator == (const CvMat &a)const
{
	if (cols != a.cols) {
		return false;
	}
	if (rows != a.rows) {
		return false;
	}
	if (c_ != a.c_) {
		return false;
	}
	if (memcmp(data, a.data, memsize()) == 0)
		return true;
	return false;
}
bool CvMat::operator != (const CvMat & a)const
{
	return !(*this == a);
}
mat_t CvMat::operator()(int32 i) const
{
	return get_(i);
}
mat_t CvMat::operator()(int32 i0, int32 i1) const
{
	return get_(i0, i1);
}
mat_t CvMat::operator()(int32 i0, int32 i1, int32 i2) const
{
	return get_(i0, i1, i2);
}
mat_t lzh::CvMat::operator()(Point p) const
{
	return get_(p.y, p.x);
}
mat_t lzh::CvMat::operator()(Point3 p) const
{
	return get_(p.y, p.x, p.z);
}
CvMat lzh::CvMat::operator()(Rect roi) const
{
	return range(roi);
}
CvMat lzh::CvMat::operator()(Range row, Range col) const
{
	return range(row.v2, row.v1, col.v2, col.v1);
}
CvMat CvMat::operator()(int32 i, RANK rc) const
{
	return cut(i, rc);
}
CvMat CvMat::operator()(int32 v1, int32 v2, RANK rc) const
{
	return cut(v1, v2, rc);
}
CvMat CvMat::cut(int32 i, RANK rc) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (i < 0) THROW_INFO(ERR_INFO_VALUE);
#endif // MAT_DEBUG
	switch (rc) {
	case ROW:
		if (i > rows - 1) THROW_INFO(ERR_INFO_MEMOUT);
		return row(i);
	case COL:
		if (i > cols - 1) THROW_INFO(ERR_INFO_MEMOUT);
		return col(i);
	case CHANNEL:
		if (i > c_ - 1) THROW_INFO(ERR_INFO_MEMOUT);
		return channel(i);
	default:return Mat();
	}
}
CvMat CvMat::cut(int32 v1, int32 v2, RANK rc) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX(data);
	if (v1 < 0 || v2 < 0) THROW_INFO(ERR_INFO_VALUE);
#endif // MAT_DEBUG
	switch (rc) {
	case ROW:
#ifdef MAT_DEBUG
		if (v1 > cols - 1 || v2 > c_ - 1) THROW_INFO(ERR_INFO_MEMOUT);
#endif // MAT_DEBUG
		return CvMat(1, rows, 1, stride, data.offset(v1 * stride[1] + v2), depth());
	case COL:
#ifdef MAT_DEBUG
		if (v1 > rows - 1 || v2 > c_ - 1) THROW_INFO(ERR_INFO_MEMOUT);
#endif // MAT_DEBUG
		return CvMat(cols, 1, 1, stride, data.offset(v1 * stride[0] * stride[1] + v2), depth());
	case CHANNEL:
#ifdef MAT_DEBUG
		if (v1 > rows - 1 || v2 > cols - 1) THROW_INFO(ERR_INFO_MEMOUT);
#endif // MAT_DEBUG
		return CvMat(1, 1, c_, stride, data.offset(toidx(v1, v2)), depth());
		break;
	default:break;
	}
	return Mat();
}
const CvMat CvMat::operator[](int32 idx) const
{
	if (dim == 3) {
		return channel(idx);
	}
	else if (dim == 2) {
		return row(idx);
	}
	else if (dim == 1) {
#ifdef MAT_DEBUG
		if (idx < 0) THROW_INFO(ERR_INFO_VALUE);
		if (idx >= len()) THROW_INFO(ERR_INFO_MEMOUT);
#endif // MAT_DEBUG
		return CvMat(1, 1, 1, data.offset(idx), depth());
	}
	else {
		THROW_INFO(ERR_INFO_UNLESS);
	}
	return CvMat();
}

bool lzh::CvMat::operator>(const CvMat & b) const
{
	FOR_RANGE(i, 0, len() > b.len() ? b.len() : len()) {
		if (compare(i, b(i), 2))
			return true;
		else if (!compare(i, b(i), 0))
			break;
	}
	return false;
}
bool lzh::CvMat::operator<(const CvMat & b) const
{
	FOR_RANGE(i, 0, len() > b.len() ? b.len() : len()) {
		if (compare(i, b(i), -2))
			return true;
		else if (!compare(i, b(i), 0))
			break;
	}
	return false;
}

void CvMat::setPrintW(uint32 w)
{
	print_width = w;
}
void CvMat::setPrintSignificantDigits(uint32 n)
{
	print_precision = n;
	//print_width = 2 + n + 3;
}
void CvMat::setPrintType(lzh::PrintType t)
{
	print_type = t;
}

const CvMat CvMat::zeros(int32 w, int32 type, ColorGamut cg)
{
	tools::check(w);
	CvMat mat(w, type, cg);
	memset(mat, 0, mat.memsize());
	return mat;
}
const CvMat CvMat::zeros(int32 w, int32 h, int32 type, ColorGamut cg)
{
	tools::check(w, h);
	CvMat mat(w, h, type, cg);
	memset(mat, 0, mat.memsize());
	return mat;
}
const CvMat CvMat::zeros(int32 w, int32 h, int32 c, int32 type, ColorGamut cg)
{
	tools::check(w, h, c);
	CvMat mat(w, h, c, type, cg);
	memset(mat, 0, mat.memsize());
	return mat;
}
const CvMat CvMat::zeros(Size size, int32 type, ColorGamut cg)
{
	tools::check(size.h, size.w);
	CvMat mat(size.h, size.w, type, cg);
	memset(mat, 0, mat.memsize());
	return mat;
}
const CvMat lzh::CvMat::zeros(Size size, int32 c, int32 type, ColorGamut cg)
{
	tools::check(size.h, size.w, c);
	CvMat mat(size.h, size.w, c, type, cg);
	memset(mat, 0, mat.memsize());
	return mat;
}
const CvMat CvMat::zeros(Size3 size, int32 type, ColorGamut cg)
{
	CvMat mat(size, type, cg);
	memset(mat, 0, mat.memsize());
	return mat;
}
const CvMat CvMat::value(Val v, int32 w, int32 type, ColorGamut cg)
{
	tools::check(w);
	CvMat mark(w, type, cg);
	for (int32 ind = 0; ind < mark.len(); ind++)
		mark.set(ind, v);
	return mark;
}
const CvMat CvMat::value(Val v, int32 w, int32 h, int32 type, ColorGamut cg)
{
	tools::check(w, h);
	CvMat mark(w, h, type, cg);
	for (int32 ind = 0; ind < mark.len(); ind++)
		mark.set(ind, v);
	return mark;
}
const CvMat CvMat::value(Val v, int32 w, int32 h, int32 c, int32 type, ColorGamut cg)
{
	tools::check(w, h, c);
	CvMat mark(w, h, c, type, cg);
	for (int32 ind = 0; ind < mark.len(); ind++)
		mark.set(ind, v);
	return mark;
}
const CvMat CvMat::ones(int32 w, int32 type, ColorGamut cg)
{
	return value(1, w, type, cg);
}
const CvMat CvMat::ones(int32 w, int32 h, int32 type, ColorGamut cg)
{
	return value(1, w, h, type, cg);
}
const CvMat CvMat::ones(int32 w, int32 h, int32 c, int32 type, ColorGamut cg)
{
	return value(1, w, h, c, type, cg);
}
const CvMat CvMat::ones(Size size, int32 type, ColorGamut cg)
{
	return value(1, size.w, size.h, type, cg);
}
const CvMat lzh::CvMat::ones(Size size, int32 c, int32 type, ColorGamut cg)
{
	return value(1, size.w, size.h, c, type, cg);
}
const CvMat CvMat::ones(Size3 size, int32 type, ColorGamut cg)
{
	return value(1, size.w, size.h, size.c, type, cg);
}
const CvMat lzh::CvMat::eye(int32 n, int32 type)
{
	tools::check(n, n);
	CvMat mark = zeros(n, n, type);
	for (int32 ind = 0; ind < n; ind++)
		mark.set(ind + ind * n, 1);
	return mark;
}


const CvMat lzh::operator+(const CvMat & m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, m.get_(i) + val);
	return mark;
}
const CvMat lzh::operator+(const CvMat & m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_TYPE_(m.depth(), a.depth());
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		return m.get_(0) + a;
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		return m + a.get_(0);
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		CvMat mat(m.size3(), m.depth());
		for (int32 i = 0; i < m.rows; i++)
			for (int32 j = 0; j < m.cols; j++)
				for (int32 z = 0; z < m.channels(); z++)
					mat.set(i, j, z, m.get_(i, j, z) + a.get_(z));
		return mat;
	}
#ifdef MAT_DEBUG
	if (m.size3() != a.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, m.get_(i) + a.get_(i));
	return mark;
}
const CvMat lzh::operator + (Val val, const CvMat &mat)
{
	return mat + val;
}

const CvMat lzh::operator-(const CvMat & m)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, -m.get_(i));
	return mark;
}
const CvMat lzh::operator-(const CvMat & m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, m.get_(i) - val);
	return mark;
}
const CvMat lzh::operator-(const CvMat & m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_TYPE_(m.depth(), a.depth());
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		return m.get_(0) - a;
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		return m - a.get_(0);
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		CvMat mat(m.size3(), m.depth());
		for (int32 i = 0; i < m.rows; i++)
			for (int32 j = 0; j < m.cols; j++)
				for (int32 z = 0; z < m.channels(); z++)
					mat.set(i, j, z, m.get_(i, j, z) - a.get_(z));
		return mat;
	}
#ifdef MAT_DEBUG
	if (m.size3() != a.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, m.get_(i) - a.get_(i));
	return mark;
}
const CvMat lzh::operator-(Val val, const CvMat &mat)
{
	return val + (-mat);
}

const CvMat lzh::operator*(const CvMat & m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, m(i) * val);
	return mark;
}
const CvMat lzh::operator*(const CvMat & m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_MATRIX_(a);
	CHECK_TYPE_(m.depth(), a.depth());
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		return m(0) * a;
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		return m * a(0);
	}
#ifdef MAT_DEBUG
	if (m.cols != a.rows) THROW_INFO(ERR_INFO_MULT);
	if (m.channels() != a.channels()) THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	CvMat mark(a.cols, m.rows, m.channels(), m.depth());
	for (int32 z = 0; z < m.channels(); z++)
		for (int32 i = 0; i < m.rows; i++)
			for (int32 j = 0; j < a.cols; j++) {
				mat_t temp = 0;
				for (int32 d = 0; d < m.cols; d++)
					temp = temp + m(i, d, z) * a(d, j, z);
				mark.set(i, j, z, temp);
			}
	return mark;
}
const CvMat lzh::operator*(Val val, const CvMat &mat)
{
	return mat * val;
}

const CvMat lzh::operator/(const CvMat & m, Val val)
{
	return m * (1.0 / val);
}
const CvMat lzh::operator/(const CvMat & m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_TYPE_(m.depth(), a.depth());
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		return m.get_(0) / a;
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		return m / a.get_(0);
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		CvMat mat(m.size3(), m.depth());
		for (int32 i = 0; i < m.rows; i++)
			for (int32 j = 0; j < m.cols; j++)
				for (int32 z = 0; z < m.channels(); z++)
					mat.set(i, j, z, m.get_(i, j, z) / a.get_(z));
		return mat;
	}
#ifdef MAT_DEBUG
	if (m.size3() != a.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	CvMat mark(m.size3(), m.depth());
	for (int32 i = 0; i < m.len(); i++)
		mark.set(i, m.get_(i) / a.get_(i));
	return mark;
}
const CvMat lzh::operator/(Val val, const CvMat &mat)
{
	Mat m;
	lzh::Div(mat, m, val, LEFT);
	return m;
}

const CvMat lzh::operator^(const CvMat & m, Val power)
{
	return m.pow(power);
}

const CvMat lzh::operator~(const CvMat & m)
{
	return m.BitNot();
}

const CvMat lzh::operator!(const CvMat & m)
{
	return m.BitNot();
}
const CvMat lzh::operator&(const CvMat & m, Val val)
{
	return m.BitAnd(val);
}
const CvMat lzh::operator&(const CvMat & m, const CvMat & a)
{
	return m.BitAnd(a);
}
const CvMat lzh::operator&(Val val, const CvMat & m)
{
	return m & val;
}

const CvMat lzh::operator|(const CvMat & m, Val val)
{
	return m.BitOr(val);
}
const CvMat lzh::operator|(const CvMat & m, const CvMat & a)
{
	return m.BitOr(a);
}
const CvMat lzh::operator|(Val val, const CvMat & m)
{
	return m | val;
}

void lzh::operator+=(CvMat m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	for (int32 i = 0; i < m.len(); i++)
		m.add(m.toidx(i), val);
}
void lzh::operator+=(CvMat m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		m.add(0, a.First());
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		m += a.First();
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		for (int32 z = 0; z < m.channels(); z++) {
			for (int32 i = 0; i < m.rows; i++) {
				for (int32 j = 0; j < m.cols; j++) {
					m.add(m.toidx(i, j, z), a(z));
				}
			}
		}
	}
	else {
#ifdef MAT_DEBUG
		if (m.size3() != a.size3())
			THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
		for (int32 i = 0; i < m.len(); i++)
			m.add(m.toidx(i), a.get_(i));
	}
}

void lzh::operator-=(CvMat m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	for (int32 i = 0; i < m.len(); i++)
		m.reduce(m.toidx(i), val);
}
void lzh::operator-=(CvMat m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		m.reduce(0, a.First());
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		m -= a.First();
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		for (int32 z = 0; z < m.channels(); z++) {
			for (int32 i = 0; i < m.rows; i++) {
				for (int32 j = 0; j < m.cols; j++) {
					m.reduce(m.toidx(i, j, z), a(z));
				}
			}
		}
	}
	else {
#ifdef MAT_DEBUG
		if (m.size3() != a.size3())
			THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
		for (int32 i = 0; i < m.len(); i++)
			m.reduce(m.toidx(i), a.get_(i));
	}
}

void lzh::operator*=(CvMat m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	for (int32 i = 0; i < m.len(); i++)
		m.mul(m.toidx(i), val);
}
void lzh::operator*=(CvMat m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		m.mul(0, a.First());
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		m *= a.First();
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		for (int32 z = 0; z < m.channels(); z++) {
			for (int32 i = 0; i < m.rows; i++) {
				for (int32 j = 0; j < m.cols; j++) {
					m.mul(m.toidx(i, j, z), a(z));
				}
			}
		}
	}
	else {
#ifdef MAT_DEBUG
		if (m.size3() != a.size3())
			THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
		for (int32 i = 0; i < m.len(); i++)
			m.mul(m.toidx(i), a.get_(i));
	}
}

void lzh::operator/=(CvMat m, Val val)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
#endif // MAT_DEBUG
	for (int32 i = 0; i < m.len(); i++)
		m.div(m.toidx(i), val);
}
void lzh::operator/=(CvMat m, const CvMat & a)
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	CHECK_MATRIX_(a);
#endif // MAT_DEBUG
	if (m.rows == 1 && m.cols == 1 && m.channels() == 1) {
		m.div(0, a.First());
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == 1) {
		m /= a.First();
	}
	else if (a.rows == 1 && a.cols == 1 && a.channels() == m.channels()) {
		for (int32 z = 0; z < m.channels(); z++) {
			for (int32 i = 0; i < m.rows; i++) {
				for (int32 j = 0; j < m.cols; j++) {
					m.div(m.toidx(i, j, z), a(z));
				}
			}
		}
	}
	else {
#ifdef MAT_DEBUG
		if (m.size3() != a.size3())
			THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
		for (int32 i = 0; i < m.len(); i++)
			m.div(m.toidx(i), a.get_(i));
	}
}

void lzh::operator&=(CvMat m, Val val)
{
	FOR_RANGE(i, 0, m.len())m.BitAnd(i, val);
}
void lzh::operator&=(CvMat m, const CvMat & a)
{
#ifdef MAT_DEBUG
	if (m.size3() != a.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	FOR_RANGE(i, 0, m.len())m.BitAnd(i, a(i));
}

void lzh::operator|=(CvMat m, Val val)
{
	FOR_RANGE(i, 0, m.len())m.BitOr(i, val);
}
void lzh::operator|=(CvMat m, const CvMat & a)
{
#ifdef MAT_DEBUG
	if (m.size3() != a.size3())
		THROW_INFO(ERR_INFO_SIZE);
#endif // MAT_DEBUG
	FOR_RANGE(i, 0, m.len())m.BitOr(i, a(i));
}