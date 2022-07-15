#pragma once
#include "Eyestack/Design/Paramgr.hpp"
#include "GaoCe.hpp"

namespace esd = Eyestack::Design;

/**
 * @brief GaoCeConfigUi_MVSInitParams 初始化参数窗口
 */
class GaoCeConfigUi_MVSInitParams : public esd::Paramgr
{
  Q_OBJECT

  using _T = GaoCeConfigUi_MVSInitParams;
  using _S = esd::Paramgr;

public:
  GaoCeConfigUi_MVSInitParams(GaoCe::GaoCe& algo);
};

class GaoCeConfigUi_DLPInitParams : public esd::Paramgr
{
  Q_OBJECT

  using _T = GaoCeConfigUi_DLPInitParams;
  using _S = esd::Paramgr;

public:
  GaoCeConfigUi_DLPInitParams(GaoCe::GaoCe& algo);
};

class GaoCeConfigUi_ReInitParams : public esd::Paramgr
{
  Q_OBJECT

  using _T = GaoCeConfigUi_ReInitParams;
  using _S = esd::Paramgr;

public:
  GaoCeConfigUi_ReInitParams(GaoCe::GaoCe& algo);
};
