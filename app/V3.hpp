#pragma once

#include "GaoCe.hpp"
#include <Eyestack/Base.hpp>

namespace GaoCe {

namespace esb = Eyestack::Base;

/**
 * @brief 高测算法 V1 版
 *
 * 首先调用 learn_brightness_threshold、learn_real_ratio、learn_real_ratio
 * 训练算法参数，然后调用 detect 进行缺陷检测。
 */
class V3 : public GaoCe
{
  // GaoCe interface
public:
  virtual void recon_pcl_with_gray_liting(
    std::vector<cv::Mat>& inputImgs,
    pcl::PointCloud<pcl::PointXYZ>* cloud) override;
  virtual void transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
                                     CV_OUT cv::Mat* depthImage) override;

  virtual void find_camcorners(
    cv::Mat& camImg,         //输入，相机采集的单张图像
    cv::Size camPatternSize, //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
    ) override;

  virtual void camera_calib(
    CalibCamProcessParam& calibCamProcessParam) override;

  virtual void find_procorners(
    cv::Mat& proImg,              //输入，相机采集的单张图像
    cv::Mat& cornersCoarse,       //输入，粗角点信息
    cv::Size proPatternSize,      //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* proCorners,   //输出，投影图案角点的像素坐标
    CV_OUT cv::Mat* proCamCorners //输出，棋盘格角点的像素坐标
    ) override;

  virtual void rays_palnes(CV_OUT CalibOutputParam* calibOutputParam) override;

  virtual void projector_calib(
    CalibProjProcessParam& calibProjProcessParam) override;

  virtual void data_transform() override;
};

}
