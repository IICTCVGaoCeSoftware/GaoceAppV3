#include "GaoCe_InitParams.hpp"

GaoCeConfigUi_MVSInitParams::GaoCeConfigUi_MVSInitParams(GaoCe::GaoCe& algo)
{
  set_table(algo.param_camera_table());
}

GaoCeConfigUi_DLPInitParams::GaoCeConfigUi_DLPInitParams(GaoCe::GaoCe& algo)
{
  set_table(algo.param_projector_table());
}

GaoCeConfigUi_ReInitParams::GaoCeConfigUi_ReInitParams(GaoCe::GaoCe& algo)
{
  set_table(algo.param_3dreconstruction_table());
}
