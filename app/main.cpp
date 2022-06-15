#include "GaoCe.hpp"
#include "Worker.hpp"
#include "version.hpp"
#include "wrapper.hpp"

int
main(int argc, char* argv[])
{
  esf::Application app(argc, argv);
  app.setApplicationName("高测系统V3 (v" GaoCeAppV3_VERSION ")");

  //  es::Gencom::ginit();
  //  es::Com_DLP::ginit();
  //  es::Com_MVS::ginit();
  std::unique_ptr<GaoCe::GaoCe> _gaoce;
  _gaoce = std::move(GaoCe::create_v1());
  //  worker->_algo = std::move(wrapper);
  //  app.reg_worker(worker);

  //  //  获取相机画面
  //  std::function<cv::Mat()> getInput;
  //  getInput = [worker]() -> cv::Mat {
  //    es::Com_MVS::MvsCameraWrapper::Shared mc;
  //    bool colored;
  //    bool timeout;

  //    if (QThread::currentThread() == worker->thread()) {
  //      mc = worker->_mc.camera();
  //      colored = worker->_mc.colored();
  //      timeout = worker->_mc.timeout();
  //    } else {
  //      QMetaObject::invokeMethod(
  //        worker,
  //        [worker, &mc, &colored, &timeout]() {
  //          mc = worker->_mc.camera();
  //          colored = worker->_mc.colored();
  //          timeout = worker->_mc.timeout();
  //        },
  //        Qt::BlockingQueuedConnection);
  //    }

  //    if (!mc)
  //      return cv::Mat();

  //    try {
  //      return mc->snap_cvmat(timeout, colored);

  //    } catch (const es::Com_MVS::MvsError& e) {
  //      esf::Application::notifier().notify_text(
  //        e.repr(), QtMsgType::QtCriticalMsg, "获取图像失败");
  //    }

  //    return cv::Mat();
  //  };

  //  worker->_getInput = getInput;

  //  es::Com_MVS::MvsCamera::SubUi _mcUi{ worker->_mc, "相机输入" };
  //  app.reg_sub_ui(_mcUi);

  //  //  es::Com_DLP::DLP::SubUi _dlpUi{ worker->_dlp, "投影仪" };
  //  //  app.reg_sub_ui(_dlpUi);

  //  GaoCeConfigSubUi _cSubUi{ *worker };
  //  app.reg_sub_ui(_cSubUi);

  return app.exec();
}

