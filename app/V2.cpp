//#include "V2.hpp"
//#include <Eigen/Core>
//#include <Eigen/Dense>
//#include <opencv2/core/eigen.hpp>
//#include <opencv2/opencv.hpp>
//#include <pcl/io/pcd_io.h>

//#include <pcl/common/transforms.h>
// namespace GaoCe {

// V2::V2() {}

// V2::~V2() {}

// void
// V2::recon_pcl_with_gray_liting(std::vector<cv::Mat>& inputImgs,
//                                pcl::PointCloud<pcl::PointXYZ>* cloud)
//{

//  ReconstructRealTimeInputParam reconstructRealTimeInputParam;

//  init_reconstruct_param(reconstructRealTimeInputParam,
//                         _paramInfoCollectStructure);

//  recon_3D_info(inputImgs, reconstructRealTimeInputParam, cloud);

//  int ptNum = cloud->points.size();
//  cv::Mat ptsMat = cv::Mat(3, cloud->points.size(), CV_32FC1);
//  for (int col = 0; col < ptNum; col++) {
//    ptsMat.at<float>(0, col) =
//      cloud->points[col].x -
//      _paramInfoCollectStructure._externalCamParamMat.at<float>(0, 3);
//    ptsMat.at<float>(1, col) =
//      cloud->points[col].y -
//      _paramInfoCollectStructure._externalCamParamMat.at<float>(1, 3);
//    ptsMat.at<float>(2, col) =
//      cloud->points[col].z -
//      _paramInfoCollectStructure._externalCamParamMat.at<float>(2, 3);
//  }

//  cv::Mat invR =
//    _paramInfoCollectStructure._externalCamParamMat({ 0, 3 }, { 0, 3 }).t();

//  ptsMat = invR * ptsMat;

//  for (int col = 0; col < ptNum; col++) {

//    cloud->points[col].x = ptsMat.at<float>(0, col);
//    cloud->points[col].y = ptsMat.at<float>(1, col);
//    cloud->points[col].z = ptsMat.at<float>(2, col);
//  }
//}

// void
// V2::transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
//                           CV_OUT cv::Mat* depthImage)
//{
//   //  test_depthGeneration_param(_transformDepthImageParam);
//   std::cout << _transformDepthImageParam._externalProjParamMat << std::endl;
//   std::cout << _transformDepthImageParam._internalProjParamMat << std::endl;
//   std::cout << _transformDepthImageParam._scaleDepth;
//   //  convertToDepthImage(cloud,
//   //                      _transformDepthImageParam._externalProjParamMat,
//   //                      _transformDepthImageParam._internalProjParamMat,
//   //                      _transformDepthImageParam._depthImageSize.height,
//   //                      _transformDepthImageParam._depthImageSize.width,
//   //                      100,
//   //                      depthImage);

//  std::vector<int> compression_params;
//  compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
//  compression_params.push_back(0);
//  compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
//  compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);
//  cv::imwrite("depthImage.png", *depthImage, compression_params);
//}

// void
// V2::find_camcorners(
//   cv::Mat& camImg,         //输入，相机采集的单张图像
//   cv::Size camPatternSize, //输入，行列方向的棋盘格个数
//   CV_OUT cv::Mat* camCorners //输出，角点的像素坐标（num，2)，（row，col）
//)
//{
//   cv::Size camCornersSize;
//   camCornersSize.width = camPatternSize.width - 1;
//   camCornersSize.height = camPatternSize.height - 1;
//   /* 提取角点 */
//   // vector<cv::Point2f> camCornersTemp;
//   if (0 == cv::findChessboardCornersSB(camImg, camCornersSize, *camCorners))
//   {
//     exit(1);
//   } else {
//     /* 亚像素精确化 */
//     find4QuadCornerSubpix(
//       camImg, *camCorners, cv::Size(10, 10)); //对粗提取的角点进行精确化
//     //    drawChessboardCorners(camImg, camCornersSize, *camCorners, true);
//     //    //用于在图片中标记角点
//   }

