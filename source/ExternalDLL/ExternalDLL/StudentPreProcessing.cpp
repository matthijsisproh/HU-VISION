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
	IntensityImage* image2 = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	int width = image2->getWidth();
	int height = image2->getHeight();

	//code that will optimise the algorithm that applies the horizontal filter on the image and stores it in a new image
	int values[3] = { 0,0,0 };
	uint_fast8_t valueToCalculate = 2;
	IntensityImage* imageHorizontalEdges = ImageFactory::newIntensityImage(width, height);
	for (unsigned int x = 1; x < width - 1; x++) {
		//calculate the first two horizontal values
		values[0] = -1 * image.getPixel(x - 1, 0) + image.getPixel(x + 1, 0);
		values[1] = -1 * image.getPixel(x - 1, 1) + image.getPixel(x + 1, 1);
		valueToCalculate = 2;
		//then, only calculate one each time, delete one that is not needed anymore and add all values together 
		for (unsigned int y = 1; y < height - 1; y++) {
			values[valueToCalculate] = -1 * image.getPixel(x - 1, y + 1) + image.getPixel(x + 1, y + 1);
			imageHorizontalEdges->setPixel(x, y, abs(values[0] + values[1] + values[2]));
			if (valueToCalculate == 2) {
				valueToCalculate = 0;
			}else {
				valueToCalculate++;
			}
		}
	}

	//same as above but for the the vertical filter
	IntensityImage* imageVerticalEdges = ImageFactory::newIntensityImage(width, height);
	for (unsigned int y = 1; y < height - 1; y++) {
		values[0] = -1 * image.getPixel(0, y - 1) + image.getPixel(0, y + 1);
		values[1] = -1 * image.getPixel(1, y - 1) + image.getPixel(1, y + 1);
		valueToCalculate = 2;
		for (unsigned int x = 1; x < width - 1; x++) {
			values[valueToCalculate] = -1 * image.getPixel(x + 1, y - 1) + image.getPixel(x + 1, y + 1);
			imageVerticalEdges->setPixel(x, y, abs(values[0] + values[1] + values[2]));
			if (valueToCalculate == 2) {
				valueToCalculate = 0;
			}
			else {
				valueToCalculate++;
			}
		}
	}
	//then combine the two images to the finale image
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			image2->setPixel(i, j, 255 - sqrt(imageHorizontalEdges->getPixel(i, j) * imageHorizontalEdges->getPixel(i, j) + imageVerticalEdges->getPixel(i, j) * imageVerticalEdges->getPixel(i, j)));
		}
	}

	//make the sides and edges of the picture white
	for (unsigned int i = 0; i < height; i++) {
		image2->setPixel(0, i, 255);
		image2->setPixel(width - 1, i, 255);
	}
	for (unsigned int i = 1; i < width - 1; i++) {
		image2->setPixel(i, 0, 255);
		image2->setPixel(i, height - 1, 255);
	}

	//delete all allocated images
	delete imageHorizontalEdges;
	delete imageVerticalEdges;
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