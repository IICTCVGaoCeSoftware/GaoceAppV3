//#include "calib_3D.hpp"

//// 相机标定函数
// namespace calib_3D {

// void
// calib(std::vector<std::vector<cv::Point3f>> pointWorldCord,
//       std::vector<std::vector<cv::Point2f>> pointPixel,
//       std::vector<int> pointCounts,
//       cv::Size imageSize,
//       int imgsCount,
//       CalibResult* calibResult)
//{
//   //定义内外参，畸变系数矩阵
//   cv::Mat inMatrix =
//     cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0)); //投影仪内参数矩阵
//   cv::Mat distCoeffs = cv::Mat(
//     1, 5, CV_32FC1, cv::Scalar::all(0)); //
//     投影仪的5个畸变系数：k1,k2,p1,p2,k3
//   std::vector<cv::Mat> exMatrix;
//   std::vector<cv::Mat> tvecsMat; // 每幅图像的平移向量
//   std::vector<cv::Mat> rvecsMat; //  每幅图像的旋转向量

//  // 开始标定
//  cv::calibrateCamera(pointWorldCord,
//                      pointPixel,
//                      imageSize,
//                      inMatrix,
//                      distCoeffs,
//                      rvecsMat,
//                      tvecsMat,
//                      0);
//  double err = 0.0;
//  double totalErr = 0.0;
//  for (int i = 0; i < imgsCount; i++) {
//    //计算相机的外参矩阵
//    cv::Mat tempRotationMat =
//      cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0)); /* 摄像机外参旋转矩阵 */
//    cv::Rodrigues(rvecsMat[i], tempRotationMat); //得到旋转矩阵
//    cv::Mat tempCamExMatrix =
//      cv::Mat(3, 4, CV_32FC1, cv::Scalar::all(0)); /* 摄像机外参数矩阵 */
//    cv::hconcat(tempRotationMat, tvecsMat[i], tempCamExMatrix);
//    exMatrix.push_back(tempCamExMatrix);

//    //计算相机的重投影误差
//    std::vector<cv::Point2f> tempProjectedPoints;
//    /*
//    通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点
//     */
//    cv::projectPoints(pointWorldCord[i],
//                      rvecsMat[i],
//                      tvecsMat[i],
//                      inMatrix,
//                      distCoeffs,
//                      tempProjectedPoints);
//    std::vector<cv::Point2f> imageCorner = pointPixel[i]; // 第i张角点坐标
//    cv::Mat tempImagePointMat = cv::Mat(1, imageCorner.size(), CV_32FC2);
//    cv::Mat tempProjectedPointForI =
//      cv::Mat(1, tempProjectedPoints.size(), CV_32FC2);
//    for (int j = 0; j < imageCorner.size(); j++) {
//      tempProjectedPointForI.at<cv::Vec2f>(0, j) =
//        cv::Vec2f(tempProjectedPoints[j].x, tempProjectedPoints[j].y);
//      tempImagePointMat.at<cv::Vec2f>(0, j) =
//        cv::Vec2f(imageCorner[j].x, imageCorner[j].y);
//    }
//    err = cv::norm(tempProjectedPointForI, tempImagePointMat, cv::NORM_L2);
//    totalErr += err /= pointCounts[i];
//    std::cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" <<
//    endl;
//    // fout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
//    // projectedPoints.push_back(tempProjectedPoints);
//  }
//  /*保存内参和畸变系数，以便后面直接矫正*/
//  cv::Mat inMatrix64, exMatrix64, distCoeffs64;
//  inMatrix.convertTo(inMatrix64, CV_64FC1);
//  exMatrix[0].convertTo(exMatrix64, CV_64FC1);
//  distCoeffs.convertTo(distCoeffs64, CV_64FC1);
//  calibResult->_inMatrix = inMatrix64;
//  calibResult->_exMatrix = exMatrix64;
//  calibResult->_distortion = distCoeffs64;
//  cv::Mat errMat = cv::Mat(1, 1, CV_64FC1);
//  errMat = (totalErr / imgsCount);
//  calibResult->_reprojErr = errMat;
//  // std::cout << "总体平均误差：" << calibResult->_reprojErr << "像素" <<
//  endl;
//  // fout << "总体平均误差：" << total_err / image_count << "像素" << endl <<
//  // endl; cout << "相机内参数矩阵：" << endl; cout << calibResult->_inMatrix
//  <<
//  // endl << endl; cout << "畸变系数：" << endl; cout <<
//  // calibResult->_distortion << endl << endl << endl; cout <<
//  // "相机外参数矩阵！" << endl; cout << calibResult->_exMatrix << endl <<
//  endl
//  // << endl; cout << "标定完成！" << endl;
//}

// void
// camera_calib(CalibCamProcessParamInput& calibCamProcessParam,
//              CalibCamResultReturn* calibCamResult)

//{
//  /* 初始化相机，图片，角点参数 */
//  std::vector<cv::Mat> imageCornerMat =
//    calibCamProcessParam._camCornersMat; //所有图片的所有角点
//  std::vector<cv::Size> boardSize =
//    calibCamProcessParam._camPatternSize; //棋盘格行列方向的个数
//  double squareSizex =
//    calibCamProcessParam._camRealDx; // 实际测量得到的标定板上每个棋盘格的大小
//  double squareSizey = calibCamProcessParam._camRealDy;
//  cv::Size imageSize = calibCamProcessParam._imgSize; //相机采集的图像大小
//  int imgsCount = imageCornerMat.size();              //图像的张数
//  // vector<Mat> imageCalibrateVector;
//  // vector<vector<Point2f>> image_points_seq;