//  //标定实现算法
//}

// void
// V2::camera_calib(CalibCamProcessParam& calibCamProcessParam)
//{
//   //标定实现
//   //该步骤对成员变量 _CalibCamResult赋值
//   calib_3D::CalibCamProcessParamInput calibCamProcessParamInput;
//   calibCamProcessParamInput._camCornersMat =
//     calibCamProcessParam._camCornersMat;
//   calibCamProcessParamInput._camPatternSize =
//     calibCamProcessParam._camPatternSize;
//   calibCamProcessParamInput._camRealDx = calibCamProcessParam._camRealDx;
//   calibCamProcessParamInput._camRealDy = calibCamProcessParam._camRealDy;
//   calibCamProcessParamInput._imgSize = calibCamProcessParam._imgSize;
//   calib_3D::CalibCamResultReturn calibCamResultReturn;
//   calib_3D::camera_calib(calibCamProcessParamInput, &calibCamResultReturn);
//   _calibCamResult._camDistortion = calibCamResultReturn._camDistortion;
//   _calibCamResult._camExMatrix = calibCamResultReturn._camExMatrix;
//   _calibCamResult._camInMatrix = calibCamResultReturn._camInMatrix;
//   _calibCamResult._camReprojErr = calibCamResultReturn._camReprojErr;
//   qDebug() << "the adds is" << &_calibCamResult;
//   auto p2 = &_calibCamResult;

//  //对数据结构体赋值

//  cv::Mat camInMatrix32, camExMatrix32, camDistortion32;
//  _calibCamResult._camInMatrix.convertTo(camInMatrix32, CV_32FC1);
//  _calibCamResult._camExMatrix.convertTo(camExMatrix32, CV_32FC1);
//  _calibCamResult._camDistortion.convertTo(camDistortion32, CV_32FC1);
//  _paramInfoCollectStructure._camImgSize = calibCamProcessParam._imgSize;
//  _paramInfoCollectStructure._internalCamParamMat.release();
//  _paramInfoCollectStructure._internalCamParamMat = camInMatrix32.clone();
//  _paramInfoCollectStructure._camDistortion.release();
//  _paramInfoCollectStructure._camDistortion = camDistortion32.clone();
//  double Err1 = _calibCamResult._camReprojErr.at<double>(0, 0);
//}

// void
// V2::find_procorners(
//   cv::Mat& proImg,               //输入，相机采集的单张图像
//   cv::Mat& cornersCoarse,        //输入，粗角点信息
//   cv::Size proPatternSize,       //输入，行列方向的棋盘格个数
//   CV_OUT cv::Mat* proImgCorners, //输出，投影图案角点的像素坐标
//   CV_OUT cv::Mat* proCamCorners  //输出，棋盘格角点的像素坐标
//)
//{
//   cv::Size proCornersSize;
//   proCornersSize.width = proPatternSize.width - 1;
//   proCornersSize.height = proPatternSize.height - 1;
//   cv::Mat probBinImg; // 处理过的能检测到角点的投影图案，不含打印棋盘格
//   cv::threshold(proImg, probBinImg, 50, 255, cv::THRESH_BINARY);
//   // namedWindow("grayImg", WINDOW_NORMAL);
//   // imshow("grayImg", probBinImg);
//   // waitKey(0);
//   // destroyWindow("grayImg");

//  /* 提取投影图案的角点 */
//  if (0 ==
//      cv::findChessboardCornersSB(probBinImg, proCornersSize, *proImgCorners))
//      {
//    // cout << "找不到角点!\n"; //找不到角点
//    exit(1);
//  } else {
//    // cout << "角点优化中..." << endl;
//    /* 亚像素精确化 */
//    cv::find4QuadCornerSubpix(probBinImg,
//                              *proImgCorners,
//                              cv::Size(10,
//                                       10)); //对粗提取的角点进行精确化
//  }
//  /* 提取打印图案的精确角点 */
//  // void compute_fine_corners(cv::Mat & , int , int );
//  int pixelsDx = 10;
//  int pixelsDy = 10;
//}

