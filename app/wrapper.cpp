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
  , _ip1(*worker._algo)
  , _swIp1(add_mdi_action("相机配置", _ip1))
  , _ip2(*worker._algo)
  , _swIp2(add_mdi_action("投影仪配置", _ip2))
  , _ip3(*worker._algo)
  , _swIp3(add_mdi_action("重建配置", _ip3))

{
  connect(&_reConWin, &ReConstructWindow::s_show, this, &_T::when_show1);
  connect(&_MVScal, &MVS_Calibration::s_show, this, &_T::when_show2);
  connect(&_DLPcal, &DLP_Calibration::s_show, this, &_T::when_show3);
}

void
GaoCeConfigSubUi::when_show1()
{
  _ip1.show();
  _ip1.setWindowFlags(Qt::WindowStaysOnTopHint);
}

void
GaoCeConfigSubUi::when_show2()
{
  _ip2.show();
  _ip2.setWindowFlags(Qt::WindowStaysOnTopHint);
}

void
GaoCeConfigSubUi::when_show3()
{
  _ip3.show();
  _ip3.setWindowFlags(Qt::WindowStaysOnTopHint);
}

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
