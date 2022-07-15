#include "DLP_Calibration.hpp"
#include "wrapper.hpp"

DLP_Calibration::DLP_Calibration(GaoCe::GaoCe& algo, QWidget* parent)
  : _S(parent)
  , _algo(algo)
  , _refreshButton("刷新输入")
  , _calButton("标定投影仪")
  , _reCalButton("重新标定")
  , _saveImg("保存图片")
  , _config("更多设置")
{
  // 配置组件
  _imageSpin.setPrefix("采集图像 ");
  _imageSpin.setValue(20);
  _imageSpin.setSuffix(" 张");
  _rowNumSpin.setPrefix("行方向 ");
  _rowNumSpin.setValue(15);
  _colNumSpin.setPrefix("列方向 ");
  _colNumSpin.setValue(15);
  _chessNum.setText("棋盘格个数");
  _rowOffset.setPrefix("行方向 ");
  _rowOffset.setValue(5);
  _rowOffset.setSuffix(" 像素");
  _colOffset.setPrefix("列方向 ");
  _colOffset.setValue(0);
  _colOffset.setSuffix(" 像素");
  _horiDis.setPrefix("水平间距 ");
  _horiDis.setDecimals(1);
  _horiDis.setSingleStep(0.1);
  _horiDis.setValue(31);
  _horiDis.setSuffix(" mm");
  _verDis.setPrefix("垂直间距 ");
  _verDis.setDecimals(1);
  _verDis.setSingleStep(0.1);
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
  _maskRow.setPrefix("行");
  _maskCol.setPrefix("列");
  _insertMask.setText("插入标定矩阵");
  _excCorner.setText("提取角点");
  _showMask.setText("显示Mask矩阵");
  _showMask.setChecked(false);
  _showDistri.setText("显示角点分布图");
  _showDistri.setChecked(true);
  _projDistri.setText("投影仪角点分布");
  _projDistri.setAlignment(Qt::AlignCenter);
  _calDistri.setText("标定板角点分布");
  _calDistri.setAlignment(Qt::AlignCenter);
  _projMaskL.setText("投影仪Mask矩阵");
  _projMaskL.setAlignment(Qt::AlignCenter);
  _calMastL.setText("标定板Mask矩阵");
  _calMastL.setAlignment(Qt::AlignCenter);
  _calMask.setRowCount(2);
  _calMask.setColumnCount(2);
  QString filename = "C:\\Gaoce\\temp.txt";
  file = new QFile(filename);
  file->setFileName(filename);
  bool ret = file->open(QIODevice::WriteOnly | QIODevice::Truncate);

  connect(&_timer, &QTimer::timeout, this, &_T::when_timer_timeout);
  _timer.start(50);

  // 逻辑禁用关系
  _calButton.setEnabled(false);
  _reCalButton.setEnabled(false);
  _selPoint.setEnabled(false);
  _noSelPoint.setEnabled(false);
  _excCorner.setEnabled(false);

  _camera.set_power(true);
  _camera.s_powerClicked(false);

  // 默认显示角点分布图
  _showImgCorner.show();
  _projDistri.show();
  _showCamCorner.show();
  _calDistri.show();
  _projMask.hide();
  _projMaskL.hide();
  _calMask.hide();
  _calMastL.hide();

  // 初始化角点图
  cv::Mat img1(2048, 2592, CV_8UC3, cv::Scalar(0));
  _showICorner = img1;
  cv::Mat img2(2048, 2592, CV_8UC3, cv::Scalar(0));
  _showCCorner = img2;
  _showImgCorner.display(_showICorner);
  _showCamCorner.display(_showCCorner);

  // 布局界面
  _leftWidget.setLayout(&_stackLayout);
  _stackLayout.addWidget(&_camera);
  _stackLayout.addWidget(&_inputBench);
  _leftLayout.addWidget(&_leftWidget);
  _leftLayout.addWidget(&_current);

  // 右边的垂直界面
  auto vlayout = new QVBoxLayout();

  // 选择显示角点或者Mask
  _buttongroup = new QButtonGroup(this);
  _buttongroup->addButton(&_showMask, 1);
  _buttongroup->addButton(&_showDistri, 2);
  auto selectlayout = new QHBoxLayout();
  selectlayout->addWidget(&_showMask);
  selectlayout->addWidget(&_showDistri);
  vlayout->addLayout(selectlayout);

  // 插入投影仪的mask矩阵
  vlayout->addWidget(&_projMask);
  vlayout->addWidget(&_projMaskL);
  _calMask.setMinimumSize(50, 50);
  _calMask.setMaximumSize(330, 300);

  // 角点分布图
  vlayout->addWidget(&_showImgCorner);
  vlayout->addWidget(&_projDistri);
  vlayout->addWidget(&_showCamCorner);
  vlayout->addWidget(&_calDistri);

  // 插入标定板的Mask矩阵界面
  auto masklayout = new QHBoxLayout();
  masklayout->addWidget(&_maskRow);
  masklayout->addWidget(&_maskCol);
  masklayout->addWidget(&_insertMask);
  vlayout->addLayout(masklayout);

  // 插入标定板的mask矩阵
  vlayout->addWidget(&_calMask);
  vlayout->addWidget(&_calMastL);
  _calMask.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  _calMask.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  _projMask.setRowCount(_rowNumSpin.value() - 1);
  _projMask.setColumnCount(_colNumSpin.value() - 1);

  _projMask.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  _projMask.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  _projMask.horizontalHeader()->setVisible(true);
  _projMask.verticalHeader()->setVisible(true);
  set_table();

  // 采集图像张数
  auto inputLayout = new QHBoxLayout();
  inputLayout->addWidget(&_imageNum);
  inputLayout->addWidget(&_imageSpin);
  vlayout->addLayout(inputLayout);

  // 棋盘格行列方向大小
  auto chesslayout = new QHBoxLayout();
  chesslayout->addWidget(&_chessNum);
  chesslayout->addWidget(&_rowNumSpin);
  chesslayout->addWidget(&_colNumSpin);
  vlayout->addLayout(chesslayout);

  // 初始偏移
  auto offsetlayout = new QHBoxLayout();
  offsetlayout->addWidget(&_initOffset);
  offsetlayout->addWidget(&_rowOffset);
  offsetlayout->addWidget(&_colOffset);
  vlayout->addLayout(offsetlayout);

  // 投影分辨率
  auto resolutionlayout = new QHBoxLayout();
  resolutionlayout->addWidget(&_resolution);
  resolutionlayout->addWidget(&_reso1);
  resolutionlayout->addWidget(&_multi);
  resolutionlayout->addWidget(&_reso2);
  vlayout->addLayout(resolutionlayout);

  // 棋盘格的顶点间距
  auto chessDislayout = new QHBoxLayout();
  chessDislayout->addWidget(&_chessDis);
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
  vlayout->addWidget(&_saveImg);

  auto hlayout = new QHBoxLayout();
  hlayout->addLayout(&_leftLayout);
  hlayout->addLayout(vlayout);
  hlayout->setStretch(0, 8);
  hlayout->setStretch(1, 2);

  auto calLayout = new QHBoxLayout();
  calLayout->addWidget(&_calButton);
  calLayout->addWidget(&_config);
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

  connect(
    &_noSelPoint, &QPushButton::clicked, this, &_T::on_noSelPoint_clicked);
  connect(
    &_reCalButton, &QPushButton::clicked, this, &_T::on_reCalButton_clicked);
  connect(&_config, &QPushButton::clicked, this, &_T::on_config_clicked);

  connect(
    &_insertMask, &QPushButton::clicked, this, &_T::on_insertMask_clicked);
  connect(&_saveImg, &QPushButton::clicked, this, &_T::on_saveImg_clicked);

  connect(_buttongroup,
          SIGNAL(buttonClicked(int)),
          this,
          SLOT(handleRadioGroup(int)));

  connect(&_rowNumSpin, &::QSpinBox::valueChanged, this, &_T::cal_initOffset);
  connect(&_colNumSpin, &::QSpinBox::valueChanged, this, &_T::cal_initOffset);
  connect(&_rowNumSpin, &::QSpinBox::valueChanged, this, &_T::set_table);
  connect(&_colNumSpin, &::QSpinBox::valueChanged, this, &_T::set_table);

  // 初始化状态
  _stackLayout.setCurrentIndex(0);
}

