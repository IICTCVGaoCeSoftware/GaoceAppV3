#include "ReConstructWindow.hpp"
#include "pcl/io/pcd_io.h"
#include <vtkVertexGlyphFilter.h>

namespace esb = Eyestack::Base;
namespace esd = Eyestack::Design;
namespace esf = Eyestack::Framework;
extern esb::Profiler gProfiler;

ReConstructWindow::ReConstructWindow(GaoCe::GaoCe& algo, QWidget* parent)
  : _S(parent)
  , _algo(algo)
{
  initialVtkWidget();

  _reconContinue.setText("连续重建");
  _reconOnce.setText("重建一次");
  _reconStop.setText("结束");
  _savePCL.setText("保存点云");
  _saveDeepImg.setText("保存深度图");
  _showCamera.setText("显示相机画面");
  _showCamera.setChecked(true);
  _showDeepImg.setText("显示深度图像");
  _showDeepImg.setChecked(true);

  //   cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
  // cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
  //  QString filename = "G:/bun_zipper.ply";

  //  //读取文件
  //  vtkSmartPointer<vtkPLYReader> reader =
  //  vtkSmartPointer<vtkPLYReader>::New();

  //  reader->SetFileName(filename.toStdString().c_str());
  //  reader->Update();

  //  //将source转换成mapper
  //  vtkSmartPointer<vtkPolyDataMapper> mapper =
  //    vtkSmartPointer<vtkPolyDataMapper>::New();
  //  mapper->SetInputConnection(reader->GetOutputPort());

  //  //送入渲染引擎进行显示
  //  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  //  actor->SetMapper(mapper);

  //  //渲染
  //  vtkSmartPointer<vtkRenderer> renderer =
  //  vtkSmartPointer<vtkRenderer>::New(); renderer->AddActor(actor);
  //  renderer->SetBackground(.0, .0, .0);
  //  _camera.display_qstring("sssssssss");

  //  //设置渲染窗口
  //  vtkSmartPointer<vtkGenericOpenGLRenderWindow> window =
  //    vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  //  window->AddRenderer(renderer);

  //  _pointCloud.SetRenderWindow(window);

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

  _widget1 = new QWidget();
  auto hlayout = new QHBoxLayout();
  hlayout->addWidget(&_camera);
  hlayout->addWidget(&_deepImg);
  _widget1->setLayout(hlayout);
  layout->addWidget(_widget1);

  auto finalLayout = new QHBoxLayout();
  finalLayout->addLayout(layout);
  finalLayout->addLayout(vlayout);
  finalLayout->setStretch(0, 9);
  finalLayout->setStretch(1, 1);

  setLayout(finalLayout);

  // 连接信号
  connect(&_reconOnce, &QPushButton::clicked, this, &_T::on_reconOnce_clicked);
  connect(&_reconContinue,
          &QPushButton::clicked,
          this,
          &_T::on_reconContinue_clicked);
  connect(&_reconStop, &QPushButton::clicked, this, &_T::on_reconStop_clicked);
  connect(&_savePCL, &QPushButton::clicked, this, &_T::on_savePCL_clicked);
  connect(
    &_saveDeepImg, &QPushButton::clicked, this, &_T::on_saveDeepImg_clicked);

  connect(
    &_showCamera, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));

  connect(
    &_showDeepImg, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged1(int)));
}

void
ReConstructWindow::onStateChanged(int state)
{
  if (state == Qt::Checked) {
    _widget1->show();
    _camera.show();
  } else if (state == Qt::Unchecked) {
    _camera.hide();
    if (!_showDeepImg.isChecked()) {
      _widget1->hide();
    }
  }
}

void
ReConstructWindow::onStateChanged1(int state)
{
  if (state == Qt::Checked) {
    _widget1->show();

    _deepImg.show();
  } else if (state == Qt::Unchecked) {
    _deepImg.hide();
    if (!_showCamera.isChecked()) {
      _widget1->hide();
    }
  }
}

void
ReConstructWindow::on_reconOnce_clicked()
{
  //重建
  std::string path = "G:/v1";
  std::vector<std::string> fn;
  cv::glob(path, fn, false);

  cv::Mat img;
  std::vector<cv::Mat> imgList;
  for (auto img_path : fn) {
    cv::Mat img = cv::imread(img_path, cv::IMREAD_GRAYSCALE);
    imgList.push_back(img);
  }

  {
    esb::Profiler::Scoper timer(gProfiler, "realTime::reconstruction");
    _algo.recon_pcl_with_gray_liting(imgList, &cloud);
  }

  pcl::visualization::CloudViewer viewer("Cloud Viewer");
  cloud2 = cloud.makeShared();
  _algo.transform_depth_image(cloud, &transform_depth_image);
  _deepImg.display_cvmat(transform_depth_image);

  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

  for (int i = 0; i < cloud2->size(); i++) {
    points->InsertNextPoint(cloud2->at(i).x, cloud2->at(i).y, cloud2->at(i).z);
  }

  vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
  polyData->SetPoints(points);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
  glyphFilter->SetInputData(polyData);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .1, .1);
  _pointCloud.GetRenderWindow()->AddRenderer(renderer);

  //  viewer.showCloud(cloud2);
  //  while (!viewer.wasStopped()) {
  //  }
}

void
ReConstructWindow::initialVtkWidget()
{
  //初始化颜色及大小信息
  unsigned red = 255;
  unsigned green = 255;
  unsigned blue = 255;

  double size = 1.0;
  //点云加载
  cloud2.reset(new pcl::PointCloud<pcl::PointXYZ>);
  _viewer111.reset(new pcl::visualization::PCLVisualizer("_viewer111", false));
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(
    cloud2, red, green, blue); //自定义点云颜色
  _viewer111->addPointCloud<pcl::PointXYZ>(cloud2, single_color, "cloud");
  _viewer111->setPointCloudRenderingProperties(
    pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
    size,
    "cloud"); //设置点云单个点的大小
  _pointCloud.SetRenderWindow(_viewer111->getRenderWindow());
  _viewer111->setupInteractor(_pointCloud.GetInteractor(),
                              _pointCloud.GetRenderWindow());
  _pointCloud.update();
}

void
ReConstructWindow::on_reconContinue_clicked()
{}

void
ReConstructWindow::on_reconStop_clicked()
{}

void
ReConstructWindow::on_savePCL_clicked()
{}

void
ReConstructWindow::on_saveDeepImg_clicked()
{}

void
ReConstructWindow::on_showDeepImg_checked()
{
  //  _algo.transform_depth_image(cloud, &transform_depth_image);

  //  // TODO 显示深度图
  _deepImg.display_cvmat(transform_depth_image);

  //    std::ofstream profile("E:/projects/EXP/log/profile.log");
  //  profile << gProfiler << std::endl;
  //  profile.close();
}
