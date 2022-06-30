#pragma once
#include "GaoCe.hpp"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include <Eyestack/Design/ImageBench.hpp>
#include <Eyestack/Design/ImageLabel.hpp>
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
  /**
   * @brief 获取相机输入
   */
  std::function<cv::Mat()> _getInput = []() { return cv::Mat(); };

public:
  MVS_Calibration(GaoCe::GaoCe& algo, QWidget* parent = nullptr);

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
  QPushButton _selPoint, _noSelPoint, _saveImg;
  QLineEdit _error;
  QDoubleSpinBox _xSize, _ySize;
  QLabel _current;
  cv::Mat image;
  cv::Mat saveImg;
  cv::Mat camCorners;
  int temp = 1;

private slots:
  void on_refresh_clicked();
  void on_selPoint_clicked();
  void on_noSelPoint_clicked();
  void on_calButton_clicked();
  void on_reCalButton_clicked();
  void on_saveImg_clicked();
};
