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
  _savePCD.setText("保存为PCD");
  _savePLY.setText("保存为PLY");
  _saveDeepImg.setText("保存深度图");
  _showCamera.setText("显示相机画面");
  _showCamera.setChecked(true);
  _showDeepImg.setText("显示深度图像");
  _showDeepImg.setChecked(true);
  _selShow.addItem("请选择重构对象");
  _selShow.addItem("构建点云");
  _selShow.addItem("构建深度图");

  auto vlayout = new QVBoxLayout();
  vlayout->addWidget(&_selShow);
  vlayout->addWidget(&_reconOnce);
  vlayout->addWidget(&_reconContinue);
  vlayout->addWidget(&_reconStop);
  vlayout->addWidget(&_showCamera);
  vlayout->addWidget(&_showDeepImg);
  vlayout->addWidget(&_savePCD);
  vlayout->addWidget(&_savePLY);
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

  disable_all();

  // 连接信号
  connect(&_reconOnce, &QPushButton::clicked, this, &_T::on_reconOnce_clicked);
  connect(&_reconContinue,
          &QPushButton::clicked,
          this,
          &_T::on_reconContinue_clicked);
  connect(&_reconStop, &QPushButton::clicked, this, &_T::on_reconStop_clicked);
  connect(&_savePCD, &QPushButton::clicked, this, &_T::on_savePCD_clicked);
  connect(&_savePLY, &QPushButton::clicked, this, &_T::on_savePLY_clicked);

  connect(
    &_saveDeepImg, &QPushButton::clicked, this, &_T::on_saveDeepImg_clicked);

  connect(
    &_showCamera, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));

  connect(
    &_showDeepImg, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged1(int)));

  connect(&_selShow, &QComboBox::currentIndexChanged, this, &_T::enable_all);

  connect(&_timer, &QTimer::timeout, this, &_T::when_timer_timeout);

  _timer.start(50);
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
ReConstructWindow::on_savePCD_clicked()
{
  if (cloud.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("点云为空，无法保存");
    MBox.exec();
    return;
  }
  QString filename = QFileDialog::getSaveFileName(this, "保存PCD", "*.pcd");
  QFile file(filename);                       //创建文件对象
  pcl::io::savePCDFile(filename.toStdString(), cloud);
}

void
ReConstructWindow::on_savePLY_clicked()
{
  if (cloud.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("点云为空，无法保存");
    MBox.exec();
    return;
  }
  QString filename = QFileDialog::getSaveFileName(this, "保存PCD", "*.ply");
  QFile file(filename); //创建文件对象
  pcl::io::savePLYFile(filename.toStdString(), cloud);
}

void
ReConstructWindow::on_saveDeepImg_clicked()
{
  // TODO
  QString filename =
    QFileDialog::getSaveFileName(this, "保存深度图像", "*.ply");
  QFile file(filename);
}

void
ReConstructWindow::on_showDeepImg_checked()
{
  // TODO 显示深度图
  _deepImg.display_cvmat(transform_depth_image);

  //    std::ofstream profile("E:/projects/EXP/log/profile.log");
  //  profile << gProfiler << std::endl;
  //  profile.close();
}

void
ReConstructWindow::when_timer_timeout()
{
  _camera.display_cvmat(_getInput());
}

void
ReConstructWindow::disable_all()
{
  _reconOnce.setEnabled(false);
  _reconStop.setEnabled(false);
  _reconContinue.setEnabled(false);
  _savePCD.setEnabled(false);
  _savePLY.setEnabled(false);
  _saveDeepImg.setEnabled(false);
}

void
ReConstructWindow::enable_all()
{
  if (_selShow.currentIndex() != 0) {
    _reconOnce.setEnabled(true);
    _reconStop.setEnabled(true);
    _reconContinue.setEnabled(true);
    _savePCD.setEnabled(true);
    _savePLY.setEnabled(true);
    _saveDeepImg.setEnabled(true);
  }
}
