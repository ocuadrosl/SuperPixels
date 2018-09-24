#include <iostream>

#include "itkImage.h"
#include "itkRGBPixel.h"

#include "common/InputOutput.h"
#include "SuperPixels.h"

int main()
{

	//typedefs
	const unsigned DIMENSION = 2;
	using componentType = unsigned char;
	using rgbType=itk::RGBPixel<componentType>;
	using rgbImageType=itk::Image<rgbType, DIMENSION>;
	using rgbImagePointer = rgbImageType::Pointer;

	rgbImagePointer image = io::readImage<rgbImageType>("/home/oscar/MEGA/post-doc/src/input/rp/patient_1/00529 (1).jpg");

	SuperPixels<rgbImageType> superPixels;
	superPixels.setImage(image);
	superPixels.SetSpLenghSize(50);
	superPixels.compute();

	//rgbImageType::PixelType::Dimension

	std::cout << "DONE" << std::endl;

	return 0;

}