//  /* 先判断每张图片是否存在角点 */
//  std::vector<std::vector<cv::Point2f>> imageCornerPoint2f;
//  for (int i = 0; i < imgsCount; i++) {
//    std::vector<cv::Point2f> imageCorner =
//      cv::Mat_<cv::Point2f>(imageCornerMat[i]); // 第i张角点坐标
//    if (!imageCorner.size())                    // 未提取到角点报错
//    {
//      cout << "未提取角点，无法标定！" << endl;
//      break;
//    }
//    imageCornerPoint2f.push_back(imageCorner);
//  }

//  /* 以下开始相机标定 */
//  cout << "开始相机标定..." << endl;

//  /* 初始化标定板上角点的三维坐标 */
//  std::vector<std::vector<cv::Point3f>>
//    objectPoints; // 用于保存标定板上角点的三维坐标
//  int i, j, t;
//  for (t = 0; t < imgsCount; t++) {
//    std::vector<cv::Point3f>
//      tempPointSet; // 用于保存标定板每个不同时刻选择的角点对应的三维坐标
//    // for (i = 0; i < boardSize[t].height - 1; i++)
//    //{
//    //	for (j = 0; j < boardSize[t].width - 1; j++)
//    //	{
//    //		cv::Point3f realPoint;  // 其中一个角点的三维坐标
//    //		// 假设标定板放在世界坐标系中z=0的平面上
//    //		realPoint.x = i * squareSizex;
//    //		realPoint.y = j * squareSizey;
//    //		realPoint.z = 0;
//    //		tempPointSet.push_back(realPoint);
//    //	}
//    // }
//    for (i = boardSize[t].height - 2; i >= 0; i--) {
//      for (j = boardSize[t].width - 2; j >= 0; j--) {
//        cv::Point3f realPoint; // 其中一个角点的三维坐标
//        // 假设标定板放在世界坐标系中z=0的平面上
//        realPoint.x = i * squareSizey;
//        realPoint.y = j * squareSizex;
//        realPoint.z = 0;
//        tempPointSet.push_back(realPoint);
//      }
//    }
//    objectPoints.push_back(tempPointSet);
//  }
//  /* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
//  std::vector<int> pointCounts; // 每幅图像中角点的数量
//  for (i = 0; i < imgsCount; i++) {
//    pointCounts.push_back((boardSize[i].width - 1) * (boardSize[i].height -
//    1));
//  }
//  struct CalibResult* calibResult = new CalibResult;
//  calib(objectPoints,
//        imageCornerPoint2f,
//        pointCounts,
//        imageSize,
//        imgsCount,
//        calibResult);
//  calibCamResult->_camInMatrix = calibResult->_inMatrix;
//  calibCamResult->_camExMatrix = calibResult->_exMatrix;
//  calibCamResult->_camDistortion = calibResult->_distortion;
//  calibCamResult->_camReprojErr = calibResult->_reprojErr;
//  cout << "总体平均误差：" << calibCamResult->_camReprojErr << "像素" << endl;
//  // fout << "总体平均误差：" << total_err / image_count << "像素" << endl <<
//  // endl; cout << "相机内参数矩阵：" << endl; cout <<
//  calibCamResult->_inMatrix
//  // << endl << endl; cout << "畸变系数：" << endl; cout <<
//  // calibCamResult->_distortion << endl << endl << endl; cout <<
//  // "相机外参数矩阵！" << endl; cout <<  calibCamResult->_exMatrix << endl <<
//  // endl << endl; cout << "标定完成！" << endl;
//}

////精细化打印图案的角点
// void
// compute_fine_corners(cv::Mat cornersCoarse,
//                      int pixelsDx,
//                      int pixelsDy,
//                      cv::Mat& proCamCorners)
//{
//   proCamCorners = cornersCoarse;
// }
////投影仪标定函数
// void
// projector_calib(CalibProjProcessParamInput& calibProjProcessPara,
//                 CalibCamResultReturn& calibCamResult,
//                 CV_OUT CalibProjResultReturn* calibProjResult)
//{
//   /******* 初始化参数 *******/
//   /* 初始化投影图案及打印棋盘格的角点，打印棋盘格的真实距离 */
//   std::vector<cv::Mat> proImgCorners =
//     calibProjProcessPara._proImgCorners;
//     //所有投影的图片在相机像素坐标下的角点
//   std::vector<cv::Mat> proCamCorners =
//     calibProjProcessPara
//       ._proCamCorners; //输入，所有打印棋盘格在相机像素坐标下的角点
//   double squareSizex = calibProjProcessPara._proCbDx; // 打印棋盘格的实际大小
//   double squareSizey = calibProjProcessPara._proCbDy;
//   /*投影仪，投影相关图案*/
//   cv::Size proSize = calibProjProcessPara._proResolution; //投影仪分辨率
//   std::vector<cv::Size> boardSize =
//     calibProjProcessPara._proPatternSize; //棋盘格行列方向的个数
//   int proOffsetDx = calibProjProcessPara._proRealDx; //投影图案的水平偏移
//   int proOffsetDy = calibProjProcessPara._proRealDy; //投影图案的竖直偏移
//   /*相机相关图案*/
//   // cv::Size imageSize = calibCamResult._imgSize;    //相机采集的图像大小
//   cv::Mat camInMatrix = calibCamResult._camInMatrix;     //相机的内参
//   cv::Mat camDistortion = calibCamResult._camDistortion; //相机的畸变系数
//   /*图像张数*/
//   int imgsCount = proImgCorners.size(); //图像的张数

//  /* 先判断每张图片是否存在角点 */
//  for (int i = 0; i < imgsCount; i++) {
//    std::vector<cv::Point2f> imageCorner = proImgCorners[i]; // 第i张角点坐标
//    if (!imageCorner.size()) // 未提取到角点报错
//    {
//      // cout << "未提取角点，无法标定！" << endl;
//      break;
//    }
//  }