// void
// V2::projector_calib(CalibProjProcessParam& calibProjProcessParam)
//{
//   //标定实现
//   // 赋值CalibProjResult
//   calib_3D::CalibProjProcessParamInput calibProjProcessParamInput;
//   calibProjProcessParamInput._proCamCorners =
//     calibProjProcessParam._proCamCorners;
//   calibProjProcessParamInput._proCbDx = calibProjProcessParam._proCbDx;
//   calibProjProcessParamInput._proCbDy = calibProjProcessParam._proCbDy;
//   calibProjProcessParamInput._proImgCorners =
//     calibProjProcessParam._proImgCorners;
//   calibProjProcessParamInput._proPatternSize =
//     calibProjProcessParam._proPatternSize;
//   calibProjProcessParamInput._proRealDx = calibProjProcessParam._proRealDx;
//   calibProjProcessParamInput._proRealDy = calibProjProcessParam._proRealDy;
//   calibProjProcessParamInput._proResolution =
//     calibProjProcessParam._proResolution;
//   calib_3D::CalibProjResultReturn calibProjResultReturn;

//  calib_3D::CalibCamResultReturn calibCamResultReturn;
//  calibCamResultReturn._camDistortion = _calibCamResult._camDistortion;
//  calibCamResultReturn._camExMatrix = _calibCamResult._camExMatrix;
//  calibCamResultReturn._camInMatrix = _calibCamResult._camInMatrix;
//  calibCamResultReturn._camReprojErr = _calibCamResult._camReprojErr;
//  // 赋值

//  calib_3D::projector_calib(
//    calibProjProcessParamInput, calibCamResultReturn, &calibProjResultReturn);
//  // 赋值
//  _calibProjResult._proDistortion = calibProjResultReturn._proDistortion;
//  _calibProjResult._proExMatrix = calibProjResultReturn._proExMatrix;
//  _calibProjResult._proInMatrix = calibProjResultReturn._proInMatrix;
//  _calibProjResult._proReprojErr = calibProjResultReturn._proReprojErr;

//  _calibCamResult._camDistortion.release();
//  _calibCamResult._camExMatrix.release();
//  _calibCamResult._camInMatrix.release();
//  _calibCamResult._camReprojErr.release();
//  _calibCamResult._camDistortion =
//  calibCamResultReturn._camDistortion.clone(); _calibCamResult._camExMatrix =
//  calibCamResultReturn._camExMatrix.clone(); _calibCamResult._camInMatrix =
//  calibCamResultReturn._camInMatrix.clone(); _calibCamResult._camReprojErr =
//  calibCamResultReturn._camReprojErr.clone();
//  // 数据结构体赋值
//  // 后加
//  cv::Mat proInMatrix32, proExMatrix32, proDistortion32, camExMatrix32;
//  _calibProjResult._proInMatrix.convertTo(proInMatrix32, CV_32FC1);
//  _calibProjResult._proExMatrix.convertTo(proExMatrix32, CV_32FC1);
//  _calibProjResult._proDistortion.convertTo(proDistortion32, CV_32FC1);
//  _calibCamResult._camExMatrix.convertTo(camExMatrix32, CV_32FC1);

//  _paramInfoCollectStructure._externalCamParamMat.release();
//  _paramInfoCollectStructure._externalCamParamMat = camExMatrix32.clone();
//  _paramInfoCollectStructure._proResolution =
//    calibProjProcessParam._proResolution;
//  _paramInfoCollectStructure._externalProjParamMat.release();
//  _paramInfoCollectStructure._externalProjParamMat = proExMatrix32;
//  _paramInfoCollectStructure._internalProjParamMat.release();
//  _paramInfoCollectStructure._internalProjParamMat = proInMatrix32;
//  _paramInfoCollectStructure._proDistortion.release();
//  _paramInfoCollectStructure._proDistortion = _calibProjResult._proDistortion;
//}

