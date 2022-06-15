#pragma once
#include "Eyestack/Base.hpp"
#include "pcl/io/pcd_io.h"
#include <pcl/io/ply_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
typedef cv::Vec<uchar, 9> Vec9b;
typedef cv::Vec<uchar, 10> Vec10b;
typedef cv::Vec<uchar, 11> Vec11b;
typedef cv::Vec<uchar, 12> Vec12b;
typedef cv::Vec<double, 3> Vec3d;
typedef cv::Vec<double, 4> Vec4d;
typedef cv::Vec<float, 3> Vec3f;
typedef cv::Vec<float, 4> Vec4f;

struct PtInfo
{
  int _col;
  int _idPlane;
};

struct SizeInfo
{
  int _imgHeight;
  int _imgWidth;
  int _projPlaneNum;
};

struct FeatureNode
{
  int _midColFloor;
  int _midColCeil;
  double _midColParam;
  int _idPlane;
  int _row;
  int _midSubPixel;
};

struct ReconstructRealTimeInputParam
{
  cv::Mat _camOriPt;
  cv::Mat _dirLineVectors;
  cv::Mat _internalCamParamMat;
  cv::Mat _externalPlaneMat;
  int _offsetGrayCode;
  cv::Mat _dirLinethetas;
  cv::Mat _pairMat;
  std::map<std::string, int> _grayCodeStringMap;
  int _numPlanes;
  int _projMaxValue;
  float _minThresholdContrast;
  int _codeLength;
};

std::map<std::string, int>
grayCodeString(int n, int offset);
std::map<int, std::vector<uchar>>
grayCodeVector(int n, int offset);

void
find_compare_index(int curId,
                   int nextId,
                   std::map<int, std::vector<uchar>>& comparingMap,
                   int* foundIndex);

cv::Mat
generate_pair_plane_Id_mat(int numPlanes,
                           std::map<int, std::vector<uchar>>& comparingMap);

void
decodeGrayCode(cv::Mat& grayCodeMat,
               std::map<std::string, int>& graycodeTMPString,
               cv::Mat& maskValid,
               int codeLength,
               cv::Mat& imgCol);
void
getStSubPixelGray(int row,
                  int col,
                  std::vector<cv::Mat>& imgGrayThresholds,
                  cv::Mat& pairMat,
                  cv::Mat& imgCol,
                  double* subPixel,
                  bool* isAdd);
void
getEdSubPixelGray(int row,
                  int col,
                  std::vector<cv::Mat>& imgGrayThresholds,
                  cv::Mat& pairMat,
                  cv::Mat& imgCol,
                  double* subPixel,
                  bool* isAdd);
void
generate_feature_from_col_list(cv::Mat& imgCol,
                               cv::Mat& pairMat,
                               std::vector<cv::Mat>& imgGrayThresholds,
                               std::vector<FeatureNode>& featureInfo);
void
line_plane_intersection_subpixel(
  std::vector<FeatureNode>& featureInfo,
  ReconstructRealTimeInputParam& reconstructParam,
  pcl::PointCloud<pcl::PointXYZ>* cloud);

void
line_plane_intersection_pixel(cv::Mat& imgCol,
                              ReconstructRealTimeInputParam& reconstructParam,
                              pcl::PointCloud<pcl::PointXYZ>* cloud);
void
convertToDepthImage(pcl::PointCloud<pcl::PointXYZ>& cloud,
                    cv::Mat& projExternalParam,
                    cv::Mat& projInterParam,
                    int imageHeight,
                    int imageWidth,
                    int scaleDepth,
                    cv::Mat* depthImage);
void
recon_3D_info(std::vector<cv::Mat>& imgList,
              ReconstructRealTimeInputParam& reconstructParam,
              pcl::PointCloud<pcl::PointXYZ>* cloud);