//  /* 以下开始投影仪标定 */
//  cout << "开始投影仪标定..." << endl;

//  //求得相机外参
//  std::vector<cv::Mat> proCamExMatrix;       //相机每个标定面下的外参
//  std::vector<cv::Point3f> realCornerVector; //打印图案对应的真实坐标
//  for (int i = 0; i < imgsCount; i++) {
//    cv::Mat tempExMatrix;
//    compute_ex_matrix(squareSizex,
//                      squareSizey,
//                      camInMatrix,
//                      camDistortion,
//                      proCamCorners[i],
//                      tempExMatrix,
//                      realCornerVector);
//    proCamExMatrix.push_back(tempExMatrix);
//  }
//  // compute_ex_matrix_new(squareSizex, squareSizey, camInMatrix,
//  camDistortion,
//  // proCamCorners[i], tempExMatrix, realCornerVector); 生成投影仪的投影图案
//  cv::Mat proAllPixel;                                 //投影图案
//  std::vector<std::vector<cv::Point2f>> proPixelPoint; //所有图片的投影图案
//  for (int i = 0; i < imgsCount; i++) {
//    std::vector<cv::Point2f>
//      proPixelPointOne; //从投影图案中可识别到的角点坐标（二维）
//    generate_chessboard(proSize,
//                        boardSize[i],
//                        proOffsetDx,
//                        proOffsetDy,
//                        proAllPixel,
//                        proPixelPointOne);
//    proPixelPoint.push_back(proPixelPointOne);
//  }

//  //求取投影图案对应的角点三维坐标
//  // 求取过程：
//  //
//  已知打印图案对应的真实坐标realCornerVector，将其变换到相机坐标系下，并根据最小二乘法重新拟合平面
//  //
//  求得相机拍摄到的投影图案中选取出来的角点（proImgCorners）对应射线，通过线面相交确定其在相机坐标系下的坐标，并转换到真实世界，得到真实坐标

//  std::vector<cv::Mat>
//    realProCornersWorldCord; //投影图案角点在世界坐标系下的三维坐标
//  for (int i = 0; i < imgsCount; i++) {
//    //将打印图案对应的真实坐标realCornerVector，将其变换到相机坐标系下
//    // vector < Point3f> tempRealCornerVector;
//    // tempRealCornerVector = Mat_<Point3f>(proCamExMatrix[i].colRange(0, 3) *
//    // Mat(realCornerVector) + proCamExMatrix[i].colRange(3, 4));
//    cv::Mat tempRealCornerVector;
//    cv::Mat realCornerMat = cv::Mat(4, 4, CV_64FC1, cv::Scalar::all(0));
//    for (int i = 0; i < 4; i++) {
//      realCornerMat.at<double>(i, 0) = realCornerVector[i].x;
//      realCornerMat.at<double>(i, 1) = realCornerVector[i].y;
//      realCornerMat.at<double>(i, 2) = realCornerVector[i].z;
//      realCornerMat.at<double>(i, 3) = 1;
//    }
//    cv::Mat proCamExMatrixi;
//    proCamExMatrix[i].convertTo(proCamExMatrixi, CV_64FC1);
//    tempRealCornerVector =
//      proCamExMatrixi * (realCornerMat.t()); //均为CV_64F类型
//    // realCornerMat = Mat(realCornerVector);
//    // cv::gemm(proCamExMatrix[i].colRange(0, 3), realCornerMat.t(), 1,
//    // proCamExMatrix[i].colRange(3, 4), 1, tempRealCornerVector);
//    //根据最小二乘法重新拟合平面
//    cv::Mat camFitPlane;
//    fit_plane(tempRealCornerVector.t(), camFitPlane);
//    //求得相机拍摄到的投影图案中选取出来的角点（proImgCorners）对应射线
//    cv::Mat pixelRays; //射线方程
//    pixel2ray(proImgCorners[i], camInMatrix, camDistortion, pixelRays);
//    //线面相交求得投影图案角点在相机坐标系下的三维坐标
//    cv::Mat realProCornersCamCord = cv::Mat(
//      3, pixelRays.cols, CV_64FC1); //投影图案角点在相机坐标系下的三维坐标
//    // cv::Mat realProDepth;
//    cv::Mat tempProCornersWorldCord = cv::Mat(
//      3, pixelRays.cols, CV_64FC1); //暂存投影图案角点在世界坐标系下的坐标
//    // cv::Mat worldOcm = (cv::Mat_<double>(4, 1) << 0, 0, 0,1);
//    cv::Mat worldOcmInCamCord = cv::Mat(3, 1, CV_64FC1, cv::Scalar::all(0));
//    // cv::Mat worldOcmInCamCord = proCamExMatrix[i] * worldOcm;
//    intersect_line_with_plane3D(
//      pixelRays, camFitPlane.t(), worldOcmInCamCord, realProCornersCamCord);
//    // cv::Mat realProCornersCamCord4Dims = Mat(4, pixelRays.cols, CV_64FC1);
//    // for (int i = 0; i < pixelRays.cols; i++)
//    //{
//    //	realProCornersCamCord4Dims.at<double>(0, i) =
//    // realProCornersCamCord.at<double>(0, i);
//    //	realProCornersCamCord4Dims.at<double>(1, i) =
//    // realProCornersCamCord.at<double>(1, i);
//    //	realProCornersCamCord4Dims.at<double>(2, i) =
//    // realProCornersCamCord.at<double>(2, i);
//    //	realProCornersCamCord4Dims.at<double>(3, i) = 1;
//    // }
//    cv::Mat tMatrixRepeat =
//      cv::repeat(proCamExMatrixi.colRange(3, 4), 1, pixelRays.cols);
//    tempProCornersWorldCord = (proCamExMatrixi.colRange(0, 3)).t() *
//                              (realProCornersCamCord - tMatrixRepeat);

