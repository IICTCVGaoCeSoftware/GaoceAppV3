#include "GaoCe.hpp"
#include "ReConstructWindow.hpp"
#include "Worker.hpp"
#include "version.hpp"
#include "wrapper.hpp"

int
main(int argc, char* argv[])
{
  esf::Application app(argc, argv);
  app.setApplicationName("高测系统V3 (v" GaoCeAppV3_VERSION ")");

  es::Gencom::ginit();
  es::Com_DLP::ginit();
  es::Com_MVS::ginit();
  auto worker = new Worker();
  auto wrapper = std::make_unique<GaoCeWrapper>();
  wrapper->_gaoce = std::move(GaoCe::create_v1());
  worker->_algo = std::move(wrapper);
  app.reg_worker(worker);

  //  获取相机画面
  std::function<cv::Mat()> getInput;
  std::function<cv::Mat()> input;

  input = [worker]() -> cv::Mat {
    es::Com_MVS::MvsCameraWrapper::Shared mc;
    mc = worker->_mc.camera();
    if (!mc)
      return cv::Mat();
    mc->SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);
    mc->SetEnumValue("TriggerSource", 7);
    mc->CommandExecute("TriggerSoftware");

    try {
      return mc->snap_cvmat(50);
    } catch (const es::Com_MVS::MvsError& e) {
      esf::Application::notifier().notify_text(
        e.repr(), QtMsgType::QtCriticalMsg, "获取图像失败");
    }

    return cv::Mat();
  };

  getInput = [worker]() -> cv::Mat {
    es::Com_MVS::MvsCameraWrapper::Shared mc;
    bool colored;
    bool timeout;

    if (QThread::currentThread() == worker->thread()) {
      mc = worker->_mc.camera();
      colored = worker->_mc.colored();
      timeout = worker->_mc.timeout();
    } else {
      QMetaObject::invokeMethod(
        worker,
        [worker, &mc, &colored, &timeout]() {
          mc = worker->_mc.camera();
          colored = worker->_mc.colored();
          timeout = worker->_mc.timeout();
        },
        Qt::BlockingQueuedConnection);
    }

    if (!mc)
      return cv::Mat();

    try {
      return mc->snap_cvmat(timeout, colored);

    } catch (const es::Com_MVS::MvsError& e) {
      esf::Application::notifier().notify_text(
        e.repr(), QtMsgType::QtCriticalMsg, "获取图像失败");
    }

    return cv::Mat();
  };

  worker->_getInput = getInput;
  worker->_input = input;

  es::Com_MVS::MvsCamera::SubUi _mcUi{ worker->_mc, "相机输入" };
  app.reg_sub_ui(_mcUi);

  es::Com_DLP::DLP::SubUi _dlpUi{ worker->_dlp, "投影仪" };
  app.reg_sub_ui(_dlpUi);

  GaoCeConfigSubUi _cSubUi{ *worker };
  {
    _cSubUi._reConWin._getInput_soft = input;
    _cSubUi._MVScal._getInput = _cSubUi._DLPcal._getInput =
      _cSubUi._reConWin._getInput = getInput;
  }
  app.reg_sub_ui(_cSubUi);

  return app.exec();
}
