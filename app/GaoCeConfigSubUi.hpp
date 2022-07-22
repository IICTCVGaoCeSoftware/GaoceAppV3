#include "DLP_Calibration.hpp"
#include "GaoCe_InitParams.hpp"
#include "MVS_Calibration.h"
#include "PatternCoding.hpp"
#include "Worker.hpp"

#include <Eyestack/Framework.hpp>

namespace esf = Eyestack::Framework;

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

  //  ReConstructWindow _reConWin;
  //  QMdiSubWindow& _swReconWin;

  GaoCeConfigUi_MVSInitParams _ip1;
  GaoCeConfigUi_DLPInitParams _ip2;
  GaoCeConfigUi_ReInitParams _ip3;

  QMdiSubWindow& _swIp1;
  QMdiSubWindow& _swIp2;
  QMdiSubWindow& _swIp3;

public:
  GaoCeConfigSubUi(Worker& worker);

private slots:
  void when_show1();
  void when_show2();

public slots:
  void when_show3();

  // void disable_all();
  // void enable_all();
};

/**
 * @brief 高测配置向导类
 */
class GaoCeConfigWizard : public QWizard
{
  using _T = GaoCeConfigWizard;
  using _S = QWizard;

public:
  GaoCeConfigWizard(GaoCeConfigSubUi& configUi);

private:
  GaoCeConfigSubUi& _configUi;
  //  QWizardPage welcomPage;
  //  QWizardPage wpPage;
  //  QWizardPage lbtPage;
  //  QWizardPage lrrPage;
  //  QWizardPage lpPage;
  //  QWizardPage ltPage;
  //  QWizardPage idpPage;

  // QWidget interface
protected:
  virtual void showEvent(QShowEvent* event) override;
  virtual void hideEvent(QHideEvent* event) override;
};
