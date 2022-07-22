#include "Worker.hpp"

void
Worker::c_start(qint64 cycle)
{
  //  try {
  //    _algo->init_param();
  //  } catch (...) {
  //    esf::Application::notifier().notify_error(std::current_exception(),
  //                                              "运行启动失败");
  //    return;
  //  }

  _S::c_start(cycle);
}

void
Worker::work()
{
  es::Com_DLP::DlpcWrapper::Shared dlp;
  dlp->initDlpc();
  dlp->RunOnce();

  std::vector<cv::Mat> imgList;
  for (int i = 0; i < 500; i++) {
    cv::Mat temp = _input().clone();
    // QString str = "D:/Gaoce/Timage/" + QString::number(i) + ".bmp";
    try {
      if (!temp.empty()) {
        // cv::imwrite(str.toStdString(), temp);
        imgList.push_back(std::move(temp));
        if (imgList.size() == 24) {
          break;
        }
      }
    } catch (...) {
      esf::Application::notifier().notify_error(std::current_exception(),
                                                "高测算法");
    }
  }

  pcl::PointCloud<pcl::PointXYZ> _cloud;
  cv::Mat deepImg;
  _algo->recon_pcl_with_gray_liting(imgList, &_cloud);
  _algo->transform_depth_image(_cloud, &deepImg);

  bool noStop = _noStop.load(std::memory_order_relaxed);
  if (!noStop)
    c_stop();

  emit s_displayGaoCeResults(
    deepImg,
    QSharedPointer<pcl::PointCloud<pcl::PointXYZ>>::create(std::move(_cloud)));
}
