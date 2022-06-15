#pragma once

//#include <Eyestack/Com_DLP/DLP.hpp>
#include <Eyestack/Com_MVS/MvsCamera.hpp>
#include <Eyestack/Framework.hpp>
#include <Eyestack/Gencom.hpp>
#include <GaoCe.hpp>

namespace es = Eyestack;
namespace esf = Eyestack::Framework;
namespace esg = Eyestack::Gencom;

/**
 * @brief 工作对象类
 */
class Worker : public esf::Worker
{
  Q_OBJECT

  using _S = esf::Worker;

public:
  std::function<cv::Mat()> _getInput;

  std::unique_ptr<GaoCe::GaoCe> _algo;
  esg::VideoCapture _vc{ *this };
  es::Com_MVS::MvsCamera _mc{ *this };
  //  es::Com_DLP::DLP _dlp{ *this };
  std::atomic_bool _noStop{ false };

  // Worker interface
protected:
  virtual void c_start(qint64 cycle) override;
  virtual void work() override;
};
