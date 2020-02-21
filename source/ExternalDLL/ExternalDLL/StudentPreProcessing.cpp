#include "StudentPreProcessing.h"
#include <iostream>
#include <array>

// Do nothing
IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

// Do nothing
IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

// Edge Detection
IntensityImage* StudentPreProcessing::stepEdgeDetection(const IntensityImage& image) const {
	int kernel[9][9] = {{0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, 
						{1,1,1,-4,-4,-4,1,1,1}, {1,1,1,-4,-4,-4,1,1,1}, {1,1,1,-4,-4,-4,1,1,1}, 
						{0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}
						};
	auto * image2 = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	*image2 = image;
	int total = 0;
	for (unsigned int x = 4; x < image.getWidth() - 4; x++) {
		for (unsigned int y = 4; y < image.getHeight() - 4; y++) {
			total = 0;
			for (unsigned int mx = 0; mx < 9; mx++) {
				for (unsigned int my = 0; my < 9; my++) {
					total += kernel[mx][my] * image.getPixel(x - 4 + mx, y - 4 + my);
				}
			}
			image2->setPixel(x, y, abs(total));
			total = 0;
		}
	}
	return image2;
}

// Thresholding
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