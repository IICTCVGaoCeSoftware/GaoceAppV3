#pragma once
#include "Eyestack/Base.hpp"
#include "pcl/io/pcd_io.h"
#include <opencv2\opencv.hpp>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

namespace calib_3D {
struct CalibResult
{
  cv::Mat _inMatrix;   //输出，标定得到的内参矩阵
  cv::Mat _exMatrix;   //输出，标定得到的外参矩
  cv::Mat _distortion; //输出，标定得到的畸变系数
  cv::Mat _reprojErr;  //输出，重投影误差
};
struct CalibCamProcessParamInput
{                                      // 成员变量：
  std::vector<cv::Mat> _camCornersMat; //输入，该窗口相机采集的角点
  std::vector<cv::Size>
    _camPatternSize; //输入，包括每一张图像的行列方向的棋盘格个数
  double _camRealDx; //输入，棋盘格x方向的真实尺寸
  double _camRealDy; //输入，棋盘格y方向的真实尺寸
  cv::Size _imgSize; //图像分辨率
};

struct CalibCamResultReturn
{                         //成员变量：
  cv::Mat _camInMatrix;   //输出，标定得到的相机内参矩阵
  cv::Mat _camExMatrix;   //输出，标定得到的相机外参矩阵
  cv::Mat _camDistortion; //输出，标定得到的相机畸变系数
  cv::Mat _camReprojErr;  //输出，重投影误差
};

struct CalibProjProcessParamInput
{
  std::vector<cv::Mat> _proImgCorners; //输入，该窗口相机采集的所有有效图像角点
  std::vector<cv::Mat> _proCamCorners; //输入，所有打印棋盘格的角点
  std::vector<cv::Size> _proPatternSize; //输入，行列方向投影的棋盘格个数
  cv::Size _proResolution;               //投影仪的分辨率
  double _proRealDx;                     //输入，投影图案的水平偏移
  double _proRealDy;                     //输入，投影图案的竖直偏移
  double _proCbDx; //输入，棋盘格顶点间的水平距离
  double _proCbDy; //输入，棋盘格顶点间的竖直距离
};

struct CalibProjResultReturn
{
  cv::Mat _proInMatrix;   //输出，标定得到的DLP内参矩阵
  cv::Mat _proExMatrix;   //输出，标定得到的DLP外参矩阵
  cv::Mat _proDistortion; //输出，标定得到的DLP畸变系数
  cv::Mat _proReprojErr;  //输出，重投影误差
};

struct CalibOutputParamReturn
{
  cv::Mat _camOriPt;             // 相机原点
  cv::Mat _dirLineVectors;       //相机直线的方向向量
  cv::Mat _internalCamParamMat;  //相机内参
  cv::Mat _externalPlaneMat;     //投影仪面方程信息
  cv::Mat _externalProjParamMat; //投影仪外参
  cv::Mat _internalProjParamMat; // 投影仪内参
};
void
camera_calib(CalibCamProcessParamInput& calibCamProcessParam,
             CalibCamResultReturn* calibCamResult);

void
compute_fine_corners(cv::Mat cornersCoarse,
                     int pixelsDx,
                     int pixelsDy,
                     cv::Mat& proCamCorners);
void
projector_calib(CalibProjProcessParamInput& calibProjProcessPara,
                CalibCamResultReturn& calibCamResult,
                CV_OUT CalibProjResultReturn* calibProjResult);

void
compute_ex_matrix(double squareSizex,
                  double squareSizey,
                  cv::Mat camInMatrix,
                  cv::Mat camDistortion,
                  cv::Mat& imgCamCornerVector,
                  cv::Mat& proCamExMatrix,
                  std::vector<cv::Point3f>& realCornerVector);
void
generate_chessboard(cv::Size proSize,
                    cv::Size boardSize,
                    int proOffsetDx,
                    int proOffsetDy,
                    cv::Mat& proAllPixel,
                    std::vector<cv::Point2f>& proPixelPoint);
void
fit_plane(cv::Mat points, cv::Mat& plane);
void
pixel2ray(std::vector<cv::Point2f> imgCorners,
          cv::Mat camInMatrix,
          cv::Mat camDistortion,
          cv::Mat& pixelRays);
cv::Mat
normCorners(std::vector<cv::Point2f> imgCorners,
            cv::Mat camInMatrix,
            cv::Mat camDistortion);

void
intersect_line_with_plane3D(cv::Mat pixelRays,
                            cv::Mat camFitPlane,
                            cv::Mat worldOcmInCamCord,
                            cv::Mat& realProCornersCamCord);
void
rays_planes(cv::Size camResolution,
            cv::Size proResolution,
            CalibCamResultReturn& calibCamResult,
            CalibProjResultReturn& calibProjResult,
            CalibOutputParamReturn* calibOutputParam);

}
