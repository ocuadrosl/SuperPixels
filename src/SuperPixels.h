/*
 * SuperPixels.h
 *
 *  Created on: Sep 20, 2018
 *      Author: oscar
 */

#ifndef SRC_SUPERPIXELS_H_
#define SRC_SUPERPIXELS_H_

#include "common/ColorTransforms.h"

#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "common/Math.h"

template<typename imageType>
class SuperPixels
{

private:

	//typedefs
	static const unsigned DIMENSION = imageType::IndexType::Dimension;
	//input RGB image Type
	using imagePointer = typename imageType::Pointer;

	//CIELAB image type
	using labType=itk::RGBPixel<double>;
	using labImageType=itk::Image<labType, DIMENSION>;
	using labImagePointer = typename labImageType::Pointer;

	//label image type
	using labelImageType=itk::Image<unsigned short, DIMENSION>;
	using labelImagePointer = typename labelImageType::Pointer;

	imagePointer inputImage;

	//variables
	labImagePointer labImage; //CIELAB
	labelImagePointer labelImage;
	unsigned spLengthSize; //super pixels length size
	unsigned spNumber;

	//to store color and index means
	std::vector<labType> spPixelMeans;
	std::vector<typename labImageType::IndexType> spIndexMeans;

	//methods
	void inputImageToCielab();
	void updateLabelSp();
	void createLabelImage();

public:
	SuperPixels();
	~SuperPixels()
	{
	}
	;

	void setImage(const imagePointer& inputImage);
	void compute();
	void SetSpLenghSize(unsigned length);

};

template<typename imageType>
SuperPixels<imageType>::SuperPixels()
{

	spLengthSize = 10;
	spNumber = 1;
}

template<typename imageType>
void SuperPixels<imageType>::updateLabelSp()
{


}
template<typename imageType>
void SuperPixels<imageType>::SetSpLenghSize(unsigned length)
{
	this->spLengthSize = length;

}

template<typename imageType>
void SuperPixels<imageType>::createLabelImage()
{

	//create label image
	labelImage = labelImageType::New();
	typename labelImageType::SizeType size;
	for (unsigned i = 0; i < DIMENSION; ++i)
	{
		size[i] = inputImage->GetLargestPossibleRegion().GetSize()[i];
	}
	typename labImageType::RegionType region;
	region.SetSize(size);
	labelImage->SetRegions(region);
	labelImage->Allocate();

	//compute super pixels size and umber of super pixels
	typename imageType::SizeType imageSize = inputImage->GetLargestPossibleRegion().GetSize();
	typename labelImageType::SizeType spSize;
	spSize.Fill(0);
	for (unsigned i = 0; i < DIMENSION; ++i)
	{

		spSize[i] = imageSize[i] / spLengthSize;
		spNumber *= spSize[i];
	}

	//set labels
	itk::ImageRegionIteratorWithIndex<labelImageType> labelIt(labelImage, labelImage->GetLargestPossibleRegion());

	typename labelImageType::IndexType index;
	typename labelImageType::IndexType indexAux;
	unsigned label = 0;

	for (labelIt.GoToBegin(); !labelIt.IsAtEnd(); ++labelIt)
	{
		index = labelIt.GetIndex();
		for (unsigned i = 0; i < DIMENSION; ++i)
		{
			indexAux[i] = std::floor(math::minMax<unsigned>(index[i], 0, imageSize[i], 0, spSize[i]));
		}

		label = math::matrixTovectorIndex<typename labelImageType::IndexType>(indexAux, spSize[1]);

		labelIt.Set(label);

	}

	io::writeImage < labelImageType > (labelImage, "/home/oscar/src/SuperPixels/output/grid.png");

}

template<typename imageType>
void SuperPixels<imageType>::compute()
{
	inputImageToCielab();
	createLabelImage();

}

template<typename imageType>
void SuperPixels<imageType>::inputImageToCielab()
{

	//creating a new image
	labImage = labImageType::New();

	typename labImageType::SizeType size;

	for (unsigned i = 0; i < DIMENSION; ++i)
	{
		size[i] = inputImage->GetLargestPossibleRegion().GetSize()[i];
	}
	typename labImageType::RegionType region;
	region.SetSize(size);
	labImage->SetRegions(region);

	labImage->Allocate();

	itk::ImageRegionIterator < imageType > inputIt(inputImage, inputImage->GetLargestPossibleRegion());
	itk::ImageRegionIterator<labImageType> labIt(labImage, labImage->GetLargestPossibleRegion());
	labIt.GoToBegin();
	inputIt.GoToBegin();

	//rgb to cielab
	for (; !inputIt.IsAtEnd(); ++inputIt, ++labIt)
	{
		labIt.Set(ct::rgbToLab<imageType, labImageType>(inputIt.Get()));
		//labIt.Set(ct::xyzToLab<labImageType, labImageType>(ct::rgbToXyz<imageType, labImageType>(inputIt.Get())));
	}

}

template<typename imageType>
void SuperPixels<imageType>::setImage(const imagePointer& inputImage)
{
	this->inputImage = inputImage;

}

#endif /* SRC_SUPERPIXELS_H_ */