#ifdef USE_CAM
// 相机测试用
void
DLP_Calibration::on_refresh_clicked()
{
  if (temp > _imageSpin.value()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("图像数已达上线，请标定或增加图像");
    MBox.exec();
    return;
  }
  image = _getInput();
  image.copyTo(saveImg);
  if (image.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("警告");
    MBox.setText("相机未抓取到图片");
    MBox.exec();
    return;
  }
  temp++;
  _current.setText("当前选取图片" + QString::number(temp++));
  _inputBench.display(image);
  _stackLayout.setCurrentIndex(1);
  _refreshButton.setEnabled(false);
  _excCorner.setEnabled(true);
}

#else
// 图像测试用
void
DLP_Calibration::on_refresh_clicked()
{
  if (temp > _imageSpin.value()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("图像数已达上线，请标定或增加图像");
    MBox.exec();
    return;
  }

  _current.setText("当前选取图片" + QString::number(temp));

  QString str = "D:/IICT/DLPPattern/images/projector(0711)/";
  QString s = QString::number(temp);
  str = str + s;
  str += ".bmp";
  image = cv::imread(str.toStdString());
  // 深拷贝
  image.copyTo(saveImg);
  if (image.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("警告");
    MBox.setText("相机未抓取到图片");
    MBox.exec();
    return;
  }
  temp++;
  _stackLayout.setCurrentIndex(1);
  _inputBench.display(image);
  _refreshButton.setEnabled(false);
  _excCorner.setEnabled(true);
}

