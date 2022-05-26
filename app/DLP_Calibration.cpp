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
  _imageSpin.setSuffix(" 张");
  _rowNumSpin.setPrefix("行方向 ");
  _colNumSpin.setPrefix("列方向 ");
  _chessNum.setText("棋盘格个数");
  _rowSize.setPrefix("行方向 ");
  _rowSize.setSuffix(" mm");
  _colSize.setPrefix("列方向 ");
  _colSize.setSuffix(" mm");
  _horiDis.setPrefix("水平间距 ");
  _horiDis.setSuffix(" mm");
  _verDis.setPrefix("垂直间距 ");
  _verDis.setSuffix(" mm");
  _imageNum.setText("采集图像的张数");
  _initOffset.setText("初始偏移");
  _chessDis.setText("棋盘格的顶点间距");
  _cornerPoint.setText("采用当前角点");
  _selPoint.setText("√");
  _noSelPoint.setText("×");
  _errorShow.setText("重投影误差显示");
  _resolution.setText("投影分辨率");

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

  // 初始偏移
  vlayout->addWidget(&_initOffset);
  auto offsetlayout = new QHBoxLayout();
  offsetlayout->addWidget(&_rowSize);
  offsetlayout->addWidget(&_colSize);
  vlayout->addLayout(offsetlayout);

  // 投影分辨率
  auto resolutionlayout = new QHBoxLayout();
  resolutionlayout->addWidget(&_resolution);
  resolutionlayout->addWidget(&_reso);
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

  auto calLayout = new QHBoxLayout();
  calLayout->addWidget(&_calButton);
  calLayout->addWidget(&_errorShow);
  calLayout->addWidget(&_reCalButton);

  auto Finallayout = new QVBoxLayout();
  Finallayout->addLayout(hlayout);
  Finallayout->addLayout(calLayout);

  setLayout(Finallayout);

  _leftLayout.setCurrentIndex(0);
}
