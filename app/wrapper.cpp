#include "wrapper.hpp"

GaoCeConfigSubUi::GaoCeConfigSubUi(Worker& worker)
  : _S("算法")
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
