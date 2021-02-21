#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <d3d9helper.h>

#ifndef __X_H_INCLUDED__
#define __X_H_INCLUDED__

void runAutoClicker();

cv::Point findImageOnScreen(cv::Mat img, std::string path);

cv::Mat screenshot();

void click(cv::Point point);

void camera();

#endif