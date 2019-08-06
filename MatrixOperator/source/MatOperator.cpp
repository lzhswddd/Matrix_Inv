#include "MatOperator.h"
using namespace lzh;

mat_t lzh::trace(IMat src)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	if (mat.enable() == -2) THROW_INFO(ERR_INFO_SQUARE);
#endif //MAT_DEBUG
	mat_t sum = 0;
	for (int32 index = 0; index < mat.rows(); index++) {
		sum += mat((index + index * mat.cols())*mat.channels());
	}
	return sum;
}
mat_t lzh::cof(IMat src, int32 x, int32 y)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	if (x >= mat.cols() || y >= mat.rows())
		THROW_INFO(ERR_INFO_MEMOUT);
#endif //MAT_DEBUG
	mat.DimCheck();
	Mat a(mat.cols() - 1, mat.rows() - 1);
	int32 n = mat.rows();
	for (int32 i = 0, k = 0; i < n; i++)
		for (int32 j = 0; j < n; j++)
			if ((i != x) && (j != y)) {
				a(k) = mat(i*n + j);
				k++;
			}
	return det(a);
}
mat_t lzh::det(IMat src)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	mat.DimCheck();
	if (mat.enable() == -2)
		THROW_INFO(ERR_INFO_SQUARE);
#endif //MAT_DEBUG
	int32 n = mat.rows();
	if (n == 1)
		return mat(0);
	else {
		Mat a;
		Trapezoidal(mat, a, false);
		mat_t answer = 1;
		for (int32 i = 0; i < n; i++) {
			answer *= a(i, i);
			if (isinf(answer))break;
		}
		return answer;
	}
}
mat_t lzh::Norm(IMat src, int32 num)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	if (mat.cols() != 1 && mat.rows() != 1)
		THROW_INFO(ERR_INFO_NORM);
	mat.DimCheck();
	if (num <= 0)
		THROW_INFO(ERR_INFO_VALUE);
#endif //MAT_DEBUG
	if (num == 1)
		return mat.sum(1, true);
	else if (num == 2)
		return sqrt(mat.sum(2, true));
	//else if (isinf(num) == 1)
	//	return abs(matrix[find(findmax())]);
	//else if (isinf(num) == -1)
	//	return abs(matrix[find(findmin())]);
	else
		return pow(mat.sum(num, true), 1 / _T(num));
}

void lzh::adj(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	if (mat.enable() == -2)
		THROW_INFO(ERR_INFO_SQUARE);
#endif //MAT_DEBUG
	int32 n = mat.rows();
	int32 channel = mat.channels();
	Mat a(n, n, channel);
	for (int32 z = 0; z < channel; z++) {
		for (int32 i = 0; i < n; i++)
			for (int32 j = 0; j < n; j++) {
				mat_t m = cof(mat, i, j);
				a(i, j, z) = _T(pow(-1, i + j + 2))*m;
			}
	}
	a.setTran();
	dst = a;
}
void lzh::inv(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	if (mat.channels() != 1)
		THROW_INFO(ERR_INFO_DIM);
#endif //MAT_DEBUG
	Mat m = mat.clone();
	mat_t determinant = det(m);
	if (isnan(determinant) || determinant == 0) {
		THROW_INFO(ERR_INFO_DET);
	}
	else {
		Mat dst_(m, Mat::eye(m.rows()), COL);
		RowSimplest(dst_, dst_);
		m = dst_(Rect(m.rows(), 0, m.cols(), m.rows())).clone();
	}
	dst.set(m);
}
void lzh::diag(IMat src, OutputArray dst, int32 k)
{
	Mat m = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(m);
	if (m.channels() != 1) THROW_INFO(ERR_INFO_DIM);
	if (m.dims() != 1) THROW_INFO(ERR_INFO_NORM);
#endif //MAT_DEBUG
	int32 pos = k < 0 ? -k : k;
	Mat mat = Mat::zeros(m.len() + pos, m.len() + pos);
	const Val_ *data = m;
	Val_ *p = mat;
	for (int32 h = 0; h < mat.rows(); h++)
	{
		for (int32 w = 0; w < mat.cols(); w++)
		{
			if (h + k == w)
				*p = *data;
			p += 1;
		}
		data += 1;
	}
	dst.set(mat);
}
void lzh::pinv(IMat src, OutputArray dst, Dire direc)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	Mat result;
	switch (direc)
	{
	case LEFT:result = (mat.t()*mat).inv()*mat.t(); break;
	case RIGHT: {
		Mat m = mat.t();
		lzh::pinv(m, result, LEFT);
		result.setTran();
		break;
	}
	default:
		THROW_INFO(ERR_INFO_VALUE);
	}
	dst.set(result);
}
void lzh::tran(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	Mat a(mat.rows(), mat.cols(), mat.channels());
	int32 n = mat.rows(),
		m = mat.cols();
	for (int32 z = 0; z < mat.channels(); z++)
		for (int32 i = 0; i < n; i++)
			for (int32 j = 0; j < m; j++)
				a(j, i, z) = mat(i, j, z);
	dst.set(a);
}

