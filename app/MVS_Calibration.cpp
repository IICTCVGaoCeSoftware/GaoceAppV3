#include "MVS_Calibration.h"
#include "wrapper.hpp"

// ==========================================================================
// MVS_Calibration
// ==========================================================================

MVS_Calibration::MVS_Calibration(GaoCe::GaoCe& algo, QWidget* parent)
  : _S(parent)
  , _algo(algo)
  , _refreshButton("刷新输入")
  , _calButton("标定相机")
  , _reCalButton("重新标定")
{
  // 配置组件
  _imageSpin.setPrefix("采集图像 ");
  _imageSpin.setValue(15);
  _imageSpin.setSuffix(" 张");
  _rowNumSpin.setPrefix("行方向 ");
  _rowNumSpin.setValue(10);
  _colNumSpin.setPrefix("列方向 ");
  _colNumSpin.setValue(6);
  _rowSize.setPrefix("行方向 ");
  _rowSize.setValue(5);
  _rowSize.setSuffix(" mm");
  _colSize.setPrefix("列方向 ");
  _colSize.setValue(5);
  _colSize.setSuffix(" mm");
  _imageNum.setText("采集图像的张数");
  _chessNum.setText("棋盘格个数");
  _chessSize.setText("棋盘格尺寸大小");
  _cornerPoint.setText("采用当前角点");
  _selPoint.setText("√");
  _noSelPoint.setText("×");
  _errorShow.setText("重投影误差显示");
  _current.setText("当前选取图片" + QString::number(temp));

  // 布局界面
  _leftLayout.addWidget(&_bench);
  _leftLayout.addWidget(&_current);

  // 右边的垂直界面
  auto vlayout = new QVBoxLayout();
  vlayout->addStretch();
  vlayout->addWidget(&_imageNum);
  vlayout->addWidget(&_imageSpin);
  vlayout->addSpacing(20);

  // 棋盘格行列方向大小
  vlayout->addWidget(&_chessNum);
  auto chesslayout = new QHBoxLayout();
  chesslayout->addWidget(&_rowNumSpin);
  chesslayout->addWidget(&_colNumSpin);
  vlayout->addLayout(chesslayout);

  // 棋盘格尺寸大小
  vlayout->addWidget(&_chessSize);
  auto chesssizelayout = new QHBoxLayout();
  chesssizelayout->addWidget(&_rowSize);
  chesssizelayout->addWidget(&_colSize);
  vlayout->addLayout(chesssizelayout);

  // 刷新输入
  vlayout->addWidget(&_refreshButton);

  // 是否采用角点
  vlayout->addWidget(&_cornerPoint);
  auto pointLayout = new QHBoxLayout();
  pointLayout->addWidget(&_selPoint);
  pointLayout->addWidget(&_noSelPoint);
  vlayout->addLayout(pointLayout);

  auto hlayout = new QHBoxLayout();
  hlayout->addLayout(&_leftLayout);
  hlayout->addLayout(vlayout);

  auto calLayout = new QHBoxLayout();
  calLayout->addWidget(&_calButton);
  calLayout->addSpacing(30);
  calLayout->addWidget(&_errorShow);
  calLayout->addWidget(&_error);
  calLayout->addSpacing(30);
  calLayout->addWidget(&_reCalButton);

  auto Finallayout = new QVBoxLayout();
  Finallayout->addLayout(hlayout);
  Finallayout->addLayout(calLayout);

  setLayout(Finallayout);

  // 连接信号
  connect(
    &_refreshButton, &QPushButton::clicked, this, &_T::on_refresh_clicked);

  connect(&_selPoint, &QPushButton::clicked, this, &_T::on_selPoint_clicked);

  connect(&_calButton, &QPushButton::clicked, this, &_T::on_calButton_clicked);
}

void
MVS_Calibration::on_refresh_clicked()
{
<<<<<<< HEAD
  QString str = "E://projects//EXP//images//images//C";
=======
  _current.setText("当前选取图片" + QString::number(temp));

  QString str = "D:/IICT/DLPPattern/images/camera/C";

>>>>>>> 1740259 (算法测试跑通)
  QString s = QString::number(temp++);
  str = str + s;
  str += ".bmp";
  cv::Mat image = cv::imread(str.toStdString());
<<<<<<< HEAD
  _bench.display(image);
  cv::Size camPatternSize = cv::Size(11, 6);
  // cv::Size2i num(_rowNumSpin.text().toInt(), _colNumSpin.text().toInt());
  _algo.find_camcorners(image, camPatternSize, &result);
  cv::Point2d p(result.at<double>(0), result.at<double>(1));
  qDebug() << p.x << " " << p.y;
=======
  cv::Size camPatternSize = cv::Size(11, 6);
  cv::Mat imgCamGray;
  cv::cvtColor(image, imgCamGray, cv::COLOR_BGR2GRAY);
  _algo.find_camcorners(imgCamGray, camPatternSize, &camCorners);
  std::vector<cv::Point2f> imagecorner = cv::Mat_<cv::Point2f>(camCorners);

  for (uint8_t i = 0; i < imagecorner.size(); i++) {
    circle(image, imagecorner[i], 10, cv::Scalar(0, 0, 255), 5);
  }
  _bench.display(image);
  _refreshButton.setEnabled(false);
>>>>>>> 1740259 (算法测试跑通)
}

void
MVS_Calibration::on_selPoint_clicked()
{
  cv::Size camPatternSize = cv::Size(11, 6);
  calibCamProcessParam._camCornersMat.push_back(camCorners);
  calibCamProcessParam._camPatternSize.push_back(camPatternSize);
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("提取角点成功");
  MBox.exec();
  _refreshButton.setEnabled(true);
}

void
MVS_Calibration::on_calButton_clicked()
{
  cv::Size camImgSize = cv::Size(2592, 2048);
  calibCamProcessParam._imgSize = camImgSize;
  calibCamProcessParam._camRealDx = 5;
  calibCamProcessParam._camRealDy = 5;

  _algo.camera_calib(calibCamProcessParam);

  GaoCeWrapper* myWrapper = dynamic_cast<GaoCeWrapper*>(&_algo);
  if (myWrapper) {
    qDebug() << "myWrapper is not null";

    qDebug() << "the add2 = " << &myWrapper->_gaoce->_calibCamResult;
  } else
    qDebug() << "myWrapper is  null";

  qDebug() << "outside add is:" << &_algo._calibCamResult;

  // cv::Mat temp1 = _algo._calibCamResult._camInMatrix;
  cv::Mat temp = _algo._calibCamResult._camReprojErr;

  // double Err = _algo._calibCamResult._camReprojErr.at<double>(0, 0);
  double Err1 =
    myWrapper->_gaoce->_calibCamResult._camReprojErr.at<double>(0, 0);

  _error.setText(QString::number(Err1, 'f', 2));
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("标定相机成功");
  MBox.exec();
}
