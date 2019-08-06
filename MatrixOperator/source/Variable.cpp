#include "Variable.h"
using namespace lzh;

size_t lzh::alignSize(size_t sz, int32 n) {
	return (sz + n - 1) & -n;
}

void * lzh::fastMalloc(size_t size) {
	uint8 *udata = (uint8 *)malloc(size + sizeof(void *) + MALLOC_ALIGN);
	if (!udata)
		return 0;
	uint8 **adata = alignPtr((uint8 **)udata + 1, MALLOC_ALIGN);
	adata[-1] = udata;
	return adata;
}

void lzh::fastFree(void * data) {
	if (data) {
		uint8 *udata = ((uint8 **)data)[-1];
		free(udata);
	}
}

uint32 lzh::calmemsize(int32 type)
{
	switch (type) {
	case lzh::TP_8S:	return sizeof(int8);
	case lzh::TP_8U:	return sizeof(uint8);
	case lzh::TP_16S:	return sizeof(int16);
	case lzh::TP_16U:	return sizeof(uint16);
	case lzh::TP_32S:	return sizeof(int32);
	case lzh::TP_32U:	return sizeof(uint32);
	case lzh::TP_64S:	return sizeof(int64);
	case lzh::TP_64U:	return sizeof(uint64);
	case lzh::TP_32F:	return sizeof(float32);
	case lzh::TP_64F:	return sizeof(float64);
	case lzh::TP_64D:	return sizeof(float64_);
	default:THROW_INFO(ERR_INFO_TYPE); break;
	}
	return 0;
}


