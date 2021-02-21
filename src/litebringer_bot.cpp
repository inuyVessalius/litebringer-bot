#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <Windows.h>

void runAutoClicker();

cv::Point findImageOnScreen(cv::Mat img, std::string path);

cv::Mat screenshot();

void click(cv::Point point);

void camera();

int main()
{
	std::cout << "Hold Esc to exit.\n";

	do {
		runAutoClicker();
	} while (GetAsyncKeyState(VK_ESCAPE) == 0);

	// camera();

	return 0;
}

void runAutoClicker()
{
	cv::Point scrollPos = findImageOnScreen(screenshot(), "assets/scroll_done.png");

	if (scrollPos != cv::Point(-1, -1)) {

		click(scrollPos);

		cv::Point sendOnQuestPos;

		do {
			sendOnQuestPos = findImageOnScreen(screenshot(), "assets/send_on_quest.png");
		} while (sendOnQuestPos == cv::Point(-1, -1) and GetAsyncKeyState(VK_ESCAPE) == 0);

		click(sendOnQuestPos);

		cv::Point confirmPos;

		do {
			confirmPos = findImageOnScreen(screenshot(), "assets/confirm.png");
		} while (confirmPos == cv::Point(-1, -1) and GetAsyncKeyState(VK_ESCAPE) == 0);

		click(confirmPos);
	}
}


cv::Point findImageOnScreen(cv::Mat _screenshot, std::string _image)
{
	double minVal, maxVal;
	cv::Point minLoc, maxLoc, matchLoc = cv::Point(-1, -1);

	cv::Mat image = cv::imread(_image, cv::IMREAD_COLOR), result, screenshot;

	_screenshot.copyTo(screenshot);
	int result_cols = screenshot.cols, result_rows = screenshot.rows;

	result.create(result_rows, result_cols, CV_32FC1);

	matchTemplate(screenshot, image, result, cv::TM_CCOEFF_NORMED);

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

	if (maxVal >= 0.8) {
		// rectangle(screenshot, matchLoc, cv::Point(matchLoc.x + image.cols, matchLoc.y + image.rows), cv::Scalar::all(0), 2, 8, 0);
		// rectangle(result, matchLoc, cv::Point(matchLoc.x + image.cols, matchLoc.y + image.rows), cv::Scalar::all(0), 2, 8, 0);
		// 
		// imshow("image_window", screenshot);
		// cv::waitKey(0);
		// imshow("result_window", result);
		// cv::waitKey(0);
		matchLoc = maxLoc + cv::Point(image.cols / 2, image.rows / 2);
	}

	return matchLoc;
}

cv::Mat screenshot()
{
	cv::Mat src;
	HDC dcScreen = GetDC(NULL);
	HDC dcTarget = CreateCompatibleDC(dcScreen); // and a device context to put it in
	BITMAPINFOHEADER  bitmapInfoH;

	int width = GetDeviceCaps(dcScreen, HORZRES), height = GetDeviceCaps(dcScreen, VERTRES);

	src.create(height, width, CV_8UC4);

	HBITMAP hBitmap = CreateCompatibleBitmap(dcScreen, width, height);

	// get a new bitmap
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(dcTarget, hBitmap);

	BitBlt(dcTarget, 0, 0, width, height, dcScreen, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(dcTarget, hOldBitmap);

	bitmapInfoH.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bitmapInfoH.biWidth = width;
	bitmapInfoH.biHeight = -height;  // positive = upside down, negative = normal
	bitmapInfoH.biPlanes = 1;
	bitmapInfoH.biBitCount = 32;
	bitmapInfoH.biCompression = BI_RGB;
	bitmapInfoH.biSizeImage = 0;
	bitmapInfoH.biXPelsPerMeter = 0;
	bitmapInfoH.biYPelsPerMeter = 0;
	bitmapInfoH.biClrUsed = 0;
	bitmapInfoH.biClrImportant = 0;

	GetDIBits(dcTarget, hBitmap, 0, height, src.data, (BITMAPINFO*)&bitmapInfoH, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

	// clean up
	DeleteObject(hBitmap);
	DeleteDC(dcTarget);
	DeleteDC(dcScreen);

	cv::cvtColor(src, src, cv::COLOR_RGBA2RGB);

	return src;
}

void click(cv::Point point)
{
	if (point != cv::Point(-1, -1)) {
		INPUT inputs[2];
		ZeroMemory(inputs, sizeof(inputs));

		SetCursorPos(point.x, point.y);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
}


void camera()
{
	cv::VideoCapture cap(0);
	cv::Mat img;

	while (true) {
		cap.read(img);

		cv::imshow("video", img);
		cv::waitKey(1);
	}
}
