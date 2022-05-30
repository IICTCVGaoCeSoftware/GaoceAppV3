#pragma once

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
#include "Eyestack/Design/ImageLabel.hpp"
#include "GaoCe.hpp"
#include <Eyestack/Framework.hpp>
#include <QVTKOpenGLNativeWidget.h>
#include <boost/thread/thread.hpp>
#include <pcl/PCLPointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

namespace esb = Eyestack::Base;
namespace esd = Eyestack::Design;

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

private:
  GaoCe::GaoCe& _algo;
  esd::ImageLabel _camera;
  QPushButton _reconOnce, _reconContinue, _reconStop, _savePCL, _saveDeepImg;
  QVTKOpenGLNativeWidget _pointCloud;
  QCheckBox _showCamera, _showDeepImg;
  boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
};
