#pragma once
#ifndef __MATTYPE_H__
#define __MATTYPE_H__

#include <vector>

namespace lzh
{
#ifdef LMAT_32F
	typedef float mat_t;
#elif defined LMAT_8U
	typedef uchar mat_t;
#elif defined LMAT_8S
	typedef char mat_t;
#elif defined LMAT_32S
	typedef int  mat_t;
#elif defined LMAT_64F
	typedef double mat_t;
#elif defined LMAT_64D
	typedef long double mat_t;
#else
	typedef float mat_t;
#endif

#define MAT_TYPE(t)		(lzh::DataType<t>::type)
#define MAT_T			(lzh::DataType<lzh::mat_t>::type)
#define MAT_8S			TP_8S
#define MAT_8U			TP_8U
#define MAT_16S			TP_16S
#define MAT_16U			TP_16U
#define MAT_32S			TP_32S
#define MAT_32U			TP_32U
#define MAT_64S			TP_64S
#define MAT_64U			TP_64U
#define MAT_32F			TP_32F
#define MAT_64F			TP_64F
#define MAT_64D			TP_64D
#define _T(v)			(lzh::mat_t(v))
#define _I(v)			(int32(v))

#define PI					3.1415926535897932384626433832795
#define PI_					_T(PI)
#define D_PI				6.283185307179586476925286766559
#define D_PI_				_T(D_PI)
	//LeakyReLU的超参
#define LReLU_alpha			0.2
#define LReLU_alpha_		_T(LReLU_alpha)
//ELU的超参
#define ELU_alpha			1.6732632423543772848170429916717
#define ELU_alpha_			_T(ELU_alpha)
//SeLU的超参
#define SELU_scale			1.0507009873554804934193349852946
#define SELU_scale_			_T(SELU_scale)

#define shrink_factor		1.247330950103979
#define shrink_factor_		_T(shrink_factor)

#define ang2rad				0.01745329251994329576923690768489
#define rad2ang				57.295779513082320876798154814105
#define ang2rad_			_T(ang2rad)
#define rad2ang_			_T(rad2ang)

#define gauss_factor_1D		2.506628274631000502415765284811
#define gauss_factor_2D		6.283185307179586476925286766559
#define gauss_factor_1D_	_T(gauss_factor_1D)
#define gauss_factor_2D_	_T(gauss_factor_2D)

	typedef char					int8;
	typedef unsigned char			uint8;
	typedef short					int16;
	typedef unsigned short			uint16;
	typedef int						int32;
	typedef unsigned int			uint32;
	typedef long long				int64;
	typedef unsigned long long		uint64;
	typedef float					float32;
	typedef double					float64;
	typedef long double				float64_;

	static const uint32 M_SIZE = sizeof(mat_t);