// void
// V2::rays_palnes(CalibOutputParam* calibOutputParam)
//{
//   // 标定，实现对calibOutputParam赋值

//  calib_3D::CalibCamResultReturn calibCamResultReturn;
//  calibCamResultReturn._camDistortion = _calibCamResult._camDistortion;
//  calibCamResultReturn._camExMatrix = _calibCamResult._camExMatrix;
//  calibCamResultReturn._camInMatrix = _calibCamResult._camInMatrix;
//  calibCamResultReturn._camReprojErr = _calibCamResult._camReprojErr;

//  calib_3D::CalibProjResultReturn calibProjResultReturn;
//  calibProjResultReturn._proDistortion = _calibProjResult._proDistortion;
//  calibProjResultReturn._proExMatrix = _calibProjResult._proExMatrix;
//  calibProjResultReturn._proInMatrix = _calibProjResult._proInMatrix;
//  calibProjResultReturn._proReprojErr = _calibProjResult._proReprojErr;

//  calib_3D::CalibOutputParamReturn calibOutputParamReturn;
//  // 线面相交
//  calib_3D::rays_planes(_paramInfoCollectStructure._camImgSize,
//                        _paramInfoCollectStructure._proResolution,
//                        calibCamResultReturn,
//                        calibProjResultReturn,
//                        &calibOutputParamReturn);

//  // 1、相机原点赋值
//  cv::Mat cameraOript = cv::Mat::zeros(1, 3, CV_64FC1);
//  cameraOript.at<double>(0, 0) =
//    calibOutputParamReturn._camOriPt.at<double>(0, 0);
//  cameraOript.at<double>(0, 1) =
//    calibOutputParamReturn._camOriPt.at<double>(1, 0);
//  cameraOript.at<double>(0, 2) =
//    calibOutputParamReturn._camOriPt.at<double>(2, 0);
//  cv::swap(calibOutputParam->_camOriPt, cameraOript);

//  // 2、直线方向向量赋值
//  cv::Mat dirLineVectors =
//    cv::Mat::ones(_paramInfoCollectStructure._camImgSize.height,
//                  _paramInfoCollectStructure._camImgSize.width,
//                  CV_64FC(3));
//  for (int row = 0; row < _paramInfoCollectStructure._camImgSize.height;
//       row++) {
//    for (int col = 0; col < _paramInfoCollectStructure._camImgSize.width;
//         col++) {
//      int indexId = row + col * _paramInfoCollectStructure._camImgSize.height;
//      for (int channel = 0; channel < 3; channel++) {
//        dirLineVectors.at<Vec3d>(row, col)[channel] =
//          calibOutputParamReturn._dirLineVectors.at<double>(channel, indexId);
//      }
//    }
//  }
//  cv::swap(calibOutputParam->_dirLineVectors, dirLineVectors);

//  // 3、平面向量赋值
//  cv::Mat externalPlaneMat = cv::Mat::ones(
//    1, _paramInfoCollectStructure._proResolution.width, CV_64FC(4));
//  {
//    for (int i = 0; i < _paramInfoCollectStructure._proResolution.width; i++)
//    {
//      externalPlaneMat.at<Vec4d>(0, i)[0] =
//        calibOutputParamReturn._externalPlaneMat.at<double>(i, 0);
//      externalPlaneMat.at<Vec4d>(0, i)[1] =
//        calibOutputParamReturn._externalPlaneMat.at<double>(i, 1);
//      externalPlaneMat.at<Vec4d>(0, i)[2] =
//        calibOutputParamReturn._externalPlaneMat.at<double>(i, 2);
//      externalPlaneMat.at<Vec4d>(0, i)[3] =
//        calibOutputParamReturn._externalPlaneMat.at<double>(i, 3);
//    }
//  }
//  cv::swap(calibOutputParam->_externalPlaneMat, externalPlaneMat);

