#pragma once
#ifndef __CVMAT_H__
#define __CVMAT_H__

#include "Variable.h"

namespace lzh
{
	/**
	内存管理类
	*/
	class PtrMat
	{
	public:
		PtrMat();
		PtrMat(int32 size, int32 type);
		PtrMat(const PtrMat &m);
		PtrMat(int32 n, const void *p, int32 type);
		~PtrMat();
		void create(uint32 len, int32 type);
		void addref();
		void release();
		template<typename _Tp> _Tp* begin();
		template<typename _Tp> const _Tp* begin()const;
		template<typename _Tp> _Tp* end();
		template<typename _Tp> const _Tp* end()const;
		template<typename _Tp> _Tp& at(int32 i);
		template<typename _Tp> const _Tp& at(int32 i)const;
		bool operator == (void *m) const;
		bool operator != (void *m) const;
		template<typename _Tp> _Tp& operator [] (int32 i) const;
		template<typename _Tp> operator _Tp* ();
		template<typename _Tp> operator const _Tp* ()const;
		uint8* operator + (int32 i)const;
		uint8* operator - (int32 i)const;
		template<typename _Tp> _Tp get(int32 i) const;
		bool empty()const;
		int32 depth()const;
		int32 getTp()const;
		int32 size()const;
		int32 &T();
		int32 &L();
		uint8* &P();
		uint8* obj()const;
		void* index(int32 i)const;
		void* add(int32 i)const;
		void* reduce(int32 i)const;
		void* offset(int32 i)const;
		int32* memCount()const;
		void set(const PtrMat &ptr);
		void set(const void* p, int32 length, int32 data_type);
		void set(const void* p, int32 length, int32 data_type, const int32 *count);
		void set(const Mat &mat);
		PtrMat & operator=(const PtrMat & m);
		uint8* operator ()();
		const uint8* operator ()()const;
	protected:
		int32 len;
		uint8 *data;
		int32 type;
		void init(const void* p, int32 type, int32 len, const int32 *count);
	private:
		int32 *refcount = 0;
	};

