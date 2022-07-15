#pragma once
#include "GaoCe.hpp"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include <Eyestack/Design/ImageBench.hpp>
#include <Eyestack/Design/ImageLabel.hpp>
#include <Eyestack/Design/Monitor.hpp>
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
  void set_table();

private:
  GaoCe::GaoCe& _algo;
  QWidget _leftWidget;
  GaoCe::CalibProjProcessParam calibProjProcessPara;
  QStackedLayout _stackLayout;
  QVBoxLayout _leftLayout;
  esd::QuadrangleSelector _inputBench;
  esd::Monitor _camera;
  QLabel _imageNum, _chessNum, _initOffset, _chessDis, _errorShow, _cornerPoint;
  QLabel _resolution, _multi;
  QSpinBox _imageSpin, _rowNumSpin, _colNumSpin, _maskRow, _maskCol;
  QSpinBox _rowOffset, _colOffset;
  QDoubleSpinBox _horiDis, _verDis;
  QLineEdit _reso1, _reso2;
  QPushButton _refreshButton, _calButton, _reCalButton, _saveImg, _config;
  QPushButton _selPoint, _noSelPoint, _excCorner, _insertMask;
  QLineEdit _error;
  QLabel _current, _projDistri, _calDistri, _projMaskL, _calMastL;

  cv::Mat proImgCorners; // 输出的投影棋盘格角点
  cv::Mat proCamCorners; // 精细化的打印角点
  cv::Mat proCamCornersCoarse; // 投影仪粗角点（外面）
  cv::Mat calCamCornersCoarse; // 标定板粗角点（里面）
  cv::Mat proProjCorners; //输出，投影棋盘格角点在投影仪的像素坐标
  cv::Mat camRepErr;

  cv::Mat image; // 主界面显示的图像
  cv::Mat saveImg;
  QTimer _timer;
  int temp = 1;

  esd::ImageLabel _showImgCorner;
  esd::ImageLabel _showCamCorner;
  cv::Mat _showICorner; // 投影仪角点分布
  cv::Mat _showCCorner; // 标定板角点分布

  QButtonGroup* _buttongroup;
  QRadioButton _showMask;
  QRadioButton _showDistri;
  QTableWidget _projMask;
  QTableWidget _calMask;
  QFile* file;

signals:
  void s_show();

private slots:
  void handleRadioGroup(int id);
  void on_refresh_clicked();
  void on_selPoint_clicked();
  void on_noSelPoint_clicked();
  void on_calButton_clicked();
  void on_reCalButton_clicked();
  void on_excCorner_clicked();
  void on_insertMask_clicked();
  void on_saveImg_clicked();
  void on_config_clicked();
  void cal_initOffset();
  // 配置界面的电源键控制监视定时器的启动和停止
  void when_configMonitor_powerClicked(bool power);
  // 当 _timer 计时结束时取帧刷新到界面上
  void when_timer_timeout();

private:
  /**
   * @brief 读取四边形的顶点，方向是↖↙↘↗
   * @param proCamCornersCoarse
   */
  void read_CamCorners(cv::Mat& proCamCornersCoarse,
                       cv::Mat& calCamCornersCoarse);
  void hide_all();
  void show_all();
};
