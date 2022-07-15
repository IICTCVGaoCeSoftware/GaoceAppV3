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
  , _showErr("显示误差")
{
  _config.setText("更多设置");
  _reconOnce.setText("重建一次");
  _reconStop.setText("结束");
  _savePCD.setText("保存为PCD");
  _savePLY.setText("保存为PLY");
  _saveDeepImg.setText("保存深度图");
  _showCamera.setText("显示相机画面");
  _showCamera.setChecked(true);
  _showDeepImg.setText("显示深度图像");
  _showDeepImg.setChecked(true);
  _showPC.setText("显示点云图");
  _showPC.setChecked(true);
  _showPC.hide();
  _selShow.addItem("请选择重构对象");
  _selShow.addItem("构建点云");
  _selShow.addItem("构建深度图");

  // 右边菜单栏的垂直界面
  auto vlayout = new QVBoxLayout();
  vlayout->addWidget(&_selShow);
  vlayout->addWidget(&_config);
  vlayout->addWidget(&_reconOnce);
  vlayout->addWidget(&_reconStop);
  vlayout->addWidget(&_showCamera);
  vlayout->addWidget(&_showDeepImg);
  vlayout->addWidget(&_showPC);
  vlayout->addWidget(&_savePCD);
  vlayout->addWidget(&_savePLY);
  vlayout->addWidget(&_saveDeepImg);
  vlayout->addWidget(&_showErr);
  vlayout->addWidget(&_err);

  // 显示点云
  pointLayout = new QHBoxLayout();
  pointLayout->addWidget(&_pointCloud);

  hlayout = new QHBoxLayout();
  hlayout->addWidget(&_camera);
  hlayout->addWidget(&_deepImg);

  auto showLayout = new QVBoxLayout();
  showLayout->addLayout(pointLayout);
  showLayout->addLayout(hlayout);

  auto finalLayout = new QHBoxLayout();
  finalLayout->addLayout(showLayout);
  finalLayout->addLayout(vlayout);
  finalLayout->setStretch(0, 9);
  finalLayout->setStretch(1, 1);

  setLayout(finalLayout);

  disable_all();

  // 连接信号
  connect(&_reconOnce, &QPushButton::clicked, this, &_T::on_reconOnce_clicked);
  connect(&_config, &QPushButton::clicked, this, &_T::on_reconContinue_clicked);
  connect(&_reconStop, &QPushButton::clicked, this, &_T::on_reconStop_clicked);
  connect(&_savePCD, &QPushButton::clicked, this, &_T::on_savePCD_clicked);
  connect(&_savePLY, &QPushButton::clicked, this, &_T::on_savePLY_clicked);

  connect(
    &_saveDeepImg, &QPushButton::clicked, this, &_T::on_saveDeepImg_clicked);

  connect(&_showErr, &QPushButton::clicked, this, &_T::on_showErr_clicked);

  connect(
    &_showCamera, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));

  connect(
    &_showDeepImg, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged1(int)));

  connect(&_showPC, SIGNAL(stateChanged(int)), this, SLOT(on_PC_Changed(int)));

  connect(&_selShow, &QComboBox::currentIndexChanged, this, &_T::enable_all);
  connect(&_selShow,
          SIGNAL(currentIndexChanged(int)),
          this,
          SLOT(switch_window(int)));

  connect(&_selShow, &QComboBox::currentIndexChanged, this, &_T::switch_window);

  connect(&_timer, &QTimer::timeout, this, &_T::when_timer_timeout);

  _timer.start(50);
}

// 显示相机
void
ReConstructWindow::onStateChanged(int state)
{
  if (state == Qt::Checked) {
    _camera.show();
  } else if (state == Qt::Unchecked) {
    _camera.hide();
    if (_selShow.currentIndex() == 1) {
      _pointCloud.show();
    } else if (_selShow.currentIndex() == 2) {
      _deepImg.show();
    }
  }
}

// 显示深度图
void
ReConstructWindow::onStateChanged1(int state)
{
  if (state == Qt::Checked) {
    _deepImg.show();
  } else if (state == Qt::Unchecked) {
    _deepImg.hide();
    if (_selShow.currentIndex() == 1) {
      _pointCloud.show();
    } else if (_selShow.currentIndex() == 2) {
      _deepImg.show();
    }
  }
}

