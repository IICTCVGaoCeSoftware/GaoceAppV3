#pragma once

#include <Eyestack/Com_DLP/DLP.hpp>
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
  std::function<cv::Mat()> _input;

  std::unique_ptr<GaoCe::GaoCe> _algo;
  esg::VideoCapture _vc{ *this };
  es::Com_MVS::MvsCamera _mc{ *this };
  es::Com_DLP::DLP _dlp{ *this };

  // 原子变量 _noStop变量设置为false，保证线程安全
  std::atomic_bool _noStop{ false };

signals:
  void s_displayGaoCeResults(
    ::cv::Mat _deepImg,
    QSharedPointer<pcl::PointCloud<pcl::PointXYZ>> _cloud);

  //  void s_Runonce();

protected:
  /**
   * @brief 当外界请求自动运行时调用此槽，该槽在工作线程中被执行。
   * @param cycle 目标运行周期，单位毫秒
   */
  virtual void c_start(qint64 cycle) override;
  /**
   * @brief 当外界请求触发运行一次时调用此槽，该槽在工作线程中被执行。
   *
   * 默认实现为：当工作对象不处于停止状态时，发射触发信号，立即调用一次工作
   * 函数，然后返回之前状态（会发射相关信号）。
   */
  // virtual void c_trigger() override;

  virtual void work() override;
};