//    //投影图案角点在世界坐标系下的三维坐标
//    // cv::gemm(proCamExMatrix[i].colRange(0, 3).t(), realProCornersCamCord,
//    1,
//    // -tMatrixRepeat, 1, tempProCornersWorldCord);
//    realProCornersWorldCord.push_back(tempProCornersWorldCord);
//  }

//  // 多幅图像的角点在世界坐标系下的坐标
//  std::vector<std::vector<cv::Point3f>>
//    proCornersWorldCord;        //扩展后的角点坐标，多幅图像
//  std::vector<int> pointCounts; // 每幅图像中角点的数量
//  for (int i = 0; i < imgsCount; i++) {
//    int countCorners = (boardSize[i].width - 1) * (boardSize[i].height - 1);
//    pointCounts.push_back(countCorners);
//    std::vector<cv::Point3f> tempWorldPoint;
//    for (int j = 0; j < countCorners; j++) {
//      cv::Point3f tempPoint;
//      tempPoint.x = realProCornersWorldCord[i].at<double>(0, j);
//      tempPoint.y = realProCornersWorldCord[i].at<double>(1, j);
//      tempPoint.z = realProCornersWorldCord[i].at<double>(2, j);
//      tempWorldPoint.push_back(tempPoint);
//    }
//    proCornersWorldCord.push_back(tempWorldPoint);
//  }
//  struct CalibResult* calibResult = new CalibResult;
//  calib(proCornersWorldCord,
//        proPixelPoint,
//        pointCounts,
//        proSize,
//        imgsCount,
//        calibResult);

//  calibProjResult->_proInMatrix = calibResult->_inMatrix;
//  calibProjResult->_proExMatrix = calibResult->_exMatrix;
//  calibProjResult->_proDistortion = calibResult->_distortion;
//  calibProjResult->_proReprojErr = calibResult->_reprojErr;
//  calibCamResult._camExMatrix = proCamExMatrix[0];
//  cout << "总体平均误差：" << calibProjResult->_proReprojErr << "像素" << endl
//       << endl;
//  cout << "投影仪内参数矩阵：" << endl;
//  cout << calibProjResult->_proInMatrix << endl << endl;
//  cout << "投影仪畸变系数：" << endl;
//  cout << calibProjResult->_proDistortion << endl << endl;
//  cout << "投影仪外参数矩：" << endl;
//  cout << calibProjResult->_proExMatrix << endl << endl;
//  cout << "相机新外参数矩：" << endl;
//  cout << calibCamResult._camExMatrix << endl << endl;
//}

//// 计算投影仪标定时标定平面对应的相机外参
// void
// compute_ex_matrix(double squareSizex,
//                   double squareSizey,
//                   cv::Mat camInMatrix,
//                   cv::Mat camDistortion,
//                   cv::Mat& imgCamCornerVector,
//                   cv::Mat& proCamExMatrix,
//                   std::vector<cv::Point3f>& realCornerVector)
//{
//   // imgCamCornerVector     相机像素坐标下的角点坐标
//   // cv::Mat camInMatrix = calibCamResult._camInMatrix;   //相机内参矩阵
//   // cv::Mat camDistortion = calibCamResult._camDistortion;   //相机内参矩阵
//   // double squareSizex = calibProjProcessPara._proCbDx;
//   // //输入，棋盘格顶点间的水平距离 double squareSizey =
//   // calibProjProcessPara._proCbDy;   //输入，棋盘格顶点间的竖直距离
//   // std::vector<cv::Point3f> realCornerVector;
//   realCornerVector.clear();
//   // 1234
//   realCornerVector.push_back(cv::Point3f(0, 0, 0));
//   realCornerVector.push_back(cv::Point3f(squareSizex, 0, 0));
//   realCornerVector.push_back(cv::Point3f(squareSizex, squareSizey, 0));
//   realCornerVector.push_back(cv::Point3f(0, squareSizey, 0));

//  //// 3,2,4,1
//  // realCornerVector.push_back(cv::Point3f(squareSizex, squareSizey, 0));
//  // realCornerVector.push_back(cv::Point3f(squareSizex, 0, 0));
//  // realCornerVector.push_back(cv::Point3f(0, squareSizey, 0));
//  // realCornerVector.push_back(cv::Point3f(0, 0, 0));
//  std::vector<cv::Point2f> imgCamCorner;
//  cv::Point2f tempPoint;
//  for (int i = 0; i < 4; i++) {
//    tempPoint.x = imgCamCornerVector.at<float>(i, 0);
//    tempPoint.y = imgCamCornerVector.at<float>(i, 1);
//    imgCamCorner.push_back(tempPoint);
//  }
//  // cv::Mat rvecs = cv::Mat::zeros(3, 1,  CV_64FC1);
//  // cv::Mat tvecs = cv::Mat::zeros(3, 1, CV_64FC1);
//  cv::Mat rvecs = cv::Mat(1, 3, CV_32FC1, cv::Scalar::all(0));
//  cv::Mat tvecs = cv::Mat(1, 3, CV_32FC1, cv::Scalar::all(0));
//  // cv::solvePnPRansac(realCornerVector, imgCamCorner, camInMatrix,
//  // camDistortion, rvecs, tvecs);

