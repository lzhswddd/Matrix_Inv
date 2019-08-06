#include "LargeNumber.h"
#include "Variable.h"
using namespace lzh;

/****************************************************************************
������
*****************************************************************************/
LargeNumber::LargeNumber() : vec_8s()
{
}
LargeNumber::LargeNumber(int8 ch) : vec_8s(1)
{
	if (ch >= '0' && ch <= '9')
		at(0) = ch - '0';
	else if (ch >= 0 && ch <= 9)
		at(0) = ch;
	else
		clear();
}
LargeNumber::LargeNumber(uint8 val) : vec_8s()
{
	if (val == 0) {
		push_back(0);
	}
	else {
		while (val)
		{
			push_back(val % 10);
			val /= 10;
		}
		reverse(begin(), end());
	}
}
LargeNumber::LargeNumber(int32 val) : vec_8s()
{
	if (val == 0) {
		push_back(0);
	}
	else {
		while (val)
		{
			push_back(val % 10);
			val /= 10;
		}
		reverse(begin(), end());
	}
}
LargeNumber::LargeNumber(int64 val) : vec_8s()
{
	if (val == 0) {
		push_back(0);
	}
	else {
		while (val)
		{
			push_back(val % 10);
			val /= 10;
		}
		reverse(begin(), end());
	}
}
LargeNumber::LargeNumber(uint32 val) : vec_8s()
{
	if (val == 0) {
		push_back(0);
	}
	else {
		while (val)
		{
			push_back(val % 10);
			val /= 10;
		}
		reverse(begin(), end());
	}
}
LargeNumber::LargeNumber(uint64 val) : vec_8s()
{
	if (val == 0) {
		push_back(0);
	}
	else {
		while (val)
		{
			push_back(val % 10);
			val /= 10;
		}
		reverse(begin(), end());
	}
}
LargeNumber::LargeNumber(const int8 *str) : vec_8s()
{
	uint32 ind = 0;
	while (str[ind] != '\0')
		ind++;
	resize(ind);
	_FOR(i, 0, ind, 1) {
		if ((str[i]<'0' || str[i]>'9') && str[i] != '-')
			continue;
		at(i) = (str[i] == '-' ? str[i] : str[i] - '0');
	}
}
LargeNumber::LargeNumber(std::string str) : vec_8s()
{
	if (str.empty())return;
	resize(str.size());
	_FOR(i, 0, str.size(), 1) {
		if ((str[i]<'0' || str[i]>'9') && str[i] != '-')
			continue;
		at(i) = (str[i] == '-' ? str[i] : str[i] - '0');
	}
}
LargeNumber::LargeNumber(int32 * ptr, int32 n) : vec_8s()
{
	if (ptr == nullptr)return;
	_FOR(i, 0, n, 1) {
		std::string str = std::to_string(ptr[i]);
		_FOR(j, 0, str.size(), 1) {
			if ((str[j]<'0' || str[j]>'9') && str[j] != '-')
				continue;
			push_back(str[j] == '-' ? str[j] : str[j] - '0');
		}
	}
}
const LargeNumber lzh::operator-(const LargeNumber& ln)
{
	LargeNumber a = ln;
	if (a[0] == '-')
		a.erase(a.begin());
	else
		a.insert(a.begin(), '-');
	return a;
}
bool lzh::operator < (const LargeNumber& a, const LargeNumber& b)
{
	if (b[0] == '-' && a[0] != '-')return false;
	else if (b[0] != '-' && a[0] == '-')return true;
	else if (b[0] == '-' && a[0] == '-') {
		if (b.size() > a.size())return false;
		else if (b.size() < a.size())return true;
		else {
			_FOR(i, 0, a.size(), 1) {
				if (b[i] < a[i])return true;
				else if (b[i] > a[i])return false;
			}
			return false;
		}
	}
	else {
		if (b.size() > a.size())return true;
		else if (b.size() < a.size())return false;
		else {
			_FOR(i, 0, a.size(), 1) {
				if (b[i] < a[i])return false;
				else if (b[i] > a[i])return true;
			}
			return false;
		}
	}
}
bool lzh::operator > (const LargeNumber& a, const LargeNumber& b)
{
	if (b[0] == '-' && a[0] != '-')return true;
	else if (b[0] != '-' && a[0] == '-')return false;
	else if (b[0] == '-' && a[0] == '-') {
		if (b.size() > a.size())return true;
		else if (b.size() < a.size())return false;
		else {
			_FOR(i, 0, a.size(), 1) {
				if (b[i] < a[i])return false;
				else if (b[i] > a[i])return true;
			}
			return false;
		}
	}
	else {
		if (b.size() > a.size())return false;
		else if (b.size() < a.size())return true;
		else {
			_FOR(i, 0, a.size(), 1) {
				if (b[i] < a[i])return true;
				else if (b[i] > a[i])return false;
			}
			return false;
		}
	}
}
bool lzh::operator <= (const LargeNumber& a, const LargeNumber& b)
{
	return !(a > b);
}
bool lzh::operator >= (const LargeNumber& a, const LargeNumber& b)
{
	return !(a < b);
}
bool lzh::operator == (const LargeNumber& a, const LargeNumber& b)
{
	if (b[0] == '-' && a[0] != '-')return false;
	else if (b[0] != '-' && a[0] == '-')return false;
	else if (b[0] == '-' && a[0] == '-') {
		if (b.size() > a.size())return false;
		else if (b.size() < a.size())return false;
		else {
			_FOR(i, 0, a.size(), 1) {
				if (b[i] < a[i])return false;
				else if (b[i] > a[i])return false;
			}
			return true;
		}
	}
	else {
		if (b.size() > a.size())return false;
		else if (b.size() < a.size())return false;
		else {
			_FOR(i, 0, a.size(), 1) {
				if (b[i] < a[i])return false;
				else if (b[i] > a[i])return false;
			}
			return true;
		}
	}
}
void lzh::operator+=(LargeNumber & a, const LargeNumber & b)
{
	a = a + b;
}
void lzh::operator-=(LargeNumber & a, const LargeNumber & b)
{
	a = a - b;
}
void lzh::operator*=(LargeNumber & a, const LargeNumber & b)
{
	a = a * b;
}
void lzh::operator/=(LargeNumber & a, const LargeNumber & b)
{
	a = a / b;
}
const LargeNumber lzh::operator +(const LargeNumber& a_, const LargeNumber& b_)
{
	LargeNumber a = a_;
	LargeNumber b = b_;
	if (a[0] == '-'&&b[0] == '-') {
		LargeNumber tempa;
		LargeNumber tempb;
		a.swap(tempa);
		b.swap(tempb);
		tempa.erase(tempa.begin());
		tempb.erase(tempb.begin());
		LargeNumber temp = tempa + tempb;
		temp.insert(temp.begin(), '-');
		return temp;
	}
	else if (a[0] == '-') {
		LargeNumber tempa = a;
		tempa.erase(tempa.begin());
		LargeNumber temp = b - tempa;
		return temp;
	}
	else if (b[0] == '-') {
		LargeNumber tempb = b;
		tempb.erase(tempb.begin());
		LargeNumber temp = a - tempb;
		return temp;
	}
	bool max_object = (a.size() > b.size() ? true : false);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	varray len_max = (a.size() > b.size() ? a.size() : b.size());
	varray len_min = (len_max == a.size() ? b.size() : a.size());
	LargeNumber s_data;
	int32 iscarry = 0;
	_FOR(i, 0, len_min, 1) {
		s_data.push_back((a[i] + b[i] + iscarry) % 10);
		iscarry = (a[i] + b[i] + iscarry) / 10;
	}
	_FOR(i, len_min, len_max, 1) {
		s_data.push_back(((max_object ? a[i] : b[i]) + iscarry) % 10);
		iscarry = ((max_object ? a[i] : b[i]) + iscarry) / 10;
	}
	if (iscarry) {
		s_data.push_back(iscarry);
	}
	reverse(s_data.begin(), s_data.end());
	return s_data;
}
const LargeNumber lzh::operator -(const LargeNumber& a_, const LargeNumber& b_)
{
	LargeNumber a = a_;
	LargeNumber b = b_;
	bool isNegative = false;
	int32 iscarry = 0;
	bool max_object = (a.size() > b.size() ? true : false);
	LargeNumber tempa = a;
	LargeNumber tempb = b;
	if (tempa[0] == '-')
		tempa.erase(tempa.begin());
	if (tempb[0] == '-')
		tempb.erase(tempb.begin());
	if (tempa < tempb) {
		LargeNumber temp = b - a;
		temp.insert(temp.begin(), '-');
		return temp;
	}
	else if (a == b)return LargeNumber("0");
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	varray len_max = (a.size() > b.size() ? a.size() : b.size());
	varray len_min = (len_max == a.size() ? b.size() : a.size());
	LargeNumber s_data;
	_FOR(i, 0, len_min, 1) {
		int8 val = a[i] - iscarry;
		int8 num = (val < 0 ? (10 + val) : val) - b[i];
		if (val > 0 && iscarry != 0)
			iscarry -= 1;
		s_data.push_back(((num < 0 ? (-num / 10 + 1) * 10 : 0) + num) % 10);
		iscarry += (num < 0 ? (-num / 10 + 1) : 0);
	}
	_FOR(i, len_min, len_min + len_max - len_min, 1) {
		if (iscarry) {
			int8 val = max_object ? a[i] : b[i] - iscarry;
			int8 num = (val < 0 ? (10 + val) : val);
			if (val > 0 && iscarry != 0)
				iscarry -= 1;
			s_data.push_back(((num < 0 ? (-num / 10 + 1) * 10 : 0) + num) % 10);
			iscarry += (num < 0 ? (-num / 10 + 1) : 0);
		}
		else
			s_data.push_back(max_object ? a[i] : b[i]);
	}
	reverse(s_data.begin(), s_data.end());
	return s_data;
}
const LargeNumber lzh::operator *(const LargeNumber& a_, const LargeNumber& b_)
{
	LargeNumber a = a_;
	LargeNumber b = b_;
	bool isan = false;
	bool isbn = false;
	if (a[0] == '-')isan = true;
	if (b[0] == '-')isbn = true;
	if (isan)a.erase(a.begin());
	if (isbn)b.erase(b.begin());
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	LargeNumber sum;
	_FOR(i, isbn ? 1 : 0, b.size(), 1) {
		if (b[i] == 0)continue;
		int8 iscarry = 0;
		LargeNumber s_data;
		_FOR(j, isan ? 1 : 0, a.size(), 1) {
			s_data.push_back((a[j] * b[i] + iscarry) % 10);
			iscarry = (a[j] * b[i] + iscarry) / 10;
		}
		if (iscarry != 0)
			s_data.push_back(iscarry);
		reverse(s_data.begin(), s_data.end());
		_FOR(k, 0, isbn ? i - 1 : i, 1)
			s_data.push_back(0);
		if (sum.size() == 0)
			sum = s_data;
		else
			sum = sum + s_data;
	}
	if ((isan || isbn) && !(isan && isbn))
		sum.insert(sum.begin(), '-');
	return sum;
}
const LargeNumber lzh::operator /(const LargeNumber& a_, const LargeNumber& b_)
{
	int32 i, j;
	int32 nTimes;//���������λ��
	int32 nTemp;//Subtract��������ֵ
	bool isan = false;
	bool isbn = false;
	LargeNumber a = a_;
	LargeNumber b = b_;
	if (a[0] == '-')isan = true;
	if (b[0] == '-')isbn = true;
	if (isan)a.erase(a.begin());
	if (isbn)b.erase(b.begin());
	int32 len1 = (int32)a.size();//��ô�����λ��
	int32 len2 = (int32)b.size();
	int32 len = len1 < len2 ? len2 : len1;
	int32 *num_a = new int32[len];//������
	int32 *num_b = new int32[len];//����
	int32 *num_c = new int32[len];//��
	memset(num_a, 0, sizeof(int32)*len);
	memset(num_b, 0, sizeof(int32)*len);
	memset(num_c, 0, sizeof(int32)*len);
	for (j = 0, i = len1 - 1; i >= 0; j++, i--)
		num_a[j] = a[i];  //���ַ���ת���ɶ�Ӧ������,�ߵ��洢
	for (j = 0, i = len2 - 1; i >= 0; j++, i--)
		num_b[j] = b[i];

	if (len1 < len2)   //���������С�ڳ��������Ϊ0
	{
		printf("0\n");
		return "0";   //����continueֱ����������ѭ���� ������һ�����
	}
	nTimes = len1 - len2;    //���λ��
	for (i = len1 - 1; i >= 0; i--)    //����������ʹ�ó����ͱ�����λ�����
	{
		if (i >= nTimes)
			num_b[i] = num_b[i - nTimes];
		else                     //��λ��0
			num_b[i] = 0;
	}
	len2 = len1;
	for (j = 0; j <= nTimes; j++)      //�ظ����ã�ͬʱ��¼���ɹ��Ĵ�������Ϊ��
	{
		while ((nTemp = LargeNumber::SubStract(num_a, num_b + j, len1, len2 - j)) >= 0)
		{
			len1 = nTemp;      //�������
			num_c[nTimes - j]++;//ÿ�ɹ���һ�Σ����̵���Ӧλ��1
		}
	}
	//������
	for (i = len - 1; num_c[i] == 0 && i >= 0; i--);//������λ0
	LargeNumber div(num_c, i + 1);
	if ((isan || isbn) && !(isan && isbn))
		div.insert(div.begin(), '-');
	FREE_ARRAY(num_a);
	FREE_ARRAY(num_b);
	FREE_ARRAY(num_c);
	return div;
}
int32 lzh::LargeNumber::SubStract(int32 * p1, int32 * p2, int32 len1, int32 len2)

{
	int32 i;
	if (len1 < len2)
		return -1;
	if (len1 == len2)
	{                        //�ж�p1 > p2
		for (i = len1 - 1; i >= 0; i--)
		{
			if (p1[i] > p2[i])   //������������������������
				break;
			else if (p1[i] < p2[i]) //���򷵻�-1
				return -1;
		}
	}
	for (i = 0; i <= len1 - 1; i++)  //�ӵ�λ��ʼ������
	{
		p1[i] -= p2[i];
		if (p1[i] < 0)          //��p1<0������Ҫ��λ
		{
			p1[i] += 10;         //��1��10
			p1[i + 1]--;           //��λ��1
		}
	}
	for (i = len1 - 1; i >= 0; i--)       //���ҽ�������λ
		if (p1[i])                  //���λ��һ����Ϊ0
			return (i + 1);       //�õ�λ��������
	return 0;                  //������ȵ�ʱ�򷵻�0
}

void lzh::LargeNumber::show() const
{
	show(std::cout);
	std::cout << std::endl;
}
void lzh::LargeNumber::show(std::ostream & out)const
{
	for (int8 ch : *this)
		out << (int8)(ch == '-' ? ch : ch + '0');
}