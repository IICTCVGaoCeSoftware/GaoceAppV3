#pragma once
#include "GaoCe.hpp"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include <Eyestack/Design/ImageBench.hpp>
#include <Eyestack/Design/Progressor.hpp>
#include <Eyestack/Framework.hpp>

namespace esb = Eyestack::Base;
namespace esd = Eyestack::Design;

// ==========================================================================
// MVS_Calibration
// ==========================================================================

/**
 * @brief 相机标定窗口
 */
class MVS_Calibration : public QWidget
{
  Q_OBJECT

  using _T = MVS_Calibration;
  using _S = QWidget;

public:
  std::function<cv::Mat()> _getInput = []() { return cv::Mat(); };

public:
  MVS_Calibration(GaoCe::GaoCe& algo, QWidget* parent = nullptr);

private:
  struct CalibCamProcessParam
  {
    // 输入，该窗口相机采集的角点
    std::vector<cv::Mat> _camCornersMat;
    //输入，包括每一张图像的行列方向的棋盘格个数
    std::vector<cv::Size> _camPatternSize;

    double _camRealDx; //输入，棋盘格x方向的真实尺寸
    double _camRealDy; //输入，棋盘格y方向的真实尺寸
  };

  struct CalibCamResult
  {
    cv::Mat _camInMatrix;   //输出，标定得到的相机内参矩阵
    cv::Mat _camExMatrix;   //输出，标定得到的相机外参矩阵
    cv::Mat _camDistortion; //输出，标定得到的相机畸变系数
    cv::Mat _camReprojErr;  //输出，重投影误差
  };

  struct CalibOutputParam
  {
    cv::Mat _camOriPt;             //  相机原点
    cv::Mat _dirLineVectors;       // 相机直线的方向向量
    cv::Mat _internalCamParamMat;  // 相机内参
    cv::Mat _externalPlaneMat;     // 投影仪面方程信息
    cv::Mat _externalProjParamMat; // 投影仪外参
    cv::Mat _internalProjParamMat; //  投影仪内参
  };

  struct ReconstructParam
  {
    cv::Mat _camOriPt;            //  相机原点
    cv::Mat _dirLineVectors;      // 相机直线的方向向量
    cv::Mat _internalCamParamMat; // 相机内参
    cv::Mat _externalPlaneMat;    // 投影仪面方程信息
    int _offsetGrayCode;          // 格雷码偏移值
    int _numPlanes;               //  平面的个数
    int _projMaxValue;            // 投影仪的投射最大值
    float _minThresholdContrast;  //  对比度
  };

  struct TransformDepthImageParam
  {
    cv::Mat _externalProjParamMat; // 投影仪外参
    cv::Mat _internalProjParamMat; //投影仪内参
    cv::Size _depthImageSize;      //深度图像大小
    float _scaleDepth;             //尺度系数
    pcl::PointCloud<pcl::PointXYZ>* _cloud;
  };

public:
  // 标定相机窗口，点击刷新按钮，算法自动提取角点
  void find_camcorners(
    cv::Mat& camImg,         //输入，相机采集的单张图像
    cv::Size camPatternSize, //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
  );
  // 相机标定窗口，点击标定按钮，得到相机的内外参数和畸变系数
  void camera_calib(CalibCamProcessParam& calibCamProcessParam);

private:
  GaoCe::GaoCe& _algo;
  QWidget _leftWidget;
  QStackedLayout _leftLayout;
  esd::ImageBench _bench;
  QLabel _imageNum, _chessNum, _chessSize, _errorShow, _cornerPoint;
  QSpinBox _imageSpin, _rowNumSpin, _colNumSpin;
  QSpinBox _rowSize, _colSize;
  QPushButton _refreshButton, _calButton, _reCalButton;
  QPushButton _selPoint, _noSelPoint;
};
