#include "ReConstructWindow.hpp"
#include "pcl/io/pcd_io.h"

ReConstructWindow::ReConstructWindow(GaoCe::GaoCe& algo, QWidget* parent)
  : _S(parent)
  , _algo(algo)
{
  _reconContinue.setText("连续重建");
  _reconOnce.setText("重建一次");
  _reconStop.setText("结束");
  _savePCL.setText("保存点云");
  _saveDeepImg.setText("保存深度图");
  _showCamera.setText("显示相机画面");
  _showCamera.setEnabled(true);
  _showDeepImg.setText("显示深度图像");
  _showDeepImg.setEnabled(true);

  cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
  QString filename = "G:/bun_zipper.ply";

  if (pcl::io::loadPCDFile(filename.toStdString(), *cloud) == -1) {
    qDebug() << "输入错误";
  }
  //读取文件
  vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
  reader->SetFileName(filename.toStdString().c_str());
  reader->Update();

  //将source转换成mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  //送入渲染引擎进行显示
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  //渲染
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.0, .0, .0);
  _camera.display_qstring("sssssssss");

  //设置渲染窗口
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> window =
    vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(renderer);

  _pointCloud.SetRenderWindow(window);

  auto vlayout = new QVBoxLayout();
  vlayout->addWidget(&_reconOnce);
  vlayout->addWidget(&_reconContinue);
  vlayout->addWidget(&_reconStop);
  vlayout->addWidget(&_showCamera);
  vlayout->addWidget(&_showDeepImg);
  vlayout->addWidget(&_savePCL);
  vlayout->addWidget(&_saveDeepImg);

  auto layout = new QVBoxLayout();
  layout->addWidget(&_pointCloud);
  layout->addWidget(&_camera);

  auto finalLayout = new QHBoxLayout();
  finalLayout->addLayout(layout);
  finalLayout->addLayout(vlayout);
  finalLayout->setStretch(0, 9);
  finalLayout->setStretch(1, 1);

  setLayout(finalLayout);

  //  connect(&_camera,
  //          &esd::Monitor::s_powerClicked,
  //          this,
  //          &_T::when_configMonitor_powerClicked);
}