/****************************************************************************
½Ó¿ÚÀà
*****************************************************************************/
template<class _Tp> inline MatPtr<_Tp>::MatPtr()
{
	init(0, 0, 0);
}
template<class _Tp> inline MatPtr<_Tp>::MatPtr(int32 size)
{
	create(size);
}
template<class _Tp> inline MatPtr<_Tp>::MatPtr(const MatPtr<_Tp> & m)
{
	init(m.data, m.type, m.len, m.refcount);
	if (refcount)
		MAT_XADD(refcount, 1);
}
template<class _Tp> inline MatPtr<_Tp>::MatPtr(const _Tp *p, int32 n)
{
	init(p, n, 0);
}
template<class _Tp> template<typename ...Types> inline MatPtr<_Tp>::MatPtr(int32 size, const Types & ...args)
{
	create(size);
	addList(0, args...);
}
template<class _Tp> inline MatPtr<_Tp>::~MatPtr() { release(); }
template<class _Tp> void inline MatPtr<_Tp>::create(uint32 len) {
	release();
	this->len = len;
	uint32 totalsize = len * sizeof(_Tp);
	data = (_Tp*)fastMalloc(totalsize + sizeof(int32));
	refcount = (int32*)(((uint8 *)data) + totalsize);
	*refcount = 1;
}
template<class _Tp> inline void MatPtr<_Tp>::addref() {
	if (refcount)
		MAT_XADD(refcount, 1);
}
template<class _Tp> inline void MatPtr<_Tp>::release() {
	if (refcount && MAT_XADD(refcount, -1) == 1)
		fastFree(data);
	init(0, 0, 0);
}
template<class _Tp> inline MatPtr<_Tp> & MatPtr<_Tp>::operator=(const MatPtr<_Tp> & m) {
	if (this == &m)
		return *this;

	if (m.refcount)
		MAT_XADD(m.refcount, 1);

	release();
	data = m.data;
	len = m.len;
	refcount = m.refcount;
	return *this;
}
template<class _Tp> inline bool MatPtr<_Tp>::operator==(const MatPtr<_Tp> & m) const
{
	return data == m.data;
}
template<class _Tp> inline bool MatPtr<_Tp>::operator!=(const MatPtr<_Tp> & m) const
{
	return data != m.data;
}
template<class _Tp> inline bool MatPtr<_Tp>::operator==(void * m) const { return (this->data == m); }
template<class _Tp> inline bool MatPtr<_Tp>::operator!=(void * m) const { return (this->data != m); }
template<class _Tp> inline bool MatPtr<_Tp>::empty() const
{
	return data == nullptr;
}
template<class _Tp> inline int32 MatPtr<_Tp>::size() const {
	return len;
}
template<class _Tp> inline int32 & MatPtr<_Tp>::L() {
	return len;
}
template<class _Tp> inline _Tp *& MatPtr<_Tp>::P() {
	return data;
}
template<class _Tp> inline _Tp * MatPtr<_Tp>::obj()const {
	return data;
}
template<class _Tp> inline void MatPtr<_Tp>::set(const void * p, int32 length) {
	data = (_Tp*)p; len = length;
}
template<class _Tp> inline int32* MatPtr<_Tp>::getCount() const {
	return refcount;
}
template<class _Tp> inline void MatPtr<_Tp>::setCount(int32 * refcount) {
	this->refcount = refcount;
}
template<class _Tp> inline void MatPtr<_Tp>::init(const _Tp* p, int32 len, const int32 *count) {
	data = (_Tp*)p; this->len = len; refcount = (int32*)count;
}
template<class _Tp> inline void MatPtr<_Tp>::set(const MatPtr<_Tp> & ptr) {
	data = ptr.data; len = ptr.len;
}
template<class _Tp> inline _Tp * MatPtr<_Tp>::begin()
{
	return data;
}
template<class _Tp> inline const _Tp * MatPtr<_Tp>::begin() const
{
	return data;
}
template<class _Tp> inline _Tp * MatPtr<_Tp>::end()
{
	if (data == nullptr)return nullptr;
	if (refcount == nullptr)
		return data + len;
	return (_Tp*)refcount;
}
template<class _Tp> inline const _Tp * MatPtr<_Tp>::end() const
{
	if (data == nullptr)return nullptr;
	if (refcount == nullptr)return data + len;
	return (const _Tp*)refcount;;
}
template<class _Tp> inline _Tp & MatPtr<_Tp>::at(int32 i) const
{
#ifdef MAT_DEBUG
	CHECK_PTR(data);
	CHECK_INDEX(i, len);
#endif // MAT_DEBUG
	return data[i];
}
template<class _Tp> inline _Tp & MatPtr<_Tp>::operator[](int32 i) const {
#ifdef MAT_DEBUG
	CHECK_PTR(data);
	CHECK_INDEX(i, len);
#endif // MAT_DEBUG
	return data[i];
}
template<class _Tp> inline MatPtr<_Tp>::operator _Tp*() {
	return (_Tp*)data;
}
template<class _Tp> inline MatPtr<_Tp>::operator const _Tp*() const {
	return (const _Tp*)data;
}

Val::Val() : Val_(0) {}
Val::Val(Val_ v) : Val_(v), type(MAT_T) {}
Val::Val(const int8 v) : Val_(v), type(TP_8S) {}
Val::Val(const uint8 & v) : Val_(v), type(TP_8U) {}
Val::Val(const int16 v) : Val_(v), type(TP_16S) {}
Val::Val(const uint16 v) : Val_(v), type(TP_16U) {}
Val::Val(const int32 v) : Val_(v), type(TP_32S) {}
Val::Val(const uint32 v) : Val_(v), type(TP_32U) {}
Val::Val(const int64 v) : Val_(v), type(TP_64S) {}
Val::Val(const uint64 v) : Val_(v), type(TP_64U) {}
Val::Val(const float32 v) : Val_(v), type(TP_32F) {}
Val::Val(const float64 v) : Val_(v), type(TP_64F) {}
Val::Val(const float64_ v) : Val_(v), type(TP_64D) {}

