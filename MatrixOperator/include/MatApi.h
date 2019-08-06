#pragma once
#ifndef __MATAPI_H__
#define __MATAPI_H__

#include "Mat.h"
#include "CvMat.h"
#include "LargeNumber.h"

namespace lzh
{
	class _InputArray
	{
	public:
		enum
		{
			NONE = 0,
			MAT = 1,
			CVMAT = 2,
			STD_VECTOR = 3,
			STD_VECTOR_MAT = 4,
			STD_VECTOR_CVMAT = 5,
			STD_VECTOR_VECTOR = 6,
			VALUE = 7,
			MAT_ITER = 8,
			VECTOR = 9,
		};
		_InputArray() : obj(0) {}
		_InputArray(IMat m);
		_InputArray(const CvMat &v);
		_InputArray(const std::vector<Mat> &v);
		_InputArray(const std::vector<CvMat> &v);
		template<typename _Tp>_InputArray(MatCommaInitializer_<_Tp> &m) {
			init(&m, MAT_ITER, DataType<_Tp>::type);
		}
		template<typename _Tp> _InputArray(const _Tp &v) {
			init(&v, VALUE, DataType<_Tp>::type, Size(1, 1));
		}
		template<typename _Tp> _InputArray(const std::vector<_Tp> &v) {
			init(&v, STD_VECTOR, DataType<_Tp>::type, Size(1, (int32)v.size()));
		}
		template<typename _Tp, int32 N> _InputArray(const Vec<_Tp, N> &v) {
			init(&v, VECTOR, DataType<_Tp>::type, Size(1, N));
		}
		template<typename _Tp> _InputArray(const std::vector<std::vector<_Tp>> &v) {
			init(&v, STD_VECTOR_VECTOR, DataType<_Tp>::type, Size(1, (int32)v.size()));
		}

		CvMat getCvMat(int32 i = -1)const;
		Mat getMat(int32 i = -1)const;
		Mat getMat_(int32 i = -1)const;
		void swap(Mat & dst)const;
		bool empty()const;
		bool isMat()const;
		bool isStdVector()const;
		int32 value_type()const;
		int32 kind()const;
		int32 depth()const;
		int32 getTp()const;
		int32 size()const;
		int32 rows()const;
		int32 cols()const;
		int32 len()const;
		Size getSz() const;
		Size getSz_() const;
		template<typename _Tp> operator _Tp*() {
			return obj;
		}
		template<typename _Tp> operator const _Tp*()const {
			return obj;
		}
		const void * object()const { return obj; }
	protected:
		void init(const void *obj, int32 flags, int32 type);
		void init(const void *obj, int32 flags, int32 type, Size sz);

		int32 flags;
		int32 type;
		void *obj;
		Size sz;
	};
	typedef const _InputArray& InputArray;
	bool operator > (InputArray a, InputArray b);
	bool operator < (InputArray a, InputArray b);
	class _OutputArray : public _InputArray
	{
	public:
		_OutputArray() : _InputArray() {}
		_OutputArray(IMat m) : _InputArray(m) {}
		_OutputArray(const vec_mat &v) : _InputArray(v) {}
		_OutputArray(const CvMat &m) : _InputArray(m) {}
		_OutputArray(const vec_cvmat &v) : _InputArray(v) {}
		template<typename _Tp> _OutputArray(const std::vector<_Tp> &v) : _InputArray(v) {}


		void create(Size sz, int32 mtype) const;
		void create(Size3 sz, int32 mtype) const;
		void create(int32 rows, int32 mtype) const;
		void create(int32 rows, int32 cols, int32 mtype) const;
		void create(int32 rows, int32 cols, int32 channels, int32 mtype) const;
		void createSameSize(InputArray arr, int32 mtype) const;
		void release() const;
		void clear() const;
		Mat & getMatRef(int32 i = -1)const;
		CvMat & getCvMatRef(int32 i = -1)const;
		void setMatRef(InputArray input, int32 i = -1)const;
		void set(InputArray input)const;
		void setTo(InputArray input)const;
		void copyTo(InputArray input)const;

		void operator = (InputArray input)const;

	private:
	};
	class _InputOutputArray : public _OutputArray
	{
	public:
		_InputOutputArray() : _OutputArray() {}
		_InputOutputArray(IMat m) : _OutputArray(m) {}
		_InputOutputArray(const vec_mat &v) : _OutputArray(v) {}
		_InputOutputArray(const CvMat m) : _OutputArray(m) {}
		_InputOutputArray(const vec_cvmat &v) : _OutputArray(v) {}
		template<typename _Tp> _InputOutputArray(const _Tp &v) : _OutputArray(v) {}
		template<typename _Tp> _InputOutputArray(const std::vector<_Tp> &v) : _OutputArray(v) {}
	};
	typedef InputArray InputArrayOfArrays;
	typedef const _OutputArray& OutputArray;
	typedef OutputArray OutputArrayOfArrays;
	typedef const _InputOutputArray& InputOutputArray;
	typedef InputOutputArray InputOutputArrayOfArrays;

	template<class _Tp> inline Mat::Mat(const std::vector<_Tp>& vec)
	{
		init();
		if (!vec.empty()) {
			if (DataType<_Tp>::type == MAT_T)
				*this = _InputArray(vec).getMat();
			else {
				_InputArray _inputarray(vec);
				CvMat data = _inputarray.getCvMat();
				create(_inputarray.getSz_());
				FOR_RANGE(i, 0, data.len())operator()(i) = data.get<mat_t>(i);
			}
		}
	}

