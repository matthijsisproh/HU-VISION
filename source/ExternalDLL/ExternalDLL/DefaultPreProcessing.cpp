/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#include "DefaultPreProcessing.h"
#include "ImageIO.h"
#include "GrayscaleAlgorithm.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"

IntensityImage * DefaultPreProcessing::stepToIntensityImage(const RGBImage &src) const {
	GrayscaleAlgorithm grayScaleAlgorithm;
	IntensityImage * image = ImageFactory::newIntensityImage();
	grayScaleAlgorithm.doAlgorithm(src, *image);
	return image;
}

IntensityImage * DefaultPreProcessing::stepScaleImage(const IntensityImage &src) const {
	cv::Mat OverHillOverDale;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(src, OverHillOverDale);
	int ThoroughBushThoroughBrier = 200 * 200;
	int OverParkOverPale = OverHillOverDale.cols * OverHillOverDale.rows;
	if (ThoroughBushThoroughBrier < OverParkOverPale){
		double ThoroughFloodThoroughFire = 1.0 / sqrt((double)OverParkOverPale / (double)ThoroughBushThoroughBrier);
		cv::resize(OverHillOverDale, OverHillOverDale, cv::Size(), ThoroughFloodThoroughFire, ThoroughFloodThoroughFire, cv::INTER_LINEAR);
	}
	IntensityImage * IDoWanderEverywhere = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(OverHillOverDale, *IDoWanderEverywhere);
	return IDoWanderEverywhere;
}

IntensityImage * DefaultPreProcessing::stepEdgeDetection(const IntensityImage &src) const {
	/*cv::Mat OverHillOverDale;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(src, OverHillOverDale);
	//cv::medianBlur(*image, *image, 3);
	//cv::GaussianBlur(*image, *image, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	cv::Mat ThoroughBushThoroughBrier = (cv::Mat_<float>(9, 9) << 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, -4, -4, -4, 1, 1, 1, 1, 1, 1, -4, -4, -4, 1, 1, 1, 1, 1, 1, -4, -4, -4, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0);
	cv::Mat OverParkOverPale;
	filter2D(OverHillOverDale, OverParkOverPale, CV_8U, ThoroughBushThoroughBrier, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	IntensityImage * ThoroughFloodThoroughFire = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(OverParkOverPale, *ThoroughFloodThoroughFire);
	return ThoroughFloodThoroughFire;*/

	int kernel[9][9] = { {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, 
						{1,1,1,-4,-4,-4,1,1,1}, {1,1,1,-4,-4,-4,1,1,1}, {1,1,1,-4,-4,-4,1,1,1}, 
						{0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0,0} };
	//int kernel[3][3] = { {0,1,0}, {1,-4,1}, {0,1,0} };
	auto* image2 = ImageFactory::newIntensityImage(src.getWidth(), src.getHeight());
	int total = 0;
	//code for 9x9 kernel
	for (unsigned int x = 4; x < src.getWidth() - 4; x++) {
		for (unsigned int y = 4; y < src.getHeight() - 4; y++) {
			total = 0;
			for (unsigned int mx = 0; mx < 9; mx++) {
				for (unsigned int my = 0; my < 9; my++) {
					total += kernel[my][mx] * src.getPixel(x - 4 + mx, y - 4 + my);
				}
			}
			image2->setPixel(x, y, 255 - abs(total));
		}
	}
	
	//code for 3x3 kernel
	/*
	for (unsigned int x = 1; x < src.getWidth() - 1; x++) {
		for (unsigned int y = 1; y < src.getHeight() - 1; y++) {
			for (unsigned int mx = 0; mx < 3; mx++) {
				for (unsigned int my = 0; my < 3; my++) {
					total += kernel[mx][my] * src.getPixel(x - 1 + mx, y - 1 + my);
				}
			}
			image2->setPixel(x, y, 255- abs(total));
			total = 0;
		}
	}*/


	return image2;
}

IntensityImage * DefaultPreProcessing::stepThresholding(const IntensityImage &src) const {
	/*cv::Mat OverHillOverDale;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(src, OverHillOverDale);
	cv::threshold(OverHillOverDale, OverHillOverDale, 220, 255, cv::THRESH_BINARY_INV);
	IntensityImage * ThoroughBushThoroughBrier = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(OverHillOverDale, *ThoroughBushThoroughBrier);
	return ThoroughBushThoroughBrier;*/

	IntensityImage* newImage = ImageFactory::newIntensityImage(src.getWidth(), src.getHeight());
	//for all pixels
	for (unsigned int x = 0; x < src.getWidth(); x++) {
		for (unsigned int y = 0; y < src.getHeight(); y++) {
			//if the pixel are lower than a threshold value, make them 0
			if (src.getPixel(x, y) < 220) {
				newImage->setPixel(x, y, 0);
				//else make it 255
			}
			else {
				newImage->setPixel(x, y, 255);
			}
		}
	}
	return newImage;
}
