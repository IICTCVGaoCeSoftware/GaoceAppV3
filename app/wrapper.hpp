#pragma once

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
  GaoCeConfigSubUi(Worker& worker);
};