void
ReConstructWindow::on_reconOnce_clicked()
{
  //重建
  //  std::string path = "C:/Gaoce/image";
  // std::string path = "D:/IICT/DLPPattern/images/ban0711";
  //  std::vector<std::string> fn;
  //  cv::glob(path, fn, false);
  std::vector<cv::Mat> imgList;
  for (uint8_t i = 0; i < 24; i++) {
    cv::Mat temp = _getInput_soft();
    imgList.emplace_back(temp);
    QString str = "C/Gaoce/Timage/" + QString::number(i);
    cv::imwrite(str.toStdString(), temp);
    temp.release();
  }
  //  for (auto img_path : fn) {
  //    cv::Mat img = cv::imread(img_path, cv::IMREAD_GRAYSCALE);
  //    imgList.push_back(img);
  //  }

  {
    esb::Profiler::Scoper timer(gProfiler, "realTime::reconstruction");
    _algo.recon_pcl_with_gray_liting(imgList, &cloud);
  }

  pcl::visualization::CloudViewer viewer("Cloud Viewer");
  _cloud2 = cloud.makeShared();
  _algo.transform_depth_image(cloud, &transform_depth_image);
  _deepImg.display_cvmat(transform_depth_image);

  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

  for (int i = 0; i < _cloud2->size(); i++) {
    points->InsertNextPoint(
      _cloud2->at(i).x, _cloud2->at(i).y, _cloud2->at(i).z);
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
ReConstructWindow::on_reconContinue_clicked()
{
  emit s_show();
}

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
  if (transform_depth_image.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("无法保存，请刷新输入");
    MBox.exec();
    return;
  }
  QString filename =
    QFileDialog::getSaveFileName(this, "保存深度图像", "*.png");
  QFile file(filename);
  std::vector<int> compression_params;
  compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(0);
  compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
  compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);
  if (file.exists()) {
    cv::imwrite(
      filename.toStdString(), transform_depth_image, compression_params);
  }
}

void
ReConstructWindow::on_showDeepImg_checked()
{
  // TODO 显示深度图
  _deepImg.display_cvmat(transform_depth_image);
}

void
ReConstructWindow::on_showErr_clicked()
{
  if (cloud.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("点云为空，无法计算");
    MBox.exec();
    return;
  }
  float err = 0;
  _algo.compute_3dprecision_pointcloud(cloud, &err);
  QString str = QString("ERROR is %1").arg(err);
  _err.setText(str);
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
  _config.setEnabled(false);
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
    _config.setEnabled(true);
    _savePCD.setEnabled(true);
    _savePLY.setEnabled(true);
    _saveDeepImg.setEnabled(true);
  }
}

void
ReConstructWindow::switch_window(int index)
{
  // 构建点云
  if (index == 1) {
    QLayoutItem* child;
    while ((child = pointLayout->takeAt(0)) != 0) {
      // setParent为NULL，防止删除之后界面不消失
      if (child->widget()) {
        child->widget()->setParent(NULL);
      }
      delete child;
    }
    while ((child = hlayout->takeAt(0)) != 0) {
      // setParent为NULL，防止删除之后界面不消失
      if (child->widget()) {
        child->widget()->setParent(NULL);
      }
      delete child;
    }
    pointLayout->addWidget(&_pointCloud);
    hlayout->addWidget(&_camera);
    hlayout->addWidget(&_deepImg);
    _pointCloud.show();
    _camera.show();
    _deepImg.show();
    _showPC.hide();
    _showDeepImg.show();
  } else if (index == 2) {
    QLayoutItem* child;
    while ((child = pointLayout->takeAt(0)) != 0) {
      // setParent为NULL，防止删除之后界面不消失
      if (child->widget()) {
        child->widget()->setParent(NULL);
      }
      delete child;
    }
    while ((child = hlayout->takeAt(0)) != 0) {
      // setParent为NULL，防止删除之后界面不消失
      if (child->widget()) {
        child->widget()->setParent(NULL);
      }
      delete child;
    }
    pointLayout->addWidget(&_deepImg);
    hlayout->addWidget(&_camera);
    hlayout->addWidget(&_pointCloud);
    _pointCloud.show();
    _camera.show();
    _deepImg.show();
    _showPC.show();
    _showDeepImg.hide();
  }
}

void
ReConstructWindow::on_PC_Changed(int state)
{
  if (state == Qt::Checked) {
    _pointCloud.show();
  }

  else if (state == Qt::Unchecked) {
    _pointCloud.hide();
    if (_selShow.currentIndex() == 1) {
      _pointCloud.show();
    } else if (_selShow.currentIndex() == 2) {
      _deepImg.show();
    }
  }
}
