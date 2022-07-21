#pragma once
#include <GaoCe.hpp>

class GaoCeSkeleton : public GaoCe::GaoCe
{
public:
  std::unique_ptr<GaoCe> _gaoce;

  // GaoCe interface
public:
  virtual Eyestack::Design::Paramgr::Table& param_camera_table() override
  {
    return _table;
  };
  virtual Eyestack::Design::Paramgr::Table& param_projector_table() override
  {
    return _table;
  };
  virtual Eyestack::Design::Paramgr::Table& param_3dreconstruction_table()
    override
  {
    return _table;
  };

  virtual void recon_pcl_with_gray_liting(
    std::vector<cv::Mat>& inputImgs,
    pcl::PointCloud<pcl::PointXYZ>* cloud) override{};

  virtual void transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
                                     CV_OUT cv::Mat* depthImage) override{};
  virtual void find_camcorners(
    cv::Mat& camImg,         //输入，相机采集的单张图像
    cv::Size camPatternSize, //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
    ) override{};

  virtual void camera_calib(::GaoCe::CalibCamProcessParam& calibCamProcessParam,
                            cv::Mat* camRepErr) override{};

  virtual void find_procorners(
    cv::Mat& proImg,        //输入，相机采集的单张图像
    cv::Mat& cornersCoarse, //输入，粗角点信息
    cv::Mat& cornersProjCoarse,
    cv::Size proResolution,
    cv::Size calibPatternSize,
    cv::Size proPatternSize, //输入，行列方向的棋盘格个数
    double proOffsetDx,
    double proOffsetDy,
    CV_OUT cv::Mat* proImgCorners, //输出，投影图案角点的像素坐标
    CV_OUT cv::Mat* proCamCorners, //输出，棋盘格角点的像素坐标
    CV_OUT cv::Mat* proProjCorners) override{};

  virtual void rays_palnes() override{};

  virtual void projector_calib(
    ::GaoCe::CalibProjProcessParam& calibProjProcessParam,
    cv::Mat* camRepErr) override{};

  virtual void data_transform() override{};

  virtual void recon_depth_with_gray_liting(
    std::vector<cv::Mat>& inputImgs,
    CV_OUT cv::Mat* depthImage) override{};
  virtual void transform_pointcloud(
    cv::Mat& depthImage,
    pcl::PointCloud<pcl::PointXYZ>& cloud) override{};

  virtual void compute_3dprecision_pointcloud(
    pcl::PointCloud<pcl::PointXYZ>& cloud,
    float* precision) override{};

  virtual ::GaoCe::RealTime3DReconstructionParam dump_config() override
  {
    return _param;
  };
  virtual void load_config(
    ::GaoCe::RealTime3DReconstructionParam loadParam) override{};
  virtual void reset_config() override{};
  // GaoCe interface

private:
  Eyestack::Design::Paramgr::Table _table;
  ::GaoCe::RealTime3DReconstructionParam _param;
};
