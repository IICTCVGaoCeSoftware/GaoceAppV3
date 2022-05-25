#include "Worker.hpp"

int
main(int argc, char* argv[])
{
  esf::Application app(argc, argv);
  // app.setApplicationName("高测系统 (v" GaoCeAppV3_VERSION ")");
  es::Gencom::ginit();
  es::Com_DLP::ginit();
  es::Com_MVS::ginit();

  auto worker = new Worker();

  app.reg_worker(worker);

  esg::VideoCapture::SubUi _vcSubUi{ worker->_vc, "视频\n捕获器" };
  _vcSubUi.setWindowTitle("视频捕获器");
  app.reg_sub_ui(_vcSubUi);

  es::Com_MVS::MvsCamera::SubUi _mcUi{ worker->_mc, "相机输入" };
  app.reg_sub_ui(_mcUi);

  es::Com_DLP::DLP::SubUi _dlpUi{ worker->_dlp, "投影仪" };
  app.reg_sub_ui(_dlpUi);

  return app.exec();
}

