#include "cvtColor.h"
using namespace lzh;

void cvtColor::ConverTo(InputArray src, OutputArray dst, ColorGamut code)
{
	CvMat img = src.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(img);
#endif
	ColorGamut cg = img.colorGamut();
	if (code == cg) {
		dst.set(img);
	}
	else {
		switch (cg)
		{
		case lzh::ColorGamutCustom:
			switch (code)
			{
			case lzh::ColorGamutGray:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					RGB2GRAY(src, dst);
				else if (img.channels() == 4)
					RGBA2GRAY(src, dst);
				else if (img.channels() == 1)
					dst.set(img);
				break;
			case lzh::ColorGamutRGB:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					dst.set(img);
				else if (img.channels() == 4)
					RGBA2RGB(src, dst);
				else if (img.channels() == 1)
					GRAY2RGB(src, dst);
				break;
			case lzh::ColorGamutBGR:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					dst.set(img);
				else if (img.channels() == 4)
					BGRA2BGR(src, dst);
				else if (img.channels() == 1)
					GRAY2BGR(src, dst);
				break;
			case lzh::ColorGamutRGBA:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					RGB2RGBA(src, dst);
				else if (img.channels() == 4)
					dst.set(img);
				else if (img.channels() == 1)
					GRAY2RGBA(src, dst);
				break;
			case lzh::ColorGamutBGRA:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					BGR2BGRA(src, dst);
				else if (img.channels() == 4)
					dst.set(img);
				else if (img.channels() == 1)
					GRAY2BGRA(src, dst);
				break;
			case lzh::ColorGamutHSV:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					RGB2HSV(src, dst);
				else if (img.channels() == 4) {
					RGBA2RGB(src, dst);
					RGB2HSV(dst, dst);
				}
				else if (img.channels() == 1) {
					GRAY2RGB(src, dst);
					RGB2HSV(dst, dst);
				}
				break;
			case lzh::ColorGamutXYZ:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					RGB2XYZ(src, dst);
				else if (img.channels() == 4) {
					RGBA2RGB(src, dst);
					RGB2XYZ(dst, dst);
				}
				else if (img.channels() == 1) {
					GRAY2RGB(src, dst);
					RGB2XYZ(dst, dst);
				}
				break;
			case lzh::ColorGamutLab:
				CHECK_EXCEPTION(if (!(img.channels() == 2 || img.channels() > 4)), THROW_INFO_STR("通道上不符合要求"));
				if (img.channels() == 3)
					RGB2Lab(src, dst);
				else if (img.channels() == 4) {
					RGBA2RGB(src, dst);
					RGB2Lab(dst, dst);
				}
				else if (img.channels() == 1) {
					GRAY2RGB(src, dst);
					RGB2Lab(dst, dst);
				}
				break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutGray:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutRGB:GRAY2RGB(src, dst);	break;
			case lzh::ColorGamutBGR:GRAY2BGR(src, dst); break;
			case lzh::ColorGamutRGBA:GRAY2RGBA(src, dst); break;
			case lzh::ColorGamutBGRA:GRAY2BGRA(src, dst); break;
			case lzh::ColorGamutHSV:GRAY2RGB(src, dst); RGB2HSV(dst, dst); break;
			case lzh::ColorGamutXYZ:GRAY2RGB(src, dst); RGB2XYZ(dst, dst); break;
			case lzh::ColorGamutLab:GRAY2RGB(src, dst); RGB2Lab(dst, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutRGB:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:RGB2GRAY(src, dst); break;
			case lzh::ColorGamutBGR:RGB2BGR(src, dst); break;
			case lzh::ColorGamutRGBA:RGB2RGBA(src, dst); break;
			case lzh::ColorGamutBGRA:RGB2BGRA(src, dst); break;
			case lzh::ColorGamutHSV:RGB2HSV(dst, dst); break;
			case lzh::ColorGamutXYZ:RGB2XYZ(dst, dst); break;
			case lzh::ColorGamutLab:RGB2Lab(dst, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutBGR:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:BGR2GRAY(src, dst); break;
			case lzh::ColorGamutRGB:BGR2RGB(src, dst);	break;
			case lzh::ColorGamutRGBA:BGR2RGBA(src, dst); break;
			case lzh::ColorGamutBGRA:BGR2BGRA(src, dst); break;
			case lzh::ColorGamutHSV:BGR2HSV(dst, dst); break;
			case lzh::ColorGamutXYZ:BGR2XYZ(dst, dst); break;
			case lzh::ColorGamutLab:BGR2Lab(dst, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutRGBA:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:BGR2GRAY(src, dst); break;
			case lzh::ColorGamutRGB:RGBA2RGB(src, dst);	break;
			case lzh::ColorGamutBGR:RGBA2BGR(src, dst);	break;
			case lzh::ColorGamutBGRA:RGBA2BGRA(src, dst); break;
			case lzh::ColorGamutHSV:RGBA2RGB(src, dst); RGB2HSV(dst, dst); break;
			case lzh::ColorGamutXYZ:RGBA2RGB(src, dst); RGB2XYZ(dst, dst); break;
			case lzh::ColorGamutLab:RGBA2RGB(src, dst); RGB2Lab(dst, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutBGRA:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:BGRA2GRAY(src, dst); break;
			case lzh::ColorGamutRGB:BGRA2RGB(src, dst);	break;
			case lzh::ColorGamutBGR:BGRA2BGR(src, dst);	break;
			case lzh::ColorGamutRGBA:BGRA2RGBA(src, dst); break;
			case lzh::ColorGamutHSV:BGRA2BGR(src, dst); BGR2HSV(dst, dst); break;
			case lzh::ColorGamutXYZ:BGRA2BGR(src, dst); BGR2XYZ(dst, dst); break;
			case lzh::ColorGamutLab:BGRA2BGR(src, dst); BGR2Lab(dst, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutHSV:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:HSV2RGB(src, dst); RGB2GRAY(dst, dst); break;
			case lzh::ColorGamutRGB:HSV2RGB(src, dst);	break;
			case lzh::ColorGamutBGR:HSV2BGR(src, dst);	break;
			case lzh::ColorGamutRGBA:HSV2RGB(src, dst); RGB2RGBA(src, dst); break;
			case lzh::ColorGamutBGRA:HSV2BGR(src, dst); BGR2BGRA(src, dst); break;
			case lzh::ColorGamutXYZ:HSV2RGB(src, dst); RGB2XYZ(dst, dst); break;
			case lzh::ColorGamutLab:HSV2RGB(src, dst); RGB2Lab(dst, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutXYZ:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:XYZ2RGB(src, dst); RGB2GRAY(dst, dst); break;
			case lzh::ColorGamutRGB:XYZ2RGB(src, dst);	break;
			case lzh::ColorGamutBGR:XYZ2BGR(src, dst);	break;
			case lzh::ColorGamutRGBA:XYZ2RGB(src, dst); RGB2RGBA(src, dst); break;
			case lzh::ColorGamutBGRA:XYZ2BGR(src, dst); BGR2BGRA(src, dst); break;
			case lzh::ColorGamutHSV:XYZ2RGB(src, dst); RGB2HSV(dst, dst); break;
			case lzh::ColorGamutLab:XYZ2Lab(src, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		case lzh::ColorGamutLab:
			switch (code)
			{
			case lzh::ColorGamutCustom:dst.set(src); break;
			case lzh::ColorGamutGray:Lab2RGB(src, dst); RGB2GRAY(dst, dst); break;
			case lzh::ColorGamutRGB:Lab2RGB(src, dst);	break;
			case lzh::ColorGamutBGR:Lab2BGR(src, dst);	break;
			case lzh::ColorGamutRGBA:Lab2RGB(src, dst); RGB2RGBA(src, dst); break;
			case lzh::ColorGamutBGRA:Lab2BGR(src, dst); BGR2BGRA(src, dst); break;
			case lzh::ColorGamutHSV:Lab2RGB(src, dst); RGB2HSV(dst, dst); break;
			case lzh::ColorGamutXYZ:Lab2XYZ(src, dst); break;
			default:THROW_INFO_STR("不支持的色域");
			}
			break;
		default:THROW_INFO_STR("不支持的色域");
		}
	}
}
void cvtColor::Lab2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutLab || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	Lab2XYZ(src_, dst);
	XYZ2RGB(dst, dst);
}
void cvtColor::Lab2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutLab || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	Lab2XYZ(src_, dst);
	XYZ2BGR(dst, dst);
}
void cvtColor::RGB2Lab(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	RGB2XYZ(src_, dst);
	XYZ2Lab(dst, dst);
}
void cvtColor::BGR2Lab(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	BGR2XYZ(src_, dst);
	XYZ2Lab(dst, dst);
}
void cvtColor::Lab2XYZ(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutLab || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat XYZ(src.size3(), src.depth(), ColorGamutXYZ);
	Vec3m lab, xyz, fxyz;
	Vec3m param = Vec3m(XYZ_Xn, XYZ_Yn, XYZ_Zn) * 255;
	mat_t param_16116 = _T(16.0 / 116.0), param_div = _T(7.787);
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			lab = Vec3m(src(i, j, 0), src(i, j, 1), src(i, j, 2));
			fxyz[1] = (lab[0] + 16) / 116;
			if (fxyz[1] > 0.206893f)
				xyz[1] = fxyz[1] * fxyz[1] * fxyz[1];
			else
				xyz[1] = (fxyz[1] - param_16116) / param_div;

			fxyz[0] = lab[1] / 500 + fxyz[1];
			if (fxyz[0] > 0.206893f)
				xyz[0] = fxyz[0] * fxyz[0] * fxyz[0];
			else
				xyz[0] = (fxyz[0] - param_16116) / param_div;

			fxyz[2] = fxyz[1] - lab[2] / 200;
			if (fxyz[2] > 0.206893f)
				xyz[2] = fxyz[2] * fxyz[2] * fxyz[2];
			else
				xyz[2] = (fxyz[2] - param_16116) / param_div;
			xyz *= param;
			XYZ.set(i, j, xyz);
		}
	}
	dst.set(XYZ);
}
void cvtColor::XYZ2Lab(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutXYZ || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat Lab(src.size3(), src.depth(), ColorGamutLab);
	Vec3m lab, xyz, fxyz;
	Vec3m param = Vec3m(XYZ_Xn, XYZ_Yn, XYZ_Zn) * 255;
	mat_t param_13 = _T(1.0 / 3.0), param_16116 = _T(16.0 / 116.0);
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			xyz = Vec3m(src(i, j, 0) / param[0], src(i, j, 1) / param[1], src(i, j, 2) / param[2]);
			if (xyz[1] > 0.008856)
			{
				fxyz[1] = pow(xyz[1], param_13);
				lab[0] = _T(116.0) * fxyz[1] - _T(16.0);
			}
			else
			{
				fxyz[1] = _T(7.787) * xyz[1] + param_16116;
				lab[0] = _T(903.3)*fxyz[1];
			}
			lab[0] = lab[0] > 0 ? lab[0] : 0;
			if (xyz[0] > 0.008856)
				fxyz[0] = pow(xyz[0], param_13);
			else
				fxyz[0] = _T(7.787) * xyz[0] + param_16116;
			if (xyz[2] > 0.008856)
				fxyz[2] = pow(xyz[2], param_13);
			else
				fxyz[2] = _T(7.787) * xyz[2] + param_16116;
			lab[1] = _T(500.0) * (fxyz[0] - fxyz[1]);
			lab[2] = _T(200.0) * (fxyz[1] - fxyz[2]);
			Lab.set(i, j, lab);
		}
	}
	dst.set(Lab);
}
void cvtColor::XYZ2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutXYZ || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat BGR(src.size3(), src.depth(), ColorGamutBGR);
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			Vec3m bgr = Vec3m(xyz2rgb * Vec3m(src(i, j, 0), src(i, j, 1), src(i, j, 2)).t());
			BGR.set(i, j, bgr[2]); BGR.set(i, j, bgr[1]); BGR.set(i, j, bgr[0]);
		}
	}
	dst.set(BGR);
}
void cvtColor::XYZ2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutXYZ || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat RGB(src.size3(), src.depth(), ColorGamutRGB);
	FOR_RANGE(i, 0, src.rows)
		FOR_RANGE(j, 0, src.cols)
		RGB.set(i, j, Vec3m(xyz2rgb * Vec3m(src(i, j, 0), src(i, j, 1), src(i, j, 2)).t()));
	dst.set(RGB);
}
void cvtColor::BGR2XYZ(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat XYZ(src.size3(), src.depth(), ColorGamutXYZ);
	FOR_RANGE(i, 0, src.rows)
		FOR_RANGE(j, 0, src.cols)
		XYZ.set(i, j, Vec3m(rgb2xyz * Vec3m(src(i, j, 2), src(i, j, 1), src(i, j, 0)).t()));
	dst.set(XYZ);
}
void cvtColor::RGB2XYZ(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat XYZ(src.size3(), src.depth(), ColorGamutXYZ);
	FOR_RANGE(i, 0, src.rows)
		FOR_RANGE(j, 0, src.cols)
		XYZ.set(i, j, Vec3m(rgb2xyz * Vec3m(src(i, j, 0), src(i, j, 1), src(i, j, 2)).t()));
	dst.set(XYZ);
}
void cvtColor::HSV2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutHSV || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat BGR(src.size3(), src.depth(), ColorGamutBGR);
	Vec3m bgr;
	Vec3m hsv;
	Vec3m pqt;
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			hsv = Vec3m(src(i, j, 0), src(i, j, 1), src(i, j, 2));
			if (hsv[1] == 0) {
				BGR.set(i, j, Vec3m(hsv[2], hsv[2], hsv[2]));
				continue;
			}
			else {
				if (hsv[0] == 360)
				{
					hsv[0] = 0;
				}
				hsv[0] /= 60;
				int32 hi = int32(hsv[0]);
				mat_t f = hsv[0] - hi;
				pqt[0] = hsv[2] * (1 - hsv[1]);
				pqt[1] = hsv[2] * (1 - f * hsv[1]);
				pqt[2] = hsv[2] * (1 - (1 - f)*hsv[1]);
				switch (hi)
				{
				case 0:bgr = Vec3m(pqt[0], pqt[2], hsv[2]); break;
				case 1:bgr = Vec3m(pqt[0], hsv[2], pqt[1]); break;
				case 2:bgr = Vec3m(pqt[2], hsv[2], pqt[0]); break;
				case 3:bgr = Vec3m(hsv[2], pqt[1], pqt[0]); break;
				case 4:bgr = Vec3m(hsv[2], pqt[0], pqt[2]); break;
				default:bgr = Vec3m(pqt[1], pqt[0], hsv[2]); break;
				}
				BGR.set(i, j, bgr);
			}
		}
	}
	normalize(BGR, dst, 0, 255, NORM_MINMAX);
}
void cvtColor::HSV2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutHSV || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat RGB(src.size3(), src.depth(), ColorGamutRGB);
	Vec3m rgb;
	Vec3m hsv;
	Vec3m pqt;
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			hsv = Vec3m(src(i, j, 0), src(i, j, 1), src(i, j, 2));
			if (hsv[1] == 0) {
				RGB.at<Vec3m>(i, j) = Vec3m(hsv[2], hsv[2], hsv[2]);
				continue;
			}
			else {
				if (hsv[0] == 360)
				{
					hsv[0] = 0;
				}
				hsv[0] /= 60;
				int32 hi = int32(hsv[0]);
				mat_t f = hsv[0] - hi;
				pqt[0] = hsv[2] * (1 - hsv[1]);
				pqt[1] = hsv[2] * (1 - f * hsv[1]);
				pqt[2] = hsv[2] * (1 - (1 - f)*hsv[1]);
				switch (hi)
				{
				case 0:rgb = Vec3m(hsv[2], pqt[2], pqt[0]); break;
				case 1:rgb = Vec3m(pqt[1], hsv[2], pqt[0]); break;
				case 2:rgb = Vec3m(pqt[0], hsv[2], pqt[2]); break;
				case 3:rgb = Vec3m(pqt[0], pqt[1], hsv[2]); break;
				case 4:rgb = Vec3m(pqt[2], pqt[0], hsv[2]); break;
				default:rgb = Vec3m(hsv[2], pqt[0], pqt[1]); break;
				}
				RGB.set(i, j, 0, rgb[0]);
				RGB.set(i, j, 1, rgb[1]);
				RGB.set(i, j, 2, rgb[2]);
			}
		}
	}
	normalize(RGB, dst, 0, 255, NORM_MINMAX);
}
void cvtColor::BGR2HSV(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat HSV(src.size3(), src.depth(), ColorGamutHSV);
	Vec3m bgr;
	Vec3m hsv;
	Vec3m del_rgb;
	mat_t Cmax, Delta;
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			bgr[0] = src(i, j, 0) / 255;
			bgr[1] = src(i, j, 1) / 255;
			bgr[2] = src(i, j, 2) / 255;
			Cmax = Max(bgr);
			Delta = Cmax - Min(bgr);
			hsv[2] = Cmax;
			if (Cmax == 0)
				hsv[1] = 0;
			else
				hsv[1] = Delta / Cmax;
			if (Delta == 0) {
				hsv[0] = 0;
			}
			else if (Cmax == bgr[2]) {
				hsv[0] = 60 * (bgr[1] - bgr[0]) / Delta;
			}
			else if (Cmax == bgr[1])
				hsv[0] = 60 * ((bgr[0] - bgr[2]) / Delta + 2);
			else if (Cmax == bgr[0])
				hsv[0] = 60 * ((bgr[2] - bgr[1]) / Delta + 4);
			if (hsv[0] < 0)
				hsv[0] += 360;
			HSV.set(i, j, 0, hsv[0]);
			HSV.set(i, j, 1, hsv[1]);
			HSV.set(i, j, 2, hsv[2]);
		}
	}
	dst.set(HSV);
	dst.set(HSV);
}
void cvtColor::RGB2HSV(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat HSV(src.size3(), src.depth(), ColorGamutHSV);
	Vec3m rgb;
	Vec3m hsv;
	Vec3m del_rgb;
	mat_t Cmax, Delta;
	FOR_RANGE(i, 0, src.rows) {
		FOR_RANGE(j, 0, src.cols) {
			rgb[0] = src(i, j, 0) / 255;
			rgb[1] = src(i, j, 1) / 255;
			rgb[2] = src(i, j, 2) / 255;
			Cmax = Max(rgb);
			Delta = Cmax - Min(rgb);
			hsv[2] = Cmax;
			if (Cmax == 0)
				hsv[1] = 0;
			else
				hsv[1] = Delta / Cmax;
			if (Delta == 0) {
				hsv[0] = 0;
			}
			else if (Cmax == rgb[0]) {
				hsv[0] = 60 * (rgb[1] - rgb[2]) / Delta;
			}
			else if (Cmax == rgb[1])
				hsv[0] = 60 * ((rgb[2] - rgb[0]) / Delta + 2);
			else if (Cmax == rgb[2])
				hsv[0] = 60 * ((rgb[0] - rgb[1]) / Delta + 4);
			if (hsv[0] < 0)
				hsv[0] += 360;
			HSV.set(i, j, 0, hsv[0]);
			HSV.set(i, j, 1, hsv[1]);
			HSV.set(i, j, 2, hsv[2]);
		}
	}
	dst.set(HSV);
}
void cvtColor::BGR2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat rgb(src.size3(), src.depth(), ColorGamutRGB);
	FOR_RANGE(i, 0, 3)
		src.channel(i).setTo(rgb.channel(2 - i));
	dst.set(rgb);
}
void cvtColor::RGB2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	if (src.empty())return;
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat bgr(src.size3(), src.depth(), ColorGamutBGR);
	FOR_RANGE(i, 0, 3)
		src.channel(i).setTo(bgr.channel(2 - i));
	dst.set(bgr);
}
void cvtColor::BGR2BGRA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, 4, src.depth(), ColorGamutBGRA);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, 2, src(i, j, 0));
			img.set(i, j, 1, src(i, j, 1));
			img.set(i, j, 0, src(i, j, 2));
			img.set(i, j, 3, 0);
		}
	}
	dst.set(img);
}
void cvtColor::RGB2RGBA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, 4, src.depth(), ColorGamutRGBA);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, 0, src(i, j, 0));
			img.set(i, j, 1, src(i, j, 1));
			img.set(i, j, 2, src(i, j, 2));
			img.set(i, j, 3, 0);
		}
	}
	dst.set(img);
}
void cvtColor::GRAY2BGRA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 1), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutGray || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat v(4);
	FOR_RANGE(i, 0, 3)
		v[i] = src;
	v[3] = CvMat::zeros(src.size(), src.depth());
	CvMat bgra; merge(v, bgra);
	bgra.setColorGamut(ColorGamutBGRA);
	dst.set(bgra);
}
void cvtColor::GRAY2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	if (src.empty())return;
	CHECK_EXCEPTION(if (src.channels() == 1), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutGray || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat v(3);
	FOR_RANGE(i, 0, 3)
		v[i] = src;
	CvMat bgr; merge(v, bgr);
	bgr.setColorGamut(ColorGamutBGR);
	dst.set(bgr);
}
void cvtColor::GRAY2RGBA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 1), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutGray || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat v(4);
	FOR_RANGE(i, 0, 3) v[i] = src;
	v[3] = CvMat::zeros(src.size(), src.depth());
	CvMat rgba; merge(v, rgba);
	rgba.setColorGamut(ColorGamutRGBA);
	dst.set(rgba);
}
void cvtColor::GRAY2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	if (src.empty())return;
	CHECK_EXCEPTION(if (src.channels() == 1), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutGray || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat v(3);
	FOR_RANGE(i, 0, 3) v[i] = src;
	CvMat rgb; merge(v, rgb);
	rgb.setColorGamut(ColorGamutRGB);
	dst.set(rgb);
}
void cvtColor::RGBA2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGBA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat rgba;
	split(src, rgba);
	CvMat rgb; merge(rgba, 3, rgb);
	rgb.setColorGamut(ColorGamutRGB);
	dst.set(rgb);
}
void cvtColor::BGRA2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGRA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat rgba;
	split(src, rgba);
	CvMat rgb; merge(rgba, 3, rgb);
	rgb.setColorGamut(ColorGamutBGR);
	dst.set(rgb);
}
void cvtColor::RGBA2BGRA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGBA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat rgba;
	split(src, rgba);
	__swap(rgba[0], rgba[2]);
	CvMat bgra; merge(rgba, 4, bgra);
	bgra.setColorGamut(ColorGamutBGRA);
	dst.set(bgra);
}
void cvtColor::BGRA2RGBA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGRA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat bgra;
	split(src, bgra);
	__swap(bgra[0], bgra[2]);
	CvMat rgba; merge(bgra, 4, rgba);
	rgba.setColorGamut(ColorGamutRGBA);
	dst.set(rgba);
}
void cvtColor::RGB2BGRA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, 4, src.depth(), ColorGamutRGBA);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, 0, src(i, j, 2));
			img.set(i, j, 1, src(i, j, 1));
			img.set(i, j, 2, src(i, j, 0));
			img.set(i, j, 3, 0);
		}
	}
	dst.set(img);
}
void cvtColor::BGR2RGBA(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, 4, src.depth(), ColorGamutRGBA);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, 0, src(i, j, 2));
			img.set(i, j, 1, src(i, j, 1));
			img.set(i, j, 2, src(i, j, 0));
			img.set(i, j, 3, 0);
		}
	}
	dst.set(img);
}
void cvtColor::RGBA2BGR(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGBA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat rgba;
	split(src, rgba);
	__swap(rgba[0], rgba[2]);
	CvMat bgr; merge(rgba, 3, bgr);
	bgr.setColorGamut(ColorGamutBGR);
	dst.set(bgr);
}
void cvtColor::BGRA2RGB(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGRA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	vec_cvmat bgra;
	split(src, bgra);
	__swap(bgra[0], bgra[2]);
	CvMat rgb; merge(bgra, 3, rgb);
	rgb.setColorGamut(ColorGamutRGB);
	dst.set(rgb);
}
void cvtColor::RGB2GRAY(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGB || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, src.depth(), ColorGamutGray);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, src(i, j, 0) * _T(0.11) + src(i, j, 1) * _T(0.59) + src(i, j, 2) * _T(0.3));
		}
	}
	dst.set(img);
}
void cvtColor::RGBA2GRAY(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutRGBA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, src.depth(), ColorGamutGray);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, src(i, j, 0) * _T(0.11) + src(i, j, 1) * _T(0.59) + src(i, j, 2) * _T(0.3));
		}
	}
	dst.set(img);
}
void cvtColor::BGR2GRAY(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 3), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGR || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, src.depth(), ColorGamutGray);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, src(i, j, 2) * _T(0.11) + src(i, j, 1) * _T(0.59) + src(i, j, 0) * _T(0.3));
		}
	}
	dst.set(img);
}
void cvtColor::BGRA2GRAY(InputArray src_, OutputArray dst)
{
	CvMat src = src_.getCvMat();
#ifdef MAT_DEBUG
	CHECK_MATRIX_(src);
#endif
	CHECK_EXCEPTION(if (src.channels() == 4), THROW_INFO_STR("通道数不符合要求!"));
	ColorGamut colorGamut = src.colorGamut();
	CHECK_EXCEPTION(if (colorGamut == ColorGamutBGRA || colorGamut == ColorGamutCustom), THROW_INFO_STR("图像类型错误"));
	CvMat img(src.cols, src.rows, src.depth(), ColorGamutGray);
	for (int32 i = 0; i < src.rows; ++i) {
		for (int32 j = 0; j < src.cols; ++j) {
			img.set(i, j, src(i, j, 2) * _T(0.11) + src(i, j, 1) * _T(0.59) + src(i, j, 0) * _T(0.3));
		}
	}
	dst.set(img);
}
