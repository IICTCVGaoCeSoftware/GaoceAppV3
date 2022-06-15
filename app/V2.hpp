//#pragma once

//#include "GaoCe.hpp"
//#include "calib_3D.hpp"
//#include "recon_3D.hpp"
//#include <Eyestack/Base.hpp>
//#include <Eyestack/Design/Paramgr.hpp>

//// pcl导入测试
//#include <pcl/io/pcd_io.h>

// namespace GaoCe {

// namespace esb = Eyestack::Base;
// namespace esd = Eyestack::Design;
// namespace esdp = esd::paramgr;

///**
// * @brief 高测算法
// */
// class V2 : public GaoCe
//{
// public:
//  V2();
//  ~V2();

// public:
//   virtual void recon_pcl_with_gray_liting(
//     std::vector<cv::Mat>& inputImgs,
//     pcl::PointCloud<pcl::PointXYZ>* cloud) override;
//   virtual void transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
//                                      CV_OUT cv::Mat* depthImage) override;
//   virtual void find_camcorners(
//     cv::Mat& camImg,         //输入，相机采集的单张图像
//     cv::Size camPatternSize, //输入，行列方向的棋盘格个数
//     CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
//     ) override;
//   virtual void camera_calib(
//     CalibCamProcessParam& calibCamProcessParam) override;

//  virtual void find_procorners(
//    cv::Mat& proImg,              //输入，相机采集的单张图像
//    cv::Mat& cornersCoarse,       //输入，粗角点信息
//    cv::Size proPatternSize,      //输入，行列方向的棋盘格个数
//    CV_OUT cv::Mat* proCorners,   //输出，投影图案角点的像素坐标
//    CV_OUT cv::Mat* proCamCorners //输出，棋盘格角点的像素坐标
//    ) override;

//  virtual void projector_calib(
//    CalibProjProcessParam& calibProjProcessParam) override;

//  virtual void rays_palnes(CalibOutputParam* calibOutputParam) override;

//  virtual void data_transform() override;
//  struct ParamInfoCollectStructure
//  {
//    cv::Size _camImgSize;
//    cv::Size _proResolution;
//    cv::Mat _camDistortion;
//    cv::Mat _proDistortion;
//    cv::Mat _camOriPt;
//    cv::Mat _dirLineVectors;
//    cv::Mat _externalPlaneMat;
//    cv::Mat _internalCamParamMat;
//    cv::Mat _externalCamParamMat;
//    cv::Mat _externalProjParamMat;
//    cv::Mat _internalProjParamMat;
//    float _scaleDepth;
//  };
//  ParamInfoCollectStructure _paramInfoCollectStructure;
//  // GaoCe interface
// private:
//  esb::Profiler _profiler;

//  bool _reseted{ true };

//  esd::Paramgr::Table _paramTable;
//};
//}

// void
// transformDataStructure(
//   GaoCe::V2::ParamInfoCollectStructure& paramInfoCollectStructure,
//   GaoCe::ReconstructParam& reconstructParam,
//   GaoCe::TransformDepthImageParam& transformDepthImageParam);

// void
// init_reconstruct_param(
//   ReconstructRealTimeInputParam& reconstructParam,
//   GaoCe::V2::ParamInfoCollectStructure& paramInfoCollectStructure);
// void
// test_reconstruct_param(
//   ReconstructRealTimeInputParam& reconstructRealTimeInputParam,
//   GaoCe::V2::ParamInfoCollectStructure& paramInfoCollectStructure);
// void
// test_depthGeneration_param(
//   GaoCe::TransformDepthImageParam& transformDepthImageParam);