#endif

void
DLP_Calibration::on_excCorner_clicked()
{
  // 棋盘格个数
  auto row = _rowNumSpin.value();
  auto col = _colNumSpin.value();
  cv::Size proPatternSize = cv::Size(row, col);
  // 水平和垂直偏移
  auto proOffsetDx = _rowOffset.value();
  auto proOffsetDy = _colOffset.value();
  // 标定板角点个数
  auto calrow = _maskRow.value();
  auto calcol = _maskCol.value();
  cv::Size calibPatternSize = cv::Size(calrow, calcol);

  // 分辨率
  auto wide = _reso1.text().toInt();   // 1280
  auto height = _reso2.text().toInt(); // 720
  cv::Size proResolution = cv::Size(wide, height);

  //  cv::Mat imgProGray;
  //  cv::cvtColor(image, imgProGray, cv::COLOR_BGR2GRAY);

  proCamCornersCoarse = cv::Mat(4, 1, CV_32FC2);
  calCamCornersCoarse = cv::Mat(4, 1, CV_32FC2);

  read_CamCorners(proCamCornersCoarse, calCamCornersCoarse);

  _algo.find_procorners(image,
                        calCamCornersCoarse,
                        proCamCornersCoarse,
                        proResolution,
                        calibPatternSize,
                        proPatternSize,
                        proOffsetDx,
                        proOffsetDy,
                        &proImgCorners,
                        &proCamCorners,
                        &proProjCorners);

  // 没有提取到角点
  if (cv::sum(proImgCorners)[0] == 0 || cv::sum(proCamCorners)[0] == 0) {
    QMessageBox MBox;
    MBox.setWindowTitle("警告");
    MBox.setText("未提取到角点，请检查棋盘格个数是否正确");
    MBox.exec();
    return;
  }

  // 转换为三通道图片，角点标注才有颜色
  cv::Mat imgCamBGR;
  cv::cvtColor(image, imgCamBGR, cv::COLOR_GRAY2BGR);

  std::vector<cv::Point2f> imagecorner = cv::Mat_<cv::Point2f>(proImgCorners);
  std::vector<cv::Point2f> camcorner = cv::Mat_<cv::Point2f>(proCamCorners);

  // 红色代表投影仪角点
  for (int i = 0; i < imagecorner.size(); i++) {
    circle(imgCamBGR, imagecorner[i], 10, cv::Scalar(0, 0, 255), 5);
  }

  // 绿色代表标定板角点
  for (int i = 0; i < camcorner.size(); i++) {
    circle(imgCamBGR, camcorner[i], 10, cv::Scalar(0, 255, 0), 5);
  }

  _excCorner.setEnabled(false);
  _selPoint.setEnabled(true);
  _noSelPoint.setEnabled(true);
  _inputBench.display(imgCamBGR);
  imgCamBGR.release();
}

