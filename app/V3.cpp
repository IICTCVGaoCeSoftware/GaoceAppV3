//#include "V3.hpp"

// namespace GaoCe {

// void
// V3::recon_pcl_with_gray_liting(std::vector<cv::Mat>& inputImgs,
//                                pcl::PointCloud<pcl::PointXYZ>* cloud)
//{
//   cv::Mat a = cv::imread("D://IICT//DLPPattern//C1.bmp");
//   inputImgs.push_back(a);
// }

// void
// V3::transform_depth_image(pcl::PointCloud<pcl::PointXYZ>& cloud,
//                           CV_OUT cv::Mat* depthImage)
//{
//   cloud.clear();
// }

// void
// V3::find_camcorners(cv::Mat& camImg,
//                     cv::Size camPatternSize,
//                     CV_OUT cv::Mat* camCorners)
//{
//   bool t = camPatternSize.empty();
// }

// void
// V3::camera_calib(CalibCamProcessParam& calibCamProcessParam)
//{
//   double a = calibCamProcessParam._camRealDx;
// }

// void
// V3::find_procorners(cv::Mat& proImg, //输入，相机采集的单张图像
//                     cv::Mat& cornersCoarse, //输入，粗角点信息
//                     cv::Size proPatternSize, //输入，行列方向的棋盘格个数
//                     CV_OUT cv::Mat* proCorners,
//                     //输出，投影图案角点的像素坐标 CV_OUT cv::Mat*
//                     proCamCorners)
//{
//   proImg = cv::imread("D://IICT//DLPPattern//C1.bmp");
// }

// void
// V3::rays_palnes(CalibOutputParam* calibOutputParam)
//{
//   cv::Mat image = calibOutputParam->_camOriPt;
// }

// void
// V3::projector_calib(CalibProjProcessParam& calibProjProcessParam)
//{
//   double x = calibProjProcessParam._proCbDx;
// }

// void
// V3::data_transform()
//{
//   uint8_t a = 0;
//   a++;
// }

// std::unique_ptr<GaoCe>
// create_v3()
//{
//   return std::make_unique<V3>();
// }

//}
