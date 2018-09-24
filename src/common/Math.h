/*
 * Math.h
 *
 *  Created on: Sep 22, 2018
 *      Author: oscar
 */

#ifndef SRC_COMMON_MATH_H_
#define SRC_COMMON_MATH_H_

namespace math
{
template<typename type>
inline double minMax(type valueIn, type originalMin, type originalMax, type newMin, type newMax)
{
	double den;

	den = (originalMax == originalMin) ? 0.000000001 : static_cast<double>(originalMax) - static_cast<double>(originalMin);

	return ((static_cast<double>(newMax) - static_cast<double>(newMin)) * (static_cast<double>(valueIn) - static_cast<double>(originalMin)) / den) + static_cast<double>(newMin);
}

/*
 *
 * 2d
 *
 * */
template<typename indexType>
inline unsigned matrixTovectorIndex(indexType index, unsigned height)
{
	return index[0] * height + index[1];
}

}

#endif /* SRC_COMMON_MATH_H_ */