//  //  std::cout << camInMatrix.rows << std::endl;
//  cv::solvePnP(
//    realCornerVector, imgCamCorner, camInMatrix, camDistortion, rvecs, tvecs);
//  cv::Mat rotationMat =
//    cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0)); /* 摄像机外参旋转矩阵 */
//  cv::Rodrigues(rvecs, rotationMat);             //得到旋转矩阵
//  // cv::Mat camExMatrix = Mat(3, 4, CV_32FC1, Scalar::all(0)); /*
//  // 摄像机外参数矩阵 */
//  cv::hconcat(rotationMat, tvecs, proCamExMatrix);
//  // camExMatrix.push_back(tempCamExMatrix);
//  // cv::Mat rvecs1;
//  // cv::Mat tvecs1;
//  // cv::solvePnP(realCornerVector, imgCamCorner, camInMatrix, camDistortion,
//  // rvecs1, tvecs1); cv::Mat rotationMat1 = Mat(3, 3, CV_32FC1,
//  // Scalar::all(0)); /* 摄像机外参旋转矩阵 */ Rodrigues(rvecs1,
//  rotationMat1);
//  // //得到旋转矩阵
//  ////cv::Mat camExMatrix = Mat(3, 4, CV_32FC1, Scalar::all(0)); /*
//  ///摄像机外参数矩阵 */
//  // cv::Mat proCamExMatrix1;
//  // hconcat(rotationMat1, tvecs1, proCamExMatrix1);
//}

////生成投影的棋盘格图案
// void
// generate_chessboard(cv::Size proSize,
//                     cv::Size boardSize,
//                     int proOffsetDx,
//                     int proOffsetDy,
//                     cv::Mat& proAllPixel,
//                     std::vector<cv::Point2f>& proPixelPoint)
//{
//   int proHeight = proSize.height;
//   int proWidth = proSize.width;
//   int boardNumx = boardSize.width;  //棋盘格列个数
//   int boardNumy = boardSize.height; //棋盘格行个数
//   int flagX = 0;
//   int flagY = 0;
//   if (proOffsetDx > 0) {
//     flagX = 1;
//   }
//   if (proOffsetDy > 0) {
//     flagY = 1;
//   }
//   int gridSizedx =
//     (proWidth - proOffsetDx) / (boardSize.width - flagX); //棋盘格宽
//   int gridSizedy =
//     (proHeight - proOffsetDy) / (boardSize.height - flagY); //棋盘格高
//   // cv::Mat I = cv::Mat::ones(gridSizedy * boardNumy, gridSizedx *
//   boardNumx,
//   // CV_8U) * 255;

//  ////生成棋盘格图案
//  // for (int i = 0; i < boardNumx; i++)
//  //{
//  //	if ((i + 1) / 2 == 1)
//  //	{
//  //		for (int j = 0; j < boardNumy; j++)
//  //		{
//  //			if ((j + 1) / 2 == 1)
//  //			{
//  //				for (int iGridx = 0; iGridx < gridSizedx;
//  // iGridx++)
//  //				{
//  //					for (int iGridy = 0; iGridy <
//  // gridSizedy; iGridy++)
//  //					{
//  //						//I.at<uchar>(i * gridSizedx +
//  // iGridx,
//  // j
//  //*
//  // gridSizedy + iGridy) = 0; I.at<uchar>(
//  // j
//  // * gridSizedy
//  // + iGridy, i * gridSizedx + iGridx) = 0;
//  //					}
//  //				}
//  //			}
//  //		}
//  //	}
//  //	else
//  //	{
//  //		for (int j = 0; j < boardNumy; j++)
//  //		{
//  //			if ((j + 1) / 2 == 0)
//  //			{
//  //				for (int iGridx = 0; iGridx < gridSizedx;
//  // iGridx++)
//  //				{
//  //					for (int iGridy = 0; iGridy <
//  // gridSizedy; iGridy++)
//  //					{
//  //						//I.at<uchar>(i * gridSizedx +
//  // iGridx,
//  // j
//  //*
//  // gridSizedy + iGridy) = 0; I.at<uchar>(j
//  // * gridSizedy
//  // + iGridy , i * gridSizedx + iGridx) = 0;
//  //					}
//  //				}
//  //			}
//  //		}
//  //	}
//  // }

//  // cv::Mat proAllPixelTemp = I.colRange(gridSizedx - proOffsetDx, proWidth);
//  // proAllPixel = proAllPixelTemp.rowRange(gridSizedy - proOffsetDy,
//  // proHeight);

//  //生成角点坐标
//  // int  j;
//  // if (proOffsetDy > 0)
//  //{
//  //	j = proOffsetDy - 1;
//  //}
//  // else
//  //{
//  //	j = gridSizedy - 1;
//  //}
//  // cv::Point2f tempPoint;
//  // for (j ; j < (proOffsetDy + gridSizedy * (boardNumy - 1 - flagY)); j = j
//  +
//  // gridSizedy)
//  //{
//  //	int i;
//  //	if (proOffsetDx > 0)
//  //	{
//  //		i = proOffsetDx - 1;
//  //	}
//  //	else
//  //	{
//  //		i = gridSizedx - 1;
//  //	}
//  //	for (i ; i < (gridSizedx * (boardNumx - 1 - flagX) + proOffsetDx); i = i
//  //+ gridSizedx)
//  //	{
//  //		tempPoint.x = i;
//  //		tempPoint.y = j;
//  //		proPixelPoint.push_back(tempPoint);
//  //	}
//  //}

//  cv::Point2f tempPoint;
//  for (int j = boardNumy - 1 - flagY; j >= 1 - flagY; j--) {
//    for (int i = boardNumx - 1 - flagX; i >= 1 - flagX; i--) {
//      tempPoint.x = i * gridSizedx + proOffsetDx - 0.5;
//      tempPoint.y = j * gridSizedy + proOffsetDy - 0.5;
//      proPixelPoint.push_back(tempPoint);
//    }
//  }
//  cv::Mat mattixPoint = cv::Mat(proPixelPoint);

