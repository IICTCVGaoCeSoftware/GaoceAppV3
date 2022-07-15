#pragma once

#include "DLP_Calibration.hpp"
#include "GaoCe_InitParams.hpp"
#include "MVS_Calibration.h"
#include "PatternCoding.hpp"
#include "ReConstructWindow.hpp"
#include "Worker.hpp"
#include <Eyestack/Framework.hpp>

namespace esf = Eyestack::Framework;

class GaoCeWrapper : public GaoCe::GaoCe
{
public:
  std::unique_ptr<GaoCe> _gaoce;

  // GaoCe interface
public:
  virtual Eyestack::Design::Paramgr::Table& param_camera_table() override;
  virtual Eyestack::Design::Paramgr::Table& param_projector_table() override;
  virtual Eyestack::Design::Paramgr::Table& param_3dreconstruction_table()
    override;

  virtual void recon_pcl_with_gray_liting(
    std::vector<cv::Mat>& inputImgs,
    pcl::PointCloud<pcl::PointXYZ>* cloud) override;

  virtual void transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
                                     CV_OUT cv::Mat* depthImage) override;
  virtual void find_camcorners(
    cv::Mat& camImg,         //输入，相机采集的单张图像
    cv::Size camPatternSize, //输入，行列方向的棋盘格个数
    CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
    ) override;

  virtual void camera_calib(::GaoCe::CalibCamProcessParam& calibCamProcessParam,
                            cv::Mat* camRepErr) override;

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
    CV_OUT cv::Mat* proProjCorners) override;

  virtual void rays_palnes() override;

  virtual void projector_calib(
    ::GaoCe::CalibProjProcessParam& calibProjProcessParam,
    cv::Mat* camRepErr) override;

  virtual void data_transform() override;

  virtual void recon_depth_with_gray_liting(
    std::vector<cv::Mat>& inputImgs,
    CV_OUT cv::Mat* depthImage) override;
  virtual void transform_pointcloud(
    cv::Mat& depthImage,
    pcl::PointCloud<pcl::PointXYZ>& cloud) override;

  virtual void compute_3dprecision_pointcloud(
    pcl::PointCloud<pcl::PointXYZ>& cloud,
    float* precision) override;

  virtual ::GaoCe::RealTime3DReconstructionParam dump_config() override;
  virtual void load_config(
    ::GaoCe::RealTime3DReconstructionParam loadParam) override;
  virtual void reset_config() override;
};

/**
 * @brief 高测配置UI界面
 */
class GaoCeConfigSubUi : public esf::MainWindow::SubUi::MdiMenu
{
  Q_OBJECT

  using _T = GaoCeConfigSubUi;
  using _S = esf::MainWindow::SubUi::MdiMenu;

public:
  MVS_Calibration _MVScal;
  QMdiSubWindow& _swMVScal;

  DLP_Calibration _DLPcal;
  QMdiSubWindow& _swDLPcal;

  PatternCoding _PatternCoding;
  QMdiSubWindow& _swPatternCoding;

  ReConstructWindow _reConWin;
  QMdiSubWindow& _swReconWin;

  GaoCeConfigUi_MVSInitParams _ip1;
  GaoCeConfigUi_DLPInitParams _ip2;
  GaoCeConfigUi_ReInitParams _ip3;

  QMdiSubWindow& _swIp1;
  QMdiSubWindow& _swIp2;
  QMdiSubWindow& _swIp3;

public:
  GaoCeConfigSubUi(Worker& worker);

private slots:
  void when_show1();
  void when_show2();
  void when_show3();

  // void disable_all();
  // void enable_all();
};
