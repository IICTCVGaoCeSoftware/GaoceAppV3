#include "wrapper.hpp"

GaoCeConfigSubUi::GaoCeConfigSubUi(Worker& worker)
  : _S("算法")
  , _MVScal(*worker._algo)
  , _swMVScal(add_mdi_action("相机标定", _MVScal))
  , _DLPcal(*worker._algo)
  , _swDLPcal(add_mdi_action("投影仪标定", _DLPcal))
  , _PatternCoding(*worker._algo)
  , _swPatternCoding(add_mdi_action("图案编码", _PatternCoding))
  , _reConWin(*worker._algo)
  , _swReconWin(add_mdi_action("重建窗口", _reConWin))
{

}

void
GaoCeWrapper::init_param()
{
  return _gaoce->init_param();
}

void
GaoCeWrapper::reset_config() noexcept
{
  return _gaoce->reset_config();
}

void
GaoCeWrapper::dump_config(QDataStream& ds) noexcept(false)
{
  return _gaoce->dump_config(ds);
}

void
GaoCeWrapper::load_config(QDataStream& ds) noexcept(false)
{
  return _gaoce->load_config(ds);
}