//  // 4、平面向量赋值
//  calibOutputParam->_externalProjParamMat =
//    calibOutputParamReturn._externalProjParamMat;
//  calibOutputParam->_internalCamParamMat =
//    calibOutputParamReturn._internalCamParamMat;
//  calibOutputParam->_internalProjParamMat =
//    calibOutputParamReturn._internalProjParamMat;

//  // 5、标定信息收集结构的赋值
//  _calibOutputParam._camOriPt = calibOutputParam->_camOriPt;
//  _calibOutputParam._dirLineVectors = calibOutputParam->_dirLineVectors;
//  _calibOutputParam._externalPlaneMat = calibOutputParam->_externalPlaneMat;
//  _calibOutputParam._externalProjParamMat =
//    calibOutputParam->_externalProjParamMat;
//  _calibOutputParam._internalCamParamMat =
//    calibOutputParam->_internalCamParamMat;
//  _calibOutputParam._internalProjParamMat =
//    calibOutputParam->_internalProjParamMat;

//  cv::Mat camOriPt32, dirLineVectors32, externalPlaneMat32,
//    externalProjParamMat32, internalCamParamMat32, internalProjParamMat32;
//  calibOutputParam->_camOriPt.convertTo(camOriPt32, CV_32FC1);
//  calibOutputParam->_dirLineVectors.convertTo(dirLineVectors32, CV_32FC3);
//  calibOutputParam->_externalPlaneMat.convertTo(externalPlaneMat32, CV_32FC4);
//  calibOutputParam->_externalProjParamMat.convertTo(externalProjParamMat32,
//                                                    CV_32FC1);
//  calibOutputParam->_internalCamParamMat.convertTo(internalCamParamMat32,
//                                                   CV_32FC1);
//  calibOutputParam->_internalProjParamMat.convertTo(internalProjParamMat32,
//                                                    CV_32FC1);

//  _paramInfoCollectStructure._camOriPt = camOriPt32.clone();
//  _paramInfoCollectStructure._dirLineVectors = dirLineVectors32.clone();
//  _paramInfoCollectStructure._externalPlaneMat = externalPlaneMat32.clone();

//  _transformDepthImageParam._externalProjParamMat =
//    _paramInfoCollectStructure._externalProjParamMat;
//  _transformDepthImageParam._internalProjParamMat =
//    _paramInfoCollectStructure._internalProjParamMat;
//  _transformDepthImageParam._depthImageSize =
//    _paramInfoCollectStructure._proResolution;
//  _transformDepthImageParam._scaleDepth =
//    _paramInfoCollectStructure._scaleDepth;
//}

// void
// V2::data_transform()
//{
//   //! todo 缺相机外参，单独引入
//   transformDataStructure(
//     _paramInfoCollectStructure, _reconstructParam,
//     _transformDepthImageParam);
// }

// std::unique_ptr<GaoCe>
// create_v2()
//{
<<<<<<< HEAD
//   return std::unique_ptr<V2>(new V2());
=======
//   return std::make_unique<V2>();
//   // return std::unique_ptr<V2>(new V2());
>>>>>>> 1740259 (算法测试跑通)
// }
// }

// void
// transformDataStructure(
//   GaoCe::V2::ParamInfoCollectStructure& paramInfoCollectStructure,
//   GaoCe::ReconstructParam& reconstructParam,
//   GaoCe::TransformDepthImageParam& transformDepthImageParam)
//{
//   reconstructParam._camOriPt = paramInfoCollectStructure._camOriPt;
//   reconstructParam._dirLineVectors =
//   paramInfoCollectStructure._dirLineVectors;
//   reconstructParam._internalCamParamMat =
//     paramInfoCollectStructure._internalCamParamMat;
//   reconstructParam._externalPlaneMat =
//     paramInfoCollectStructure._externalPlaneMat;

//  transformDepthImageParam._externalProjParamMat =
//    paramInfoCollectStructure._externalProjParamMat;
//  transformDepthImageParam._internalProjParamMat =
//    paramInfoCollectStructure._internalProjParamMat;
//  transformDepthImageParam._depthImageSize =
//    paramInfoCollectStructure._proResolution;
//  // 默认尺度参数100
//  paramInfoCollectStructure._scaleDepth = 100;
//  transformDepthImageParam._scaleDepth =
//  paramInfoCollectStructure._scaleDepth;
//}