//  /*I = I(:, GridSizedx - proOffsetDx : end);*/
//  // x = ((GridSizedx * 14 + 5) : -GridSizedx : 90) + 0.5 - 1;
//  // y = (GridSizedy:GridSizedy: GridSizedy * 14) + 0.5 - 1;
//  //[X, Y] = meshgrid(x, y);
//  // X = X; Y = Y;
//}

//// Fit a hyperplane to a set of ND points.
//// 输入的points为（N,3）
//// 输出的plane为（4,1）
//// Note: Input points must be in the form of an NxM matrix, where M is the
//// dimensionality.
////       This function finds the best-fit plane P, in the least-squares
////       sense, between the points (X,Y,Z). The resulting plane P is described
////       by the coefficient vector W, where W(1)*X + W(2)*Y +W(3)*Z = W(3),
///for /       (X,Y,Z) on the plane P.
// void
// fit_plane(cv::Mat points, cv::Mat& plane)
//{
//   //输入的points为（N,3）
//   // 输出的plane为（4,1）
//   //点的行和列，传入的每一行为1个点
//   int rows = points.rows; //行
//   int cols = points.cols;
//   //  points2 = [X(:)-meanX ,Y(:)-meanY,Z(:)-meanZ]
//   cv::Mat centroid = cv::Mat(1, cols, CV_64FC1, cv::Scalar::all(0));
//   for (int i = 0; i < cols; i++) {
//     for (int j = 0; j < rows; j++) {
//       centroid.at<double>(0, i) += points.at<double>(j, i);
//     }
//     centroid.at<double>(0, i) /= rows;
//   }

//  cv::Mat points2 = cv::Mat::ones(
//    rows, cols, CV_64FC1); // points2 = [X(:)-meanX ,Y(:)-meanY,Z(:)-meanZ]
//  for (int i = 0; i < rows; i++) {
//    for (int j = 0; j < cols; j++) {
//      points2.at<double>(i, j) =
//        points.at<double>(i, j) - centroid.at<double>(0, j);
//    }
//  }

//  // 非奇异值分解
//  // cv::Mat A, W, U, V;
//  cv::Mat A = cv::Mat(cols, cols, CV_64FC1);
//  cv::Mat W = cv::Mat(cols, cols, CV_64FC1);
//  cv::Mat U = cv::Mat(cols, cols, CV_64FC1);
//  cv::Mat V = cv::Mat(cols, cols, CV_64FC1);
//  cv::gemm(points2.t(),
//           points,
//           1,
//           NULL,
//           0,
//           A); // Mat的乘法，输出到A，A= 1⋅points2⋅points + 0⋅NULL
//  cv::SVD::compute(A.t(), W, U, V); //非奇异值分解

//  //平面方程
//  plane = cv::Mat::zeros(cols + 1, 1, CV_64FC1);
//  for (int c = 0; c < cols; c++) {
//    plane.at<double>(c, 0) = V.at<double>(cols - 1, c);
//    plane.at<double>(cols, 0) +=
//      plane.at<double>(c, 0) * centroid.at<double>(0, c);
//  }
//}

// cv::Mat
// normCorners(std::vector<cv::Point2f> imgCorners,
//             cv::Mat camInMatrix,
//             cv::Mat camDistortion)
//// cv::Mat normalize(std::vector<cv::Point2f> imgCorners, cv::Mat fc, cv::Mat
//// cc, cv::Mat camDistortion)
//{
//  // 从像素坐标系转换到图像坐标系
//  // cv::Mat fc = (cv::Mat_<double>(1, 2) << camInMatrix.at<double>(0, 0),
//  // camInMatrix.at<double>(1, 1)); cv::Mat cc = (cv::Mat_<double>(1, 2) <<
//  // camInMatrix.at<double>(0, 2), camInMatrix.at<double>(1, 2));
//  int pointSize = size(imgCorners);
//  std::vector<cv::Point2f> undistortCorners;
//  cv::Mat normImgPoint = cv::Mat(3, pointSize, CV_64FC1);
//  undistortPoints(imgCorners,
//                  undistortCorners,
//                  camInMatrix,
//                  camDistortion); //返回去畸变后并归一化的坐标
//  for (int i = 0; i < pointSize; i++) {
//    // cv::Point2f temp;
//    // normImgPoint.at<double>(0, i) = (undistortCorners[i].x -
//    cc.at<double>(1,
//    // 1)) / fc.at<double>(1, 1); normImgPoint.at<double>(1, i) =
//    // (undistortCorners[i].y - cc.at<double>(1, 2)) / fc.at<double>(1, 2);
//    normImgPoint.at<double>(0, i) = undistortCorners[i].x;
//    normImgPoint.at<double>(1, i) = undistortCorners[i].y;
//    normImgPoint.at<double>(2, i) = 1;
//    // normImgPoint.push_back(temp);
//  }

//  return normImgPoint;
//  // double k1 = camDistortion.at<uchar>(0, 0);
//  // double k2 = camDistortion.at<uchar>(0, 1);
//  // double k3 = camDistortion.at<uchar>(0, 2);
//  // double p1 = camDistortion.at<uchar>(0, 3);
//  // double p2 = camDistortion.at<uchar>(0, 4);

//  // std::vector<cv::Point2f> tempPoint = normImgPoint;  //初始的点

//  // for(int kk = 0; kk < 20; kk++)
//  //{
//  //	double r2 = norm(tempPoint, 2);
//  //	double kRadial = 1 + k1 * r2 + k2 * pow(r2, 2) + k3 * pow(r2, 3);
//  //
//  // }
//}