	enum PrintType {
		MAT_FIXED = 0,
		MAT_SCIENTIFIC = 1
	};
	enum BorderTypes {
		BORDER_CONSTANT = 0,	//!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`
		BORDER_REPLICATE = 1,	//!< `aaaaaa|abcdefgh|hhhhhhh`
		BORDER_REFLECT = 2,		//!< `fedcba|abcdefgh|hgfedcb`
		BORDER_WRAP = 3,		//!< `cdefgh|abcdefgh|abcdefg`
		BORDER_REFLECT_101 = 4, //!< `gfedcb|abcdefgh|gfedcba`
		//BORDER_TRANSPARENT = 5, //!< `uvwxyz|abcdefgh|ijklmno`
		//BORDER_ISOLATED = 16,	//!< do not look outside of ROI
		BORDER_DEFAULT = BORDER_REFLECT_101
	};
	enum MatErrorInfo {
		ERR_INFO_EMPTY = 0,
		ERR_INFO_SQUARE = 1,
		ERR_INFO_ADJ = 2,
		ERR_INFO_INV = 3,
		ERR_INFO_POW = 4,
		ERR_INFO_IND = 5,
		ERR_INFO_CON = 6,
		ERR_INFO_EIGEN = 7,
		ERR_INFO_LEN = 8,
		ERR_INFO_MEMOUT = 9,
		ERR_INFO_UNLESS = 10,
		ERR_INFO_SIZE = 11,
		ERR_INFO_MULT = 12,
		ERR_INFO_NORM = 13,
		ERR_INFO_VALUE = 14,
		ERR_INFO_PINV = 15,
		ERR_INFO_DET = 16,
		ERR_INFO_DIM = 17,
		ERR_INFO_PTR = 18,
		ERR_INFO_NOT2D = 19,
		ERR_INFO_FILE = 20,
		ERR_INFO_TYPE = 21,
		ERR_INFO_DIV = 22,
		ERR_INFO_FFT = 23,
		ERR_INFO_CHANNEL = 24
	};
	static const int8 *errinfo[] = {
		"error 0: 矩阵为空!\0",
		"error 1: 矩阵不是方阵!\0",
		"error 2: 矩阵不是方阵，不能设置伴随矩阵!\0",
		"error 3: 矩阵不是方阵，不能设置逆矩阵!\0",
		"error 4: 矩阵不是方阵，不能进行次幂运算!\0",
		"error 5: 矩阵不是方阵，不能设置为单位矩阵!\0",
		"error 6: 矩阵不收敛!\0",
		"error 7: 矩阵没有实数特征值!\0",
		"error 8: 矩阵维度为0!\0",
		"error 9: 矩阵索引出界!\0",
		"error 10: 矩阵索引无效!\0",
		"error 11: 两个矩阵维度不一致!\0",
		"error 12: 两个矩阵维度不满足乘法条件!\0",
		"error 13: 矩阵维度不为1，不是向量!\0",
		"error 14: 参数违法!\0",
		"error 15: 计算逆矩阵失败!\0",
		"error 16: 行列式为0!\0",
		"error 17: 不支持三维操作!\0",
		"error 18: 指针为空!\0",
		"error 19: 输入矩阵维度必须为2D!\0",
		"error 20: 没有找到文件!\0",
		"error 21: 类型不符!\0",
		"error 22: 除数为0!\0",
		"error 23: 快速傅里叶变换矩阵尺寸必须是2的次幂!\0",
		"error 24: 矩阵通道数不符!\0"
	};
	/**
	SPECIAL_SOLUTION	方程有特解
	GENERAL_SOLUTION	方程有通解
	NO_SOLUTION			方程无解
	*/
	enum EQUATION
	{
		SPECIAL_SOLUTION = 0,	//方程有特解
		GENERAL_SOLUTION = 1,	//方程有通解
		NO_SOLUTION = -1		//方程无解
	};
	/**
	MIN_TO_MAX	从小到大
	MAX_TO_MIN	从大到小
	*/
	enum ORDER
	{
		MIN_TO_MAX = 0,
		MAX_TO_MIN = 1,
		DISTANCE = 3
	};
	/**
	ROW		行
	COL		列
	CHANNEL	通道
	*/
	enum RANK {
		ROW = 0,
		COL = 1,
		CHANNEL = 2
	};
	enum Dire {
		LEFT = 0,
		RIGHT = 1,
	};
	enum Axis {
		X = 0,
		Y = 1,
		Z = 2,
	};
	enum
	{
		NO_ANGLE = 0,

		ANGLE0_OFFSET = 0,
		ANGLE45_OFFSET = 1,
		ANGLE90_OFFSET = 2,
		ANGLE135_OFFSET = 3,
		ANGLE180_OFFSET = 4,
		ANGLE225_OFFSET = 5,
		ANGLE270_OFFSET = 6,
		ANGLE315_OFFSET = 7,

		ANGLE0 = 1 << _I(ANGLE0_OFFSET),
		ANGLE45 = 1 << _I(ANGLE45_OFFSET),
		ANGLE90 = 1 << _I(ANGLE90_OFFSET),
		ANGLE135 = 1 << _I(ANGLE135_OFFSET),
		ANGLE180 = 1 << _I(ANGLE180_OFFSET),
		ANGLE225 = 1 << _I(ANGLE225_OFFSET),
		ANGLE270 = 1 << _I(ANGLE270_OFFSET),
		ANGLE315 = 1 << _I(ANGLE315_OFFSET),
		ANGLEALL = 0xFF
	};
	enum LaplaceType
	{
		Four_Dire = 4,
		Eight_Dire = 8
	};
	enum SharpenScale
	{
		SHARPEN_LEVEL1 = 1,
		SHARPEN_LEVEL2 = 2,
	};
	/**
	EqualIntervalSampling 等间隔采样
	LocalMean 局部均值
	*/
	enum ReductionMothed
	{
		EqualIntervalSampling = 0,
		LocalMean = 1,
		INTER_NEARLY = 2,
		INTER_LINEAR = 3,
		INTER_AREA = 4,
		INTER_CUBIC = 5,
	};
	/**
	旋转方向顺时针
	ROTATE_90_ANGLE 90度
	ROTATE_180_ANGLE 180度
	ROTATE_270_ANGLE 270度
	*/
	enum RotateAngle
	{
		ROTATE_90_ANGLE = 0,
		ROTATE_180_ANGLE,
		ROTATE_270_ANGLE
	};
	enum CompareType
	{
		LESS = -2,
		LESS_EQUAL = -1,
		EQUAL = 0,
		GREATER_EQUAL = 1,
		GREATER = 2
	};
	/**
	二值化方法
	*/
	enum ThreshMethod
	{
		THRESH_BINARY = 0,
		THRESH_BINARY_INV = 1,
		THRESH_TRUNC = 2,
		THRESH_TOZERO = 3,
		THRESH_TOZERO_INV = 4,
		THRESH_OTSU = 5
	};
	enum NormType
	{
		NORM_L1 = 0,
		NORM_L2 = 1,
		NORM_INF = 2,
		NORM_MINMAX = 3,
		NORM_SUM = 4,
		NORM_IMAGE = 5,
		NORM_ZSCORE = 6
	};
	enum MorphShape
	{
		MORPH_RECT = 0,
		MORPH_CROSS = 1,
		MORPH_ELLIPSE = 2
	};
	enum MorphType
	{
		MORPH_OPEN = 0,//开运算
		MORPH_CLOSE = 1,//闭运算
		MORPH_GRADIENT = 2,//形态学梯度
		MORPH_TOPHAT = 3,//顶帽
		MORPH_BLACKHAT = 4,//黑帽
		MORPH_ERODE = 5,//腐蚀
		MORPH_DILATE = 6	//膨胀
	};
	enum ConvolutionType {
		/* Return the full convolution, including border */
		CONVOLUTION_FULL,

