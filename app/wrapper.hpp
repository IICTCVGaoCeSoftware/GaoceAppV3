#pragma once

#include "DLP_Calibration.hpp"
#include "MVS_Calibration.h"
#include "PatternCoding.hpp"
#include "ReConstructWindow.hpp"
#include "Worker.hpp"
#include <Eyestack/Framework.hpp>

namespace esf = Eyestack::Framework;

class GaoCeWrapper : public GaoCe::GaoCe
{
public:
  std::unique_ptr<GaoCe> _gaoce;

  // GaoCe interface
public:
  virtual void init_param() override;
  virtual std::vector<Result> detect(const cv::Mat& img) override;
  virtual void reset_config() noexcept override;
  virtual void dump_config(QDataStream& ds) noexcept(false) override;
  virtual void load_config(QDataStream& ds) noexcept(false) override;
};

/**
 * @brief 高测配置UI界面
 */
class GaoCeConfigSubUi : public esf::MainWindow::SubUi::MdiMenu
{
  Q_OBJECT

  using _T = GaoCeConfigSubUi;
  using _S = esf::MainWindow::SubUi::MdiMenu;

public:
  MVS_Calibration _MVScal;
  QMdiSubWindow& _swMVScal;
  DLP_Calibration _DLPcal;
  QMdiSubWindow& _swDLPcal;
  PatternCoding _PatternCoding;
  QMdiSubWindow& _swPatternCoding;
  ReConstructWindow _reConWin;
  QMdiSubWindow& _swReconWin;

public:
  GaoCeConfigSubUi(Worker& worker);

  // private slots:
  //   void disable_all();
  //   void enable_all();
};
