#include "StudentPreProcessing.h"
#include <iostream>

IntensityImage* StudentPreProcessing::applyFilterToImage(const IntensityImage& image, const std::vector<std::vector<int>>& filter, int divide_factor)const{
	float total = 0;
	IntensityImage* image2 = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	//offset is used to start and end the for loop so that the filter doesnt go out of bounds
	uint_fast8_t offset = (filter.size() - 1) / 2;
	for (unsigned int x = offset; x < image.getWidth() - offset; x++) {
		for (unsigned int y = offset; y < image.getHeight() - offset; y++) {
			total = 0;
			for (int mx = 0; mx < filter.size(); mx++) {
				for (int my = 0; my < filter.size(); my++) {
					//add the computed value to the total
					total += filter[my][mx] * image.getPixel((x - offset) + mx, (y - offset) + my);
				}
			}
			//then assign the total the the pixel in a new image
			image2->setPixel(x, y, abs(total) / divide_factor);
		}
	}
	return image2;
}

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
	float total = 0;
	//std::vector<std::vector<int>> gaussian_smoother = { {1,4,7,4,1}, {4,16,26,16,4}, {7,26,41,26,7}, {4,16,26,16,4}, {1,4,7,4,1} };
	std::vector<std::vector<int>> gaussian_smoother = { {1,2,1}, {2,4,2}, {1,2,1} };
	
	//IntensityImage* gaussian_smoothed_image = applyFilterToImage(image, gaussian_smoother, 16);

	std::vector<std::vector<int>> kernel_horizontal = { {-1,-1,-1}, {0,0,0}, {1,1,1} };
	std::vector<std::vector<int>> kernel_vertical = { {-1,0,1}, {-1,0,1}, {-1,0,1} };
	/*float kernel[9][9] = { {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0},
						{1,1,1,-4,-4,-4,1,1,1}, {1,1,1,-4,-4,-4,1,1,1}, {1,1,1,-4,-4,-4,1,1,1},
						{0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0} };*/
	/*float kernel[9][9] = { {0,1,1,2,2,2,1,1,0}, {1,2,4,5,5,5,4,2,1}, {1,4,5,3,0,3,5,4,1},
						{2,5,3,-12,-24,-12,3,5,2}, {2,5,0,-24,-40,-24,0,5,2}, {2,5,3,-12,-24,-12,3,5,2},
						{1,4,5,3,0,3,5,4,1}, {1,2,4,5,5,5,4,2,1}, {0,1,1,2,2,2,1,1,0} };*/
	IntensityImage* image2 = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	//code for 3x3 kernel
	IntensityImage* imageHorizontalEdges = applyFilterToImage(image, kernel_horizontal);
	IntensityImage* imageVerticalEdges = applyFilterToImage(image, kernel_vertical);

	for (unsigned int i = 0; i < image.getWidth(); i++) {
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			image2->setPixel(i, j, 255 - sqrt(imageHorizontalEdges->getPixel(i, j) * imageHorizontalEdges->getPixel(i, j) + imageVerticalEdges->getPixel(i, j) * imageVerticalEdges->getPixel(i, j)));
		}
	}
	return image2;
}

// Thresholding
IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	/*float average_pixel = 0;
	for (unsigned int i = 0; i < image.getWidth(); i++) {
		for (unsigned int j = 0; j < image.getHeight(); j++) {
			average_pixel += image.getPixel(i, j);
		}
	}
	average_pixel /= (image.getHeight() * image.getWidth());
	std::cout << int(average_pixel);*/
	IntensityImage* newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	//for all pixels
	for (unsigned int x = 0; x < image.getWidth(); x++) {
		for (unsigned int y = 0; y < image.getHeight(); y++) {
			//if the pixel are lower than a threshold value, make them 0
			if (image.getPixel(x, y) < 220) {
				newImage->setPixel(x, y, 0);
				//else make it 255
			}else {
				newImage->setPixel(x, y, 255);
			}
		}
	}
	return newImage;
}