	class _InputArray; template<class _Tp> class MatCommaInitializer_;
	class CvMat
	{
	public:
		explicit CvMat();
		/**
		生成w_的向量
		@param w		向量长度
		*/
		CvMat(int32 w, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成w_*h_的矩阵
		@param w		矩阵列数
		@param h		矩阵行数
		*/
		CvMat(int32 w, int32 h, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成h_*w_*depth的矩阵
		@param w		矩阵列数
		@param h		矩阵行数
		@param c		矩阵通道数
		*/
		CvMat(int32 w, int32 h, int32 c, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成size*1的矩阵
		@param size	矩阵尺寸
		*/
		CvMat(Size size, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成size*c的矩阵
		@param size	矩阵尺寸
		*/
		CvMat(Size size, int32 c, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成size的矩阵
		@param size	矩阵尺寸
		*/
		CvMat(Size3 size, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成指定色域, 大小为size的矩阵
		@param colorGamut	指定色域
		*/
		CvMat(ColorGamut colorGamut, Size size, int32 flags);
		/**
		拷贝函数
		*/
		CvMat(const PtrMat &src, Size3 sz, bool copyData = false);
		/**
		深拷贝函数
		*/
		CvMat(const void * p, Size3 sz, int32 flags);
		/**
		拷贝函数
		@param src		拷贝对象
		*/
		CvMat(const CvMat &src);
		/**
		引用对象
		@param inputarray	接口输入
		*/
		CvMat(const _InputArray & inputarray);
		/**
		将矩阵a和b合并(COL为按列合并|ROW为按行合并)
		@param a		输入矩阵1
		@param b		输入矩阵2
		@param merge	合并方式
		*/
		CvMat(const lzh::CvMat &a, const lzh::CvMat &b, RANK merge);
		/**
		构造函数
		深拷贝m
		@param m 矩阵
		*/
		template<typename _Tp> CvMat(const MatCommaInitializer_<_Tp> &m);
		/**
		生成1*w*1的向量,元素为data
		@param w		列数
		@param data		矩阵
		*/
		CvMat(int32 w, const void *data, int32 flags, bool copyData = false);
		/**
		生成h*w*1的矩阵,元素为data
		@param w		矩阵列数
		@param h		矩阵行数
		@param data		矩阵元素
		*/
		CvMat(int32 w, int32 h, const void *data, int32 flags, bool copyData = false);
		/**
		生成h*w*c的矩阵,元素为data
		@param w		矩阵列数
		@param h		矩阵行数
		@param c		矩阵通道数
		@param data		矩阵元素
		*/
		CvMat(int32 w, int32 h, int32 c, const void *data, int32 flags, bool copyData = false);
		/**
		生成size的向量,元素为data
		@param size		尺寸
		@param data		矩阵
		*/
		CvMat(Size size, const void *data, int32 flags, bool copyData = false);
		/**
		生成size的向量,元素为data
		@param size		尺寸
		@param data		矩阵
		*/
		CvMat(Size size, int32 c, const void *data, int32 flags, bool copyData = false);
		/**
		生成size的向量,元素为data
		@param size		尺寸
		@param data		矩阵
		*/
		CvMat(Size3 size, const void *data, int32 flags, bool copyData = false);
		/**
		生成h*w*c的矩阵,元素为data
		@param w		矩阵列数
		@param h		矩阵行数
		@param c		矩阵通道数
		@param step		步长
		@param data		矩阵元素
		*/
		CvMat(int32 w, int32 h, int32 c, MatStep step, const void *data, int32 flags);
		/**
		生成size的矩阵
		Mat m(Size(10), 1,2,3,4,5,6,7,8,9,10);
		@param size		矩阵大小
		@param v		第一个参数(确定类型)
		@param ...		不定参数
		*/
		template<typename _Tp> CvMat(Size3 size, int32 flags, _Tp v, ...);
		//template<class _Tp, int32 N>
		//CvMat(const Vec<_Tp, N> &vec)
		//{
		//	init();
		//	data.set(&vec.data[0], N, MAT_TYPE(_Tp));
		//}
		//template<class _Tp>
		//CvMat(const Point2_<_Tp> &p)
		//{
		//	init();
		//	data.set(&p.x, 2, MAT_TYPE(_Tp));
		//}
		//template<class _Tp>
		//CvMat(const Point3_<_Tp> &p)
		//{
		//	init();
		//	data.set(&p.x, 3, MAT_TYPE(_Tp));
		//}
		CvMat(const Mat & src, int32 flags = MAT_T);
		~CvMat();
		/**
		生成w的向量
		@param w		列数
		*/
		void create(int32 w, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成w*h的矩阵
		@param w		列数
		@param h		行数
		*/
		void create(int32 w, int32 h, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成w*h*c的张量
		@param w		列数
		@param h		行数
		@param c		通道数
		*/
		void create(int32 w, int32 h, int32 c, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成size的矩阵
		@param size		矩阵大小
		*/
		void create(Size size, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		生成size的张量
		@param size		矩阵大小
		*/
		void create(Size3 size, int32 flags, ColorGamut cg = ColorGamutCustom);
		void createColorGamut(ColorGamut colorGamut, Size sz, int32 flags);
		mat_t First()const;
		mat_t Last()const;
		template<typename _Tp> _Tp & first()const;
		template<typename _Tp> _Tp & last()const;
		template<typename _Tp> _Tp* begin();
		template<typename _Tp> const _Tp* begin()const;
		template<typename _Tp> _Tp* end();
		template<typename _Tp> const _Tp* end()const;
		int32 * memCount()const;
		PtrMat& ptr();
		const PtrMat& ptr()const;
		const Mat toMat()const;
		bool isDeepCopy() const;
		/**
		@brief 内存长度
		*/
		uint32 memsize()const;
		/**
		@brief 检查维度
		*/
		void DimCheck()const;
		/**
		@brief 返回矩阵尺寸(h_,w_,c_)
		*/
		Size3 size3()const;
		/**
		@brief 返回矩阵偏移
		*/
		int32 total()const;
		/**
		@brief 返回矩阵偏移
		*/
		int32 total_()const;
		/**
		@brief 返回维度
		*/
		int32 dims()const;
		/**
		@brief 返回步长
		*/
		MatStep step()const;
		/**
		@brief 中心
		*/
		Point center()const;
		/**
		@brief 返回类型
		*/
		int32 depth()const;
		/**
		@brief 返回类型
		*/
		int32 type()const;
		/**
		@brief 返回通道数
		*/
		int32 channels()const;
		/**
		@brief 返回行秩
		*/
		int32 rank()const;
		/**
		@brief 返回色域
		*/
		ColorGamut colorGamut()const;
		/**
		@brief 返回矩阵大小Size(h_,w_)
		*/
		Size size()const;
		int32 toidx(int32 i)const;
		int32 toidx(int32 i, int32 j)const;
		int32 toidx(int32 i, int32 j, int32 k)const;
		template<typename _Tp> void set(int32 i, _Tp v);
		template<typename _Tp> void set(int32 i0, int32 i1, _Tp v);
		template<typename _Tp> void set(int32 i0, int32 i1, int32 i2, _Tp v);
		template<typename _Tp> void set(Point p, _Tp v);
		template<typename _Tp> void set(Point3 p, _Tp v);
		template<typename _Tp, int32 N> void set(int32 i0, int32 i1, const Vec<_Tp, N> &v);
		void set(int32 i, const void * v, int32 addr_offset);
		void set(int32 i0, int32 i1, const void * v, int32 addr_offset);
		void set(int32 i0, int32 i1, int32 i2, const void * v, int32 addr_offset);
		void assign(int32 i, int32 j);
		void swap(int32 i, int32 j);
		template<typename _Tp> void add(int32 i, _Tp v);
		template<typename _Tp> void reduce(int32 i, _Tp v);
		template<typename _Tp> void mul(int32 i, _Tp v);
		template<typename _Tp> void div(int32 i, _Tp v);
		const CvMat add(const CvMat & m);
		const CvMat reduce(const CvMat & m);
		const CvMat mul(const CvMat & m);
		const CvMat div(const CvMat & m);

		mat_t get_(int32 i)const;
		mat_t get_(int32 i0, int32 i1)const;
		mat_t get_(int32 i0, int32 i1, int32 i2)const;
		template<typename _Tp> _Tp get(int32 i)const;
		template<typename _Tp> _Tp get(int32 i0, int32 i1)const;
		template<typename _Tp> _Tp get(int32 i0, int32 i1, int32 i2)const;
		int32 rankSize(RANK r)const;
		/**
		保存矩阵
		@param file		保存文件名
		@param binary	选择文本还是二进制
		binary = false	选择文本
		binary = true	选择二进制
		*/
		void save(std::string file, bool binary = true)const;
		/**
		二进制保存矩阵
		@param file		保存文件指针
		*/
		void save(FILE *file)const;
		/**
		读取矩阵
		@param file		读取文件名
		只支持二进制读取
		*/
		void load(std::string file);
		/**
		读取矩阵
		@param file		读取文件指针
		只支持二进制读取
		*/
		void load(FILE *file);
		/**
		@brief 返回矩阵大小(h_*w_*c_)
		*/
		int32 len()const;
		/**
		@brief 返回矩阵大小(h_*w_*c_)
		*/
		int32 elementlen()const;
		/**
		@brief 返回矩阵状态
		0为矩阵
		-1为空矩阵
		-2为非方阵
		*/
		int32 enable()const;
		/**
		@brief 返回矩阵是否为空
		*/
		bool empty()const;
		/**
		@brief 返回矩阵是否为矩阵
		*/
		bool Square()const;
		/**
		数据深拷贝到mat
		@param mat		输入
		*/
		void copyTo(CvMat& mat)const;
		/**
		数据覆盖到mat
		@param mat		输入
		*/
		void setTo(CvMat mat)const;
		/**
		数据转换
		@param m		输出
		@param type		数据类型
		*/
		void convertTo(CvMat &m, int32 type)const;
		/**
		数据转换
		@brief 返回type数据类型矩阵
		@param type		数据类型
		*/
		const CvMat convert(int32 type)const;
		/**
		在矩阵最左边或最右边添加一列1
		@param dire		选择添加方式
		*/
		void setAddOnes(Dire dire = RIGHT);
		/**
		在矩阵最左边或最右边添加一列0
		@param dire		选择添加方式
		*/
		void setAddZeros(Dire dire = RIGHT);
		/**
		释放内存
		*/
		void release();
		/**
		@brief 按索引返回矩阵元素
		@param w		索引
		*/
		template<typename _Tp> _Tp& at(int32 w);
		/**
		@brief 按索引返回矩阵元素
		@param w		列索引
		@param h		行索引
		*/
		template<typename _Tp> _Tp& at(int32 h, int32 w);
		/**
		@brief 按索引返回矩阵元素
		@param w		列索引
		@param h		行索引
		@param c		通道索引
		*/
		template<typename _Tp> _Tp& at(int32 h, int32 w, int32 c);
		/**
		@brief 返回对应索引元素
		@param p 索引
		*/
		template<typename _Tp> _Tp& at(Point p);
		/**
		@brief 返回对应索引元素
		@param p 索引
		*/
		template<typename _Tp> _Tp& at(Point3i p);
		/**
		@brief 按索引返回矩阵元素
		@param w		索引
		*/
		template<typename _Tp> const _Tp& at(int32 w)const;
		/**
		@brief 按索引返回矩阵元素
		@param w		列索引
		@param h		行索引
		*/
		template<typename _Tp> const _Tp& at(int32 h, int32 w)const;
		/**
		@brief 按索引返回矩阵元素
		@param w		列索引
		@param h		行索引
		@param c		通道索引
		*/
		template<typename _Tp> const _Tp& at(int32 h, int32 w, int32 c)const;
		/**
		@brief 返回对应索引元素
		@param p 索引
		*/
		template<typename _Tp> const _Tp& at(Point p)const;
		/**
		@brief 返回对应索引元素
		@param p 索引
		*/
		template<typename _Tp> const _Tp& at(Point3i p)const;
		/**
		@brief 将索引转换为对应矩阵列索引
		@param index	索引
		*/
		int32 toX(int32 index)const;
		/**
		@brief 将索引转换为对应矩阵行索引
		@param index	索引
		*/
		int32 toY(int32 index)const;
		/**
		@brief 将索引转换为对应矩阵通道索引
		@param index	索引
		*/
		int32 toZ(int32 index)const;

		/**
		@brief 返回矩阵与value相等的第一个元素索引
		@param value	元素
		*/
		template<typename _Tp>
		int32 find(_Tp value)const;
		/**
		@brief 返回矩阵元素最大值的索引
		*/
		int32 maxAt()const;
		/**
		@brief 返回矩阵元素最小值的索引
		*/
		int32 minAt()const;
		/**
		@brief 返回矩阵是否包含value
		@param value	元素
		*/
		template<typename _Tp> bool contains(_Tp value)const;
		template<typename _Tp> bool isValue(int32 i, _Tp v)const;
		template<typename _Tp> bool isValue(Point p, _Tp v)const;
		bool isZero(int32 i)const;
		bool isZero(Point p)const;
		bool isOne(int32 i)const;
		bool isOne(Point p)const;
		bool compare(int32 i1, int32 i2, int32 op)const;
		template<typename _Tp> bool compare(int32 i, _Tp v, int32 op)const;
		void BitNot(int32 idx);
		void BitAnd(int32 idx, Val val);
		void BitOr(int32 idx, Val val);
		const CvMat BitNot()const;
		const CvMat BitAnd(Val val)const;
		const CvMat BitAnd(const CvMat & a)const;
		const CvMat BitOr(Val val)const;
		const CvMat BitOr(const CvMat & a)const;
		/**
		@brief 返回矩阵的最大值
		@param is_abs	是否绝对值
		*/
		mat_t Max(bool is_abs = false)const;
		/**
		@brief 返回矩阵的最小值
		@param is_abs	是否绝对值
		*/
		mat_t Min(bool is_abs = false)const;
		/**
		@brief 返回矩阵元素最大值
		*/
		template<typename _Tp> _Tp& findmax();
		/**
		@brief 返回矩阵元素最小值
		*/
		template<typename _Tp> _Tp& findmin();
		/**
		@brief 将矩阵按索引区域拷贝元素到src矩阵中
		@param src			被拷贝矩阵
		@param Row_Start	截取行初始索引值
		@param Row_End		截取行结束索引值
		@param Col_Start	截取列初始索引值
		@param Col_End		截取列结束索引值
		*/
		void copy(CvMat &src, int32 Row_Start, int32 Row_End, int32 Col_Start, int32 Col_End)const;
		/**
		@brief 将矩阵拷贝到src
		@param src 被拷贝矩阵
		*/
		void swap(CvMat &src)const;
		/**
		@brief mChannel 将src覆盖到第c_通道
		@param src		矩阵
		@param c_	通道数
		*/
		void mChannel(const lzh::CvMat &src, int32 c);
		/**
		@brief mChannel 将src覆盖到第c_通道
		@param src		矩阵
		@param c_	通道数
		*/
		void mChannel(const lzh::CvMat &src, int32 w, int32 h);
		/**
		@brief 设置矩阵维度
		不允许改变矩阵长度
		@param size		矩阵大小
		*/
		void reshape(Size3 size);
		/**
		@brief 设置矩阵维度
		不允许改变矩阵长度
		@param h_		矩阵行数
		@param w_		矩阵列数
		@param c_	矩阵通道
		*/
		void reshape(int32 w, int32 h, int32 c);
		/**
		@brief 设置矩阵大小
		如果矩阵原大小不等于h_*w_*1则元素全部重置为0
		@param h_	矩阵行数
		@param w_	矩阵列数
		*/
		bool setSize(int32 w, int32 h, int32 c);
		/**
		@brief 拷贝矩阵src
		@param src	拷贝矩阵
		*/
		void setvalue(const lzh::CvMat &src);
		/**
		@brief 设置逆矩阵
		*/
		void setInv();
		/**
		@brief 设置矩阵的num次幂
		@param num	次幂
		*/
		void setPow(mat_t num);
		/**
		@brief 设置单位矩阵
		*/
		void setIden();
		/**
		@brief 设置伴随矩阵
		*/
		void setAdj();
		/**
		@brief 设置转置矩阵
		*/
		void setTran();
		/**
		设置色域
		@param cg	指定色域
		*/
		void setColorGamut(ColorGamut cg);

		/**
		@brief 命令行输出矩阵
		*/
		void show()const;
		/**
		@brief 输出矩阵
		*/
		std::ostream & show(std::ostream & out)const;

		/**
		@brief 返回h行矩阵
		@param 索引
		*/
		CvMat row(int32 h);
		/**
		@brief 返回h行矩阵
		@param 索引
		*/
		const CvMat row(int32 h)const;
		/**
		@brief 返回w列矩阵
		@param 索引
		*/
		CvMat col(int32 w);
		/**
		@brief 返回w列矩阵
		@param 索引
		*/
		const CvMat col(int32 w)const;
		/**
		@brief 返回c通道矩阵
		@param 通道索引
		*/
		CvMat channel(int32 c);
		/**
		@brief 返回c通道矩阵
		@param 通道索引
		*/
		const CvMat channel(int32 c)const;
		template<typename _Tp> const CvMat addvalue(Dire dire, _Tp v) const;
		/**
		@brief 在矩阵最左边或最右边添加一列1
		@param dire		选择添加方式
		*/
		const CvMat addones(Dire dire = RIGHT)const;
		/**
		@brief 在矩阵最左边或最右边添加一列0
		@param dire		选择添加方式
		*/
		const CvMat addzeros(Dire dire = RIGHT)const;
		/**
		@brief 返回start到end矩阵
		@param start	开始索引
		@param end		结束索引
		*/
		const CvMat range(int32 start, int32 end)const;
		/**
		@brief 返回roi范围的矩阵
		@param roi	开始索引
		*/
		const CvMat range(Rect roi)const;
		/**
		@brief 返回roi范围的矩阵
		@param roi	开始索引
		*/
		const CvMat range(int32 h_start, int32 h_end, int32 w_start, int32 w_end)const;
		/**
		@brief 返回h_start到h_end行矩阵
		@param h_start	行开始索引
		@param h_end	行结束索引
		*/
		const CvMat rowRange(int32 h_start, int32 h_end)const;
		/**
		@brief 返回w_start到w_end列矩阵
		@param w_start	列开始索引
		@param w_end	列结束索引
		*/
		const CvMat colRange(int32 w_start, int32 w_end)const;
		/**
		@brief 返回c_start到c_end通道矩阵
		@param c_start	通道开始索引
		@param c_end	通道结束索引
		*/
		const CvMat channelRange(int32 c_start, int32 c_end)const;
		/**
		@brief 返回深拷贝矩阵
		*/
		const CvMat clone()const;
		/**
		@brief 返回取反矩阵
		*/
		const CvMat opp()const;
		/**
		@brief 返回绝对值矩阵
		*/
		const CvMat abs()const;
		/**
		@brief 返回按num次幂矩阵
		@param num 次幂
		*/
		const CvMat mPow(int32 num)const;
		/**
		@brief 返回按num次幂矩阵
		@param num 次幂
		*/
		const CvMat pow(mat_t num)const;
		/**
		@brief 返回按元素取指数矩阵
		*/
		const CvMat exp()const;
		/**
		@brief 返回按元素取对数矩阵
		*/
		const CvMat log()const;
		/**
		@brief 返回按元素取开方矩阵
		*/
		const CvMat sqrt()const;
		/**
		@brief 返回伴随矩阵
		*/
		const CvMat adj()const;
		/**
		@brief 返回转置矩阵
		*/
		const CvMat t()const;
		/**
		@brief 返回逆矩阵
		*/
		const CvMat inv()const;
		/**
		@brief 返回逆矩阵
		*/
		const CvMat diag(int32 k = 0)const;
		/**
		@brief 返回逆序矩阵
		矩阵必须是向量
		*/
		const CvMat reverse()const;
		/**
		@brief 返回特征向量(未完成)
		*/
		const CvMat EigenvectorsMax(mat_t offset = 1e-8)const;
		/**
		@brief sigmoid函数
		*/
		const CvMat sigmoid()const;
		/**
		@brief tanh函数
		*/
		const CvMat tanh()const;
		/**
		@brief relu函数
		*/
		const CvMat relu()const;
		/**
		@brief elu函数
		*/
		const CvMat elu()const;
		/**
		@brief selu函数
		*/
		const CvMat selu()const;
		/**
		@brief leaky_relu函数
		*/
		const CvMat leaky_relu()const;
		/**
		@brief softmax函数
		*/
		const CvMat softmax()const;
		/**
		@brief 返回行列式
		*/
		mat_t Det();
		/**
		@brief 返回num范数
		@param num 几范数
		*/
		mat_t norm(int32 num = 1)const;
		/**
		@brief 返回对应索引的余子式
		@param x 列索引
		@param y 行索引
		*/
		mat_t Cof(int32 x, int32 y);
		mat_t EigenvalueMax(mat_t offset = 1e-8)const;
		/**
		@brief 返回矩阵元素和
		@param num	设置次幂
		@param _abs 是否取绝对值
		*/
		mat_t sum(int32 num = 1, bool _abs = false)const;
		/**
		@brief 返回平均值
		*/
		mat_t mean()const;
		/**
		@brief 返回标准差
		*/
		mat_t std()const;
		/**
		@brief 返回标准差
		*/
		mat_t D()const;
		/**
		@brief 重载运算符=
		拷贝
		*/
		CvMat & operator = (const CvMat &temp);
		/**
		@brief 重载运算符=
		拷贝
		*/
		CvMat & operator = (const Mat &temp);
		/**
		@brief 重载运算符==
		判断矩阵是否相等
		*/
		bool operator == (const lzh::CvMat &a)const;
		/**
		@brief 重载运算符!=
		判断矩阵是否不相等
		*/
		bool operator != (const lzh::CvMat &a)const;
		mat_t operator () (int32 i)const;
		mat_t operator () (int32 i0, int32 i1)const;
		mat_t operator () (int32 i0, int32 i1, int32 i2)const;
		mat_t operator () (Point p)const;
		mat_t operator () (Point3 p)const;
		CvMat operator () (Rect roi)const;
		CvMat operator () (Range row, Range col)const;
		/**
		@brief 返回矩阵对应索引的列或行
		@param index	索引
		@param rc		索引方式
		*/
		CvMat operator () (int32 index, RANK rc)const;
		/**
		@brief 返回矩阵对应索引的列或行
		@param index	索引
		@param rc		索引方式
		*/
		CvMat operator () (int32 v1, int32 v2, RANK rc)const;
		/**
		@brief 返回矩阵对应索引的列或行
		@param index	索引
		@param rc		索引方式
		*/
		CvMat cut(int32 index, RANK rc)const;
		/**
		@brief 返回矩阵对应索引的列或行
		@param index	索引
		@param rc		索引方式
		*/
		CvMat cut(int32 v1, int32 v2, RANK rc)const;

		const CvMat operator [] (int32 idx) const;

		bool operator > (const CvMat &b) const;
		bool operator < (const CvMat &b) const;

		template<typename _Tp> operator _Tp *();
		template<typename _Tp> operator const _Tp *() const;

		/**
		@brief 返回元素为0的w向量
		@param w		向量长度
		*/
		static const CvMat zeros(int32 w, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为0的h*w矩阵
		@param w		矩阵列数
		@param h		矩阵行数
		*/
		static const CvMat zeros(int32 w, int32 h, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为0的h*w*c矩阵
		@param w		矩阵列数
		@param h		矩阵行数
		@param c		矩阵通道数
		*/
		static const CvMat zeros(int32 w, int32 h, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为0的size矩阵
		@param size 矩阵大小
		*/
		static const CvMat zeros(Size size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为0的size矩阵
		@param size 矩阵大小
		*/
		static const CvMat zeros(Size size, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为0的size矩阵
		@param size 矩阵大小
		*/
		static const CvMat zeros(Size3 size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为v的w向量
		@param v		填充元素
		@param w		向量长度
		*/
		static const CvMat value(Val v, int32 w, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为v的h*w矩阵
		@param v		填充元素
		@param w		矩阵列数
		@param h		矩阵行数
		*/
		static const CvMat value(Val v, int32 w, int32 h, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为v的h_*w_*c_矩阵
		@param v		填充元素
		@param w		矩阵列数
		@param h		矩阵行数
		@param c		矩阵通道数
		*/
		static const CvMat value(Val v, int32 w, int32 h, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为1的w向量
		@param w		向量长度
		*/
		static const CvMat ones(int32 w, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为1的h*w矩阵
		@param w	矩阵列数
		@param h	矩阵行数
		*/
		static const CvMat ones(int32 w, int32 h, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为1的h*w*c矩阵
		@param w		矩阵列数
		@param h		矩阵行数
		@param c		矩阵通道数
		*/
		static const CvMat ones(int32 w, int32 h, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为1的size矩阵
		@param size 矩阵大小
		*/
		static const CvMat ones(Size size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为1的size矩阵
		@param size 矩阵大小
		*/
		static const CvMat ones(Size size, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回元素为1的size矩阵
		@param size 矩阵大小
		*/
		static const CvMat ones(Size3 size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief 返回生成的n*n*1单位矩阵
		@param n 矩阵大小
		*/
		static const CvMat eye(int32 n, int32 flag);


		/**
		设置打印宽度
		@param w 宽度
		*/
		static void setPrintW(uint32 w);
		/**
		设置打印有效数字
		@param n 位数
		*/
		static void setPrintSignificantDigits(uint32 n);
		/**
		设置打印方法
		@param t 打印方法
		*/
		static void setPrintType(lzh::PrintType t);

		int32 rows;
		int32 cols;
		PtrMat data;
	protected:
		template<typename _Tp> void setv(int32 i, _Tp v);
		void setp(int32 i, const void * v, int32 addr_offset);

		static lzh::uint32 print_width;
		static lzh::uint32 print_precision;
		static lzh::PrintType print_type;

		void init();
		void checkSquare();
#ifdef MAT_DEBUG
		void checkindex(int32 index);
		void checkindex(int32 index_x, int32 index_y);
#endif // MAT_DEBUG
		void setsize(int32 w, int32 h = 1, int32 c = 1);

	private:
		int32 c_;
		MatStep stride;
		int32 dim;
		ColorGamut _type;
		bool square;
	};
	/**
	@brief CvMat_ 工具类
	继承Mat类，用于实现
	CvMat mat = (CvMat_<_Tp>(3, 3) <<
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1);
	*/
	template<typename _Tp> class CvMat_ : public CvMat
	{
	public:
		explicit CvMat_() : CvMat() {}
		/**
		@brief 生成w的向量
		@param w		长度
		*/
		CvMat_(int32 w) : CvMat(w, DataType<_Tp>::type) {}
		/**
		@brief 生成h*w的矩阵
		@param w		列数
		@param h		行数
		*/
		CvMat_(int32 w, int32 h) : CvMat(w, h, DataType<_Tp>::type) {}
		/**
		@brief 生成h*w*c的张量
		@param w		列数
		@param h		行数
		@param depth	通道数
		*/
		CvMat_(int32 w, int32 h, int32 c) : CvMat(w, h, c, DataType<_Tp>::type) {}
		/**
		@brief 生成size的矩阵
		@param size		尺寸
		*/
		CvMat_(Size size) : CvMat(size, DataType<_Tp>::type) {}
		/**
		@brief 生成size的矩阵
		@param size		尺寸
		*/
		CvMat_(Size size, int32 c) : CvMat(size, c, DataType<_Tp>::type) {}
		/**
		@brief 生成size的矩阵
		@param size		尺寸
		*/
		CvMat_(Size3 size) : CvMat(size) {}
		CvMat_(std::initializer_list<_Tp> _Ilist) : CvMat((int32)_Ilist.size(), _Ilist.begin(), DataType<_Tp>::type) {}
		operator _Tp *();
		operator const _Tp *()const;

		_Tp& at(int32 i);
		_Tp& at(int32 i0, int32 i1);
		_Tp& at(int32 i0, int32 i1, int32 i2);
		_Tp& at(Point p);
		_Tp& at(Point3 p);

		const _Tp& at(int32 i)const;
		const _Tp& at(int32 i0, int32 i1)const;
		const _Tp& at(int32 i0, int32 i1, int32 i2)const;
		const _Tp& at(Point p)const;
		const _Tp& at(Point3 p)const;

		_Tp* ptr(int32 i);
		_Tp* ptr(int32 i0, int32 i1);
		_Tp* ptr(int32 i0, int32 i1, int32 i2);
		_Tp* ptr(Point p);
		_Tp* ptr(Point3 p);

		const _Tp* ptr(int32 i)const;
		const _Tp* ptr(int32 i0, int32 i1)const;
		const _Tp* ptr(int32 i0, int32 i1, int32 i2)const;
		const _Tp* ptr(Point p)const;
		const _Tp* ptr(Point3 p)const;

		_Tp& operator () (int32 i);
		_Tp& operator () (int32 i0, int32 i1);
		_Tp& operator () (int32 i0, int32 i1, int32 i2);
		_Tp& operator () (Point p);
		_Tp& operator () (Point3 p);

		const _Tp& operator () (int32 i)const;
		const _Tp& operator () (int32 i0, int32 i1)const;
		const _Tp& operator () (int32 i0, int32 i1, int32 i2)const;
		const _Tp& operator () (Point p)const;
		const _Tp& operator () (Point3 p)const;

	};
	typedef CvMat_<mat_t> Mat_;

	/**
	@brief MatCommaInitializer_ 工具类
	作为迭代器，用于实现
	Mat mat = (CvMat_(3, 3) <<
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1);
	*/
	template<class _Tp> class MatCommaInitializer_
	{
	public:
		explicit MatCommaInitializer_() {}
		MatCommaInitializer_(const CvMat_<_Tp>& m) {
			head = (_Tp*)m.data();
			it = head;
			h = m.rows;
			w = m.cols;
			c = m.channels();
		}
		template<typename _T2> MatCommaInitializer_<_Tp>& operator , (_T2 v);
		int32 rows()const { return h; }
		int32 cols()const { return w; }
		int32 channels()const { return c; }
		_Tp * data()const { return head; }
		int32 size()const { return h * w*c; }
	private:
		int32 h;
		int32 w;
		int32 c;
		_Tp *it;
		_Tp *head;
	};
	template<typename _Tp> template<typename _T2> inline
		MatCommaInitializer_<_Tp>& MatCommaInitializer_<_Tp>::operator , (_T2 v)
	{
#ifdef MAT_DEBUG
		if (this->it == this->head + h * w*c)
			THROW_INFO(ERR_INFO_MEMOUT);
#endif
		*this->it = _Tp(v);
		++this->it;
		return *this;
	}
	template<typename _Tp, typename _T2> inline
		MatCommaInitializer_<_Tp> operator << (const CvMat_<_Tp> & m, _T2 val)
	{
		MatCommaInitializer_<_Tp> commaInitializer(m);
		return (commaInitializer, val);
	}

	template<typename _Tp> inline _Tp * PtrMat::begin()
	{
#ifdef MAT_DEBUG
		CHECK_TYPE(_Tp, type);
#endif // MAT_DEBUG
		return (_Tp*)data;
	}
	template<typename _Tp> inline const _Tp * PtrMat::begin() const
	{
#ifdef MAT_DEBUG
		CHECK_TYPE(_Tp, depth());
#endif // MAT_DEBUG
		return (const _Tp*)data;
	}
	template<typename _Tp> inline _Tp * PtrMat::end()
	{
#ifdef MAT_DEBUG
		CHECK_PTR(data);
		CHECK_TYPE(_Tp, type);
#endif // MAT_DEBUG
		if (refcount == nullptr)
			return ((_Tp*)(data)) + len;
		return (_Tp*)refcount;
	}
	template<typename _Tp> inline const _Tp * PtrMat::end() const
	{
#ifdef MAT_DEBUG
		CHECK_PTR(data);
		CHECK_TYPE(_Tp, depth());
#endif // MAT_DEBUG
		if (refcount == nullptr)return (const _Tp*)(data)+len;
		return (const _Tp*)refcount;;
	}
	template<typename _Tp> inline _Tp & PtrMat::at(int32 i)
	{
#ifdef MAT_DEBUG
		CHECK_PTR(data);
		CHECK_TYPE(_Tp, depth());
		CHECK_INDEX(i, len);
#endif // MAT_DEBUG
		return ((_Tp*)data)[i];
	}
	template<typename _Tp> inline const _Tp & PtrMat::at(int32 i) const
	{
#ifdef MAT_DEBUG
		CHECK_PTR(data);
		CHECK_TYPE(_Tp, depth());
		CHECK_INDEX(i, len);
#endif // MAT_DEBUG
		return ((const _Tp*)data)[i];
	}
	template<typename _Tp> inline _Tp & PtrMat::operator[](int32 i) const {
#ifdef MAT_DEBUG
		CHECK_PTR(data);
		CHECK_TYPE(_Tp, depth());
		CHECK_INDEX(i, len);
#endif // MAT_DEBUG
		return ((_Tp*)data)[i];
	}
	template<typename _Tp> inline PtrMat::operator _Tp*()
	{
		return (_Tp*)data;
	}
	template<typename _Tp> inline PtrMat::operator const _Tp*() const
	{
		return (const _Tp*)data;
	}
	template<typename _Tp> inline _Tp PtrMat::get(int32 i) const {
#ifdef MAT_DEBUG
		CHECK_PTR(data);
		CHECK_INDEX(i, len);
#endif // MAT_DEBUG
		_Tp v;
		MAT_VALUE(_Tp, depth(), data, i, v);
		return v;
	}

	template<typename _Tp> inline CvMat::CvMat(const MatCommaInitializer_<_Tp>& m) {
		create(m.rows(), m.rows(), m.channels(), DataType<_Tp>::type);
		memcpy(data, m.data(), memsize());
	}
	template<typename _Tp> inline CvMat::CvMat(Size3 size, int32 flags, _Tp v, ...) {
		init();
		create(size, flags);
		va_list ap;
		va_start(ap, v);
		set(0, v);
		FOR_RANGE(i, 1, size.area())
			set(i, va_arg(ap, _Tp));
		va_end(ap);
	}
	template<typename _Tp>  _Tp & CvMat::first() const
	{
		return data.at<_Tp>(0);
	}
	template<typename _Tp> inline _Tp & CvMat::last() const
	{
		return data.at<_Tp>(data.size() - 1);
	}
	template<typename _Tp> inline _Tp * CvMat::begin()
	{
		return data.begin<_Tp>();
	}
	template<typename _Tp> inline const _Tp * CvMat::begin() const
	{
		return data.begin<_Tp>();
	}
	template<typename _Tp> inline _Tp * CvMat::end()
	{
		return data.end<_Tp>();
	}
	template<typename _Tp> inline const _Tp * CvMat::end() const
	{
		return data.end<_Tp>();
	}
	template<typename _Tp> inline void CvMat::set(int32 i, _Tp v) {
		setv(toidx(i), v);
	}
	template<typename _Tp> inline void CvMat::set(int32 i0, int32 i1, _Tp v) {
		setv(toidx(i0, i1), v);
	}
	template<typename _Tp> inline void CvMat::set(int32 i0, int32 i1, int32 i2, _Tp v) {
		setv(toidx(i0, i1, i2), v);
	}
	template<typename _Tp> inline void CvMat::set(Point p, _Tp v)
	{
		setv(toidx(p.y, p.x), v);
	}
	template<typename _Tp> inline void CvMat::set(Point3 p, _Tp v)
	{
		setv(toidx(p.y, p.x, p.z), v);
	}
	template<typename _Tp, int32 N> inline void CvMat::set(int32 i0, int32 i1, const Vec<_Tp, N>& v)
	{
		FOR(i, Range(0, N))
			setv(toidx(i0, i1, i), v[i]);
	}
	template<typename _Tp> inline void CvMat::add(int32 i, _Tp v)
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
		CHECK_INDEX(i, elementlen());
#endif // MAT_DEBUG
		switch (depth()) {
		case lzh::TP_8S:	MAT_GETARRAY(int8, data(), i) += (int8)v;		break;
		case lzh::TP_8U:	MAT_GETARRAY(uint8, data(), i) += (uint8)v;	break;
		case lzh::TP_16S:	MAT_GETARRAY(int16, data(), i) += (int16)v;	break;
		case lzh::TP_16U:	MAT_GETARRAY(uint16, data(), i) += (uint16)v;	break;
		case lzh::TP_32S:	MAT_GETARRAY(int32, data(), i) += (int32)v;	break;
		case lzh::TP_32U:	MAT_GETARRAY(uint32, data(), i) += (uint32)v;	break;
		case lzh::TP_64S:	MAT_GETARRAY(int64, data(), i) += (int64)v;	break;
		case lzh::TP_64U:	MAT_GETARRAY(uint64, data(), i) += (uint64)v;	break;
		case lzh::TP_32F:	MAT_GETARRAY(float32, data(), i) += (float32)v;	break;
		case lzh::TP_64F:	MAT_GETARRAY(float64, data(), i) += (float64)v;	break;
		case lzh::TP_64D:	MAT_GETARRAY(float64_, data(), i) += (float64_)v;	break;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
	}
	template<typename _Tp> inline void CvMat::reduce(int32 i, _Tp v)
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
		CHECK_INDEX(i, elementlen());
#endif // MAT_DEBUG
		switch (depth()) {
		case lzh::TP_8S:	MAT_GETARRAY(int8, data(), i) -= (int8)v;		break;
		case lzh::TP_8U:	MAT_GETARRAY(uint8, data(), i) -= (uint8)v;	break;
		case lzh::TP_16S:	MAT_GETARRAY(int16, data(), i) -= (int16)v;	break;
		case lzh::TP_16U:	MAT_GETARRAY(uint16, data(), i) -= (uint16)v;	break;
		case lzh::TP_32S:	MAT_GETARRAY(int32, data(), i) -= (int32)v;	break;
		case lzh::TP_32U:	MAT_GETARRAY(uint32, data(), i) -= (uint32)v;	break;
		case lzh::TP_64S:	MAT_GETARRAY(int64, data(), i) -= (int64)v;	break;
		case lzh::TP_64U:	MAT_GETARRAY(uint64, data(), i) -= (uint64)v;	break;
		case lzh::TP_32F:	MAT_GETARRAY(float32, data(), i) -= (float32)v;	break;
		case lzh::TP_64F:	MAT_GETARRAY(float64, data(), i) -= (float64)v;	break;
		case lzh::TP_64D:	MAT_GETARRAY(float64_, data(), i) -= (float64_)v;	break;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
	}
	template<typename _Tp> inline void CvMat::mul(int32 i, _Tp v)
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
		CHECK_INDEX(i, elementlen());
#endif // MAT_DEBUG
		switch (depth()) {
		case lzh::TP_8S:	MAT_GETARRAY(int8, data(), i) *= (int8)v;		break;
		case lzh::TP_8U:	MAT_GETARRAY(uint8, data(), i) *= (uint8)v;	break;
		case lzh::TP_16S:	MAT_GETARRAY(int16, data(), i) *= (int16)v;	break;
		case lzh::TP_16U:	MAT_GETARRAY(uint16, data(), i) *= (uint16)v;	break;
		case lzh::TP_32S:	MAT_GETARRAY(int32, data(), i) *= (int32)v;	break;
		case lzh::TP_32U:	MAT_GETARRAY(uint32, data(), i) *= (uint32)v;	break;
		case lzh::TP_64S:	MAT_GETARRAY(int64, data(), i) *= (int64)v;	break;
		case lzh::TP_64U:	MAT_GETARRAY(uint64, data(), i) *= (uint64)v;	break;
		case lzh::TP_32F:	MAT_GETARRAY(float32, data(), i) *= (float32)v;	break;
		case lzh::TP_64F:	MAT_GETARRAY(float64, data(), i) *= (float64)v;	break;
		case lzh::TP_64D:	MAT_GETARRAY(float64_, data(), i) *= (float64_)v;	break;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
	}
	template<typename _Tp> inline void CvMat::div(int32 i, _Tp v)
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
		CHECK_INDEX(i, elementlen());
		if (v == 0)
			THROW_INFO(ERR_INFO_DIV);
#endif // MAT_DEBUG
		switch (depth()) {
		case lzh::TP_8S:	MAT_GETARRAY(int8, data(), i) /= (int8)v;		break;
		case lzh::TP_8U:	MAT_GETARRAY(uint8, data(), i) /= (uint8)v;	break;
		case lzh::TP_16S:	MAT_GETARRAY(int16, data(), i) /= (int16)v;	break;
		case lzh::TP_16U:	MAT_GETARRAY(uint16, data(), i) /= (uint16)v;	break;
		case lzh::TP_32S:	MAT_GETARRAY(int32, data(), i) /= (int32)v;	break;
		case lzh::TP_32U:	MAT_GETARRAY(uint32, data(), i) /= (uint32)v;	break;
		case lzh::TP_64S:	MAT_GETARRAY(int64, data(), i) /= (int64)v;	break;
		case lzh::TP_64U:	MAT_GETARRAY(uint64, data(), i) /= (uint64)v;	break;
		case lzh::TP_32F:	MAT_GETARRAY(float32, data(), i) /= (float32)v;	break;
		case lzh::TP_64F:	MAT_GETARRAY(float64, data(), i) /= (float64)v;	break;
		case lzh::TP_64D:	MAT_GETARRAY(float64_, data(), i) /= (float64_)v;	break;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
	}
	template<typename _Tp>
	inline _Tp CvMat::get(int32 i) const { return data.get<_Tp>(toidx(i)); }
	template<typename _Tp> inline _Tp CvMat::get(int32 i0, int32 i1) const { return data.get<_Tp>(toidx(i0, i1)); }
	template<typename _Tp> inline _Tp CvMat::get(int32 i0, int32 i1, int32 i2) const { return data.get<_Tp>(toidx(i0, i1, i2)); }
	template<typename _Tp> inline _Tp & CvMat::at(int32 w) {
		return data.at<_Tp>(toidx(w));
	}
	template<typename _Tp> inline _Tp & CvMat::at(int32 h, int32 w) {
		return data.at<_Tp>(toidx(h, w));
	}
	template<typename _Tp> inline _Tp & CvMat::at(int32 h, int32 w, int32 c) {
		return data.at<_Tp>(toidx(h, w, c));
	}
	template<typename _Tp> inline _Tp & CvMat::at(Point p) {
		return at<_Tp>(toidx(p.y, p.x));
	}
	template<typename _Tp> inline _Tp & CvMat::at(Point3i p) {
		return at<_Tp>(toidx(p.y, p.x, p.z));
	}
	template<typename _Tp> inline const _Tp & CvMat::at(int32 w) const {
		return data.at<_Tp>(toidx(w));
	}
	template<typename _Tp> inline const _Tp & CvMat::at(int32 h, int32 w) const {
		return data.at<_Tp>(toidx(h, w));
	}
	template<typename _Tp> inline const _Tp & CvMat::at(int32 h, int32 w, int32 c) const {
		return data.at<_Tp>(toidx(h, w, c));
	}
	template<typename _Tp> inline const _Tp & CvMat::at(Point p) const {
		return at<_Tp>(toidx(p.y, p.x));
	}
	template<typename _Tp> inline const _Tp & CvMat::at(Point3i p) const {
		return at<_Tp>(toidx(p.y, p.x, p.z));
	}
	template<typename _Tp> inline int32 CvMat::find(_Tp value) const
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
#endif //MAT_DEBUG
		for (int32 ind = 0; ind < len(); ind++)
			if (compare(ind, value, 0))
				return ind;
		return -1;
	}
	template<typename _Tp> inline bool CvMat::contains(_Tp value) const
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
#endif //MAT_DEBUG
		for (int32 ind = 0; ind < len(); ind++)
			if (compare(ind, value, 0))
				return true;
		return false;
	}
	template<typename _Tp> inline bool CvMat::isValue(int32 i, _Tp v) const
	{
		switch (depth()) {
		case lzh::TP_8S:	return MAT_GETARRAY(int8, data(), i) == (int8)v;
		case lzh::TP_8U:	return MAT_GETARRAY(uint8, data(), i) == (uint8)v;
		case lzh::TP_16S:	return MAT_GETARRAY(int16, data(), i) == (int16)v;
		case lzh::TP_16U:	return MAT_GETARRAY(uint16, data(), i) == (uint16)v;
		case lzh::TP_32S:	return MAT_GETARRAY(int32, data(), i) == (int32)v;
		case lzh::TP_32U:	return MAT_GETARRAY(uint32, data(), i) == (uint32)v;
		case lzh::TP_64S:	return MAT_GETARRAY(int64, data(), i) == (int64)v;
		case lzh::TP_64U:	return MAT_GETARRAY(uint64, data(), i) == (uint64)v;
		case lzh::TP_32F:	return MAT_GETARRAY(float32, data(), i) == (float32)v;
		case lzh::TP_64F:	return MAT_GETARRAY(float64, data(), i) == (float64)v;
		case lzh::TP_64D:	return MAT_GETARRAY(float64_, data(), i) == (float64_)v;
		default:THROW_INFO(ERR_INFO_TYPE);
		}
	}
	template<typename _Tp> inline bool CvMat::isValue(Point p, _Tp v) const
	{
		return isValue(toidx(p.y, p.x), v);
	}
	template<typename _Tp> inline bool CvMat::compare(int32 i, _Tp v, int32 op) const
	{
		bool state = false;
		switch (depth()) {
		case lzh::TP_8S:	COMPARE(((const int8*)data())[i], v, op, state); break;
		case lzh::TP_8U:	COMPARE(((const uint8*)data())[i], v, op, state); break;
		case lzh::TP_16S:	COMPARE(((const int16*)data())[i], v, op, state); break;
		case lzh::TP_16U:	COMPARE(((const uint16*)data())[i], v, op, state); break;
		case lzh::TP_32S:	COMPARE(((const int32*)data())[i], v, op, state); break;
		case lzh::TP_32U:	COMPARE(((const uint32*)data())[i], v, op, state); break;
		case lzh::TP_64S:	COMPARE(((const int64*)data())[i], v, op, state); break;
		case lzh::TP_64U:	COMPARE(((const uint64*)data())[i], v, op, state); break;
		case lzh::TP_32F:	COMPARE(((const float32*)data())[i], v, op, state); break;
		case lzh::TP_64F:	COMPARE(((const float64*)data())[i], v, op, state); break;
		case lzh::TP_64D:	COMPARE(((const float64_*)data())[i], v, op, state); break;
		default:return false;
		}
		return state;
	}
	template<typename _Tp> inline _Tp & CvMat::findmax()
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
#endif //MAT_DEBUG
		int32 max_adr = 0;
		for (int32 ind = 1; ind < len(); ind++)
			if (compare(max_adr, ind, -2))
				max_adr = ind;
		return at<_Tp>(max_adr);
	}
	template<typename _Tp> inline _Tp & CvMat::findmin()
	{
#ifdef MAT_DEBUG
		CHECK_MATRIX(data);
#endif //MAT_DEBUG
		int32 min_adr = 0;
		for (int32 ind = 1; ind < len(); ind++)
			if (compare(min_adr, ind, 2))
				min_adr = ind;
		return at<_Tp>(min_adr);
	}
	template<typename _Tp> inline const CvMat CvMat::addvalue(Dire dire, _Tp v) const
	{
		CvMat temp(cols + 1, rows, c_, depth());
		for (int32 i = 0; i < rows; i++) {
			for (int32 j = 0; j < cols + 1; j++) {
				for (int32 z = 0; z < c_; z++) {
					if (dire == LEFT) {
						if (j == 0)
							temp.set(temp.toidx(i, 0, z), v);
						else
							temp.assign(temp.toidx(i, j, z), temp.toidx(i, j - 1, z));
					}
					else if (dire == RIGHT) {
						if (j == cols)
							temp.set(temp.toidx(i, cols, z), v);
						else
							temp.assign(temp.toidx(i, j, z), temp.toidx(i, j, z));
					}
				}
			}
		}
		return temp;
	}
	template<typename _Tp> inline CvMat::operator _Tp *() {
		return (_Tp*)data();
	}
	template<typename _Tp> inline CvMat::operator const _Tp *() const {
		return (const _Tp*)data();
	}
	template<typename _Tp> inline void CvMat::setv(int32 i, _Tp v) {
#ifdef MAT_DEBUG
		CHECK_INDEX(i, elementlen());
#endif // MAT_DEBUG
		switch (depth()) {
		case lzh::TP_8S:	MAT_GETARRAY(int8, data(), i) = (int8)v;			break;
		case lzh::TP_8U:	MAT_GETARRAY(uint8, data(), i) = (uint8)v;		break;
		case lzh::TP_16S:	MAT_GETARRAY(int16, data(), i) = (int16)v;		break;
		case lzh::TP_16U:	MAT_GETARRAY(uint16, data(), i) = (uint16)v;		break;
		case lzh::TP_32S:	MAT_GETARRAY(int32, data(), i) = (int32)v;		break;
		case lzh::TP_32U:	MAT_GETARRAY(uint32, data(), i) = (uint32)v;		break;
		case lzh::TP_64S:	MAT_GETARRAY(int64, data(), i) = (int64)v;		break;
		case lzh::TP_64U:	MAT_GETARRAY(uint64, data(), i) = (uint64)v;		break;
		case lzh::TP_32F:	MAT_GETARRAY(float32, data(), i) = (float32)v;	break;
		case lzh::TP_64F:	MAT_GETARRAY(float64, data(), i) = (float64)v;	break;
		case lzh::TP_64D:	MAT_GETARRAY(float64_, data(), i) = (float64_)v;	break;
		default:return;
		}
	}


	template<typename _Tp> inline CvMat_<_Tp>::operator _Tp*() {
		return data;
	}
	template<typename _Tp> inline CvMat_<_Tp>::operator const _Tp*() const {
		return data;
	}

	template<typename _Tp> inline _Tp & CvMat_<_Tp>::at(int32 i)
	{
		return ((CvMat*)this)->at<_Tp>(i);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::at(int32 i0, int32 i1)
	{
		return ((CvMat*)this)->at<_Tp>(i0, i1);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::at(int32 i0, int32 i1, int32 i2)
	{
		return ((CvMat*)this)->at<_Tp>(i0, i1, i2);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::at(Point p)
	{
		return ((CvMat*)this)->at<_Tp>(p);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::at(Point3 p)
	{
		return ((CvMat*)this)->at<_Tp>(p);
	}

	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::at(int32 i) const
	{
		return ((const CvMat*)this)->at<_Tp>(i);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::at(int32 i0, int32 i1) const
	{
		return ((const CvMat*)this)->at<_Tp>(i0, i1);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::at(int32 i0, int32 i1, int32 i2) const
	{
		return ((const CvMat*)this)->at<_Tp>(i0, i1, i2);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::at(Point p) const
	{
		return ((const CvMat*)this)->at<_Tp>(p);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::at(Point3 p) const
	{
		return ((const CvMat*)this)->at<_Tp>(p);
	}

	template<typename _Tp> inline _Tp * CvMat_<_Tp>::ptr(int32 i)
	{
		return ((CvMat*)this)->ptr<_Tp>(i);
	}
	template<typename _Tp> inline _Tp * CvMat_<_Tp>::ptr(int32 i0, int32 i1)
	{
		return ((CvMat*)this)->ptr<_Tp>(i0, i1);
	}
	template<typename _Tp> inline _Tp * CvMat_<_Tp>::ptr(int32 i0, int32 i1, int32 i2)
	{
		return ((CvMat*)this)->ptr<_Tp>(i0, i1, i2);
	}
	template<typename _Tp> inline _Tp * CvMat_<_Tp>::ptr(Point p)
	{
		return ((CvMat*)this)->ptr<_Tp>(p);
	}
	template<typename _Tp> inline _Tp * CvMat_<_Tp>::ptr(Point3 p)
	{
		return ((CvMat*)this)->ptr<_Tp>(p);
	}

	template<typename _Tp> inline const _Tp * CvMat_<_Tp>::ptr(int32 i) const
	{
		return ((const CvMat*)this)->ptr<_Tp>(i);
	}
	template<typename _Tp> inline const _Tp * CvMat_<_Tp>::ptr(int32 i0, int32 i1) const
	{
		return ((const CvMat*)this)->ptr<_Tp>(i0, i1);
	}
	template<typename _Tp> inline const _Tp * CvMat_<_Tp>::ptr(int32 i0, int32 i1, int32 i2) const
	{
		return ((const CvMat*)this)->ptr<_Tp>(i0, i1, i2);
	}
	template<typename _Tp> inline const _Tp * CvMat_<_Tp>::ptr(Point p) const
	{
		return ((const CvMat*)this)->ptr<_Tp>(p);
	}
	template<typename _Tp> inline const _Tp * CvMat_<_Tp>::ptr(Point3 p) const
	{
		return ((const CvMat*)this)->ptr<_Tp>(p);
	}

	template<typename _Tp> inline _Tp & CvMat_<_Tp>::operator()(int32 i)
	{
		return at(i);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::operator()(int32 i0, int32 i1)
	{
		return at(i0, i1);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::operator()(int32 i0, int32 i1, int32 i2)
	{
		return at(i0, i1, i2);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::operator()(Point p)
	{
		return at(p);
	}
	template<typename _Tp> inline _Tp & CvMat_<_Tp>::operator()(Point3 p)
	{
		return at(p);
	}

	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::operator()(int32 i) const
	{
		return at(i);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::operator()(int32 i0, int32 i1) const
	{
		return at(i0, i1);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::operator()(int32 i0, int32 i1, int32 i2) const
	{
		return at(i0, i1, i2);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::operator()(Point p) const
	{
		return at(p);
	}
	template<typename _Tp> inline const _Tp & CvMat_<_Tp>::operator()(Point3 p) const
	{
		return at(p);
	}
	template<class _Tp, int32 N>
	inline Vec<_Tp, N>::Vec(const CvMat & m)
	{
		if (m.len() >= N) {
			if (DataType<_Tp>::type == m.depth())
				memcpy(data, m.data, N * sizeof(_Tp));
			else
				for (int32 i = 0; i < N; i++)
					data[i] = _Tp(m(i));
		}
	}

	typedef std::vector<lzh::CvMat>									vec_cvmat;
	typedef std::vector<std::vector<lzh::CvMat>>					vecs_cvmat;


	extern const CvMat operator + (const CvMat & m, Val val);
	extern const CvMat operator + (const CvMat & m, const CvMat & a);
	extern const CvMat operator + (Val val, const CvMat & m);

	extern const CvMat operator - (const CvMat & m);
	extern const CvMat operator - (const CvMat & m, Val val);
	extern const CvMat operator - (const CvMat & m, const CvMat & a);
	extern const CvMat operator - (Val val, const CvMat & m);

	extern const CvMat operator * (const CvMat & m, Val val);
	extern const CvMat operator * (const CvMat & m, const CvMat & a);
	extern const CvMat operator * (Val val, const CvMat & m);

	extern const CvMat operator / (const CvMat & m, Val val);
	extern const CvMat operator / (const CvMat & m, const CvMat & a);
	extern const CvMat operator / (Val val, const CvMat & m);

	extern const CvMat operator ^ (const CvMat & m, Val power);

	extern const CvMat operator ~ (const CvMat & m);
	extern const CvMat operator ! (const CvMat & m);

	extern const CvMat operator & (const CvMat & m, Val val);
	extern const CvMat operator & (const CvMat & m, const CvMat & a);
	extern const CvMat operator & (Val val, const CvMat & m);

	extern const CvMat operator | (const CvMat & m, Val val);
	extern const CvMat operator | (const CvMat & m, const CvMat & a);
	extern const CvMat operator | (Val val, const CvMat & m);

	extern void operator += (CvMat m, Val val);
	extern void operator += (CvMat m, const CvMat & a);

	extern void operator -= (CvMat m, Val val);
	extern void operator -= (CvMat m, const CvMat & a);

	extern void operator *= (CvMat m, Val val);
	extern void operator *= (CvMat m, const CvMat & a);

	extern void operator /= (CvMat m, Val val);
	extern void operator /= (CvMat m, const CvMat & a);

	extern void operator &= (CvMat m, Val val);
	extern void operator &= (CvMat m, const CvMat & a);

	extern void operator |= (CvMat m, Val val);
	extern void operator |= (CvMat m, const CvMat & a);
}

#endif //__CVMAT_H__