void
DLP_Calibration::on_selPoint_clicked()
{
  auto row = _rowNumSpin.value();
  auto col = _colNumSpin.value();
  cv::Size proPatternSize = cv::Size(row, col);

  // 水平和垂直偏移
  auto hor = _horiDis.value();
  auto ver = _verDis.value();

  // 水平和垂直偏移
  auto ros = _rowOffset.value();
  auto cos = _colOffset.value();

  // 导入投影仪Mask矩阵
  cv::Mat proimg(
    _rowNumSpin.value() - 1, _colNumSpin.value() - 1, CV_8UC1, cv::Scalar(0));

  // 导入标定板Mask矩阵
  cv::Mat calimg(
    _calMask.rowCount(), _calMask.columnCount(), CV_8UC1, cv::Scalar(0));

  for (int row = 0; row < _projMask.rowCount(); row++) {
    for (int col = 0; col < _projMask.columnCount(); col++) {
      uint8_t item = _projMask.item(row, col)->text().toUInt();
      proimg.at<uchar>(row, col) = item;
    }
  }

  for (int row = 0; row < _calMask.rowCount(); row++) {
    for (int col = 0; col < _calMask.columnCount(); col++) {
      uint8_t item = _calMask.item(row, col)->text().toUInt();
      calimg.at<uchar>(row, col) = item;
    }
  }

  calibProjProcessPara._proRealDx.push_back(ros);
  calibProjProcessPara._proRealDy.push_back(cos);
  calibProjProcessPara._proCbDx.push_back(hor);
  calibProjProcessPara._proCbDy.push_back(ver);
  calibProjProcessPara._proImgCorners.push_back(proImgCorners);
  calibProjProcessPara._proCamCorners.push_back(proCamCorners);
  calibProjProcessPara._proPatternSize.push_back(proPatternSize);
  calibProjProcessPara._projCornersMask.push_back(proimg);
  calibProjProcessPara._camCornersMask.push_back(calimg);
  calibProjProcessPara._proProjCorners.push_back(proProjCorners);

  QTextStream stream(file);
  stream << row << " " << col << " " << ros << " " << cos << " " << hor << " "
         << ver << "\n";

  stream << "Proj Corner:"
         << "\n";
  for (uint8_t i = 0; i < proCamCornersCoarse.rows * proCamCornersCoarse.cols;
       i++) {
    stream << "corners x" << i << " "
           << proCamCornersCoarse.at<cv::Vec2f>(i, 0)[0];
    stream << "corners y" << i << "  "
           << proCamCornersCoarse.at<cv::Vec2f>(i, 0)[1] << "\n";
  }
  stream << "Cal Corner:"
         << "\n";
  for (uint8_t i = 0; i < calCamCornersCoarse.rows * calCamCornersCoarse.cols;
       i++) {
    stream << "corners x" << i << " "
           << calCamCornersCoarse.at<cv::Vec2f>(i, 0)[0];
    stream << "corners y" << i << " "
           << calCamCornersCoarse.at<cv::Vec2f>(i, 0)[1] << "\n";
  }

  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("提取角点成功");
  MBox.exec();

  // 画到角点图上
  std::vector<cv::Point2f> imagecorner = cv::Mat_<cv::Point2f>(proImgCorners);
  std::vector<cv::Point2f> camcorner = cv::Mat_<cv::Point2f>(proCamCorners);

  // 红色代表投影仪角点
  for (int i = 0; i < imagecorner.size(); i++) {
    circle(_showICorner, imagecorner[i], 10, cv::Scalar(0, 0, 255), 5);
  }
  _showImgCorner.display_cvmat(_showICorner);

  // 绿色代表标定板角点
  for (int i = 0; i < camcorner.size(); i++) {
    circle(_showCCorner, camcorner[i], 10, cv::Scalar(0, 255, 0), 5);
  }
  _showCamCorner.display_cvmat(_showCCorner);

  _stackLayout.setCurrentIndex(0);
  // 逻辑禁用
  _refreshButton.setEnabled(true);
  _selPoint.setEnabled(false);
  _noSelPoint.setEnabled(false);
  _excCorner.setEnabled(false);
  _calButton.setEnabled(true);
}