// void
// pixel2ray(std::vector<cv::Point2f> imgCorners,
//           cv::Mat camInMatrix,
//           cv::Mat camDistortion,
//           cv::Mat& pixelRays)
//{
//   // 从像素坐标系转换到图像坐标系
//   // cv::Mat fc = (cv::Mat_<double>(1, 2) << camInMatrix.at<uchar>(0, 0),
//   // camInMatrix.at<uchar>(1, 1)); cv::Mat cc = (cv::Mat_<double>(1, 2) <<
//   // camInMatrix.at<uchar>(0, 2), camInMatrix.at<uchar>(1, 2));
//   cv::Mat tempCorners =
//     normCorners(imgCorners, camInMatrix, camDistortion); //归一化并齐次化角点
//   cv::Mat pixelRaysTemp = cv::Mat(tempCorners.rows, tempCorners.cols,
//   CV_64FC1);
//   // cv::Mat onesMat = cv::Mat::ones(1, tempCorners.cols, CV_8U);
//   // tempCorners.push_back(onesMat);
//   for (int i = 0; i < tempCorners.cols; i++) {
//     double sum = 0;
//     for (int j = 0; j < tempCorners.rows; j++) {
//       sum += tempCorners.at<double>(j, i) * tempCorners.at<double>(j, i);
//     }
//     pixelRaysTemp.at<double>(0, i) = tempCorners.at<double>(0, i) /
//     sqrt(sum); pixelRaysTemp.at<double>(1, i) = tempCorners.at<double>(1, i)
//     / sqrt(sum); pixelRaysTemp.at<double>(2, i) = tempCorners.at<double>(2,
//     i) / sqrt(sum);
//   }
//   pixelRays = pixelRaysTemp;
// }

// void
// rays_planes(cv::Size camResolution,
//             cv::Size proResolution,
//             CalibCamResultReturn& calibCamResult,
//             CalibProjResultReturn& calibProjResult,
//             CalibOutputParamReturn* calibOutputParam)
//{
//   //投影仪的分辨率
//   //相机的分辨率
//   cv::Mat camInMatrix = calibCamResult._camInMatrix;
//   cv::Mat camExMatrix = calibCamResult._camExMatrix;     //传入第一个外参
//   cv::Mat camDistortion = calibCamResult._camDistortion; //相机的内参
//   cv::Mat proInMatrix = calibProjResult._proInMatrix;
//   cv::Mat proExMatrix = calibProjResult._proExMatrix; //传入第一个外参
//   cv::Mat proDistortion = calibProjResult._proDistortion; //投影仪的内参

//  //相机射线和原点标定
//  std::vector<cv::Point2f> camPoint;
//  for (int i = 0; i < camResolution.width; i++) {
//    for (int j = 0; j < camResolution.height; j++) {
//      cv::Point2f tempPoint;
//      tempPoint.x = i;
//      tempPoint.y = j;
//      camPoint.push_back(tempPoint);
//    }
//  }
//  cv::Mat camRays, tempCamOriPt, tempDirLineVector;
//  pixel2ray(camPoint, camInMatrix, camDistortion, camRays);
//  cv::Mat camExMatrix64, camRays64;
//  camExMatrix.convertTo(camExMatrix64, CV_64FC1);
//  camRays.convertTo(camRays64, CV_64FC1);
//  cv::Mat camExMatrixRepeat =
//    cv::repeat(camExMatrix64.colRange(3, 4), 1, camRays.cols);
//  //  cv::Mat ma1 = (camExMatrix.colRange(0, 3) * (camExMatrix.colRange(0,
//  //  3).t())); cv::Mat ma2 = cv::Mat(3, camRays.cols, CV_64FC1); for (int i =
//  //  0; i < camRays.cols; i++) {
//  //    for (int j = 0; j < 3; j++) {
//  //      ma2.at<double>(j, i) =
//  //        camRays.at<double>(j, i) - camExMatrix.at<double>(j, 3);
//  //    }
//  //  }
//  //  cv::Mat ma2 = camRays - camExMatrixRepeat;
//  //  tempDirLineVector = ma1 * ma2 + camExMatrixRepeat;
//  //  tempCamOriPt = -ma1 * camExMatrix + camExMatrix;
//  //  cv::gemm(ma1, ma2, 1, camExMatrixRepeat, 1, tempDirLineVector);
//  //  cv::gemm(ma1, -camExMatrix, 1, camExMatrix, 1, tempCamOriPt);

//  cv::gemm((camExMatrix64.colRange(0, 3) * (camExMatrix64.colRange(0,
//  3).t())),
//           camRays64 - camExMatrixRepeat,
//           1,
//           camExMatrixRepeat,
//           1,
//           tempDirLineVector);
//  cv::gemm((camExMatrix64.colRange(0, 3) * (camExMatrix64.colRange(0,
//  3).t())),
//           -camExMatrix64,
//           1,
//           camExMatrix64,
//           1,
//           tempCamOriPt);
//  // cv::Mat camDemo = tempDirLineVector.colRange(0, 50);
//  calibOutputParam->_camOriPt = tempCamOriPt;
//  calibOutputParam->_dirLineVectors = tempDirLineVector;
//  calibOutputParam->_internalCamParamMat = camInMatrix;