// void
// init_reconstruct_param(
//   ReconstructRealTimeInputParam& reconstructParam,
//   GaoCe::V2::ParamInfoCollectStructure& paramInfoCollectStructure)
//{
//   int H = paramInfoCollectStructure._camImgSize.height;
//   int W = paramInfoCollectStructure._camImgSize.width;
//   int numPlanes = paramInfoCollectStructure._proResolution.width;
//   reconstructParam._numPlanes = numPlanes;
//   reconstructParam._projMaxValue = 255;
//   reconstructParam._camOriPt.release();
//   reconstructParam._camOriPt = paramInfoCollectStructure._camOriPt;
//   reconstructParam._dirLineVectors =
//   paramInfoCollectStructure._dirLineVectors;
//   //低对比度阈值
//   reconstructParam._minThresholdContrast = 0.3;

//  //角度赋值
//  reconstructParam._dirLinethetas.release();
//  reconstructParam._dirLinethetas = cv::Mat::zeros(H, W, CV_32FC(3));
//  {
//    for (int row = 0; row < H; row++) {
//      for (int col = 0; col < W; col++) {
//        for (int i = 0; i < 3; i++) {
//          reconstructParam._dirLinethetas.at<Vec3f>(row, col)[i] =
//            acos(reconstructParam._dirLineVectors.at<Vec3f>(row, col)[i]);
//        }
//      }
//    }
//  }
//  reconstructParam._internalCamParamMat.release();
//  reconstructParam._internalCamParamMat =
//    paramInfoCollectStructure._internalCamParamMat;
//  reconstructParam._externalPlaneMat.release();
//  reconstructParam._externalPlaneMat =
//    paramInfoCollectStructure._externalPlaneMat;

//  int codeLength = ceil(log2(numPlanes));
//  reconstructParam._codeLength = codeLength;
//  int offset = floor((pow(2, codeLength) - numPlanes) / 2);
//  reconstructParam._grayCodeStringMap = grayCodeString(codeLength, offset);
//  std::map<int, std::vector<uchar>> comparingMap =
//    grayCodeVector(codeLength, offset);
//  reconstructParam._offsetGrayCode = offset;
//  reconstructParam._pairMat =
//    generate_pair_plane_Id_mat(numPlanes, comparingMap);
//}

// cv::Mat
// importOpenCVMat(std::string path, std::string nameMat)
//{
//   cv::FileStorage fsDemo(path, cv::FileStorage::READ);
//   cv::Mat originPtMat;
//   fsDemo[nameMat] >> originPtMat;
//   return originPtMat;
// }

// void
// test_reconstruct_param(
//   ReconstructRealTimeInputParam& reconstructParam,
//   GaoCe::V2::ParamInfoCollectStructure& paramInfoCollectStructure)
//{

//  int H = 2048;
//  int W = 2592;
//  int numPlanes = 1280;
//  reconstructParam._numPlanes = numPlanes;
//  reconstructParam._projMaxValue = 255;

//  cv::Mat Oc = importOpenCVMat("E:/projects/EXP/log/Oc.yml", "Oc");
//  cv::Mat Nc = importOpenCVMat("E:/projects/EXP/log/Nc.yml", "Nc");
//  cv::Mat wPlaneCol =
//    importOpenCVMat("E:/projects/EXP/log/wPlaneCol.yml", "wPlaneCol");

//  cv::Mat cameraExternalParam = importOpenCVMat(
//    "E:/projects/EXP/log/cameraExternalParam.yml", "cameraExternalParam");

//  cv::Mat cameraInterParam = importOpenCVMat(
//    "E:/projects/EXP/log/cameraInterParam.yml", "cameraInterParam");

//  cv::Mat projExternalParam = importOpenCVMat(
//    "E:/projects/EXP/log/projExternalParam.yml", "projExternalParam");

