#pragma once

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
#include "Eyestack/Com_MVS/MvsCameraWrapper.hpp"
#include "Eyestack/Design/Monitor.hpp"
#include "GaoCe.hpp"
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
  std::function<cv::Mat()> _getInput = []() { return cv::Mat(); };

public:
  ReConstructWindow(GaoCe::GaoCe& algo, QWidget* parent = nullptr);

private:
  GaoCe::GaoCe& _algo;
  // esd::ImageLabel _camera;
  esd::Monitor _camera;
  QTimer _timer;
  QPushButton _reconOnce, _reconContinue, _reconStop, _savePCL, _saveDeepImg;
  QVTKOpenGLNativeWidget _pointCloud;
  QCheckBox _showCamera, _showDeepImg;
  boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;

private slots:
  // 配置界面的电源键控制监视定时器的启动和停止
  // void when_configMonitor_powerClicked(bool power);
  // 当 _timer 计时结束时取帧刷新到界面上
  // void when_timer_timeout();
  void onStateChanged(int state);
  void on_reconOnce_clicked();
  void on_reconContinue_clicked();
  void on_reconStop_clicked();
  void on_savePCL_clicked();
  void on_saveDeepImg_clicked();
};