		/* Return only the part that corresponds to the original image */
		CONVOLUTION_SAME,

		/* Return only the submatrix containing elements that were not influenced by the border */
		CONVOLUTION_VALID
	};
	enum MosaicMethod {
		MosaicRandom = 0,
		MosaicAngle0,
		MosaicAngle45,
		MosaicAngle90,
		MosaicAngle135,
		MosaicAngle180,
		MosaicAngle225,
		MosaicAngle270,
		MosaicAngle315,
	};
	enum ColorGamut
	{
		ColorGamutCustom = 0,
		ColorGamutGray = 1,
		ColorGamutRGB = 2,
		ColorGamutBGR = 3,
		ColorGamutRGBA = 4,
		ColorGamutBGRA = 5,
		ColorGamutHSV = 6,
		ColorGamutXYZ = 7,
		ColorGamutLab = 8,
	};

	enum
	{
		SHIFT = 8,
		KIND_SHIFT = (1 << int32(SHIFT)) - 1,

		NONE = 0,
		TP_8S = 1,
		TP_8U = 2,
		TP_16S = 3,
		TP_16U = 4,
		TP_32S = 5,
		TP_32U = 6,
		TP_64S = 7,
		TP_64U = 8,
		TP_32F = 9,
		TP_64F = 10,
		TP_64D = 11,
	};

	extern uint32 calmemsize(int32 type);
	static const uint32 TypeMemSize[] = { 0,1,1,2,2,4,4,8,8,4,8,8 };
	static const int8 * TypeString[] = {
		"unknow",
		"int8",		"uint8",
		"int16",	"uint16",
		"int32",	"uint32",
		"int64",	"uint64",
		"float32",	"float64", "float64"
	};

	typedef std::vector<lzh::int8>									vec_8s;
	typedef std::vector<lzh::uint8>									vec_8b;
	typedef std::vector<lzh::int16>									vec_16s;
	typedef std::vector<lzh::uint16>								vec_16u;
	typedef std::vector<lzh::int32>									vec_32s;
	typedef std::vector<lzh::uint32>								vec_32u;
	typedef std::vector<lzh::float32>								vec_32f;
	typedef std::vector<lzh::int64>									vec_64s;
	typedef std::vector<lzh::uint64>								vec_64u;
	typedef std::vector<lzh::float64>								vec_64f;
	typedef std::vector<lzh::float64_>								vec_64d;
	typedef std::vector<lzh::mat_t>									vec_m;
	typedef std::vector<std::vector<lzh::int8>>						vecs_8s;
	typedef std::vector<std::vector<lzh::uint8>>					vecs_8b;
	typedef std::vector<std::vector<lzh::int16>>					vecs_16s;
	typedef std::vector<std::vector<lzh::uint16>>					vecs_16u;
	typedef std::vector<std::vector<lzh::int32>>					vecs_32s;
	typedef std::vector<std::vector<lzh::uint32>>					vecs_32u;
	typedef std::vector<std::vector<lzh::float32>>					vecs_32f;
	typedef std::vector<std::vector<lzh::int64>>					vecs_64s;
	typedef std::vector<std::vector<lzh::uint64>>					vecs_64u;
	typedef std::vector<std::vector<lzh::float64>>					vecs_64f;
	typedef std::vector<std::vector<lzh::float64_>>					vecs_64d;
	typedef std::vector<std::vector<lzh::mat_t>>					vecs_m;

	typedef size_t varray;
}
#endif //__MATTYPE_H__