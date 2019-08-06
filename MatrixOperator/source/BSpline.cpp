#include "BSpline.h"
#include "MatApi.h"
using namespace lzh;

/****************************************************************************
B-样条曲线类
*****************************************************************************/
lzh::BSpline::BSpline() :
	type(UNIFORM), k(0),
	P(), nodevector()
{

}
lzh::BSpline::BSpline(BSplineType type, int32 k, IMat p) :
	type(type), k(k),
	P(p), nodevector()
{

}
void lzh::BSpline::setCtrlPoint(IMat p)
{
	P = p;
}
OMat lzh::BSpline::CtrlPoint()const
{
	return P;
}
OMat lzh::BSpline::Node()const
{
	return nodevector;
}
mat_t lzh::BSpline::BF(int32 i, int32 k, Val t)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(nodevector);
#endif //MAT_DEBUG
	if (k == 0)
		if (t >= nodevector(i) && t < nodevector(i + 1))
			return _T(1);
		else
			return _T(0);
	else {
		mat_t len1 = nodevector(i + k) - nodevector(i);
		mat_t len2 = nodevector(i + k + 1) - nodevector(i + 1);
		if (len1 == _T(0))
			len1 = _T(1);
		if (len2 == _T(0))
			len2 = _T(1);
		mat_t s1 = (t - nodevector(i)) / len1 * BF(i, k - 1, t);
		mat_t s2 = (nodevector(i + k + 1) - t) / len2 * BF(i + 1, k - 1, t);
		return s1 + s2;
	}
}
OMat lzh::BSpline::BaseFunction(Val t)const
{
	Mat mark(1, P.cols());
	for (int32 i = 0; i < P.cols(); i++)
		mark(i) = BF(i, k, t);
	return mark;
}
void lzh::BSpline::NodeVector(IMat node)
{
	if (!node.empty())
		nodevector = node;
	else {
		switch (type)
		{
		case UNIFORM:
			nodevector = linspace(0, 1, P.cols() + k + 1);
			break;
		case QUASI_UNIFORM: {
			nodevector = Mat::zeros(P.cols() + k + 1);
			int32 linepage = P.cols() - k;
			if (linepage == 1)
				for (int32 ind = P.cols() + 1; ind < P.cols() + k + 1; ind++)
					nodevector(ind) = 1;
			else {
				int32 judge = 1;
				while (judge != linepage) {
					nodevector(k + judge) = nodevector(k + judge - 1) + 1 / linepage;
					judge++;
				}
				for (int32 ind = P.cols() + 1; ind < P.cols() + k + 1; ind++)
					nodevector(ind) = 1;
			}
			break;
		}
		default:
			THROW_INFO(ERR_INFO_UNLESS);
		}
	}
}
OMat lzh::BSpline::BPiont(IMat T)const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(P);
	CHECK_MATRIX_(nodevector);
	CHECK_MATRIX_(T);
#endif //MAT_DEBUG
	Mat m(2, T.len());
	for (int32 i = 0; i < T.len(); ++i) {
		Mat p_u = P * BaseFunction(T(i));
		m(2 * i) = p_u(0);
		m(2 * i + 1) = p_u(1);
	}
	return m;
}
OMat lzh::BSpline::BPoint(int32 number)const
{
	int32 n = P.cols() - 1;
	mat_t start = _T(k) / (n + k + 1);
	mat_t end = _T(n + 1) / (n + k + 1);
	Mat t = linspace(start, end, number);
	return BPiont(t);
}
OMat lzh::BSpline::operator()(Val t) const
{
#ifdef MAT_DEBUG
	CHECK_MATRIX_(P);
	CHECK_MATRIX_(nodevector);
#endif //MAT_DEBUG
	return P * BaseFunction(t);
}
lzh::BSpline lzh::BSpline::fit(IMat P, int32 n, int32 k)
{
	int32 r = P.rows() - 1;
	n = n + 2;
	mat_t start = _T(k) / (n + k + 1),
		end = _T(n + 1) / (n + k + 1);
	Mat t = linspace(start, end, P.rows());
	Mat Node = linspace(0, 1, n + k + 1);
	//t.show();
	BSpline bs(BSpline::UNIFORM, k);
	bs.NodeVector(Node);
	Mat N(n, r + 1);
	//n = n - 1;
	for (int32 i = 0; i < n; i++) {
		for (int32 j = 0; j < P.rows(); j++) {
			N(j, i) = bs.BF(i, k, t(j));
		}
	}
	Mat m;
	LeastSquare(N, P, m);
	m = m.t();
	Mat d;
	Block(m, d, 1, m.rows() - 2, 0, 1);
	Mat p(d, d.range(0, k, 0, 1), ROW);
	bs.setCtrlPoint(p.t());
	bs.NodeVector();
	return bs;
}
