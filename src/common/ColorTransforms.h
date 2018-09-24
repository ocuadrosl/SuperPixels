/*
 * ColorTransforms.h
 *
 *  Created on: Sep 20, 2018
 *      Author: oscar
 */

#ifndef SRC_COMMON_COLORTRANSFORMS_H_
#define SRC_COMMON_COLORTRANSFORMS_H_

namespace ct
{
/*
 *sR, sG and sB (Standard RGB) input range = 0 ÷ 255
 * X, Y and Z output refer to a D65/2° standard illuminant.
 *
 * */
template<typename rgbType, typename xyzType>
inline typename xyzType::PixelType rgbToXyz(const typename rgbType::PixelType& rgbPixel)
{
	//must be double
	typename xyzType::PixelType xyzPixel;

	//Normalize to 0-1
	double nRed = static_cast<double>(rgbPixel[0]) / 255.0;
	double nGreen = static_cast<double>(rgbPixel[1]) / 255.0;
	double nBlue = static_cast<double>(rgbPixel[2]) / 255.0;

	nRed = (nRed > 0.04045) ? std::pow((nRed + 0.055) / 1.055, 2.4) : nRed / 12.92;
	nGreen = (nGreen > 0.04045) ? std::pow((nGreen + 0.055) / 1.055, 2.4) : nGreen / 12.92;
	nBlue = (nBlue > 0.04045) ? std::pow((nGreen + 0.055) / 1.055, 2.4) : nBlue / 12.92;

	nRed = nRed * 100;
	nGreen = nGreen * 100;
	nBlue = nBlue * 100;

	xyzPixel[0] = nRed * 0.4124 + nGreen * 0.3576 + nBlue * 0.1805;
	xyzPixel[1] = nRed * 0.2126 + nGreen * 0.7152 + nBlue * 0.0722;
	xyzPixel[2] = nRed * 0.0193 + nGreen * 0.1192 + nBlue * 0.9505;

	return xyzPixel;

}

/*
 * to CIELAB
 *
 * */
template<typename xyzType, typename labType>
inline typename labType::PixelType xyzToLab(const typename xyzType::PixelType& xyzPixel)
{
	typename labType::PixelType labPixel;

	double var_X = xyzPixel[0] / 95.047;
	double var_Y = xyzPixel[1] / 100.0;
	double var_Z = xyzPixel[2] / 108.883;

	//1/3 = 0.333333
	//1/116 = 0.137931034
	var_X = (var_X > 0.008856) ? std::pow(var_X, 0.333333333) : (7.787 * var_X) + 0.137931034;
	var_Y = (var_Y > 0.008856) ? std::pow(var_Y, 0.333333333) : (7.787 * var_Y) + 0.137931034;
	var_Z = (var_Z > 0.008856) ? std::pow(var_Z, 0.333333333) : (7.787 * var_Z) + 0.137931034;

	labPixel[0] = (116 * var_Y) - 16;
	labPixel[1] = 500 * (var_X - var_Y);
	labPixel[2] = 200 * (var_Y - var_Z);

	return labPixel;

}

template<typename rgbType, typename labType>
inline typename labType::PixelType rgbToLab(const typename rgbType::PixelType& rgbPixel)
{
	return xyzToLab<labType, labType>(rgbToXyz<rgbType, labType>(rgbPixel));
}

}
#endif /* SRC_COMMON_COLORTRANSFORMS_H_ */
