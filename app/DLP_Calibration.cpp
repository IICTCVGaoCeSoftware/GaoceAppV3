#include "DLP_Calibration.hpp"
#include "wrapper.hpp"

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
  _current.setText("当前选取图片" + QString::number(temp));
  _excCorner.setText("提取角点");

  //  proCamAllCornersCoarse = read_matlab(); //所有的粗角点

  // 布局界面
  _leftLayout.addWidget(&_inputBench);
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

  // 提取角点
  vlayout->addWidget(&_excCorner);

  // 是否采用角点
  vlayout->addWidget(&_cornerPoint);
  auto pointLayout = new QHBoxLayout();
  pointLayout->addWidget(&_selPoint);
  pointLayout->addWidget(&_noSelPoint);
  vlayout->addLayout(pointLayout);

  auto hlayout = new QHBoxLayout();
  hlayout->addLayout(&_leftLayout);
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
  connect(&_selPoint, &QPushButton::clicked, this, &_T::on_selPoint_clicked);
  connect(&_excCorner, &QPushButton::clicked, this, &_T::on_excCorner_clicked);
}

void
DLP_Calibration::on_refresh_clicked()
{
  _current.setText("当前选取图片" + QString::number(temp));

  QString str = "D:/IICT/DLPPattern/images/projector/P";
  QString s = QString::number(temp++);
  str = str + s;
  str += ".bmp";
  image = cv::imread(str.toStdString());

  _inputBench.display(image);
  _refreshButton.setEnabled(false);
}

void
DLP_Calibration::on_excCorner_clicked()
{
  cv::Size proPatternSize = cv::Size(16, 15);
  cv::Mat imgProGray;
  cv::cvtColor(image, imgProGray, cv::COLOR_BGR2GRAY);

  cv::Mat proCamCornersCoarse = cv::Mat(4, 1, CV_32FC2);
  proCamCornersCoarse.at<cv::Vec2f>(0, 0)[0] =
    _inputBench.get_quadrangle()[0].x;
  proCamCornersCoarse.at<cv::Vec2f>(0, 0)[1] =
    _inputBench.get_quadrangle()[0].y;

  proCamCornersCoarse.at<cv::Vec2f>(3, 0)[0] =
    _inputBench.get_quadrangle()[1].x;
  proCamCornersCoarse.at<cv::Vec2f>(3, 0)[1] =
    _inputBench.get_quadrangle()[1].y;

  proCamCornersCoarse.at<cv::Vec2f>(1, 0)[0] =
    _inputBench.get_quadrangle()[2].x;
  proCamCornersCoarse.at<cv::Vec2f>(1, 0)[1] =
    _inputBench.get_quadrangle()[2].y;

  proCamCornersCoarse.at<cv::Vec2f>(2, 0)[0] =
    _inputBench.get_quadrangle()[3].x;
  proCamCornersCoarse.at<cv::Vec2f>(2, 0)[1] =
    _inputBench.get_quadrangle()[3].y;

  _algo.find_procorners(imgProGray,
                        proCamCornersCoarse,
                        proPatternSize,
                        &proImgCorners,
                        &proCamCorners);
  std::vector<cv::Point2f> imagecorner = cv::Mat_<cv::Point2f>(proImgCorners);
  std::vector<cv::Point2f> camcorner = cv::Mat_<cv::Point2f>(proCamCorners);

  for (uint8_t i = 0; i < imagecorner.size(); i++) {
    circle(image, imagecorner[i], 10, cv::Scalar(0, 0, 255), 5);
  }

  for (uint8_t i = 0; i < camcorner.size(); i++) {
    circle(image, camcorner[i], 10, cv::Scalar(0, 255, 0), 5);
  }

  _excCorner.setEnabled(false);
  _inputBench.display(image);
}

void
DLP_Calibration::on_selPoint_clicked()
{
  cv::Size proPatternSize = cv::Size(16, 15);
  calibProjProcessPara._proImgCorners.push_back(proImgCorners);
  calibProjProcessPara._proCamCorners.push_back(proCamCorners);
  calibProjProcessPara._proPatternSize.push_back(proPatternSize);
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("提取角点成功");
  MBox.exec();
  _refreshButton.setEnabled(true);
  _excCorner.setEnabled(true);

  for (uint8_t i = 0; i < calibProjProcessPara._proCamCorners[0].rows *
                            calibProjProcessPara._proCamCorners[0].cols;
       i++) {
    qDebug() << "Sel corners2 x" << i
             << calibProjProcessPara._proCamCorners[0].at<cv::Vec2f>(i, 0)[0];
    qDebug() << "Sel corners2 y" << i
             << calibProjProcessPara._proCamCorners[0].at<cv::Vec2f>(i, 0)[1];
  }
}

void
DLP_Calibration::on_calButton_clicked()
{
  calibProjProcessPara._proRealDx = 5;
  calibProjProcessPara._proRealDy = 0;
  calibProjProcessPara._proCbDx = 23;
  calibProjProcessPara._proCbDy = 31;
  calibProjProcessPara._proResolution = cv::Size(1280, 720);

  for (uint8_t i = 0; i < calibProjProcessPara._proCamCorners[0].rows *
                            calibProjProcessPara._proCamCorners[0].cols;
       i++) {
    qDebug() << "Cal corners2 x" << i
             << calibProjProcessPara._proCamCorners[0].at<cv::Vec2f>(i, 0)[0];
    qDebug() << "Cal corners2 y" << i
             << calibProjProcessPara._proCamCorners[0].at<cv::Vec2f>(i, 0)[1];
  }

  _algo.projector_calib(calibProjProcessPara);

  GaoCeWrapper* myWrapper = dynamic_cast<GaoCeWrapper*>(&_algo);

  double Err =
    myWrapper->_gaoce->_calibProjResult._proReprojErr.at<double>(0, 0);
  _error.setText(QString::number(Err, 'f', 2));
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("标定投影仪成功");
  MBox.exec();
}
