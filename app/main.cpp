#include "GaoCe.hpp"
#include "Worker.hpp"
#include "version.hpp"
#include "wrapper.hpp"

int
main(int argc, char* argv[])
{
  auto test = GaoCe::create_v1();
  cv::Mat image = cv::imread("E:/C1.bmp");
  // cv::Mat image;
  cv::Size camImgSize = cv::Size(2592, 2048);
  cv::Mat imgCamGray;
  cv::cvtColor(image, imgCamGray, cv::COLOR_BGR2GRAY);
  cv::Mat result;
  test->find_camcorners(imgCamGray, camImgSize, &result);
  cv::imwrite("D:/result.png", result);
}

