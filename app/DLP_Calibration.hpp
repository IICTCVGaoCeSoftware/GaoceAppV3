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
  GaoCe::GaoCe& _algo;
  GaoCe::CalibProjProcessParam _param;
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
  int temp = 1;

private slots:
  void on_refresh_clicked();
  //  void on_selPoint_clicked();
  void on_calButton_clicked();
};
