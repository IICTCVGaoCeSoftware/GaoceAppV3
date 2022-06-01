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
  ReConstructWindow(GaoCe::GaoCe& algo, QWidget* parent = nullptr);

public:
  void recon_pcl_with_gray_liting(QVector<cv::Mat>& inputImgs,
                                  pcl::PointCloud<pcl::PointXYZ>* _cloud);
  void transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
                             CV_OUT cv::Mat* depthImage);

private:
  struct Wrapper
  {
    mvs::MvsCameraWrapper::Shared _camera;
    bool _grabbing{ false };
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

private:
  GaoCe::GaoCe& _algo;
  // esd::ImageLabel _camera;
  esd::Monitor _camera;
  QPushButton _reconOnce, _reconContinue, _reconStop, _savePCL, _saveDeepImg;
  QVTKOpenGLNativeWidget _pointCloud;
  QCheckBox _showCamera, _showDeepImg;
  boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;

private slots:
  // 配置界面的电源键控制监视定时器的启动和停止
  // void when_configMonitor_powerClicked(bool power);
};
