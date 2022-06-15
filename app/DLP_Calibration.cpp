#include "DLP_Calibration.hpp"

DLP_Calibration::DLP_Calibration(GaoCe::GaoCe& algo, QWidget* parent)
  : _S(parent)
  , _algo(algo)
  , _refreshButton("刷新输入")
  , _calButton("标定投影仪")
  , _reCalButton("重新标定")
{
  // 配置组件
  _imageSpin.setPrefix("采集图像 ");
  _imageSpin.setValue(10);
  _imageSpin.setSuffix(" 张");
  _rowNumSpin.setPrefix("行方向 ");
  _rowNumSpin.setValue(16);
  _colNumSpin.setPrefix("列方向 ");
  _colNumSpin.setValue(15);
  _chessNum.setText("棋盘格个数");
  _rowSize.setPrefix("行方向 ");
  _rowSize.setValue(5);
  _rowSize.setSuffix(" mm");
  _colSize.setPrefix("列方向 ");
  _colSize.setValue(0);
  _colSize.setSuffix(" mm");
  _horiDis.setPrefix("水平间距 ");
  _horiDis.setValue(31);
  _horiDis.setSuffix(" mm");
  _verDis.setPrefix("垂直间距 ");
  _verDis.setValue(23);
  _verDis.setSuffix(" mm");
  _imageNum.setText("采集图像的张数");
  _initOffset.setText("初始偏移");
  _chessDis.setText("棋盘格的顶点间距");
  _cornerPoint.setText("采用当前角点");
  _reso1.setText("1280");
  _reso2.setText("720");
  _selPoint.setText("√");
  _noSelPoint.setText("×");
  _errorShow.setText("重投影误差显示:");
  _resolution.setText("投影分辨率");
  _multi.setText("×");

  // 布局界面
  _leftWidget.setLayout(&_leftLayout);
  _leftLayout.addWidget(&_inputBench);
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

  // 初始偏移
  vlayout->addWidget(&_initOffset);
  auto offsetlayout = new QHBoxLayout();
  offsetlayout->addWidget(&_rowSize);
  offsetlayout->addWidget(&_colSize);
  vlayout->addLayout(offsetlayout);

  // 投影分辨率
  auto resolutionlayout = new QHBoxLayout();
  resolutionlayout->addWidget(&_resolution);
  resolutionlayout->addWidget(&_reso1);
  resolutionlayout->addWidget(&_multi);
  resolutionlayout->addWidget(&_reso2);
  vlayout->addLayout(resolutionlayout);

  // 棋盘格的顶点间距
  vlayout->addWidget(&_chessDis);
  auto chessDislayout = new QHBoxLayout();
  chessDislayout->addWidget(&_horiDis);
  chessDislayout->addWidget(&_verDis);
  vlayout->addLayout(chessDislayout);

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
  hlayout->setStretch(0, 8);
  hlayout->setStretch(1, 2);

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
  connect(&_calButton, &QPushButton::clicked, this, &_T::on_calButton_clicked);

  _leftLayout.setCurrentIndex(0);
}

void
DLP_Calibration::on_refresh_clicked()
{
  //  cv::Size2i num(_rowNumSpin.text().toInt(), _colNumSpin.text().toInt());
  //  QString str = cv::Mat input =
  //  cv::imread("D:/IICT/DLPPattern/images/camera");
  //  _algo.find_camcorners(_getInput(), num, result);
  //  _bench.display(_getInput());
  QString str = "D:/IICT/DLPPattern/images/projector/P";
  QString s = QString::number(temp++);
  str = str + s;
  str += ".bmp";
  cv::Mat image = cv::imread(str.toStdString());
  cv::Size2i num(_rowNumSpin.text().toInt(), _colNumSpin.text().toInt());
  //  // cv::Mat* result;
  //  //   _algo.find_camcorners(_getInput(), num, result);
  //  _bench.display(image);
}

void
DLP_Calibration::on_calButton_clicked()
{
  _algo.projector_calib(_param);
}