void lzh::POW(IMat src, OutputArray dst, int32 num)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
	if (mat.enable() == -2)
		THROW_INFO(ERR_INFO_SQUARE);
#endif //MAT_DEBUG
	Mat m;
	mat.swap(m);
	if (num > 0) {
		for (int32 i = 1; i < num; i++)
			m = m * mat;
	}
	else if (num < 0) {
		Mat a;
		mat.swap(a);
		m.setInv();
		a.setInv();
		for (int32 i = -1; i > num; i--)
			a = a * m;
		m = a;
	}
	else
		m = Mat::eye(mat.rows());
	dst.set(m);
}
void lzh::Pow(IMat src, OutputArray dst, Val num)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	Mat m(mat.size3());
	Val_ *p = m;
	for (int32 ind = 0; ind < mat.len(); ind++)
		p[ind] = pow(mat(ind), num);
	dst.set(m);
}
void lzh::Sum(IMat src, OutputArray dst, RANK r_c)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	Mat m;
	if (r_c == COL) {
		m = Mat::zeros(mat.cols(), 1, 1);
		for (int32 i = 0; i < mat.cols(); i++)
			for (int32 z = 0; z < mat.channels(); z++)
				for (int32 j = 0; j < mat.rows(); j++)
					m(i) += mat(j, i, z);
	}
	else if (r_c == ROW) {
		m = Mat::zeros(1, mat.rows(), 1);
		for (int32 i = 0; i < mat.rows(); i++)
			for (int32 z = 0; z < mat.channels(); z++)
				for (int32 j = 0; j < mat.cols(); j++)
					m(i) += mat(i, j, z);
	}
	else if (r_c == CHANNEL) {
		m = Mat::zeros(1, 1, mat.channels());
		for (int32 z = 0; z < mat.channels(); z++)
			for (int32 i = 0; i < mat.rows(); i++)
				for (int32 j = 0; j < mat.cols(); j++)
					m(z) += mat(i, j, z);
	}
	else
		THROW_INFO(ERR_INFO_VALUE);
	dst = m;
}
void lzh::Exp(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	//Mat m(mat.size3());
	//Val_ *p = m;
	//for (int32 ind = 0; ind < mat.len(); ind++) {
	//	p[ind] = exp(mat(ind));
	//	//if (m.isValue(ind, 0))
	//	//	m.set(ind, (std::numeric_limits<mat_t>::Min)());
	//}
	dst.set(Operator(mat, exp));
}
void lzh::Log(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	dst.set(Operator(mat, log));
	//Mat m(mat.size3());
	//Val_ *p = m;
	//for (int32 ind = 0; ind < mat.len(); ind++)
	//	if (mat(ind) == 0)
	//		p[ind] = (std::numeric_limits<mat_t>::Min)();
	//	else
	//		p[ind] = log(mat(ind));
	//dst.set(m);
}
void lzh::Sqrt(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	dst.set(Operator(mat, sqrt));
	//Mat m(mat.size3());
	//Val_ *p = m;
	//for (int32 ind = 0; ind < mat.len(); ind++)
	//	p[ind] = sqrt(mat(ind));
	//dst.set(m);
}
void lzh::Opp(IMat src, OutputArray dst)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	Mat m(mat.size3());
	Val_ *p = m;
	for (int32 ind = 0; ind < mat.len(); ind++)
		p[ind] = -mat(ind);
	dst.set(m);
}
void lzh::Div(IMat src, OutputArray dst, Val val, Dire dire)
{
	Mat mat = src;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(mat);
#endif //MAT_DEBUG
	Mat m(mat.size3());
	Val_ *p = m;
	for (int32 ind = 0; ind < m.len(); ind++)
		if (dire == LEFT)
			p[ind] = val / mat(ind);
		else if (dire == RIGHT)
			p[ind] = mat(ind) / val;
	dst.set(m);
}
void lzh::Div(IMat m1, IMat m2, OutputArray dst, Dire dire)
{
	Mat a = m1;
	Mat b = m2;
	Mat result;
	switch (dire)
	{
	case LEFT:	result = a.inv()*b; break;
	case RIGHT:	result = b.inv()*a; break;
	default:THROW_INFO(ERR_INFO_VALUE);
	}
	dst.set(result);
}
void lzh::Mult(IMat m1, IMat m2, OutputArray dst)
{
	Hadamard(m1, m2, dst);
}
void lzh::Hadamard(IMat m1, IMat m2, OutputArray dst)
{
	Mat a = m1;
	Mat b = m2;
	Mat mat;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(a);
	CHECK_MATRIX_(b);
#endif //MAT_DEBUG
	if (b.rows() == 1 && b.cols() == 1 && a.channels() == b.channels()) {
		mat.create(a.size3());
		for (int32 z = 0; z < mat.channels(); z++) {
			mat_t v = b(z);
			for (int32 i = 0; i < mat.rows(); i++)
				for (int32 j = 0; j < mat.cols(); j++)
					mat(i, j, z) = a(i, j, z) * v;
		}
	}
	else if (a.rows() == 1 && a.cols() == 1 && a.channels() == b.channels())
	{
		mat.create(b.size3());
		for (int32 z = 0; z < mat.channels(); z++) {
			mat_t v = a(z);
			for (int32 i = 0; i < mat.rows(); i++)
				for (int32 j = 0; j < mat.cols(); j++)
					mat(i, j, z) = b(i, j, z) * v;
		}
	}
#ifdef MAT_DEBUG
	else if (a.rows() != b.rows() || a.cols() != b.cols() || a.channels() != b.channels())
		THROW_INFO(ERR_INFO_SIZE);
#endif //MAT_DEBUG
	else {
		mat.create(a.size3());
		for (int32 ind = 0; ind < a.len(); ind++)
			mat(ind) = a(ind) * b(ind);
	}
	dst.set(mat);
}
void lzh::Dot(IMat m1, IMat m2, OutputArray dst)
{
	Mat a = m1;
	Mat b = m2;
	Mat result = a * b;
	dst.set(result);
}
void lzh::Sub(IMat a, IMat b, OutputArray dst)
{
	dst.set(a - b);
}
void lzh::Add(IMat a, IMat b, OutputArray dst)
{
	dst.set(a + b);
}
void lzh::Trapezoidal(IMat src_, OutputArray dst_, bool normalization)
{
	Mat src = src_;
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
	if (src.dims() != 2)
		THROW_INFO(ERR_INFO_NOT2D);
#endif //MAT_DEBUG 
	Mat dst = src.clone();
	int32 height = dst.rows();
	int32 width = dst.cols();
	int32 *ZeroNum = new int32[2 * height];
	for (int32 count = 0; count < height; count++) {
		for (int32 i = 0; i < height; i++) {
			int32 count_ = 0;
			for (int32 j = 0; j < width; j++) {
				if (dst.isZero(i*width + j))
					count_++;
				else break;
			}
			ZeroNum[i * 2] = i;
			ZeroNum[i * 2 + 1] = count_;
		}
		for (int32 i = 0; i < height - 1; i++) {
			for (int32 j = i + 1; j < height; j++) {
				if (ZeroNum[i * 2 + 1] > ZeroNum[j * 2 + 1]) {
					__swap(ZeroNum[i * 2], ZeroNum[j * 2]);
					__swap(ZeroNum[i * 2 + 1], ZeroNum[j * 2 + 1]);
				}
			}
		}
		Mat t(dst.size3());
		for (int32 i = 0; i < height; i++) {
			for (int32 j = 0; j < width; j++) {
				t[j + i * width] = dst[j + ZeroNum[i * 2] * width];
			}
		}
		dst = t.clone();
		if ((width - ZeroNum[count * 2 + 1]) != (width - count))
			continue;
		if (normalization && !dst.isOne(count + count * width)) {
			mat_t m = 1 / dst(count + count * width);
			for (int32 i = 0; i < width; i++) {
				if (dst.isZero(i + count * width))continue;
				dst[i + count * width] *= m;
			}
		}
		for (int32 i = count + 1; i < height; i++) {
			if ((width - ZeroNum[i * 2 + 1]) != (width - count))continue;
			mat_t m = dst[count + i * width] / dst[count + count * width];
			for (int32 j = ZeroNum[i * 2 + 1]; j < width; j++) {
				if (dst.isZero(j + count * width))continue;
				dst[j + i * width] -= m * dst[j + count * width];
			}
		}
	}
	FREE_ARRAY(ZeroNum);
	dst_.set(dst);
}
void lzh::RowSimplest(IMat src, OutputArray dst_, int32 *rank)
{
	Mat dst;
	Trapezoidal(src, dst);
	int32 height = dst.rows();
	int32 width = dst.cols();
	for (int32 i = 1; i < height; i++) {
		bool flag = false;
		int32 j;
		for (j = 0; j < width; j++) {
			if (!dst.isZero(i*width + j)) {
				flag = true;
				break;
			}
		}
		if (!flag)continue;
		for (int32 k = i - 1; k >= 0; k--) {
			mat_t m = dst[j + k * width] / dst[j + i * width];
			for (int32 l = j; l < width; l++) {
				dst[l + k * width] -= m * dst[l + i * width];
			}
		}
	}
	if (rank)
		*rank = dst.rank();
	dst_.set(dst);
}
void lzh::ColSimplest(IMat src, OutputArray dst, int32 *rank)
{
	RowSimplest(src.t(), dst, rank);
}