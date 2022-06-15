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
GaoCeWrapper::recon_pcl_with_gray_liting(std::vector<cv::Mat>& inputImgs,
                                         pcl::PointCloud<pcl::PointXYZ>* cloud)
{
  try {
    return _gaoce->recon_pcl_with_gray_liting(inputImgs, cloud);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
                                    CV_OUT cv::Mat* depthImage)
{
  try {
    return _gaoce->transform_depth_image(cloud, depthImage);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::find_camcorners(cv::Mat& camImg,
                              cv::Size camPatternSize,
                              CV_OUT cv::Mat* camCorners)
{
  try {
    return _gaoce->find_camcorners(camImg, camPatternSize, camCorners);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::camera_calib(::GaoCe::CalibCamProcessParam& calibCamProcessParam)
{
  try {
    return _gaoce->camera_calib(calibCamProcessParam);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::find_procorners(cv::Mat& proImg,
                              cv::Mat& cornersCoarse,
                              cv::Size proPatternSize,
                              CV_OUT cv::Mat* proCorners,
                              CV_OUT cv::Mat* proCamCorners)
{
  try {
    return _gaoce->find_procorners(
      proImg, cornersCoarse, proPatternSize, proCorners, proCamCorners);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::rays_palnes(CV_OUT ::GaoCe::CalibOutputParam* calibOutputParam)
{
  try {
    return _gaoce->rays_palnes(calibOutputParam);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::projector_calib(
  ::GaoCe::CalibProjProcessParam& calibProjProcessParam)
{
  try {
    return _gaoce->projector_calib(calibProjProcessParam);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::data_transform()
{
  return _gaoce->data_transform();
}