Color lzh::Color::Random()
{
	return Color(rand() % 256, rand() % 256, rand() % 256);
}
Color lzh::Color::Tab(ColorTab index)
{
	switch (index)
	{
	case lzh::Color::Amber:return Color(202, 76, 38);
		//case lzh::Color::AntiqueViolet:return Color(?, ?, ?);
	case lzh::Color::AntiqueWhite:return Color(250, 235, 215);
	case lzh::Color::Aqua:return Color(0, 255, 255);
	case lzh::Color::AquaMarine:return Color(127, 255, 170);
	case lzh::Color::AquaMarineBlue:return Color(202, 76, 38);
	case lzh::Color::Azure:return Color(240, 255, 255);
	case lzh::Color::AliceBlue:return Color(240, 248, 255);
	case lzh::Color::BabyPink:return Color(252, 229, 223);
	case lzh::Color::Beige:return Color(107, 142, 35);
	case lzh::Color::Bisque:return Color(255, 228, 196);
	case lzh::Color::Black:return Color(0, 0, 0);
	case lzh::Color::BlancheDalmond:return Color(255, 235, 205);
	case lzh::Color::Blue:return Color(0, 0, 255);
	case lzh::Color::BlueViolet:return Color(138, 43, 226);
	case lzh::Color::Brown:return Color(165, 42, 42);
	case lzh::Color::BurlyWood:return Color(222, 184, 135);
	case lzh::Color::CobaltBlue:return Color(0, 71, 171);
	case lzh::Color::CadetBlue:return Color(95, 158, 160);
	case lzh::Color::Camel:return Color(181, 134, 84);
	case lzh::Color::CharcoalGray:return Color(64, 64, 64);
	case lzh::Color::Chartreuse:return Color(127, 255, 0);
	case lzh::Color::Chocolate:return Color(210, 105, 30);
	case lzh::Color::CobaltVlue:return Color(3, 128, 183);
	case lzh::Color::Coral:return Color(255, 127, 80);
	case lzh::Color::CornflowerBlue:return Color(100, 149, 237);
	case lzh::Color::Cornsilk:return Color(255, 248, 220);
	case lzh::Color::Crimson:return Color(220, 20, 60);
	case lzh::Color::Cyan:return Color(0, 255, 255);
	case lzh::Color::DarkBlue:return Color(0, 0, 139);
	case lzh::Color::DarkCyan:return Color(0, 139, 139);
	case lzh::Color::DarkGoldenrod:return Color(184, 134, 11);
	case lzh::Color::DarkGray:return Color(169, 169, 169);
	case lzh::Color::DarkGreen:return Color(0, 100, 0);
	case lzh::Color::DarkKhaki:return Color(189, 183, 107);
	case lzh::Color::DarkMagenta:return Color(139, 0, 139);
	case lzh::Color::DarkOliveGreen:return Color(85, 107, 47);
	case lzh::Color::DarkOrange:return Color(255, 140, 0);
	case lzh::Color::DarkOrchid:return Color(153, 50, 204);
	case lzh::Color::DarkRed:return Color(139, 0, 0);
	case lzh::Color::DarkSalmon:return Color(233, 150, 122);
	case lzh::Color::DarkSeaGreen:return Color(72, 61, 139);
	case lzh::Color::DarkSlateBlue:return Color(72, 61, 139);
	case lzh::Color::DarkSlateGray:return Color(47, 79, 79);
	case lzh::Color::DarkTurquoise:return Color(0, 206, 209);
	case lzh::Color::DarkViolet:return Color(148, 0, 211);
	case lzh::Color::DeepPink:return Color(255, 20, 147);
	case lzh::Color::DeepSkyBlue:return Color(0, 191, 255);
	case lzh::Color::DimGray:return Color(105, 105, 105);
	case lzh::Color::DoderBlue:return Color(30, 144, 255);
	case lzh::Color::DodgerBlue:return Color(30, 144, 255);
	case lzh::Color::EmeraldGreen:return Color(21, 174, 103);
	case lzh::Color::FireBrick:return Color(178, 34, 34);
	case lzh::Color::FloralWhite:return Color(255, 250, 240);
	case lzh::Color::ForestGreen:return Color(34, 139, 34);
	case lzh::Color::Fuchsia:return Color(255, 0, 255);
	case lzh::Color::Gainsboro:return Color(220, 220, 220);
	case lzh::Color::GhostWhite:return Color(248, 248, 255);
	case lzh::Color::Gold:return Color(255, 215, 0);
	case lzh::Color::Goldenrod:return Color(218, 165, 32);
	case lzh::Color::Gray:return Color(128, 128, 128);
	case lzh::Color::Green:return Color(0, 128, 0);
	case lzh::Color::GreenYellow:return Color(173, 255, 47);
	case lzh::Color::HoneyDew:return Color(240, 255, 240);
	case lzh::Color::HotPink:return Color(255, 105, 180);
	case lzh::Color::IndianRed:return Color(205, 92, 92);
	case lzh::Color::Indigo:return Color(75, 0, 130);
	case lzh::Color::Ivory:return Color(255, 255, 240);
	case lzh::Color::Khaki:return Color(240, 230, 140);
	case lzh::Color::Lavender:return Color(230, 230, 250);
	case lzh::Color::LavenderBlush:return Color(255, 240, 245);
	case lzh::Color::LawnGreen:return Color(124, 252, 0);
	case lzh::Color::Lemonchiffon:return Color(255, 250, 205);
	case lzh::Color::LightBlue:return Color(173, 216, 230);
	case lzh::Color::LightCoral:return Color(240, 128, 128);
	case lzh::Color::LightCyan:return Color(225, 255, 255);
	case lzh::Color::LightGoldenrodYellow:return Color(250, 250, 210);
	case lzh::Color::LightGreen:return Color(144, 238, 144);
	case lzh::Color::LightGrey:return Color(211, 211, 211);
	case lzh::Color::LightPink:return Color(255, 182, 193);
	case lzh::Color::LightSalmon:return Color(255, 160, 122);
	case lzh::Color::LightSeaGreen:return Color(32, 178, 170);
	case lzh::Color::LightSkyBlue:return Color(135, 206, 250);
	case lzh::Color::LightSlateGray:return Color(119, 136, 153);
	case lzh::Color::LightSteelBlue:return Color(176, 196, 222);
	case lzh::Color::LightYellow:return Color(255, 255, 224);
	case lzh::Color::Lilac:return Color(187, 161, 203);
	case lzh::Color::Lime:return Color(0, 255, 0);
	case lzh::Color::LimeGreen:return Color(50, 205, 50);
	case lzh::Color::Linen:return Color(250, 240, 230);
	case lzh::Color::Magenta:return Color(255, 0, 255);
	case lzh::Color::Maroon:return Color(128, 0, 0);
	case lzh::Color::Mauve:return Color(225, 152, 192);
	case lzh::Color::MediumAquamarine:return Color(0, 250, 154);
	case lzh::Color::MediumBlue:return Color(0, 0, 205);
	case lzh::Color::MediumOrchid:return Color(186, 85, 211);
	case lzh::Color::MediumPurple:return Color(147, 112, 219);
	case lzh::Color::MediumSeaGreen:return Color(60, 179, 113);
	case lzh::Color::MediumSlateBlue:return Color(123, 104, 238);
	case lzh::Color::MediumSpringGreen:return Color(245, 255, 250);
	case lzh::Color::MediumTurquoise:return Color(72, 209, 204);
	case lzh::Color::MediumVioletRed:return Color(199, 21, 133);
	case lzh::Color::MidNightBlue:return Color(25, 25, 112);
	case lzh::Color::Mintcream:return Color(0, 255, 127);
	case lzh::Color::MistyGray:
		break;
	case lzh::Color::MistyRose:return Color(255, 228, 225);
	case lzh::Color::Moccasin:return Color(255, 228, 181);
	case lzh::Color::MossGreen:return Color(105, 119, 35);
	case lzh::Color::NavajoWhite:return Color(255, 222, 173);
	case lzh::Color::NavyBlue:return Color(0, 0, 128);
	case lzh::Color::OffWhite:return Color(192, 192, 192);
	case lzh::Color::Oldlace:return Color(253, 245, 230);
	case lzh::Color::Olive:return Color(128, 128, 0);
	case lzh::Color::Olivedrab:return Color(85, 107, 47);
	case lzh::Color::Orange:return Color(255, 165, 0);
	case lzh::Color::OrangeRed:return Color(255, 69, 0);
	case lzh::Color::Orchid:return Color(218, 112, 214);
	case lzh::Color::OysterWhite:return Color(255, 251, 240);
	case lzh::Color::OliveGreen:return Color(98, 90, 5);
	case lzh::Color::PaleGoldenrod:return Color(238, 232, 170);
	case lzh::Color::PaleGreen:return Color(152, 251, 152);
	case lzh::Color::PaleTurquoise:return Color(175, 238, 238);
	case lzh::Color::PaleVioletRed:return Color(219, 112, 147);
	case lzh::Color::Pansy:return Color(139, 0, 98);
	case lzh::Color::Papayawhip:return Color(255, 239, 213);
	case lzh::Color::Peachpuff:return Color(255, 218, 185);
	case lzh::Color::Peru:return Color(205, 133, 63);
	case lzh::Color::Pink:return Color(255, 192, 203);
	case lzh::Color::Plum:return Color(221, 160, 221);
	case lzh::Color::PowderBlue:return Color(176, 224, 230);
	case lzh::Color::Purple:return Color(128, 0, 128);
	case lzh::Color::Red:return Color(255, 0, 0);
	case lzh::Color::RosyBrown:return Color(188, 143, 143);
	case lzh::Color::RoyalBlue:return Color(65, 105, 225);
	case lzh::Color::Rubine:return Color(206, 0, 88);
	case lzh::Color::SaddleBrown:return Color(139, 69, 19);
	case lzh::Color::Salmon:return Color(250, 128, 114);
	case lzh::Color::SalmonPink:return Color(242, 155, 135);
	case lzh::Color::SandyBeige:return Color(230, 195, 195);
	case lzh::Color::SandyBrown:return Color(244, 164, 96);
	case lzh::Color::Sapphire:return Color(0, 47, 167);
	case lzh::Color::Scarlet:return Color(196, 76, 85);
	case lzh::Color::SeaGreen:return Color(46, 139, 87);
	case lzh::Color::Seashell:return Color(255, 245, 238);
	case lzh::Color::Sienna:return Color(160, 82, 45);
	case lzh::Color::Silver:return Color(192, 192, 192);
	case lzh::Color::SkyBlue:return Color(135, 206, 235);
	case lzh::Color::SlateBlue:return Color(106, 90, 205);
	case lzh::Color::SlateGray:return Color(112, 128, 144);
	case lzh::Color::SmokyGray:return Color(204, 204, 204);
	case lzh::Color::Snow:return Color(255, 250, 250);
	case lzh::Color::SpringGreen:return Color(60, 179, 113);
	case lzh::Color::SteelBlue:return Color(70, 130, 180);
	case lzh::Color::Stone:return Color(112, 128, 144);
	case lzh::Color::SnowyWhite:return Color(254, 250, 249);
	case lzh::Color::Tan:return Color(210, 180, 140);
	case lzh::Color::Teal:return Color(0, 128, 128);
	case lzh::Color::Thistle:return Color(216, 191, 216);
	case lzh::Color::Tomato:return Color(255, 99, 71);
	case lzh::Color::Turquoise:return Color(64, 224, 208);
	case lzh::Color::TurquoiseBlue:return Color(0, 164, 194);
	case lzh::Color::Violet:return Color(238, 130, 238);
	case lzh::Color::Wheat:return Color(245, 222, 179);
	case lzh::Color::White:return Color(255, 255, 255);
	case lzh::Color::SmokeWhite:return Color(245, 245, 245);
	case lzh::Color::WineRed:return Color(100, 1, 37);
	case lzh::Color::Yellow:return Color(255, 255, 0);
	case lzh::Color::YellowGreen:return Color(154, 205, 50);
	default:
		break;
	}
	return Color();
}