/*
 * InputOutput.h
 *
 *  Created on: Jan 5, 2018
 *      Author: oscar
 */

#ifndef SRC_COMMON_INPUTOUTPUT_H_
#define SRC_COMMON_INPUTOUTPUT_H_

#include <vector>
#include "itkNumericSeriesFileNames.h"
#include "itkImageFileWriter.h"
#include "itkImageFileReader.h"
#include "itkCastImageFilter.h"
#include <dirent.h>
#include <iomanip>
#include "itkMeshFileWriter.h"
#include "itkTriangleMeshToBinaryImageFilter.h"

namespace io
{

void print(const std::string& message, const bool & ok, short size = 50)
{

	short diff = size - message.length();

	if (ok)
	{
		std::cout << message << std::setfill(' ') << std::setw(diff) << "[OK]" << std::endl;
	}
	else
	{
		//std::cout << message << std::setfill(' ') << std::setw(diff) << "[FAIL]" << std::endl;
	}

}




template<typename imageType>
void writeImage(const typename imageType::Pointer &image, const std::string &fileName, const std::string& message = "")
{

	typedef itk::ImageFileWriter<imageType> writer_t;
	typename writer_t::Pointer writer = writer_t::New();
	writer->SetFileName(fileName);
	writer->SetInput(image);
	writer->Update();

	print("Writing image " + message, true);
}

template<typename imageType>
typename imageType::Pointer readImage(const std::string& file_name)
{

	typedef itk::ImageFileReader<imageType> readerType;

	typename readerType::Pointer reader = readerType::New();

	reader->SetFileName(file_name);

	try
	{
		reader->Update();

	} catch (itk::ExceptionObject & e)
	{
		std::cerr << "Exception reading: " << file_name << " null pointer is returned" << std::endl;
		typename imageType::Pointer nullImage;
		return nullImage;
	}

	return reader->GetOutput();

}


template<typename inputType, typename outputType>
typename outputType::Pointer imageCast(typename inputType::Pointer inputImage)
{
	typedef itk::CastImageFilter<inputType, outputType> castFilterType;
	typename castFilterType::Pointer castFilter = castFilterType::New();
	castFilter->SetInput(inputImage);
	castFilter->Update();

	return castFilter->GetOutput();
}



}
#endif /* SRC_COMMON_INPUTOUTPUT_H_ */
