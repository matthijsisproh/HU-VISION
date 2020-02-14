#include "StudentPreProcessing.h"
#include <iostream>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage * newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	std::cout << "test";
	//for all pixels
	for(unsigned int x = 0; x < image.getWidth(); x++){
		for(unsigned int y = 0; y < image.getHeight(); y++){
			//if the pixel are lower than a threshold value, make them white
			if(image.getPixel(x, y) < 220){
				newImage->setPixel(x, y, 0);
			//else make it black
			}else{
				newImage->setPixel(x, y, 255);
			}
		}
	}
	return newImage;
}