void
DLP_Calibration::on_noSelPoint_clicked()
{
  _current.setText("当前选取图片" + QString::number(--temp));
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("提取角点失败，请重新刷新输入");
  MBox.exec();
  _stackLayout.setCurrentIndex(0);
  _refreshButton.setEnabled(true);
  _selPoint.setEnabled(false);
  _noSelPoint.setEnabled(false);
}

void
DLP_Calibration::on_calButton_clicked()
{
  calibProjProcessPara._proResolution = cv::Size(1280, 720);

  _algo.projector_calib(calibProjProcessPara, &camRepErr);

  double Err = camRepErr.at<double>(0, 0);
  _error.setText(QString::number(Err, 'f', 2));
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("标定投影仪成功");
  MBox.exec();

  // 写入中间文件
  QTextStream stream(file);
  stream << _rowOffset.value();
}

void
DLP_Calibration::on_reCalButton_clicked()
{
  calibProjProcessPara._proCamCorners.clear();
  calibProjProcessPara._proImgCorners.clear();
  calibProjProcessPara._proPatternSize.clear();

  _refreshButton.setEnabled(true);
  _calButton.setEnabled(false);
  _reCalButton.setEnabled(false);
  _selPoint.setEnabled(false);
  _noSelPoint.setEnabled(false);
  _excCorner.setEnabled(false);

  temp = 1;
  QMessageBox MBox;
  MBox.setWindowTitle("提示");
  MBox.setText("已清空所有数据，请重新刷新输入");
  MBox.exec();
}

void
DLP_Calibration::on_insertMask_clicked()
{
  _calMask.setRowCount(_maskRow.value());
  _calMask.setColumnCount(_maskCol.value());

  for (int row = 0; row < _calMask.rowCount(); row++) {
    for (int col = 0; col < _calMask.columnCount(); col++) {
      _calMask.setItem(row, col, new QTableWidgetItem("1"));
    }
  }
  handleRadioGroup(1);
  _showMask.setChecked(true);
}

void
DLP_Calibration::handleRadioGroup(int id)
{
  if (id == 1) {
    _showImgCorner.hide();
    _projDistri.hide();
    _showCamCorner.hide();
    _calDistri.hide();
    _maskRow.show();
    _maskCol.show();
    _insertMask.show();
    _projMask.show();
    _projMaskL.show();
    _calMask.show();
    _calMastL.show();
  } else if (id == 2) {
    _showImgCorner.show();
    _projDistri.show();
    _showCamCorner.show();
    _calDistri.show();
    _projMask.hide();
    _projMaskL.hide();
    _calMask.hide();
    _calMastL.hide();
  }
}

