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

public:
  // 点击刷新按钮，算法自动提取角点
  void find_camcorners(
    cv::Mat& camImg,         //输入，相机采集的单张图像
    cv::Size camPatternSize, //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
  );
  // 相机标定窗口，点击标定按钮，得到相机的内外参数和畸变系数

private:
  GaoCe::GaoCe& _algo;
  GaoCe::CalibCamProcessParam calibCamProcessParam;
  QWidget _leftWidget;
  QVBoxLayout _leftLayout;
  esd::ImageBench _bench;
  QLabel _imageNum, _chessNum, _chessSize, _errorShow, _cornerPoint;
  QSpinBox _imageSpin, _rowNumSpin, _colNumSpin;
  QSpinBox _rowSize, _colSize;
  QPushButton _refreshButton, _calButton, _reCalButton;
  QPushButton _selPoint, _noSelPoint;
  QLineEdit _error;
  QDoubleSpinBox _xSize, _ySize;
  QLabel _current;
  cv::Mat camCorners;
  cv::Mat result;
  int temp = 1;

private slots:
  void on_refresh_clicked();
  void on_selPoint_clicked();
  void on_calButton_clicked();
};
