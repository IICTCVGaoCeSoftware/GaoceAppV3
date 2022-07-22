#pragma once

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
#include "Eyestack/Com_MVS/MvsCameraWrapper.hpp"
#include "Eyestack/Design/Monitor.hpp"
#include "Eyestack/Design/Progressor.hpp"
#include "GaoCe.hpp"
#include "Worker.hpp"
#include "pcl/point_cloud.h"
#include <Eyestack/Framework.hpp>
#include <QVTKOpenGLNativeWidget.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPLYReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

namespace esf = Eyestack::Framework;
namespace esb = Eyestack::Base;
namespace esd = Eyestack::Design;
namespace mvs = Eyestack::Com_MVS;

// ==========================================================================
// ReConstructWindow
// ==========================================================================

/**
 * @brief 重建窗口
 */
class ReConstructWindow : public QWidget
{
  Q_OBJECT

  using _T = ReConstructWindow;
  using _S = QWidget;

public:
  std::function<cv::Mat()> _getInput_soft = []() { return cv::Mat(); };
  std::function<cv::Mat()> _getInput = []() { return cv::Mat(); };

signals:
  /**
   * @brief 不间断运行模式更新时发射此信号
   */
  void s_noStopUpdated(bool checked);
  /**
   * @brief 显示重建参数表
   */
  void s_show();

public:
  /**
   * @brief 配置组件 + 布局
   */
  ReConstructWindow(QWidget* parent = nullptr);

public:
  /**
   * @brief 显示准备图像
   */
  void display_DeepImg(const cv::Mat& img);

private:
  //  GaoCe::GaoCe& _algo;
  esd::Monitor _camera;
  QTimer _timer;

  QHBoxLayout* pointLayout;
  QHBoxLayout* hlayout;
  QPushButton _reconOnce, _config, _reconStop, _savePCD, _savePLY, _saveDeepImg;
  QPushButton _showErr, _tranDeepImg;
  QVTKOpenGLNativeWidget _pointCloud;
  QCheckBox _showCamera, _showDeepImg, _showPC;
  QComboBox _selShow;
  QLineEdit _err;

  QCheckBox _noStopCheck;
  QSharedPointer<pcl::PointCloud<pcl::PointXYZ>> _cloud;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud2;
  cv::Mat transform_depth_image;
  esd::ImageLabel _deepImg;

private slots:
  // 当 _timer 计时结束时取帧刷新到界面上
  void when_timer_timeout();
  // 控制相机和深度图的开关
  void onStateChanged(int state);
  void onStateChanged1(int state);
  void on_PC_Changed(int state);
  void on_reconOnce_clicked();
  void on_reconStop_clicked();
  void on_savePCD_clicked();
  void on_savePLY_clicked();
  void on_saveDeepImg_clicked();
  void on_showDeepImg_checked();
  void switch_window(int index);
  void on_reconContinue_clicked();
  void on_showErr_clicked();

public:
  // void initialVtkWidget();
  void disable_all();
  void enable_all();
};

/**
 * @brief 高测运行监控 窗口界面
 */
class ReConRunningSubUi : public esf::MainWindow::SubUi::MdiAction
{
  Q_OBJECT

  using _T = ReConRunningSubUi;
  using _S = esf::MainWindow::SubUi::MdiAction;

public:
  ReConRunningSubUi(Worker& worker);
  ReConstructWindow _ui;

private:
  Worker& _worker;
  QFile _recordFile;
  QPushButton _reportButton;

private slots:

  // MainWindow::SubUi interface
public:
  virtual void setup_ui(Eyestack::Framework::MainWindow& mw) noexcept override;
};
