#include "wrapper.hpp"

Eyestack::Design::Paramgr::Table&
GaoCeWrapper::param_camera_table()
{
  return _gaoce->param_camera_table();
}

Eyestack::Design::Paramgr::Table&
GaoCeWrapper::param_projector_table()
{
  return _gaoce->param_projector_table();
}

Eyestack::Design::Paramgr::Table&
GaoCeWrapper::param_3dreconstruction_table()
{
  return _gaoce->param_3dreconstruction_table();
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
GaoCeWrapper::camera_calib(::GaoCe::CalibCamProcessParam& calibCamProcessParam,
                           cv::Mat* camRepErr)
{
  try {
    return _gaoce->camera_calib(calibCamProcessParam, camRepErr);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::find_procorners(cv::Mat& proImg,
                              cv::Mat& cornersCoarse,
                              cv::Mat& cornersProjCoarse,
                              cv::Size proResolution,
                              cv::Size calibPatternSize,
                              cv::Size proPatternSize,
                              double proOffsetDx,
                              double proOffsetDy,
                              CV_OUT cv::Mat* proImgCorners,
                              CV_OUT cv::Mat* proCamCorners,
                              CV_OUT cv::Mat* proProjCorners)
{
  try {
    return _gaoce->find_procorners(proImg,
                                   cornersCoarse,
                                   cornersProjCoarse,
                                   proResolution,
                                   calibPatternSize,
                                   proPatternSize,
                                   proOffsetDx,
                                   proOffsetDy,
                                   proImgCorners,
                                   proCamCorners,
                                   proProjCorners);

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::rays_palnes()
{
  try {
    return _gaoce->rays_palnes();

  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::projector_calib(
  ::GaoCe::CalibProjProcessParam& calibProjProcessParam,
  cv::Mat* camRepErr)
{
  try {
    return _gaoce->projector_calib(calibProjProcessParam, camRepErr);

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

void
GaoCeWrapper::transform_pointcloud(cv::Mat& depthImage,
                                   pcl::PointCloud<pcl::PointXYZ>& cloud)
{
  try {
    return _gaoce->transform_pointcloud(depthImage, cloud);
  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::recon_depth_with_gray_liting(std::vector<cv::Mat>& inputImgs,
                                           CV_OUT cv::Mat* depthImage)
{
  try {
    return _gaoce->recon_depth_with_gray_liting(inputImgs, depthImage);
  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::compute_3dprecision_pointcloud(
  pcl::PointCloud<pcl::PointXYZ>& cloud,
  float* precision)
{
  try {
    return _gaoce->compute_3dprecision_pointcloud(cloud, precision);
  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

::GaoCe::RealTime3DReconstructionParam
GaoCeWrapper::dump_config()
{
  return _gaoce->dump_config();
}

void
GaoCeWrapper::load_config(::GaoCe::RealTime3DReconstructionParam loadParam)

{
  try {
    return _gaoce->load_config(loadParam);
  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

void
GaoCeWrapper::reset_config()

{
  try {
    return _gaoce->reset_config();
  } catch (...) {
    esf::Application::notifier().notify_error(std::current_exception(),
                                              "高测算法");
  }
}