void
DLP_Calibration::set_table()
{
  auto rowCount = _rowNumSpin.value() - 1;
  auto colCount = _colNumSpin.value() - 1;

  _projMask.setRowCount(rowCount);
  _projMask.setColumnCount(colCount);

  for (int row = 0; row < rowCount; row++) {
    for (int col = 0; col < colCount; col++) {
      _projMask.setItem(row, col, new QTableWidgetItem("1"));
    }
  }
}

void
DLP_Calibration::on_saveImg_clicked()
{
  if (saveImg.empty()) {
    QMessageBox MBox;
    MBox.setWindowTitle("提示");
    MBox.setText("无法保存，请刷新输入");
    MBox.exec();
    return;
  }
  QString filename =
    QFileDialog::getSaveFileName(this, "保存相机图像", "*.bmp");
  QFile file(filename);
  if (filename != "")
    cv::imwrite(filename.toStdString(), saveImg);
}

void
DLP_Calibration::on_config_clicked()
{
  emit s_show();
}

void
DLP_Calibration::read_CamCorners(cv::Mat& proCamCornersCoarse,
                                 cv::Mat& calCamCornersCoarse)
{
  proCamCornersCoarse.at<cv::Vec2f>(3, 0)[0] =
    _inputBench.get_outQuadrangle()[0].x;
  proCamCornersCoarse.at<cv::Vec2f>(3, 0)[1] =
    _inputBench.get_outQuadrangle()[0].y;

  proCamCornersCoarse.at<cv::Vec2f>(2, 0)[0] =
    _inputBench.get_outQuadrangle()[1].x;
  proCamCornersCoarse.at<cv::Vec2f>(2, 0)[1] =
    _inputBench.get_outQuadrangle()[1].y;

  proCamCornersCoarse.at<cv::Vec2f>(1, 0)[0] =
    _inputBench.get_outQuadrangle()[2].x;
  proCamCornersCoarse.at<cv::Vec2f>(1, 0)[1] =
    _inputBench.get_outQuadrangle()[2].y;

  proCamCornersCoarse.at<cv::Vec2f>(0, 0)[0] =
    _inputBench.get_outQuadrangle()[3].x;
  proCamCornersCoarse.at<cv::Vec2f>(0, 0)[1] =
    _inputBench.get_outQuadrangle()[3].y;

  calCamCornersCoarse.at<cv::Vec2f>(0, 0)[0] =
    _inputBench.get_quadrangle()[0].x;
  calCamCornersCoarse.at<cv::Vec2f>(0, 0)[1] =
    _inputBench.get_quadrangle()[0].y;

  calCamCornersCoarse.at<cv::Vec2f>(3, 0)[0] =
    _inputBench.get_quadrangle()[1].x;
  calCamCornersCoarse.at<cv::Vec2f>(3, 0)[1] =
    _inputBench.get_quadrangle()[1].y;

  calCamCornersCoarse.at<cv::Vec2f>(1, 0)[0] =
    _inputBench.get_quadrangle()[2].x;
  calCamCornersCoarse.at<cv::Vec2f>(1, 0)[1] =
    _inputBench.get_quadrangle()[2].y;

  calCamCornersCoarse.at<cv::Vec2f>(2, 0)[0] =
    _inputBench.get_quadrangle()[3].x;
  calCamCornersCoarse.at<cv::Vec2f>(2, 0)[1] =
    _inputBench.get_quadrangle()[3].y;
}

void
DLP_Calibration::cal_initOffset()
{
  int hor = 1280 % (_rowNumSpin.value());
  int ver = 720 % (_colNumSpin.value());
  _rowOffset.setValue(hor);
  _colOffset.setValue(ver);
}

void
DLP_Calibration::when_timer_timeout()
{
  cv::Mat image = _getInput();
  _camera.display_cvmat(image);
}

void
DLP_Calibration::when_configMonitor_powerClicked(bool power)
{
  cv::Mat image = _getInput();
  _camera.display_cvmat(image);
}