//  cv::Mat projInterParam =
//    importOpenCVMat("E:/projects/EXP/log/projInterParam.yml",
//    "projInterParam");

//  cv::Mat cameraOript = cv::Mat::zeros(1, 3, CV_64FC1);
//  cameraOript.at<double>(0, 0) = Oc.at<float>(0, 0);
//  cameraOript.at<double>(0, 1) = Oc.at<float>(1, 0);
//  cameraOript.at<double>(0, 2) = Oc.at<float>(2, 0);
//  cv::swap(cameraOript, reconstructParam._camOriPt);

//  cv::Mat dirLineVectors = cv::Mat::ones(H, W, CV_64FC(3));
//  for (int row = 0; row < H; row++) {
//    for (int col = 0; col < W; col++) {
//      int indexId = row + col * H;
//      for (int channel = 0; channel < 3; channel++) {
//        dirLineVectors.at<Vec3d>(row, col)[channel] =
//          Nc.at<float>(channel, indexId);
//      }
//    }
//  }

//  cv::swap(dirLineVectors, reconstructParam._dirLineVectors);

//  reconstructParam._minThresholdContrast = 0.3;
//  reconstructParam._dirLinethetas = cv::Mat::zeros(H, W, CV_64FC(3));
//  {
//    for (int row = 0; row < H; row++) {
//      for (int col = 0; col < W; col++) {
//        for (int i = 0; i < 3; i++) {
//          reconstructParam._dirLinethetas.at<Vec3d>(row, col)[i] =
//            acos(reconstructParam._dirLineVectors.at<Vec3d>(row, col)[i]);
//        }
//      }
//    }
//  }

//  cv::swap(reconstructParam._internalCamParamMat, cameraInterParam);

//  cv::Mat externalPlaneMat = cv::Mat::ones(1, numPlanes, CV_64FC(4));
//  {
//    for (int i = 0; i < numPlanes; i++) {
//      externalPlaneMat.at<Vec4d>(0, i)[0] = wPlaneCol.at<float>(i, 0);
//      externalPlaneMat.at<Vec4d>(0, i)[1] = wPlaneCol.at<float>(i, 1);
//      externalPlaneMat.at<Vec4d>(0, i)[2] = wPlaneCol.at<float>(i, 2);
//      externalPlaneMat.at<Vec4d>(0, i)[3] = wPlaneCol.at<float>(i, 3);
//    }
//  }

//  cv::swap(reconstructParam._externalPlaneMat, externalPlaneMat);

//  cameraExternalParam.convertTo(cameraExternalParam, CV_64FC1);

//  cv::swap(paramInfoCollectStructure._externalCamParamMat,
//  cameraExternalParam);

//  int codeLength = ceil(log2(numPlanes));
//  reconstructParam._codeLength = codeLength;
//  int offset = floor((pow(2, codeLength) - numPlanes) / 2);
//  reconstructParam._grayCodeStringMap = grayCodeString(codeLength, offset);
//  std::map<int, std::vector<uchar>> comparingMap =
//    grayCodeVector(codeLength, offset);
//  reconstructParam._pairMat =
//    generate_pair_plane_Id_mat(numPlanes, comparingMap);
//}

// void
// test_depthGeneration_param(
//   GaoCe::TransformDepthImageParam& transformDepthImageParam)
//{

//  transformDepthImageParam._depthImageSize.height = 720;
//  transformDepthImageParam._depthImageSize.width = 1280;

//  transformDepthImageParam._scaleDepth = 100;

//  cv::Mat projExternalParam = importOpenCVMat(
//    "E:/projects/EXP/log/projExternalParam.yml", "projExternalParam");

//  cv::Mat projInterParam =
//    importOpenCVMat("E:/projects/EXP/log/projInterParam.yml",
//    "projInterParam");

//  cv::swap(transformDepthImageParam._internalProjParamMat, projInterParam);

//  cv::swap(transformDepthImageParam._externalProjParamMat, projExternalParam);
//}
