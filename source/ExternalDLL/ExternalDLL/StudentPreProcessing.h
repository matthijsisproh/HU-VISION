/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "PreProcessing.h"
#include "ImageFactory.h"
#include <vector>

class StudentPreProcessing : public PreProcessing {
public:
	IntensityImage * stepToIntensityImage(const RGBImage &image) const;
	IntensityImage * stepScaleImage(const IntensityImage &image) const;
	IntensityImage * stepEdgeDetection(const IntensityImage &image) const;
	IntensityImage * stepThresholding(const IntensityImage &image) const;
private:
	//function that will apply a filter to an image
	//filter has to be square and uneven sized
	IntensityImage* applyFilterToImage(const IntensityImage& image, const std::vector<std::vector<int>>& filter, int divide_factor = 1) const;
};