//  //投影仪投影面标定
//  int count = 0;
//  std::vector<cv::Point2f> proPoint;
//  for (int i = 0; i < proResolution.width; i++) {
//    for (int j = 0; j < proResolution.height; j++) {
//      cv::Point2f tempPoint;
//      tempPoint.x = i;
//      tempPoint.y = j;
//      proPoint.push_back(tempPoint);
//    }
//  }
//  cv::Mat proRays;
//  pixel2ray(proPoint, proInMatrix, proDistortion, proRays);
//  cv::Mat proExMatrix64, proRays64;
//  proExMatrix.convertTo(proExMatrix64, CV_64FC1);
//  proRays.convertTo(proRays64, CV_64FC1);
//  cv::Mat proRaysInCamTemp; //投影仪像素射线在相机坐标系中的表示
//  cv::Mat proExMatrixRepeat =
//    cv::repeat(proExMatrix64.colRange(3, 4), 1, proRays.cols);
//  cv::Mat camExMatrixRepeatPro = cv::repeat(
//    camExMatrix64.colRange(3, 4), 1, proRays.cols); //按投影仪的列数复制
//  cv::gemm(camExMatrix64.colRange(0, 3) * proExMatrix64.colRange(0, 3).t(),
//           proRays64 - proExMatrixRepeat,
//           1,
//           camExMatrixRepeatPro,
//           1,
//           proRaysInCamTemp);
//  cv::Mat proOriInCam; //投影仪坐标系原点在相机坐标系中的表示
//  cv::gemm(camExMatrix64.colRange(0, 3) * proExMatrix64.colRange(0, 3).t(),
//           -proExMatrix64.colRange(3, 4),
//           1,
//           camExMatrix64.colRange(3, 4),
//           1,
//           proOriInCam);
//  cv::Mat tempExternalPlaneMat = cv::Mat(4, proResolution.width, CV_64FC1);
//  for (int i = 0; i < proResolution.width; i++) {
//    cv::Mat tempPoints = cv::Mat(proResolution.height + 1, 3, CV_64FC1);
//    tempPoints.at<double>(0, 0) = proOriInCam.at<double>(0, 0);
//    tempPoints.at<double>(0, 1) = proOriInCam.at<double>(1, 0);
//    tempPoints.at<double>(0, 2) = proOriInCam.at<double>(2, 0);
//    for (int j = 0; j < proResolution.height; j++) {
//      tempPoints.at<double>(j + 1, 0) =
//        proRaysInCamTemp.at<double>(0, i * proResolution.height + j);
//      tempPoints.at<double>(j + 1, 1) =
//        proRaysInCamTemp.at<double>(1, i * proResolution.height + j);
//      tempPoints.at<double>(j + 1, 2) =
//        proRaysInCamTemp.at<double>(2, i * proResolution.height + j);
//    }
//    cv::Mat tempPlane;
//    fit_plane(tempPoints, tempPlane);
//    for (int k = 0; k < 4; k++) {
//      tempExternalPlaneMat.at<double>(k, i) = tempPlane.at<double>(k, 0);
//    }
//  }

//  calibOutputParam->_camOriPt = tempCamOriPt;
//  calibOutputParam->_dirLineVectors = tempDirLineVector;
//  calibOutputParam->_internalCamParamMat = camInMatrix;
//  calibOutputParam->_internalProjParamMat = proInMatrix;
//  calibOutputParam->_externalProjParamMat = calibProjResult._proExMatrix;
//  calibOutputParam->_externalPlaneMat = tempExternalPlaneMat.t();
//}
// void
// intersect_line_with_plane3D(cv::Mat pixelRays,
//                            cv::Mat camFitPlane,
//                            cv::Mat worldOcmInCamCord,
//                            cv::Mat& realProCornersCamCord)
//{
//  // // Evaluate inner products.
//  // cv::Mat onesMat = cv::Mat::ones(3, pixelRays.cols, CV_64FC1);
//  // double nDotQ = 0, nDotV = 0;
//  // for (int i = 0; i < 3; i++)
//  //{
//  //	nDotQ += camFitPlane.at<double>(0, i) * onesMat.at<double>(0, i);
//  //	nDotV += camFitPlane.at<double>(0, i) * pixelRays.at<double>(0, i);
//  //}

//  //// Evaluate point of intersection P.
//  // float depth = (camFitPlane.at<double>(0, 3) - nDotQ) / nDotV;
//  // for (int i = 0; i < 3; i++)
//  //{
//  //	realProCornersCamCord.at<double>(0, i) = onesMat.at<double>(0, i) +
//  // depth * pixelRays.at<double>(0, i);
//  // }

//  // for (int i = 0; i < pixelRays.cols; i++)
//  //{
//  //	double sumRays = 0;
//  //	for (int j = 0; j < 3; j++)
//  //	{
//  //		sumRays += camFitPlane.at<double>(0, j) *
//  // pixelRays.at<double>(j, i);

//  //	}
//  //	//tempPoint.at<double>(0, i) = camFitPlane.at<double>(0, 3) /sum;
//  //	for (int k = 0; k < 3; k++)
//  //	{
//  //		realProCornersCamCord.at<double>(k, i) =
//  //(camFitPlane.at<double>(0, 3) / sumRays) * (pixelRays.at<double>(k, i));
//  //	}
//  //}
//  for (int i = 0; i < pixelRays.cols; i++) {
//    double sumRays = 0;
//    double sumOcm = 0;
//    for (int j = 0; j < 3; j++) {
//      sumRays += camFitPlane.at<double>(0, j) * pixelRays.at<double>(j, i);
//      sumOcm +=
//        camFitPlane.at<double>(0, j) * worldOcmInCamCord.at<double>(j, 0);
//    }
//    // tempPoint.at<double>(0, i) = camFitPlane.at<double>(0, 3) /sum;
//    for (int k = 0; k < 3; k++) {
//      realProCornersCamCord.at<double>(k, i) =
//        ((camFitPlane.at<double>(0, 3) - sumOcm) / sumRays) *
//        (pixelRays.at<double>(k, i));
//    }
//  }
//}

//}
