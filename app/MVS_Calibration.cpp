#include "MVS_Calibration.h"

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
  _imageSpin.setValue(10);
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

  // 布局界面
  _leftWidget.setLayout(&_leftLayout);
  _leftLayout.addWidget(&_bench);

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
  hlayout->addWidget(&_leftWidget);
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

  _leftLayout.setCurrentIndex(0);
}

void
MVS_Calibration::on_refresh_clicked()
{
  QString str = "E://projects//EXP//images//images//C";
  QString s = QString::number(temp++);
  str = str + s;
  str += ".bmp";
  cv::Mat image = cv::imread(str.toStdString());
  _bench.display(image);
  cv::Size camPatternSize = cv::Size(11, 6);
  // cv::Size2i num(_rowNumSpin.text().toInt(), _colNumSpin.text().toInt());
  _algo.find_camcorners(image, camPatternSize, &result);
  cv::Point2d p(result.at<double>(0), result.at<double>(1));
  qDebug() << p.x << " " << p.y;
}

void
MVS_Calibration::on_selPoint_clicked()
{
  cv::Size2i num(_rowNumSpin.text().toInt(), _colNumSpin.text().toInt());
  _param._camCornersMat.push_back(_corner);
  _param._camPatternSize.push_back(num);
  _param._camRealDx = _xSize.text().toDouble();
  _param._camRealDy = _ySize.text().toDouble();
}

void
MVS_Calibration::on_calButton_clicked()
{
  _algo.camera_calib(_param);
}
