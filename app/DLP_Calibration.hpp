#pragma once
#include "GaoCe.hpp"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include <Eyestack/Design/ImageBench.hpp>
#include <Eyestack/Design/Progressor.hpp>
#include <Eyestack/Design/QuadrangleSelector.hpp>
#include <Eyestack/Framework.hpp>

namespace esb = Eyestack::Base;
namespace esd = Eyestack::Design;

// ==========================================================================
// DLP_Calibration
// ==========================================================================

/**
 * @brief 投影仪标定窗口
 */
class DLP_Calibration : public QWidget
{
  Q_OBJECT

  using _T = DLP_Calibration;
  using _S = QWidget;

public:
  std::function<cv::Mat()> _getInput = []() { return cv::Mat(); };

public:
  DLP_Calibration(GaoCe::GaoCe& algo, QWidget* parent = nullptr);

private:
  struct CalibProjProcessParam
  {
    //输入，该窗口相机采集的所有有效图像角点
    QVector<cv::Mat> _proImgCorners;
    QVector<cv::Size> _proPatternSize; //输入，行列方向投影的棋盘格个数
    cv::Size _proResolution;               //投影仪的分辨率
    double _proRealDx; //输入，投影图案的水平偏移
    double _proRealDy; //输入，投影图案的竖直偏移
    double _proCbDx;   //输入，棋盘格顶点间的水平距离
    double _proCbDy;   //输入，棋盘格顶点间的竖直距离
  };

  struct CalibProjResult
  {
    cv::Mat _proInMatrix;   //输出，标定得到的DLP内参矩阵
    cv::Mat _proExMatrix;   //输出，标定得到的DLP外参矩阵
    cv::Mat _proDistortion; //输出，标定得到的DLP畸变系数
    cv::Mat _proReprojErr;  //输出，重投影误差
  };

public:
  // 点击刷新，算法自动提取角点
  void find_procorners(
    cv::Mat& proImg,              //输入，相机采集的单张图像
    cv::Size proPatternSize,      //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* proCorners,   //输出，投影图案角点的像素坐标
    CV_OUT cv::Mat* proCamCorners //输出，棋盘格角点的像素坐标
  );

  // 点击标定按钮，得到DLP的内外参数和畸变系数
  void projector_calib(CalibProjProcessParam& calibProjProcessParam);

private:
  GaoCe::GaoCe& _algo;
  QWidget _leftWidget;
  QStackedLayout _leftLayout;
  esd::QuadrangleSelector _inputBench;
  esd::ImageBench _bench;
  QLabel _imageNum, _chessNum, _initOffset, _chessDis, _errorShow, _cornerPoint;
  QLabel _resolution, _multi;
  QSpinBox _imageSpin, _rowNumSpin, _colNumSpin;
  QSpinBox _rowSize, _colSize, _horiDis, _verDis;
  QLineEdit _reso1, _reso2;
  QPushButton _refreshButton, _calButton, _reCalButton;
  QPushButton _selPoint, _noSelPoint;
  QLineEdit _error;
};
