#pragma once
#ifndef __CVMAT_H__
#define __CVMAT_H__

#include "Variable.h"

namespace lzh
{
	/**
	�ڴ������
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
		����w_������
		@param w		��������
		*/
		CvMat(int32 w, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����w_*h_�ľ���
		@param w		��������
		@param h		��������
		*/
		CvMat(int32 w, int32 h, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����h_*w_*depth�ľ���
		@param w		��������
		@param h		��������
		@param c		����ͨ����
		*/
		CvMat(int32 w, int32 h, int32 c, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����size*1�ľ���
		@param size	����ߴ�
		*/
		CvMat(Size size, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����size*c�ľ���
		@param size	����ߴ�
		*/
		CvMat(Size size, int32 c, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����size�ľ���
		@param size	����ߴ�
		*/
		CvMat(Size3 size, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����ָ��ɫ��, ��СΪsize�ľ���
		@param colorGamut	ָ��ɫ��
		*/
		CvMat(ColorGamut colorGamut, Size size, int32 flags);
		/**
		��������
		*/
		CvMat(const PtrMat &src, Size3 sz, bool copyData = false);
		/**
		�������
		*/
		CvMat(const void * p, Size3 sz, int32 flags);
		/**
		��������
		@param src		��������
		*/
		CvMat(const CvMat &src);
		/**
		���ö���
		@param inputarray	�ӿ�����
		*/
		CvMat(const _InputArray & inputarray);
		/**
		������a��b�ϲ�(COLΪ���кϲ�|ROWΪ���кϲ�)
		@param a		�������1
		@param b		�������2
		@param merge	�ϲ���ʽ
		*/
		CvMat(const lzh::CvMat &a, const lzh::CvMat &b, RANK merge);
		/**
		���캯��
		���m
		@param m ����
		*/
		template<typename _Tp> CvMat(const MatCommaInitializer_<_Tp> &m);
		/**
		����1*w*1������,Ԫ��Ϊdata
		@param w		����
		@param data		����
		*/
		CvMat(int32 w, const void *data, int32 flags, bool copyData = false);
		/**
		����h*w*1�ľ���,Ԫ��Ϊdata
		@param w		��������
		@param h		��������
		@param data		����Ԫ��
		*/
		CvMat(int32 w, int32 h, const void *data, int32 flags, bool copyData = false);
		/**
		����h*w*c�ľ���,Ԫ��Ϊdata
		@param w		��������
		@param h		��������
		@param c		����ͨ����
		@param data		����Ԫ��
		*/
		CvMat(int32 w, int32 h, int32 c, const void *data, int32 flags, bool copyData = false);
		/**
		����size������,Ԫ��Ϊdata
		@param size		�ߴ�
		@param data		����
		*/
		CvMat(Size size, const void *data, int32 flags, bool copyData = false);
		/**
		����size������,Ԫ��Ϊdata
		@param size		�ߴ�
		@param data		����
		*/
		CvMat(Size size, int32 c, const void *data, int32 flags, bool copyData = false);
		/**
		����size������,Ԫ��Ϊdata
		@param size		�ߴ�
		@param data		����
		*/
		CvMat(Size3 size, const void *data, int32 flags, bool copyData = false);
		/**
		����h*w*c�ľ���,Ԫ��Ϊdata
		@param w		��������
		@param h		��������
		@param c		����ͨ����
		@param step		����
		@param data		����Ԫ��
		*/
		CvMat(int32 w, int32 h, int32 c, MatStep step, const void *data, int32 flags);
		/**
		����size�ľ���
		Mat m(Size(10), 1,2,3,4,5,6,7,8,9,10);
		@param size		�����С
		@param v		��һ������(ȷ������)
		@param ...		��������
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
		����w������
		@param w		����
		*/
		void create(int32 w, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����w*h�ľ���
		@param w		����
		@param h		����
		*/
		void create(int32 w, int32 h, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����w*h*c������
		@param w		����
		@param h		����
		@param c		ͨ����
		*/
		void create(int32 w, int32 h, int32 c, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����size�ľ���
		@param size		�����С
		*/
		void create(Size size, int32 flags, ColorGamut cg = ColorGamutCustom);
		/**
		����size������
		@param size		�����С
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
		@brief �ڴ泤��
		*/
		uint32 memsize()const;
		/**
		@brief ���ά��
		*/
		void DimCheck()const;
		/**
		@brief ���ؾ���ߴ�(h_,w_,c_)
		*/
		Size3 size3()const;
		/**
		@brief ���ؾ���ƫ��
		*/
		int32 total()const;
		/**
		@brief ���ؾ���ƫ��
		*/
		int32 total_()const;
		/**
		@brief ����ά��
		*/
		int32 dims()const;
		/**
		@brief ���ز���
		*/
		MatStep step()const;
		/**
		@brief ����
		*/
		Point center()const;
		/**
		@brief ��������
		*/
		int32 depth()const;
		/**
		@brief ��������
		*/
		int32 type()const;
		/**
		@brief ����ͨ����
		*/
		int32 channels()const;
		/**
		@brief ��������
		*/
		int32 rank()const;
		/**
		@brief ����ɫ��
		*/
		ColorGamut colorGamut()const;
		/**
		@brief ���ؾ����СSize(h_,w_)
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
		�������
		@param file		�����ļ���
		@param binary	ѡ���ı����Ƕ�����
		binary = false	ѡ���ı�
		binary = true	ѡ�������
		*/
		void save(std::string file, bool binary = true)const;
		/**
		�����Ʊ������
		@param file		�����ļ�ָ��
		*/
		void save(FILE *file)const;
		/**
		��ȡ����
		@param file		��ȡ�ļ���
		ֻ֧�ֶ����ƶ�ȡ
		*/
		void load(std::string file);
		/**
		��ȡ����
		@param file		��ȡ�ļ�ָ��
		ֻ֧�ֶ����ƶ�ȡ
		*/
		void load(FILE *file);
		/**
		@brief ���ؾ����С(h_*w_*c_)
		*/
		int32 len()const;
		/**
		@brief ���ؾ����С(h_*w_*c_)
		*/
		int32 elementlen()const;
		/**
		@brief ���ؾ���״̬
		0Ϊ����
		-1Ϊ�վ���
		-2Ϊ�Ƿ���
		*/
		int32 enable()const;
		/**
		@brief ���ؾ����Ƿ�Ϊ��
		*/
		bool empty()const;
		/**
		@brief ���ؾ����Ƿ�Ϊ����
		*/
		bool Square()const;
		/**
		���������mat
		@param mat		����
		*/
		void copyTo(CvMat& mat)const;
		/**
		���ݸ��ǵ�mat
		@param mat		����
		*/
		void setTo(CvMat mat)const;
		/**
		����ת��
		@param m		���
		@param type		��������
		*/
		void convertTo(CvMat &m, int32 type)const;
		/**
		����ת��
		@brief ����type�������;���
		@param type		��������
		*/
		const CvMat convert(int32 type)const;
		/**
		�ھ�������߻����ұ����һ��1
		@param dire		ѡ����ӷ�ʽ
		*/
		void setAddOnes(Dire dire = RIGHT);
		/**
		�ھ�������߻����ұ����һ��0
		@param dire		ѡ����ӷ�ʽ
		*/
		void setAddZeros(Dire dire = RIGHT);
		/**
		�ͷ��ڴ�
		*/
		void release();
		/**
		@brief ���������ؾ���Ԫ��
		@param w		����
		*/
		template<typename _Tp> _Tp& at(int32 w);
		/**
		@brief ���������ؾ���Ԫ��
		@param w		������
		@param h		������
		*/
		template<typename _Tp> _Tp& at(int32 h, int32 w);
		/**
		@brief ���������ؾ���Ԫ��
		@param w		������
		@param h		������
		@param c		ͨ������
		*/
		template<typename _Tp> _Tp& at(int32 h, int32 w, int32 c);
		/**
		@brief ���ض�Ӧ����Ԫ��
		@param p ����
		*/
		template<typename _Tp> _Tp& at(Point p);
		/**
		@brief ���ض�Ӧ����Ԫ��
		@param p ����
		*/
		template<typename _Tp> _Tp& at(Point3i p);
		/**
		@brief ���������ؾ���Ԫ��
		@param w		����
		*/
		template<typename _Tp> const _Tp& at(int32 w)const;
		/**
		@brief ���������ؾ���Ԫ��
		@param w		������
		@param h		������
		*/
		template<typename _Tp> const _Tp& at(int32 h, int32 w)const;
		/**
		@brief ���������ؾ���Ԫ��
		@param w		������
		@param h		������
		@param c		ͨ������
		*/
		template<typename _Tp> const _Tp& at(int32 h, int32 w, int32 c)const;
		/**
		@brief ���ض�Ӧ����Ԫ��
		@param p ����
		*/
		template<typename _Tp> const _Tp& at(Point p)const;
		/**
		@brief ���ض�Ӧ����Ԫ��
		@param p ����
		*/
		template<typename _Tp> const _Tp& at(Point3i p)const;
		/**
		@brief ������ת��Ϊ��Ӧ����������
		@param index	����
		*/
		int32 toX(int32 index)const;
		/**
		@brief ������ת��Ϊ��Ӧ����������
		@param index	����
		*/
		int32 toY(int32 index)const;
		/**
		@brief ������ת��Ϊ��Ӧ����ͨ������
		@param index	����
		*/
		int32 toZ(int32 index)const;

		/**
		@brief ���ؾ�����value��ȵĵ�һ��Ԫ������
		@param value	Ԫ��
		*/
		template<typename _Tp>
		int32 find(_Tp value)const;
		/**
		@brief ���ؾ���Ԫ�����ֵ������
		*/
		int32 maxAt()const;
		/**
		@brief ���ؾ���Ԫ����Сֵ������
		*/
		int32 minAt()const;
		/**
		@brief ���ؾ����Ƿ����value
		@param value	Ԫ��
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
		@brief ���ؾ�������ֵ
		@param is_abs	�Ƿ����ֵ
		*/
		mat_t Max(bool is_abs = false)const;
		/**
		@brief ���ؾ������Сֵ
		@param is_abs	�Ƿ����ֵ
		*/
		mat_t Min(bool is_abs = false)const;
		/**
		@brief ���ؾ���Ԫ�����ֵ
		*/
		template<typename _Tp> _Tp& findmax();
		/**
		@brief ���ؾ���Ԫ����Сֵ
		*/
		template<typename _Tp> _Tp& findmin();
		/**
		@brief �������������򿽱�Ԫ�ص�src������
		@param src			����������
		@param Row_Start	��ȡ�г�ʼ����ֵ
		@param Row_End		��ȡ�н�������ֵ
		@param Col_Start	��ȡ�г�ʼ����ֵ
		@param Col_End		��ȡ�н�������ֵ
		*/
		void copy(CvMat &src, int32 Row_Start, int32 Row_End, int32 Col_Start, int32 Col_End)const;
		/**
		@brief �����󿽱���src
		@param src ����������
		*/
		void swap(CvMat &src)const;
		/**
		@brief mChannel ��src���ǵ���c_ͨ��
		@param src		����
		@param c_	ͨ����
		*/
		void mChannel(const lzh::CvMat &src, int32 c);
		/**
		@brief mChannel ��src���ǵ���c_ͨ��
		@param src		����
		@param c_	ͨ����
		*/
		void mChannel(const lzh::CvMat &src, int32 w, int32 h);
		/**
		@brief ���þ���ά��
		������ı���󳤶�
		@param size		�����С
		*/
		void reshape(Size3 size);
		/**
		@brief ���þ���ά��
		������ı���󳤶�
		@param h_		��������
		@param w_		��������
		@param c_	����ͨ��
		*/
		void reshape(int32 w, int32 h, int32 c);
		/**
		@brief ���þ����С
		�������ԭ��С������h_*w_*1��Ԫ��ȫ������Ϊ0
		@param h_	��������
		@param w_	��������
		*/
		bool setSize(int32 w, int32 h, int32 c);
		/**
		@brief ��������src
		@param src	��������
		*/
		void setvalue(const lzh::CvMat &src);
		/**
		@brief ���������
		*/
		void setInv();
		/**
		@brief ���þ����num����
		@param num	����
		*/
		void setPow(mat_t num);
		/**
		@brief ���õ�λ����
		*/
		void setIden();
		/**
		@brief ���ð������
		*/
		void setAdj();
		/**
		@brief ����ת�þ���
		*/
		void setTran();
		/**
		����ɫ��
		@param cg	ָ��ɫ��
		*/
		void setColorGamut(ColorGamut cg);

		/**
		@brief �������������
		*/
		void show()const;
		/**
		@brief �������
		*/
		std::ostream & show(std::ostream & out)const;

		/**
		@brief ����h�о���
		@param ����
		*/
		CvMat row(int32 h);
		/**
		@brief ����h�о���
		@param ����
		*/
		const CvMat row(int32 h)const;
		/**
		@brief ����w�о���
		@param ����
		*/
		CvMat col(int32 w);
		/**
		@brief ����w�о���
		@param ����
		*/
		const CvMat col(int32 w)const;
		/**
		@brief ����cͨ������
		@param ͨ������
		*/
		CvMat channel(int32 c);
		/**
		@brief ����cͨ������
		@param ͨ������
		*/
		const CvMat channel(int32 c)const;
		template<typename _Tp> const CvMat addvalue(Dire dire, _Tp v) const;
		/**
		@brief �ھ�������߻����ұ����һ��1
		@param dire		ѡ����ӷ�ʽ
		*/
		const CvMat addones(Dire dire = RIGHT)const;
		/**
		@brief �ھ�������߻����ұ����һ��0
		@param dire		ѡ����ӷ�ʽ
		*/
		const CvMat addzeros(Dire dire = RIGHT)const;
		/**
		@brief ����start��end����
		@param start	��ʼ����
		@param end		��������
		*/
		const CvMat range(int32 start, int32 end)const;
		/**
		@brief ����roi��Χ�ľ���
		@param roi	��ʼ����
		*/
		const CvMat range(Rect roi)const;
		/**
		@brief ����roi��Χ�ľ���
		@param roi	��ʼ����
		*/
		const CvMat range(int32 h_start, int32 h_end, int32 w_start, int32 w_end)const;
		/**
		@brief ����h_start��h_end�о���
		@param h_start	�п�ʼ����
		@param h_end	�н�������
		*/
		const CvMat rowRange(int32 h_start, int32 h_end)const;
		/**
		@brief ����w_start��w_end�о���
		@param w_start	�п�ʼ����
		@param w_end	�н�������
		*/
		const CvMat colRange(int32 w_start, int32 w_end)const;
		/**
		@brief ����c_start��c_endͨ������
		@param c_start	ͨ����ʼ����
		@param c_end	ͨ����������
		*/
		const CvMat channelRange(int32 c_start, int32 c_end)const;
		/**
		@brief �����������
		*/
		const CvMat clone()const;
		/**
		@brief ����ȡ������
		*/
		const CvMat opp()const;
		/**
		@brief ���ؾ���ֵ����
		*/
		const CvMat abs()const;
		/**
		@brief ���ذ�num���ݾ���
		@param num ����
		*/
		const CvMat mPow(int32 num)const;
		/**
		@brief ���ذ�num���ݾ���
		@param num ����
		*/
		const CvMat pow(mat_t num)const;
		/**
		@brief ���ذ�Ԫ��ȡָ������
		*/
		const CvMat exp()const;
		/**
		@brief ���ذ�Ԫ��ȡ��������
		*/
		const CvMat log()const;
		/**
		@brief ���ذ�Ԫ��ȡ��������
		*/
		const CvMat sqrt()const;
		/**
		@brief ���ذ������
		*/
		const CvMat adj()const;
		/**
		@brief ����ת�þ���
		*/
		const CvMat t()const;
		/**
		@brief ���������
		*/
		const CvMat inv()const;
		/**
		@brief ���������
		*/
		const CvMat diag(int32 k = 0)const;
		/**
		@brief �����������
		�������������
		*/
		const CvMat reverse()const;
		/**
		@brief ������������(δ���)
		*/
		const CvMat EigenvectorsMax(mat_t offset = 1e-8)const;
		/**
		@brief sigmoid����
		*/
		const CvMat sigmoid()const;
		/**
		@brief tanh����
		*/
		const CvMat tanh()const;
		/**
		@brief relu����
		*/
		const CvMat relu()const;
		/**
		@brief elu����
		*/
		const CvMat elu()const;
		/**
		@brief selu����
		*/
		const CvMat selu()const;
		/**
		@brief leaky_relu����
		*/
		const CvMat leaky_relu()const;
		/**
		@brief softmax����
		*/
		const CvMat softmax()const;
		/**
		@brief ��������ʽ
		*/
		mat_t Det();
		/**
		@brief ����num����
		@param num ������
		*/
		mat_t norm(int32 num = 1)const;
		/**
		@brief ���ض�Ӧ����������ʽ
		@param x ������
		@param y ������
		*/
		mat_t Cof(int32 x, int32 y);
		mat_t EigenvalueMax(mat_t offset = 1e-8)const;
		/**
		@brief ���ؾ���Ԫ�غ�
		@param num	���ô���
		@param _abs �Ƿ�ȡ����ֵ
		*/
		mat_t sum(int32 num = 1, bool _abs = false)const;
		/**
		@brief ����ƽ��ֵ
		*/
		mat_t mean()const;
		/**
		@brief ���ر�׼��
		*/
		mat_t std()const;
		/**
		@brief ���ر�׼��
		*/
		mat_t D()const;
		/**
		@brief ���������=
		����
		*/
		CvMat & operator = (const CvMat &temp);
		/**
		@brief ���������=
		����
		*/
		CvMat & operator = (const Mat &temp);
		/**
		@brief ���������==
		�жϾ����Ƿ����
		*/
		bool operator == (const lzh::CvMat &a)const;
		/**
		@brief ���������!=
		�жϾ����Ƿ����
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
		@brief ���ؾ����Ӧ�������л���
		@param index	����
		@param rc		������ʽ
		*/
		CvMat operator () (int32 index, RANK rc)const;
		/**
		@brief ���ؾ����Ӧ�������л���
		@param index	����
		@param rc		������ʽ
		*/
		CvMat operator () (int32 v1, int32 v2, RANK rc)const;
		/**
		@brief ���ؾ����Ӧ�������л���
		@param index	����
		@param rc		������ʽ
		*/
		CvMat cut(int32 index, RANK rc)const;
		/**
		@brief ���ؾ����Ӧ�������л���
		@param index	����
		@param rc		������ʽ
		*/
		CvMat cut(int32 v1, int32 v2, RANK rc)const;

		const CvMat operator [] (int32 idx) const;

		bool operator > (const CvMat &b) const;
		bool operator < (const CvMat &b) const;

		template<typename _Tp> operator _Tp *();
		template<typename _Tp> operator const _Tp *() const;

		/**
		@brief ����Ԫ��Ϊ0��w����
		@param w		��������
		*/
		static const CvMat zeros(int32 w, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ0��h*w����
		@param w		��������
		@param h		��������
		*/
		static const CvMat zeros(int32 w, int32 h, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ0��h*w*c����
		@param w		��������
		@param h		��������
		@param c		����ͨ����
		*/
		static const CvMat zeros(int32 w, int32 h, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ0��size����
		@param size �����С
		*/
		static const CvMat zeros(Size size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ0��size����
		@param size �����С
		*/
		static const CvMat zeros(Size size, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ0��size����
		@param size �����С
		*/
		static const CvMat zeros(Size3 size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊv��w����
		@param v		���Ԫ��
		@param w		��������
		*/
		static const CvMat value(Val v, int32 w, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊv��h*w����
		@param v		���Ԫ��
		@param w		��������
		@param h		��������
		*/
		static const CvMat value(Val v, int32 w, int32 h, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊv��h_*w_*c_����
		@param v		���Ԫ��
		@param w		��������
		@param h		��������
		@param c		����ͨ����
		*/
		static const CvMat value(Val v, int32 w, int32 h, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ1��w����
		@param w		��������
		*/
		static const CvMat ones(int32 w, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ1��h*w����
		@param w	��������
		@param h	��������
		*/
		static const CvMat ones(int32 w, int32 h, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ1��h*w*c����
		@param w		��������
		@param h		��������
		@param c		����ͨ����
		*/
		static const CvMat ones(int32 w, int32 h, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ1��size����
		@param size �����С
		*/
		static const CvMat ones(Size size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ1��size����
		@param size �����С
		*/
		static const CvMat ones(Size size, int32 c, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief ����Ԫ��Ϊ1��size����
		@param size �����С
		*/
		static const CvMat ones(Size3 size, int32 flag, ColorGamut cg = ColorGamutCustom);
		/**
		@brief �������ɵ�n*n*1��λ����
		@param n �����С
		*/
		static const CvMat eye(int32 n, int32 flag);


		/**
		���ô�ӡ���
		@param w ���
		*/
		static void setPrintW(uint32 w);
		/**
		���ô�ӡ��Ч����
		@param n λ��
		*/
		static void setPrintSignificantDigits(uint32 n);
		/**
		���ô�ӡ����
		@param t ��ӡ����
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
	@brief CvMat_ ������
	�̳�Mat�࣬����ʵ��
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
		@brief ����w������
		@param w		����
		*/
		CvMat_(int32 w) : CvMat(w, DataType<_Tp>::type) {}
		/**
		@brief ����h*w�ľ���
		@param w		����
		@param h		����
		*/
		CvMat_(int32 w, int32 h) : CvMat(w, h, DataType<_Tp>::type) {}
		/**
		@brief ����h*w*c������
		@param w		����
		@param h		����
		@param depth	ͨ����
		*/
		CvMat_(int32 w, int32 h, int32 c) : CvMat(w, h, c, DataType<_Tp>::type) {}
		/**
		@brief ����size�ľ���
		@param size		�ߴ�
		*/
		CvMat_(Size size) : CvMat(size, DataType<_Tp>::type) {}
		/**
		@brief ����size�ľ���
		@param size		�ߴ�
		*/
		CvMat_(Size size, int32 c) : CvMat(size, c, DataType<_Tp>::type) {}
		/**
		@brief ����size�ľ���
		@param size		�ߴ�
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
	@brief MatCommaInitializer_ ������
	��Ϊ������������ʵ��
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
