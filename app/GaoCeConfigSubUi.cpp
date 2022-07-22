#include "GaoCeConfigSubUi.hpp"

GaoCeConfigSubUi::GaoCeConfigSubUi(Worker& worker)
  : _S("算法")
  , _MVScal(*worker._algo)
  , _swMVScal(add_mdi_action("相机标定", _MVScal))
  , _DLPcal(*worker._algo)
  , _swDLPcal(add_mdi_action("投影仪标定", _DLPcal))
  , _PatternCoding(*worker._algo)
  , _swPatternCoding(add_mdi_action("图案编码", _PatternCoding))
  , _ip1(*worker._algo)
  , _swIp1(add_mdi_action("相机配置", _ip1))
  , _ip2(*worker._algo)
  , _swIp2(add_mdi_action("投影仪配置", _ip2))
  , _ip3(*worker._algo)
  , _swIp3(add_mdi_action("重建配置", _ip3))

{
  connect(&_MVScal, &MVS_Calibration::s_show, this, &_T::when_show1);
  connect(&_DLPcal, &DLP_Calibration::s_showParam, this, &_T::when_show2);
}

void
GaoCeConfigSubUi::when_show1()
{
  _ip1.show();
  _ip1.setWindowFlags(Qt::WindowStaysOnTopHint);
}

void
GaoCeConfigSubUi::when_show2()
{
  _ip2.show();
  _ip2.setWindowFlags(Qt::WindowStaysOnTopHint);
}

void
GaoCeConfigSubUi::when_show3()
{
  _ip3.show();
  _ip3.setWindowFlags(Qt::WindowStaysOnTopHint);
}

void
GaoCeConfigWizard::showEvent(QShowEvent* event)
{
  // 显示的时候从各个 MdiSubUi 上把界面借过来

  //  wpPage.layout()->addWidget(&_configUi._wp);
  //  _configUi._wp.show();
  //  lbtPage.layout()->addWidget(&_configUi._lbt);
  //  _configUi._lbt.show();
  //  lrrPage.layout()->addWidget(&_configUi._lrr);
  //  _configUi._lrr.show();
  //  lpPage.layout()->addWidget(&_configUi._lp);
  //  _configUi._lp.show();
  //  ltPage.layout()->addWidget(&_configUi._lt);
  //  _configUi._lt.show();
  //  idpPage.layout()->addWidget(&_configUi._ip);
  //  _configUi._ip.show();

  //  _configUi._swWp.setWidget(nullptr);
  //  _configUi._swWp.hide();
  //  _configUi._swLbt.setWidget(nullptr);
  //  _configUi._swLbt.hide();
  //  _configUi._swLp.setWidget(nullptr);
  //  _configUi._swLp.hide();
  //  _configUi._swLt.setWidget(nullptr);
  //  _configUi._swLt.hide();
  //  _configUi._swLrr.setWidget(nullptr);
  //  _configUi._swLrr.hide();
  //  _configUi._swIp.setWidget(nullptr);
  //  _configUi._swIp.hide();

  //  _S::showEvent(event);
}

void
GaoCeConfigWizard::hideEvent(QHideEvent* event)
{
  // 关闭时再把各个配置界面还回去

  //  _S::hideEvent(event);

  //  _configUi._swWp.setWidget(&_configUi._wp);
  //  _configUi._swLbt.setWidget(&_configUi._lbt);
  //  _configUi._swLp.setWidget(&_configUi._lp);
  //  _configUi._swLt.setWidget(&_configUi._lt);
  //  _configUi._swLrr.setWidget(&_configUi._lrr);
  //  _configUi._swIp.setWidget(&_configUi._ip);
}