	class FunOp
	{
	public:
		static mat_t angle2radian(mat_t);
		static mat_t radian2angle(mat_t);
		static mat_t EuclideanDistance_2D(mat_t, mat_t);
		static mat_t mul(mat_t, mat_t);
		static mat_t inv_mul(mat_t, mat_t);
	};
	/**
	设置随机数种子
	*/
	extern void Srandom();
	template<typename _Tp> std::vector<_Tp> range(_Tp low, _Tp top, Val gap = 1);
	/**
	@brief 返回从low到top等分成的1*len的矩阵
	@param low 下界
	@param top 上界
	@param gap 间距
	*/
	extern OMat mRange(Val low, Val top, Val gap = 1);
	/**
	@brief 返回从low到top等分成的1*len的矩阵
	@param low 下界
	@param top 上界
	@param len 等分个数
	*/
	extern OMat linspace(Val low, Val top, int32 len);
	/**
	@brief 返回随机矩阵
	符合高斯分布
	大小为size
	@param size		矩阵大小
	@param n1		先前通道
	@param n2		当前通道
	*/
	extern OMat Xavier(Size3 size, int32 n1, int32 n2);
	/**
	@brief 返回随机矩阵
	符合高斯分布
	大小为h_*w_*c_
	@param h_		矩阵行数
	@param w_		矩阵列数
	@param c_	矩阵通道数
	@param n1		先前通道
	@param n2		当前通道
	*/
	extern OMat Xavier(int32 w, int32 h, int32 c, int32 n1, int32 n2);
	/**
	@brief 返回随机矩阵
	符合高斯分布
	大小为size, 元素范围[0, 1]
	@param size		矩阵大小
	*/
	extern OMat Random(Size3 size);
	/**
	@brief 返回随机矩阵
	符合高斯分布
	大小为h_*w_*c_, 元素范围[0, 1]
	@param h_		矩阵行数
	@param w_		矩阵列数
	@param c_	矩阵通道数
	*/
	extern OMat Random(int32 w, int32 h = 1, int32 c = 1);
	extern mat_t generateGaussian(Val x, Val sigma);
	extern mat_t generateGaussian(Val x, Val y, Val sigma);
	extern mat_t generateLoG(Val x, Val sigma);
	extern mat_t generateLoG(Val x, Val y, Val sigma);
	extern mat_t generateDoG(Val x, Val sigma1, Val sigma2);
	extern mat_t generateDoG(Val x, Val y, Val sigma1, Val sigma2);
	/**
	@brief 返回矩阵的最大值
	@param src		矩阵
	@param isAbs	是否取绝对值
	*/
	extern mat_t Max(IMat src, bool isAbs = false);
	/**
	@brief 返回矩阵的最小值
	@param src		矩阵
	@param isAbs	是否取绝对值
	*/
	extern mat_t Min(IMat src, bool isAbs = false);
	/**
	@brief 返回向量的中值
	@param src	向量
	*/
	extern mat_t median(IMat src);
	/**
	@brief 返回随机数
	@param Min		最小值
	@param Max		最大值
	@param isdouble 是否随机非整数
	*/
	extern mat_t getRandData(int32 min, int32 max, bool isdouble = false);
	/**
	@brief 返回矩阵的距离
	@param a	矩阵
	@param b	矩阵
	@param num	几范数
	*/
	extern mat_t Dist(IMat a, IMat b, int32 num = 2);
	/**
	@brief 返回随机的矩阵元素
	@param src 矩阵
	*/
	extern mat_t randSample(IMat src);
	/**
	@brief 返回矩阵的第c_的通道
	@param src		矩阵
	@param c_	通道索引
	*/
	extern void split(IMat src, int32 c, OutputArray dst);
	/**
	@brief 返回按矩阵的通道数复制
	@param src 输入矩阵
	@param dst 输入矩阵通道数的矩阵数组
	*/
	extern void split(InputArray src, OutputArrayOfArrays dst);
	/**
	@brief 返回按矩阵的通道数复制
	@param src 输入矩阵
	@param dst 输入矩阵通道数的矩阵数组
	*/
	extern void split(IMat src, Mat *dst);
	/**
	@brief 返回按矩阵的通道数复制
	@param src 输入矩阵
	@param dst 输入矩阵通道数的矩阵数组
	*/
	extern void split(const CvMat & src, CvMat *dst);
	/**
	@brief 返回按通道合并的矩阵
	@param src		矩阵数组
	@param channels 通道数
	*/
	extern void merge(const Mat *src, int32 channels, OutputArray dst);
	/**
	@brief 返回按通道合并的矩阵
	@param src		矩阵数组
	@param channels 通道数
	*/
	extern void merge(InputArrayOfArrays src, OutputArray dst);
	/**
	@brief 返回按通道合并的矩阵
	@param src		矩阵数组
	@param channels 通道数
	*/
	extern void merge(InputArrayOfArrays src, int32 channels, OutputArray dst);
	/**
	@brief 返回按索引区域切割的矩阵
	@param src			矩阵
	@param Row_Start	截取行初始索引值
	@param Row_End		截取行结束索引值
	@param Col_Start	截取列初始索引值
	@param Col_End		截取列结束索引值
	*/
	extern void Block(IMat src, OutputArray dst, int32 Row_Start, int32 Row_End, int32 Col_Start, int32 Col_End, int32 Chennel_Start = 0, int32 Chennel_End = 0);
	/**
	@brief 返回随机生成元素size.x*size.y*size.z矩阵
	@param low		下界
	@param top		上界
	@param size		矩阵大小
	@param isdouble 是否生成浮点数
	*/
	extern OMat Rand(int32 low, int32 top, Size3 size, bool isdouble = false);
	/**
	@brief 返回逆序矩阵，矩阵需为一维向量
	@param src	矩阵
	*/
	extern OMat reverse(IMat src);
	/**
	@brief 返回生成h*w*c的矩阵，随机抽取矩阵src元素填充
	@param src	矩阵
	@param h	矩阵行数
	@param w	矩阵列数
	@param c	矩阵通道数
	*/
	extern OMat randSample(IMat src, int32 w, int32 h, int32 c = 1);
	/**
	@brief 返回随机抽取num次矩阵src的行或列组成的矩阵
	@param src	矩阵
	@param rc	抽取方式
	@param num	抽取次数
	*/
	extern OMat randSample(IMat src, RANK rc, int32 num = 1);
	/**
	@brief 返回op操作结果
	@param src 矩阵
	*/
	extern OMat Operator(IMat src, mat_t(*op)(mat_t));
	/**
	@brief 返回op操作结果
	@param src 矩阵
	*/
	extern OMat Operator(IMat m1, IMat m2, mat_t(*op)(mat_t, mat_t));
	/**
	@brief 返回按位非
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Bitwise_not(InputOutputArray a, int32 depth);
	/**
	@brief 返回按位非
	@param a 矩阵
	@param b 矩阵
	*/
	extern OMat Bitwise_not(IMat a, int32 depth);
	/**
	@brief 返回按位与
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Bitwise_and(InputOutputArray a, IMat b, int32 depth);
	/**
	@brief 返回按位与
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Bitwise_and(InputOutputArray a, Val b);
	/**
	@brief 返回按位与
	@param a 矩阵
	@param b 矩阵
	*/
	extern OMat Bitwise_and(IMat a, IMat b, int32 depth);
	/**
	@brief 返回按位与
	@param a 矩阵
	@param b 矩阵
	*/
	extern OMat Bitwise_and(IMat a, Val b);
	/**
	@brief 返回按位或
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Bitwise_or(InputOutputArray a, Val b);
	/**
	@brief 返回按位或
	@param a 矩阵
	@param b 矩阵
	*/
	extern void Bitwise_or(InputOutputArray a, IMat b, int32 depth);
	/**
	@brief 返回按位或
	@param a 矩阵
	@param b 矩阵
	*/
	extern OMat Bitwise_or(IMat a, IMat b, int32 depth);
	/**
	@brief 返回按位或
	@param a 矩阵
	@param b 矩阵
	*/
	extern OMat Bitwise_or(IMat a, Val b);
	/**
	@brief 返回cos结果
	@param src 矩阵
	*/
	extern OMat Cos(IMat src);
	/**
	@brief 返回cosh结果
	@param src 矩阵
	*/
	extern OMat Cosh(IMat src);
	/**
	@brief 返回sin结果
	@param src 矩阵
	*/
	extern OMat Sin(IMat src);
	/**
	@brief 返回sinh结果
	@param src 矩阵
	*/
	extern OMat Sinh(IMat src);
	/**
	@brief 返回tan结果
	@param src 矩阵
	*/
	extern OMat Tan(IMat src);
	/**
	@brief 返回tanh结果
	@param src 矩阵
	*/
	extern OMat Tanh(IMat src);
	/**
	@brief 返回acos结果
	@param src 矩阵
	*/
	extern OMat arcCos(IMat src);
	/**
	@brief 返回acosh结果
	@param src 矩阵
	*/
	extern OMat arcCosh(IMat src);
	/**
	@brief 返回asin结果
	@param src 矩阵
	*/
	extern OMat arcSin(IMat src);
	/**
	@brief 返回asinh结果
	@param src 矩阵
	*/
	extern OMat arcSinh(IMat src);
	/**
	@brief 返回atan结果
	@param src 矩阵
	*/
	extern OMat arcTan(IMat src);
	/**
	@brief 返回atanh结果
	@param src 矩阵
	*/
	extern OMat arcTanh(IMat src);
	/**
	@brief 返回atan2结果
	@param src 矩阵
	*/
	extern OMat arcTan2(IMat y, IMat x);
	/**
	@brief 弧度转角度
	@param src 矩阵
	*/
	extern OMat Radian2Angle(IMat radian);
	/**
	@brief 角度转弧度
	@param src 矩阵
	*/
	extern OMat Angle2Radian(IMat angle);
	/**
	@brief 返回矩阵的绝对值矩阵
	@param src 矩阵
	*/
	extern void Abs(IMat src, OutputArray dst);
	/**
	@brief 返回angle度2*2的旋转矩阵
	@param angle 角度
	*/
	extern OMat getRotationMat2D(Point2f center, Val angle);
	/**
	@brief 返回angle度3*3的旋转矩阵
	@param angle 角度
	*/
	extern OMat getRotationMat3D(Point2f center, Val angle);
	/**
	@brief 返回a*b
	使用傅里叶变换计算
	*/
	extern const LargeNumber fftMult(const LargeNumber &a, const LargeNumber &b);
	/**
	@brief 返回a*b
	使用傅里叶变换计算
	*/
	extern void fftMult(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回复数乘法
	@param a 矩阵
	@param b 矩阵
	*/
	extern void complexDot(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回复数乘法
	二进制平摊反转置换 O(logn)
	*/
	extern void brc(InputOutputArray src);
	extern void phase(IMat x, IMat y, OutputArray angle, bool angleInDegrees = false);
	extern void magnitude(IMat x, IMat y, OutputArray magnitude);
	extern void mulSpectrums(IMat a, IMat b, OutputArray c, bool conjB = false);
	/**
	@brief 返回矩阵按元素取a和b之间的最大值
	@param a 比较值
	@param b 比较矩阵
	*/
	extern void Max(Val a, IMat b, OutputArray dst);
	/**
	@brief 返回矩阵按元素取a和b之间的最大值
	@param a 比较矩阵
	@param b 比较矩阵
	*/
	extern void Max(IMat a, IMat b, OutputArray dst);
	/**
	@brief 返回矩阵按元素取a和b之间的最小值
	@param a 比较值
	@param b 比较矩阵
	*/
	extern void Min(Val a, IMat b, OutputArray dst);
	/**
	@brief 返回矩阵按元素取a和b之间的最小值
	@param a 比较矩阵
	@param b 比较矩阵
	*/
	extern void Min(IMat a, IMat b, OutputArray dst);
	/**
	@brief CalSize 计算卷积所需扩张的边界
	返回矩阵大小
	@param src		被卷积矩阵
	@param kern		卷积核
	@param anchor	像素对应卷积核坐标
	anchor默认为Point(-1,-1), 像素对应卷积核中心
	@param strides	滑动步长
	@param top		向上扩充几行
	@param bottom	向下扩充几行
	@param left		向左扩充几列
	@param right	向右扩充几列
	*/
	extern Size3 CalSize(Size3 src, Size3 kern, Point anchor, Size strides, int32 &top, int32 &bottom, int32 &left, int32 &right);
	/**
	@brief CalSize 计算卷积所需扩张的边界
	返回矩阵大小
	@param src		被卷积矩阵尺寸
	@param kern		卷积核尺寸
	@param anchor	像素对应卷积核坐标
	*/
	extern Size3 CalSize(Size3 src, Size3 kern, Point anchor, Size strides);
	/**
	@brief CalSize 计算卷积所需扩张的边界
	返回矩阵大小
	@param src		被卷积矩阵尺寸
	@param kern		卷积核尺寸
	@param anchor	像素对应卷积核坐标
	*/
	extern Size3 CalSize(Size3 src, Size kern, Point anchor, Size strides);
	extern void HomomorphicFilter(IMat src, OutputArray dst, Val D0, Val n, Val rL, Val rH);
	extern void GaussianFilter(IMat src, OutputArray dst, Size ksize, Val sigma, BorderTypes borderType = BORDER_DEFAULT);
	extern void unevenLightCompensate(IMat image_, OutputArray dst, int32 blockSize);
	extern void GaussianBlur(IMat src, OutputArray dst, Size ksize, Val sigma, BorderTypes borderType = BORDER_DEFAULT);
	extern void medianBlur(IMat src, OutputArray dst, int32 ksize);
	extern void blur(IMat src, OutputArray dst, Size kernel, Point anchor = Point(-1, -1), int32 iteration = 1);
	extern void erode(IMat src, OutputArray dst, IMat kernel, int32 iteration = 1, Point anchor = Point(-1, -1));
	extern void dilate(IMat src, OutputArray dst, IMat kernel, int32 iteration = 1, Point anchor = Point(-1, -1));
	extern OMat getStructuringElement(MorphShape morphshape, Size elementsize);
	extern void morphologyEx(IMat src, OutputArray dst, MorphType morphtype, IMat kernel, int32 iteration = 1, Point anchor = Point(-1, -1));
	extern void reverse(IMat src, OutputArray dst, Val v);
	/**
	@brief 返回按boundary分界填充的矩阵
	返回矩阵大小等于输入矩阵大小
	@param src				输入矩阵
	@param boundary			分界值
	@param lower			小于boundary用lower填充
	@param upper			大于boundary用upper填充
	@param boundary2upper	当矩阵元素等于boundary时(为1归upper,为-1归lower, 为0不处理)
	*/
	extern void Threshold(IMat src, OutputArray dst, Val boundary, Val lower, Val upper, int32 boundary2upper = 1);
	/**
	@brief 二值化
	返回矩阵大小等于输入矩阵大小
	@param src				输入矩阵
	@param thresh			阈值
	@param maxval			大于boundary用thresh填充
	@param method			二值化方法
	*/
	extern mat_t Threshold(IMat src, OutputArray dst, Val thresh, Val maxval, ThreshMethod method);
	extern void adaptiveThreshold(IMat src, OutputArray dst, int32 area_pro = 3, int32 percent = 15);
	extern mat_t getOtsuThreshold(IMat src);
	/**
	@brief 返回边界扩充的矩阵
	@param src			输入矩阵
	@param newSize		新矩阵尺寸
	@param borderType	边界像素外推的插值方法
	@param value		常量插值的数值
	**/
	extern void copyMakeBorder(IMat src, OutputArray dst, Size newSize, BorderTypes borderType, Val value = 0.0);
	/**
	@brief 返回边界扩充的图像
	@param src			输入图像
	@param newSize		新图像尺寸
	@param borderType	边界像素外推的插值方法
	@param value		常量插值的数值
	**/
	extern void copyMakeBorder(IMat src, OutputArray dst, Size newSize, BorderTypes borderType, const Color &value);
	/**
	@brief 返回边界扩充的矩阵
	@param src			输入矩阵
	@param top			向上扩充几行
	@param bottom		向下扩充几行
	@param left			向左扩充几列
	@param right		向右扩充几列
	@param borderType	边界像素外推的插值方法
	@param value		常量插值的数值
	**/
	extern void copyMakeBorder(IMat src, OutputArray dst, int32 top, int32 bottom, int32 left, int32 right, BorderTypes borderType, const Color &value);
	/**
	@brief 返回边界扩充的矩阵
	@param src			输入矩阵
	@param top			向上扩充几行
	@param bottom		向下扩充几行
	@param left			向左扩充几列
	@param right		向右扩充几列
	@param borderType	边界像素外推的插值方法
	@param value		常量插值的数值
	**/
	extern void copyMakeBorder(IMat src, OutputArray dst, int32 top, int32 bottom, int32 left, int32 right, BorderTypes borderType = BORDER_CONSTANT, Val value = 0.0);
	/**
	@brief 返回矩阵2维卷积结果(只支持二维输入)
	返回矩阵大小为(input.h_/strides_x, input.w_/strides_y, 1)
	@param input			输入矩阵
	@param kern				卷积核
	@param anchor			矩阵元素对应卷积核的位置
	以卷积核的左上角为(0,0)点, 默认(-1,-1)为中心
	@param strides			滑动步长
	Size.hei为x轴,Size.wid为y轴
	@param is_copy_border	是否要扩展边界
	*/
	extern void Filter2D(IMat src, OutputArray dst, IMat kern, Point anchor = Point(-1, -1), Size strides = Size(1, 1), bool is_copy_border = true, BorderTypes borderType = BORDER_CONSTANT, Val value = 0);
	extern void Convolution(IMat src, OutputArray dst, IMat kern, Point anchor = Point(-1, -1), Size strides = Size(1, 1), bool is_copy_border = true, BorderTypes borderType = BORDER_CONSTANT, Val value = 0);
	extern void img2col(IMat src, OutputArray dst, Size kernel, Point anchor = Point(-1, -1), Size strides = Size(1, 1), bool is_copy_border = true, BorderTypes borderType = BORDER_CONSTANT, Val value = 0);
	//extern void fastFilter2D(IMat src, OutputArray dst, IMat kern, Point anchor = Point(-1, -1), Size strides = Size(1, 1), bool is_copy_border = true, BorderTypes borderType = BORDER_CONSTANT, Val value = 0.0);
	extern void filter2D(IMat src, OutputArray dst, IMat kern, ConvolutionType type, BorderTypes border_types, Val value = 0);
	/**
	@brief 返回矩阵2维卷积结果(支持三维输入)
	返回矩阵大小为(input.h_/strides_x, input.w_/strides_y, 1)
	@param src				输入矩阵
	@param dst				输出矩阵
	@param kern				卷积核
	@param anchor			矩阵元素对应卷积核的位置
	以卷积核的左上角为(0,0)点, 默认(-1,-1)为中心
	@param strides			滑动步长
	Size.hei为x轴,Size.wid为y轴
	@param is_copy_border	是否要扩展边界
	*/
	extern void Conv2D(IMat src, OutputArray dst, IMat kern, Point anchor = Point(-1, -1), const Size & strides = Size(1, 1), bool is_copy_border = true);
	extern void conv2(IMat src, OutputArray dst, IMat kern, ConvolutionType type, BorderTypes border_types = BORDER_CONSTANT, const Color & value = Color(0));
	/**
	实现矩阵在水平方向，垂直方向和水平垂直方向的翻转
	@param src				输入矩阵
	@param dst				输出矩阵
	@param filpCode			旋转类型，0代表x轴旋转，任意正数代表y轴旋转，任意负数代表x和y轴同时旋转
	*/
	extern void flip(InputArray src, OutputArray dst, int32 flipCode = 0);
	extern void HighPass(IMat src, OutputArray dst, Val r = 3, Size ksize = Size(7, 7), Val sigma = 1.6);
	extern OMat ButterworthFilter(Size sz, Val D, Val n, Val high_h_v_TB, Val low_h_v_TB);
	extern OMat FourierTransform(IMat frame_bw, OutputArray image_complex, Mat *image_phase = nullptr, Mat *image_mag = nullptr);
	extern void InvFourierTransform(IMat input, OutputArray inverseTransform);
	extern OMat RobertsKernel(int32 angle);
	extern OMat PrewittKernel(int32 angle);
	extern OMat SobelKernel(int32 angle);
	extern OMat LapacianKernel(LaplaceType neighbourhood = Four_Dire);
	extern OMat GaussianKernel(Size ksize, Val sigma);
	extern OMat LoGKernel(Size ksize, Val sigma);
	extern OMat DoGKernel(Size ksize, Val sigma1, Val sigma2);
	extern OMat SharpenKernel(SharpenScale level);
	extern void ConvKernel(IMat src, OutputArray dst, OMat(*CreatKernel)(int32), int32 angle);
	extern void Sobel(IMat src, OutputArray dst, int32 angle);
	extern void Roberts(IMat src, OutputArray dst, int32 angle);
	extern void Prewitt(IMat src, OutputArray dst, int32 angle);
	extern void Sharpen(IMat src, OutputArray dst, SharpenScale level);
	extern void Lapacian(IMat src, OutputArray dst, LaplaceType laplacetype = Four_Dire);
	extern void LoG(IMat src, OutputArray dst, Size ksize, Val sigma);
	extern void DoG(IMat src, OutputArray dst, Size ksize, Val sigma1, Val sigma2);
	extern void Roberts(IMat src, OutputArray dst);
	extern void Prewitt(IMat src, OutputArray dst);
	/**
	sobel算子卷积图像
	@param src				输入矩阵
	@param dst				输出矩阵
	*/
	extern void Sobel(IMat src, OutputArray dst);

	extern void Canny(IMat dx, IMat dy, OutputArray edges, Val threshold1, Val threshold2, bool L2gradient = true);
	extern void Canny(IMat image, OutputArray edges, Val threshold1, Val threshold2, bool L2gradient = true, int32 ksize = 5, Val sigma = 1);

	class Dfs
	{
	public:
		enum
		{
			Recursion = 0,
			Iteration,
		};
		typedef bool(*DfsOperator)(InputOutputArray, Point, Object*);
		typedef void(*DfsCallBack)(Object*);
		static void DfsMark(InputOutputArray image, Val thresh, DfsOperator op, int32 method, Object* pre = nullptr, DfsCallBack callback = nullptr);
		static void DfsMark(InputOutputArray image, Point seedpoint, DfsOperator op, int32 method, Object* pre = nullptr, DfsCallBack callback = nullptr);
		static void DfsMarkRecursion(InputOutputArray image, Val thresh, DfsOperator op, Object* pre = nullptr, DfsCallBack callback = nullptr);
		static void DfsMarkRecursion(InputOutputArray image, int32 col, int32 row, DfsOperator op, Object*pre = nullptr, int32 dire = 0);
		static void DfsMarkRecursion(InputOutputArray image, Point seedpoint, DfsOperator op, Object*pre = nullptr, DfsCallBack callback = nullptr);
		static int32 DfsCalDirection(int32 &angle, int32 angle_offset);
		static bool DfsBackDirection(Point &p, int32 &state, int32 &angle);
		static bool DfsForwardDirection(int32 *stateArr, Point &p, int32 &angle, int32 angle_flag, int32 rows, int32 cols, int32 dy = 0, int32 dx = 0);
		static bool DfsForwardDirection(int32 *angleArr, int32 *stateArr, Point &p, int32 &angle, int32 rows, int32 cols);
		static void DfsMarkIteration(InputOutputArray image, Val thresh, DfsOperator op, Object*pre = nullptr, DfsCallBack callback = nullptr);
		static void DfsMarkIteration(InputOutputArray image, Point seedpoint, DfsOperator op, Object*pre = nullptr, DfsCallBack callback = nullptr);
		static void DfsMarkIteration(InputOutputArray image, int32 *angleArr, int32 *stateArr, Point seedpoint, DfsOperator op, Object * pre = nullptr, DfsCallBack callback = nullptr);
	};
	extern void MarkMainArea(InputOutputArray img, int32 col, int32 row, int32 dire);
	extern void SearchMainArea(InputOutputArray img);

	extern void floodFill(InputOutputArray image, Point seedPoint, Val newVal);
	extern void floodFill(InputOutputArray image, InputOutputArray mark, Point seedPoint, Val newVal);
	extern void floodHole(IMat src, OutputArray dst, Val newVal = 255);
	extern void findContours(IMat image, OutputArrayOfArrays contours, Val threshold1, Val threshold2, bool L2gradient = true);
	extern Rect bouningRect(InputArray contour);
	extern Rectf bouningRectf(InputArray contour);

	extern int32 mod(Val x, int32 val);
	template<typename _Tp> int32 Round(_Tp x) { return (int32)(x + (_Tp)0.5); }
	template<>extern int32 Round(float32 x);
	template<>extern int32 Round(float64 x);
	template<>extern int32 Round(float64_ x);

	/*********************************************************************
	绘制图像
	**********************************************************************/
	extern void SetPixel(InputOutputArray src, Point point, int32 x, int32 y, const Color & color);
	template<typename _Tp> void addContour(std::vector<Point2_<_Tp>>& contour, Point2_<_Tp> point, int32 x, int32 y, int32 rows, int32 cols)
	{
		contour.push_back(Point2_<_Tp>(point.x + x, point.y + y));
		contour.push_back(Point2_<_Tp>(point.x + x, point.y + -y));
		contour.push_back(Point2_<_Tp>(point.x + -x, point.y + y));
		contour.push_back(Point2_<_Tp>(point.x + -x, point.y + -y));
		contour.push_back(Point2_<_Tp>(point.x + y, point.y + x));
		contour.push_back(Point2_<_Tp>(point.x + y, point.y + -x));
		contour.push_back(Point2_<_Tp>(point.x + -y, point.y + x));
		contour.push_back(Point2_<_Tp>(point.x + -y, point.y + -x));
	}
	extern void BresenhamCircle(InputOutputArray circlePoints, Size size, Point point, int32 radius, int32 lineWidth = 1);
	extern void BresenhamCircle(InputOutputArray src, Point point, int32 radius, const Color &color, int32 lineWidth, bool fill = false);
	extern void drawPoint(InputOutputArray src, Point p, const Color & color);
	extern void circle(InputOutputArray src, Point p, int32 radius, const Color &color, int32 lineWidth = 1, bool fill = false);
	extern void circle(InputOutputArray src, int32 x, int32 y, int32 radius, const Color &color, int32 lineWidth = 1, bool fill = false);
	extern void drawFill(InputOutputArray src, vec_p2_32s &contour, const Color & color);
	extern void lines(OutputArray src, Point p1, Point p2);
	extern void lines(InputOutputArray src, Point p1, Point p2, const Color & color, int32 lineWidth = 1, bool fill = false);
	extern void lines(InputOutputArray src, IMat points, const Color & color, int32 lineWidth = 1, bool fill = false);
	extern void rectangle(InputOutputArray src, int32 x1, int32 y1, int32 x2, int32 y2, const Color & color, int32 lineWidth = 1, bool fill = false);
	extern void rectangle(InputOutputArray src, Rect rect, const Color & color, int32 lineWidth = 1, bool fill = false);
	extern void drawContours(InputOutputArray src, IMat contours, const Color & color, int32 radius = 1, int32 lineWidth = 1, bool fill = false);
	extern void drawContours(InputOutputArray src, const vecs_p2_32s & contours, int32 index, int32 radius, const Color & color, int32 lineWidth = 1, bool fill = false);
	extern void drawContour(InputOutputArray src, const vec_p2_32s & contours, const Color & color, int32 radius = 1, int32 lineWidth = 1, bool fill = false);
	extern void projection(IMat src, OutputArray vertical, OutputArray horizontal);
	extern void verticalProjection(IMat src, OutputArray vertical);
	extern void horizontalProjection(IMat src, OutputArray horizontal);
	extern void mosaic(IMat src, OutputArray dst, Rect mosaicRange, int32 ksize = 3, MosaicMethod method = MosaicAngle135);
	extern void mosaic(InputOutputArray image, Point mosaicRange, int32 ksize = 3, MosaicMethod method = MosaicAngle135);
	extern void mosaic(IMat src, OutputArray dst, vec_p2_32s mosaicRange, int32 ksize = 3, MosaicMethod method = MosaicAngle135);

	class Distance
	{
	public:
		enum DistMethod {
			MANHATTAN = 0,
			EUCLIDEAN,
			CHEBYSHEV,
			COSINE
		};
		typedef Val_(*DistFun)(InputArray v1, InputArray v2);
		static Val_ dist(InputArray v1, InputArray v2, DistMethod method);
		static Val_ Manhattan(InputArray v1, InputArray v2);
		static Val_ Euclidean(InputArray v1, InputArray v2);
		static Val_ Chebyshev(InputArray v1, InputArray v2);
		static Val_ Cosine(InputArray v1, InputArray v2);
		/**
		按距离排序
		*/
		static void Sort(InputOutputArray src, DistFun f = Euclidean, bool seachtop = false, RANK r = ROW);
	};

	/**
	仿射变换
	*/
	extern void warpAffine(IMat src, OutputArray dst, IMat M);
	/**
	傅里叶变换
	*/
	extern void dft(IMat src, OutputArray dst);
	/**
	傅里叶逆变换
	*/
	extern void idft(IMat src, OutputArray dst);
	/**
	一维快速傅里叶变换
	FFT O(nlogn)
	*/
	extern OMat fft1D(InputOutputArray src);
	/**
	一维快速傅里叶变换
	FFT O(nlogn)
	*/
	extern OMat fft1D(IMat src);
	/**
	一维快速逆傅里叶变换
	FFT O(nlogn)
	*/
	extern OMat ifft1D(IMat src);
	/**
	二维傅里叶变换
	*/
	extern OMat dft1D(IMat src);
	/**
	二维逆傅里叶变换
	*/
	extern OMat idft1D(IMat src);
	/**
	二维傅里叶变换
	*/
	extern OMat dft2D(IMat src);
	/**
	二维逆傅里叶变换
	*/
	extern OMat idft2D(IMat src);
	/**
	二维快速傅里叶变换
	*/
	extern OMat fft2D(IMat src);
	/**
	二维快速逆傅里叶变换
	*/
	extern OMat ifft2D(IMat src);
	/**
	频谱搬移至中心
	*/
	extern void dftShift(InputOutputArray src);
	/**
	频谱还原
	*/
	extern void idftShift(InputOutputArray src);
	/**
	频谱搬移至中心
	*/
	extern void dftShift(IMat src, OutputArray dst);
	/**
	频谱还原
	*/
	extern void ifftShift(IMat src, OutputArray dst);
	/**
	返回是否符合快速傅里叶的要求尺寸
	*/
	extern bool isOptimalDFTSize(int32 size);
	/**
	返回是否符合快速傅里叶的要求尺寸
	*/
	extern bool isOptimalDFTSize(Size size);
	/**
	返回是否符合快速傅里叶的要求尺寸
	*/
	extern int32 getOptimalDFTSize(int32 size);
	/**
	返回快速傅里叶的要求尺寸
	*/
	extern Size getOptimalDFTSize(Size size);
	/**
	扩展图像至快速傅里叶的要求尺寸
	*/
	extern void copyBorderDFTSize(IMat src, OutputArray dst);
	/**
	归一化
	*/
	extern void normalize(IMat src, OutputArray dst, Val alpha = 1, Val beta = 0, NormType norm_type = NORM_L2);
	/**
	生成映射矩阵
	*/
	extern OMat getPerspectiveTransform(const Point2f* src, const Point2f* dst);
	/**
	生成映射矩阵
	*/
	extern void getPerspectiveTransform(IMat src, IMat dst, OutputArray transform);
	/**
	排序
	*/
	extern void Sort(InputArray src, OutputArray dst, ORDER flag = MIN_TO_MAX, RANK r = ROW);
	/**
	排序
	*/
	extern void Sort(InputArray src, OutputArray dst, bool(*comp)(const CvMat &a, const CvMat &b), RANK r = ROW);
	/**
	排序
	*/
	extern void Sort(InputArray src, OutputArray dst, bool(*comp)(InputArray a, InputArray b), RANK r = ROW);
	/**
	@brief 返回向量叉积
	*/
	extern mat_t Cross(IMat p0, IMat p1);
	/**
	@brief 返回三点是否顺序是顺时针
	*/
	extern bool Clockwise(IMat p0, IMat p1, IMat p2);
	/**
	@brief 返回拟合结果
	最小二乘法
	@param x 自变量
	@param y 因变量
	*/
	extern void ConvexHull(IMat in, OutputArray convexhull);
	/**
	@brief 返回拟合结果
	最小二乘法
	@param x 自变量
	@param y 因变量
	*/
	extern void LeastSquare(IMat x, IMat y, OutputArray out, Mat *r = nullptr);
	/**
	@brief 返回a
	线性拟合y=a(0)*x+a(1)
	y和x必须为行向量
	保证y和x的行数相同
	@param x 自变量
	@param y 因变量
	*/
	extern void regress(IMat x, IMat y, OutputArray out, Mat *r = nullptr);
	/**
	@brief 返回P
	多项式拟合y=P(1)*x^n + P(2)*x^(n-1) +...+ P(n)*x + P(n+1)
	y和x必须为行向量
	保证y和x的行数相同
	@param x 自变量
	@param y 因变量
	*/
	extern void polyfit(IMat x, IMat y, uint32 n, OutputArray out, Mat *r = nullptr);
	/**
	拟合椭圆
	@param x
	@param y
	*/
	extern void fitEllipse(IMat x, IMat y, OutputArray circle, Mat *r = nullptr);
	/**
	拟合圆
	p必须为行向量
	@param p 点集
	*/
	extern void fitCircle(IMat p, OutputArray circle, Mat *r = nullptr);
	/**
	拟合圆
	@param x
	@param y
	*/
	extern void fitCircle(IMat x, IMat y, OutputArray circle, Mat *r = nullptr);
	/**
	拟合球
	@param x
	@param y
	*/
	extern void fitSphere(IMat x, IMat y, IMat z, OutputArray circle, Mat *r = nullptr);
	/**
	@brief 返回拟合结果
	非线性最小二乘法
	y和x必须为行向量
	保证y和x的行数相同
	@param x		自变量
	@param y		因变量
	@param a0		初始参数
	@param f		函数指针 f(a, x) = y
	@param stride		更新步长
	@param error	误差(小于误差结束更新)
	*/
	extern void NonLinearLeastSqures(IMat x, IMat y, IMat a0, OutputArray out, F f, Mat *r = nullptr, Val stride = 1e-2, Val error = 1e-6);
	/**
	@brief 返回梯度
	@param y	因变量
	@param x	自变量(缺省差值为1)
	*/
	extern void gradient(IMat y, OutputArray grad, IMat x = Mat());
	/**
	@brief 返回数值梯度
	@param f		函数指针 f(x) = y
	@param x		自变量
	@param epsilon	差值
	*/
	extern mat_t NumericGradient(NF f, Val x, Val epsilon = 1e-3);
	/**
	@brief 返回数值梯度
	@param f		函数指针 f(x) = y
	@param x		自变量
	@param epsilon	差值
	*/
	extern void NumericGradient(IMat x, Fun f, OutputArray grad, Val epsilon = 1e-3);
	/**
	@brief 返回数值梯度
	@param f		函数指针 f(a, x) = y
	@param a		自变量
	@param x		输入
	@param epsilon	差值
	*/
	extern void NumericGradient(IMat a, IMat x, F f, OutputArray grad, Val epsilon = 1e-3);
	/**
	@brief 返回积分值
	使用欧拉法求数值积分
	@param f		函数指针 f(x) = y
	@param low		积分下限
	@param high		积分上限
	@param epsilon	采样间隔
	*/
	extern mat_t EulerInt(NF f, Val low, Val high, Val epsilon = 1e-3);
	/**
	@brief 返回积分值
	使用梯形法求数值积分
	@param f		函数指针 f(x) = y
	@param low		积分下限
	@param high		积分上限
	@param epsilon	采样间隔
	*/
	extern mat_t TrapezoidInt(NF f, Val low, Val high, Val epsilon = 1e-3);
	/**
	@brief 返回积分值
	使用四阶龙格-库塔法求数值积分
	@param f		函数指针 f(x) = y
	@param low		积分下限
	@param high		积分上限
	@param epsilon	采样间隔
	*/
	extern mat_t RungeKuttaInt(NF f, Val low, Val high, Val epsilon = 1e-3);
	/**
	@brief 返回直线
	两点确定直线
	@param p1		点1
	@param p2		点2
	*/
	extern Vec2m SolveLinear(const Point2m & p1, const Point2m & p2);
	/**
	@brief 返回交点
	两条直线求交点
	@param a1	直线1斜率
	@param b1	直线1偏置
	@param a2	直线2斜率
	@param b2	直线2偏置
	*/
	extern Point2m LinearIntersection(Val a1, Val b1, Val a2, Val b2);
	/**
	@brief 返回交点
	两条直线求交点
	@param line1	直线1
	@param line2	直线2
	*/
	extern Point2m LinearIntersection(const Vec2m & line1, const Vec2m & line2);
	/**
	@brief 返回y
	多项式拟合y=P(1)*x^n + P(2)*x^(n-1) +...+ P(n)*x + P(n+1)
	x必须为行向量
	@param a 参数
	@param x 自变量
	*/
	extern void polynomial(IMat a, IMat x, OutputArray y);
	/**
	@brief 返回修改维度的矩阵
	不允许改变矩阵长度
	@param src	输入
	@param size 矩阵大小
	*/
	extern void Reshape(IMat src, Size3 size, OutputArray dst);
	/**
	@brief 返回矩阵
	按通道求和
	@param src	输入
	*/
	extern void SumChannel(IMat src, OutputArray dst);
	/**
	@brief 返回旋转矩阵
	@param src	输入
	@param dice 旋转角度
	*/
	extern void rotate(IMat src, RotateAngle dice, OutputArray dst);
	/**
	按比例缩放矩阵
	@param src		输入
	@param dst		输出
	@param xRatio	x缩放比例
	@param yRatio	y缩放比例
	@param mothed	缩放方法
	*/
	extern void resize(IMat src, OutputArray dst, Val xRatio, Val yRatio, ReductionMothed mothed);
	/**
	按大小缩放矩阵
	@param src		输入
	@param dst		输出
	@param newSize	新的矩阵大小
	@param mothed	缩放方法
	*/
	extern void resize(IMat src, OutputArray dst, Size newSize, ReductionMothed mothed);
	/**
	@brief 返回随机数
	符合高斯分布的随机数
	@param mu		期望值
	@param sigma	标准差
	*/
	extern mat_t generateGaussianNoise(Val mu = 0, Val sigma = 1);
	/**
	@brief 返回聚类结果
	K均值聚类
	@param P			输入
	@param k			对点集的分类结果
	@param K			聚类个数
	@param iteration	迭代次数
	@param error		误差(小于误差结束迭代)
	*/
	extern void kmeans(IMat P, InputOutputArray k, OutputArray classifier, int32 K, const uint32 iteration, const Val error = 1e-7);
	/**
	@brief 返回求解状态
	求解非齐次线性方程组
	齐次线性方程组使用addzeros手动添加0
	@param src		输入线性方程组
	@param dst		基础解系
	@param simplest	最简行矩阵
	@param mark		解的状态(自由解为0,特解为1,无解为nullptr)
	*/
	extern EQUATION SolveLinearEquation(IMat src, OutputArray dst, Mat *simplest = nullptr, Mat *mark = nullptr);

	namespace nn
	{
		typedef OMat(*Act)(IMat);
		typedef OMat(*LF)(IMat, IMat);

		/**
		@brief softmax函数
		Si = exp(y - Max(y)) / sum(exp(y - Max(y)))
		*/
		extern OMat Softmax(IMat x);
		/**
		@brief L1函数
		E = |y - y0|
		*/
		extern OMat L1(IMat y, IMat y0);
		/**
		@brief L2函数
		E = (y - y0)^2
		*/
		extern OMat L2(IMat y, IMat y0);
		/**
		@brief quadratic函数
		E = 1/2 * (y - y0)^2
		*/
		extern OMat Quadratic(IMat y, IMat y0);
		/**
		@brief crossentropy函数
		E = -(y * log(y0))
		*/
		extern OMat CrossEntropy(IMat y, IMat y0);
		/**
		@brief softmax + crossentropy函数
		E = -(y * log(softmax(y0)))
		*/
		extern OMat SoftmaxCrossEntropy(IMat y, IMat y0);
		/**
		@brief sigmoid函数
		y = 1/(1 + exp(-x))
		*/
		extern OMat Sigmoid(IMat x);
		/**
		@brief tanh函数
		y = (exp(x) - exp(-x)) / (exp(x) + exp(-x))
		*/
		extern OMat Tanh(IMat x);
		/**
		@brief relu函数
		y = {x if x > 0; 0 if x < 0}
		*/
		extern OMat ReLU(IMat x);
		/**
		@brief elu函数
		y = {x if x > 0; a*(exp(x) - 1) if x < 0}
		*/
		extern OMat ELU(IMat x);
		/**
		@brief selu函数
		y = scale*Elu(x)
		*/
		extern OMat SeLU(IMat x);
		/**
		@brief leaky relu函数
		y = {x if x > 0; a*x if x < 0}
		*/
		extern OMat LReLU(IMat x);
		/**
		@brief softmax导数
		y = y*(1 - y),
		*/
		extern OMat D_Softmax(IMat y);
		/**
		@brief L2导数
		y = 2 * (y0 - y),
		*/
		extern OMat D_L2(IMat y, IMat y0);
		/**
		@brief quadratic导数
		y = y0 - y
		*/
		extern OMat D_Quadratic(IMat y, IMat y0);
		/**
		@brief crossentropy导数
		y = y0 - y
		*/
		extern OMat D_CrossEntropy(IMat y, IMat y0);
		/**
		@brief softmax + crossentropy导函数
		y = y0 - y
		*/
		extern OMat D_SoftmaxCrossEntropy(IMat y, IMat y0);
		/**
		@brief sigmoid导数
		y = sigmoid(x) * (1 - sigmoid(x)),
		*/
		extern OMat D_Sigmoid(IMat x);
		/**
		@brief tanh导数
		y = 4 * d_sigmoid(x),
		*/
		extern OMat D_Tanh(IMat x);
		/**
		@brief relu导数
		y = {1 if x > 0; 0 if x < 0}
		*/
		extern OMat D_ReLU(IMat x);
		/**
		@brief elu导数
		y = {1 if x > 0; a*exp(x) if x < 0}
		*/
		extern OMat D_ELU(IMat x);
		/**
		@brief selu导数
		y = scale*d_Elu(x)
		*/
		extern OMat D_SELU(IMat x);
		/**
		@brief leaky relu导数
		y = {1 if x > 0; a if x < 0}
		*/
		extern OMat D_LReLU(IMat x);
	};

	class Timer
	{
	public:
		Timer();
		~Timer();
		void Start();
		mat_t End();
	protected:
		void* start;
		void* end;
		void* fc;
	};
	class tools
	{
	public:
		/**
		暂停程序
		*/
		static void pause();
		static int32 console(const std::string &str);
		static mat_t saveDiv(mat_t div, mat_t v);
		/**
		命令行输出
		*/
		template<typename _Tp>
		static void output(const _Tp &t) {
			std::cout << t << std::endl;
		}
		static void binaryPrint(int32 value, int32 space = 0);
		static void Wait(uint32 ms);
		static void Frequency();
		static void StartCounter();
		static mat_t EndCounter();
		static std::vector<std::string> strsplit(const std::string &str, int8 ch);
		static void getFiles(std::string path, std::vector<std::string>& files);
		template<class _Tp> static std::vector<_Tp> str2data(const std::vector<std::string> &str);
		static void readcsv(std::string filename, IOMat dst);
		static void readcsv(std::string filename, std::vector<std::vector<std::string>> &csv);
		template<typename _Tp> static const CvMat_<_Tp> readcsv(std::string filename);
		template<typename _Tp> static const CvMat StdVecToCvMat(const std::vector<_Tp> &vec);
		/**
		@brief 返回将向量转换成1*point.size()*1的矩阵
		@param point 向量
		*/
		template<typename _Tp> static const Mat Vec2Mat(const std::vector<_Tp> &point);
		/**
		@brief 返回将向量转换成point.size()*point[0].size()*1的矩阵
		@param points 向量
		*/
		template<typename _Tp> static const Mat Vec2Mat(const std::vector<std::vector<_Tp>> &points);
		template<class _Tp> static std::vector<Point2_<_Tp>> Mat2Point2D(IMat m);
		template<class _Tp> static std::vector<Point3_<_Tp>> Mat2Point3D(IMat m);
		template<typename _Tp> static const Mat Point2D2Mat(const std::vector<Point2_<_Tp>> & ps);
		template<typename _Tp> static const Mat Point3D2Mat(const std::vector<Point3_<_Tp>> & ps);
		/**
		@brief 返回将矩阵转换成一维向量
		@param src 矩阵
		*/
		template<class _Tp> static std::vector<_Tp> Mat2Vec(IMat src);
		/**
		@brief 返回将矩阵转换成向量
		@param src 矩阵
		*/
		template<class _Tp> static std::vector<std::vector<_Tp>> Mat2Vecs(IMat src);
		static void check(int32 w, int32 h = 1, int32 depth = 1);
		static std::string createfile(std::string filename);
		static std::string createtype(std::string filename);
		static std::string show_path();
		static std::string Enum2String(PrintType type);
		static std::string Enum2String(BorderTypes type);
		static std::string Enum2String(MatErrorInfo type);
		static std::string Enum2String(EQUATION type);
		static std::string Enum2String(ORDER type);
		static std::string Enum2String(RANK type);
		static std::string Enum2String(Dire type);
		static std::string Enum2String(ReductionMothed type);
		static std::string Enum2String(RotateAngle type);
		//static std::string Enum2String(BSpline::BSplineType type);
	};

	template<typename _Tp> std::vector<_Tp> range(_Tp low, _Tp top, Val gap) {
		Mat mat = mRange(low, top, gap);
		std::vector<_Tp> vec(mat.len());
		FOR_RANGE(i, 0, mat.len())vec[i] = _Tp(mat(i));
		return vec;
	}

	template<typename _Tp> inline std::vector<_Tp> lzh::tools::str2data(const std::vector<std::string> &str)
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX_(str);
#endif //MAT_DEBUG
		std::vector<_Tp> v;
		for (const std::string &s : str)
			switch (MAT_TYPE(_Tp))
			{
			case lzh::TP_8U:
				v.push_back((_Tp)std::stoi(s));
				break;
			case lzh::TP_32S:
				v.push_back((_Tp)std::stoi(s));
				break;
			case lzh::TP_32F:
				v.push_back((_Tp)std::stof(s));
				break;
			case lzh::TP_64F:
				v.push_back((_Tp)std::stod(s));
				break;
			case lzh::TP_64D:
				v.push_back((_Tp)std::stold(s));
				break;
			default:
				break;
			}
		return v;
	}
	template<typename _Tp> inline const CvMat_<_Tp> tools::readcsv(std::string filename)
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX_(filename);
#endif //MAT_DEBUG
		std::ifstream in(filename);
		CHECK_EXCEPTION(if (in.is_open()), THROW_INFO(ERR_INFO_FILE));
		std::vector<std::vector<_Tp>> vec;
		std::string str;
		while (std::getline(in, str))
		{
			vec.push_back(str2data<_Tp>(strsplit(str, ',')));
		}
		in.close();
		if (vec.empty())return;
		CvMat cvmat = _InputArray(vec).getCvMat();
		CvMat_<_Tp> cvmat_(cvmat.size3());
		memcpy(cvmat_, cvmat, cvmat.memsize());
		return cvmat_;
	}
	template<typename _Tp> inline const CvMat tools::StdVecToCvMat(const std::vector<_Tp>& vec)
	{
		return _InputArray(vec).getCvMat();
	}
	template<typename _Tp> inline const Mat lzh::tools::Vec2Mat(const std::vector<_Tp> &p)
	{
		if (p.empty())return Mat();
		Mat m(int32(p.size()));
		_Tp *data = &p[0];
		memcpy(m, data, m.memsize());
		return m;
	}
	template<typename _Tp> inline const Mat lzh::tools::Vec2Mat(const std::vector<std::vector<_Tp>> &ps)
	{
		if (ps.empty())return Mat();
		int32 size = 0;
		for (int32 i = 0; i < int32(ps.size() - 1); ++i) {
			for (int32 j = i + 1; j < int32(ps.size()); ++j) {
				if (ps[i].size() != ps[j].size())
					THROW_INFO(ERR_INFO_SIZE);
			}
		}
		int32 hei = int32(ps.size());
		int32 wid = int32(ps[0].size());
		Mat m(wid, hei);
		mat_t *ptr = m;
		for (int32 i = 0; i < hei; ++i) {
			memcpy(ptr, &ps[i][0], sizeof(_Tp)*ps[i].size());
			ptr += wid;
		}
		return m;
	}
	template<class _Tp> inline std::vector<_Tp> lzh::tools::Mat2Vec(IMat m)
	{
		if (m.empty())return std::vector<_Tp>();
		std::vector<_Tp> p(m.size());
		memcpy(&p[0], m, m.memsize());
		return p;
	}
	template<class _Tp> inline std::vector<std::vector<_Tp>> lzh::tools::Mat2Vecs(IMat m)
	{
		if (m.empty())return std::vector<std::vector<_Tp>>();
		const _Tp *ptr = m;
		std::vector<std::vector<_Tp>> ps(m.rows());
		for (int32 h = 0; h != m.rows(); ++h) {
			ps[h].resize(m.cols());
			memcpy(&ps[h][0], ptr, sizeof(_Tp)*m.cols());
		}
		return ps;
	}
	template<class _Tp> inline std::vector<Point2_<_Tp>> tools::Mat2Point2D(IMat m)
	{
		std::vector<Point2_<_Tp>> vec;
		int32 l1, l2, flag = -1;
		if (m.rows() == 2) {
			l1 = m.cols();
			l2 = m.channels();
			flag = 0;
		}
		else if (m.cols() == 2) {
			l1 = m.rows();
			l2 = m.channels();
			flag = 1;
		}
		else if (m.channels() == 2) {
			l1 = m.rows();
			l2 = m.cols();
			flag = 2;
		}
		else
			return vec;
		vec.resize(l1*l2);
		for (int32 j = 0; j < l1; j++)
			for (int32 k = 0; k < l2; k++)
				switch (flag)
				{
				case 0:vec[j*l2 + k] = Point2_<_Tp>((_Tp)m(0, j, k), (_Tp)m(1, j, k)); break;
				case 1:vec[j*l2 + k] = Point2_<_Tp>((_Tp)m(j, 0, k), (_Tp)m(j, 1, k)); break;
				case 2:vec[j*l2 + k] = Point2_<_Tp>((_Tp)m(j, k, 0), (_Tp)m(j, k, 1)); break;
				default:return vec;
				}
		return vec;
	}
	template<class _Tp> inline std::vector<Point3_<_Tp>> tools::Mat2Point3D(IMat m)
	{
		std::vector<Point3_<_Tp>> vec;
		int32 l1, l2, flag = -1;
		if (m.rows() == 3) {
			l1 = m.cols();
			l2 = m.channels();
			flag = 0;
		}
		else if (m.cols() == 3) {
			l1 = m.rows();
			l2 = m.channels();
			flag = 1;
		}
		else if (m.channels() == 3) {
			l1 = m.rows();
			l2 = m.cols();
			flag = 2;
		}
		else
			return vec;
		vec.resize(l1*l2);
		for (int32 j = 0; j < l1; j++)
			for (int32 k = 0; k < l2; k++)
				switch (flag)
				{
				case 0:vec[j*l2 + k] = Point3_<_Tp>((_Tp)m(0, j, k), (_Tp)m(1, j, k), (_Tp)m(2, j, k)); break;
				case 1:vec[j*l2 + k] = Point3_<_Tp>((_Tp)m(j, 0, k), (_Tp)m(j, 1, k), (_Tp)m(j, 2, k)); break;
				case 2:vec[j*l2 + k] = Point3_<_Tp>((_Tp)m(j, k, 0), (_Tp)m(j, k, 1), (_Tp)m(j, k, 2)); break;
				default:return vec;
				}
		return vec;
	}
	template<typename _Tp> inline const Mat tools::Point3D2Mat(const std::vector<Point3_<_Tp>> & ps)
	{
		if (ps.empty())return Mat();
		Mat m((int32)ps.size(), 3);
		int32 idx = 0;
		for (const Point3_<_Tp> &p : ps)
		{
			Mat(Size(3), p.x, p.y, p.z).copyTo(m.col(idx++));
		}
		return m;
	}
	template<typename _Tp> inline const Mat tools::Point2D2Mat(const std::vector<Point2_<_Tp>> & ps)
	{
		if (ps.empty())return Mat();
		Mat m((int32)ps.size(), 2);
		int32 idx = 0;
		for (const Point2_<_Tp> &p : ps)
		{
			Mat(Size(2), _T(p.x), _T(p.y)).copyTo(m.col(idx++));
		}
		return m;
	}
}

#endif //__MATAPI_H__
