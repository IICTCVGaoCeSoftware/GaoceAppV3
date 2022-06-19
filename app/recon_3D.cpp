//#include "recon_3D.hpp"
//#include <unsupported/Eigen/CXX11/Tensor>
// namespace esb = Eyestack::Base;
// esb::Profiler gProfiler;

// std::map<std::string, int>
// grayCodeString(int n, int offset)
//{
//   std::map<std::string, int> my_map;
//   for (int i = 0; i < pow(2, n) - offset; ++i) {
//     int offsetIndex = i + offset;
//     int garayValue = (offsetIndex >> 1) ^ offsetIndex;
//     int temp = garayValue;
//     std::vector<uchar> ivec(n);
//     int index = 0;
//     while (temp != 0) {
//       ivec[n - 1 - index] = 255 * (temp % 2);
//       temp = temp >> 1;
//       index++;
//     }
//     cv::Mat matVec(ivec);
//     std::vector<uchar> vecSTD(matVec.begin<uchar>(), matVec.end<uchar>());
//     std::string strGrayCode(vecSTD.begin(), vecSTD.end());
//     std::pair<std::string, int> mypair(strGrayCode, i);
//     my_map.insert(mypair);
//   }
//   return my_map;
// }

// std::map<int, std::vector<uchar>>
// grayCodeVector(int n, int offset)
//{
//   std::map<int, std::vector<uchar>> my_map;
//   for (int i = 0; i < pow(2, n) - offset; ++i) {
//     unsigned int offsetIndex = i + offset;

//    int garayValue = (offsetIndex >> 1) ^ offsetIndex;
//    int temp = garayValue;
//    std::vector<uchar> ivec(n);
//    int index = 0;
//    while (temp != 0) {
//      ivec[n - 1 - index] = 255 * (temp % 2);
//      temp = temp >> 1;
//      index++;
//    }

//    std::pair<int, std::vector<uchar>> mypair(i, ivec);
//    my_map.insert(mypair);
//  }
//  return my_map;
//}

// void
// find_compare_index(int curId,
//                    int nextId,
//                    std::map<int, std::vector<uchar>>& comparingMap,
//                    int* foundIndex)
//{
//   if (curId == nextId) {
//     *foundIndex = -1;
//     return;
//   }

//  std::vector<uchar> curPlaneVec = comparingMap.find(curId)->second;
//  std::vector<uchar> nextPlaneVec = comparingMap.find(nextId)->second;
//  for (int i = 0; i < curPlaneVec.size(); i++) {
//    if (curPlaneVec[i] != nextPlaneVec[i]) {
//      *foundIndex = i;
//      return;
//    }
//  }

//  *foundIndex = -1;
//  return;
//}

// cv::Mat
// generate_pair_plane_Id_mat(int numPlanes,
//                            std::map<int, std::vector<uchar>>& comparingMap)
//{

//  cv::Mat pairMat = cv::Mat::zeros(numPlanes, numPlanes, CV_32SC1);
//  for (int row = 0; row < numPlanes; row++) {
//    for (int col = 0; col < numPlanes; col++) {
//      int foundIndex;

//      find_compare_index(row, col, comparingMap, &foundIndex);
//      pairMat.at<int>(row, col) = foundIndex;
//    }
//  }
//  return pairMat;
//}

// unsigned int
// grayToBinary(unsigned int num, unsigned int numBits)
//{
//   for (unsigned int shift = 1; shift < numBits; shift <<= 1) {
//     num ^= num >> shift;
//   }
//   return num;
// }

// void
// decodeGrayCode(cv::Mat& grayCodeMat,
//                std::map<std::string, int>& graycodeTMPString,
//                cv::Mat& maskValid,
//                int codeLength,
//                cv::Mat& imgCol)
//{

//  for (int row = 0; row < grayCodeMat.rows; row++) {
//    for (int col = 0; col < grayCodeMat.cols; col++) {
//      if (maskValid.at<uchar>(row, col) == 0)
//        continue;
//      cv::Mat matVec;
//      if (codeLength == 10) {
//        auto vectmp = grayCodeMat.at<Vec10b>(row, col);
//        matVec = cv::Mat(vectmp);
//      } else if (codeLength == 11) {
//        auto vectmp = grayCodeMat.at<Vec11b>(row, col);
//        matVec = cv::Mat(vectmp);
//      } else if (codeLength == 12) {
//        auto vectmp = grayCodeMat.at<Vec12b>(row, col);
//        matVec = cv::Mat(vectmp);
//      } else
//        continue;

//      std::vector<uchar> vecSTD(matVec.begin<uchar>(), matVec.end<uchar>());
//      std::string strGrayCode(vecSTD.begin(), vecSTD.end());

//      auto planeFound = graycodeTMPString.find(strGrayCode);
//      if (planeFound == graycodeTMPString.end())
//        continue;

//      int planeId = planeFound->second;
//      imgCol.at<int>(row, col) = planeId;
//    }
//  }
//}

// void
// decodeGrayCode2(cv::Mat& grayCodeMat,
//                 int offset,
//                 cv::Mat& maskValid,
//                 int codeLength,
//                 cv::Mat& imgCol)
//{

//  for (int row = 0; row < grayCodeMat.rows; row++) {
//    for (int col = 0; col < grayCodeMat.cols; col++) {
//      if (maskValid.at<uchar>(row, col) == 0)
//        continue;
//      unsigned int planeId;
//      int codeGray = 0;

//      if (codeLength == 10) {
//        for (int c = 0; c < codeLength; c++) {
//          codeGray +=
//            pow(2, codeLength - 1 - c) * grayCodeMat.at<Vec10b>(row, col)[c];
//        }

//      } else if (codeLength == 11) {
//        for (int c = 0; c < codeLength; c++) {
//          codeGray +=
//            pow(2, codeLength - 1 - c) * grayCodeMat.at<Vec11b>(row, col)[c];
//        }

//      } else if (codeLength == 12) {
//        for (int c = 0; c < codeLength; c++) {
//          codeGray +=
//            pow(2, codeLength - 1 - c) * grayCodeMat.at<Vec11b>(row, col)[c];
//        }

//      } else
//        continue;
//      codeGray = codeGray / 255;
//      planeId = grayToBinary(codeGray, codeLength) - offset;

//      imgCol.at<int>(row, col) = planeId;
//    }
//  }
//}

// void
// decodeGrayCodeLength10(cv::Mat& grayCodeMat,
//                        int offset,
//                        cv::Mat& maskValid,
//                        int codeLength,
//                        cv::Mat& imgCol)
//{

//  for (int row = 0; row < grayCodeMat.rows; row++) {
//    for (int col = 0; col < grayCodeMat.cols; col++) {
//      if (maskValid.at<uchar>(row, col) == 0)
//        continue;
//      unsigned int planeId;
//      int codeGray = 0;

//      for (int c = 0; c < codeLength; c++) {
//        codeGray +=
//          pow(2, codeLength - 1 - c) * grayCodeMat.at<Vec10b>(row, col)[c];
//      }

//      codeGray = codeGray / 255;
//      planeId = grayToBinary(codeGray, codeLength) - offset;

//      imgCol.at<int>(row, col) = planeId;
//    }
//  }
//}

// void
// decodeGrayCodeLength11(cv::Mat& grayCodeMat,
//                        int offset,
//                        cv::Mat& maskValid,
//                        int codeLength,
//                        cv::Mat& imgCol)
//{
//   std::vector<int> pow2Value(codeLength);
//   for (int c = 0; c < codeLength; c++) {
//     pow2Value[c] = pow(2, c);
//   }

//  for (int row = 0; row < grayCodeMat.rows; row++) {
//    for (int col = 0; col < grayCodeMat.cols; col++) {
//      if (maskValid.at<uchar>(row, col) == 0)
//        continue;

//      int codeGray = 0;

//      for (int c = 0; c < codeLength; c++) {
//        codeGray +=
//          pow2Value[codeLength - 1 - c] * grayCodeMat.at<Vec11b>(row, col)[c];
//      }

//      codeGray = codeGray / 255;
//      unsigned int planeId = grayToBinary(codeGray, codeLength) - offset;
//      imgCol.at<int>(row, col) = planeId;
//    }
//  }
//}

// void
// decodeGrayCodeLength12(cv::Mat& grayCodeMat,
//                        int offset,
//                        cv::Mat& maskValid,
//                        int codeLength,
//                        cv::Mat& imgCol)
//{

//  for (int row = 0; row < grayCodeMat.rows; row++) {
//    for (int col = 0; col < grayCodeMat.cols; col++) {
//      if (maskValid.at<uchar>(row, col) == 0)
//        continue;
//      unsigned int planeId;
//      int codeGray = 0;

//      for (int c = 0; c < codeLength; c++) {
//        codeGray +=
//          pow(2, codeLength - 1 - c) * grayCodeMat.at<Vec12b>(row, col)[c];
//      }

//      codeGray = codeGray / 255;
//      planeId = grayToBinary(codeGray, codeLength) - offset;

//      imgCol.at<int>(row, col) = planeId;
//    }
//  }
//}

// void
// decodeGrayCodeLength9(cv::Mat& grayCodeMat,
//                       int offset,
//                       cv::Mat& maskValid,
//                       int codeLength,
//                       cv::Mat& imgCol)
//{

//  for (int row = 0; row < grayCodeMat.rows; row++) {
//    for (int col = 0; col < grayCodeMat.cols; col++) {
//      if (maskValid.at<uchar>(row, col) == 0)
//        continue;
//      unsigned int planeId;
//      int codeGray = 0;

//      for (int c = 0; c < codeLength; c++) {
//        codeGray +=
//          pow(2, codeLength - 1 - c) * grayCodeMat.at<Vec9b>(row, col)[c];
//      }

//      codeGray = codeGray / 255;
//      planeId = grayToBinary(codeGray, codeLength) - offset;

//      imgCol.at<int>(row, col) = planeId;
//    }
//  }
//}

// void
// decodeGrayCodeVector(std::vector<cv::Mat>& imgBinList,
//                      int offset,
//                      cv::Mat& maskValid,
//                      int codeLength,
//                      cv::Mat& imgCol)
//{
//   std::vector<int> pow2Value(codeLength);
//   for (int c = 0; c < codeLength; c++) {
//     pow2Value[c] = pow(2, c);
//   }
//   cv::parallel_for_(cv::Range(0, imgCol.rows), [&](const cv::Range& range) {
//     for (int row = range.start; row < range.end; row++) {
//       cv::parallel_for_(
//         cv::Range(0, imgCol.cols), [&](const cv::Range& range2) {
//           for (int col = range2.start; col < range2.end; col++) {

//            if (*(maskValid.data + col + row * maskValid.step[0]) == 0)
//              continue;
//            unsigned int planeId;
//            int codeGray = 0;

//            for (int c = 0; c < codeLength; c++) {
//              codeGray +=
//                pow2Value[codeLength - 1 - c] *
//                (*(imgBinList[c].data + col + row * imgBinList[c].step[0]));
//            }

//            codeGray = codeGray / 255;
//            planeId = grayToBinary(codeGray, codeLength) - offset;

//            imgCol.at<int>(row, col) = planeId;
//          }
//        });
//    }
//  });
//}

//// void
//// decodeGrayCodeVector(std::vector<cv::Mat>& imgBinList,
////                      int offset,
////                      cv::Mat& maskValid,
////                      int codeLength,
////                      cv::Mat& imgCol)
////{
////   std::vector<int> pow2Value(codeLength);
////   for (int c = 0; c < codeLength; c++) {
////     pow2Value[c] = pow(2, c);
////   }

////  for (int row = 0; row < imgBinList[0].rows; row++) {
////    for (int col = 0; col < imgBinList[0].cols; col++) {
////      //      if (maskValid.at<uchar>(row, col) == 0)
////      //        continue;
////      if (*(maskValid.data + col + row * maskValid.step[0]) == 0)
////        continue;
////      unsigned int planeId;
////      int codeGray = 0;

////      for (int c = 0; c < codeLength; c++) {
////        //        codeGray +=
////        //          pow2Value[codeLength - 1 - c] *
////        imgBinList[c].at<uchar>(row,
////        //          col);
////        codeGray += pow2Value[codeLength - 1 - c] *
////                    (*(imgBinList[c].data + col + row *
////                    imgBinList[c].step[0]));
////      }

////      codeGray = codeGray / 255;
////      planeId = grayToBinary(codeGray, codeLength) - offset;

////      imgCol.at<int>(row, col) = planeId;
////    }
////  }
////}

// void
// getStSubPixelGray(int row,
//                   int col,
//                   std::vector<cv::Mat>& imgGrayThresholds,
//                   cv::Mat& pairMat,
//                   cv::Mat& imgCol,
//                   double* subPixel,
//                   bool* isAdd)
//{

//  int curId = imgCol.at<int>(row, col);
//  int nextId = imgCol.at<int>(row, col - 1);
//  int foundIndex = -1;

//  if (nextId == -1) {
//    for (int i = 0; i < imgGrayThresholds.size(); i++) {
//      if (imgGrayThresholds[i].at<int>(row, col) *
//            imgGrayThresholds[i].at<int>(row, col - 1) <=
//          0) {
//        foundIndex = i;
//        break;
//      }
//    }

//  } else {
//    foundIndex = pairMat.at<int>(curId, nextId);
//  }
//  if (foundIndex == -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }
//  cv::Mat& imgGray = imgGrayThresholds[foundIndex];
//  int leftPtVal = imgGray.at<int>(row, col - 1);
//  int curPtVal = imgGray.at<int>(row, col);

//  if (leftPtVal == curPtVal) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }
//  double distK = -double(curPtVal) / (leftPtVal - curPtVal);
//  if (distK > 1 || distK < -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  *subPixel = col + distK;
//}

// void
// getStSubPixelGray2(int row,
//                    int col,
//                    std::vector<cv::Mat>& imgGrayThresholds,
//                    cv::Mat& pairMat,
//                    cv::Mat& imgCol,
//                    float* subPixel,
//                    bool* isAdd)
//{

//  int curId = imgCol.at<int>(row, col);
//  int nextId = imgCol.at<int>(row, col - 1);
//  int foundIndex = -1;

//  if (nextId == -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;

//  } else {
//    foundIndex = pairMat.at<int>(curId, nextId);
//  }
//  if (foundIndex == -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  int selectIndex = 2 + foundIndex * 2;
//  int leftPtVal =
//    (int)imgGrayThresholds[selectIndex].at<uchar>(row, col - 1) -
//    (int)imgGrayThresholds[selectIndex + 1].at<uchar>(row, col - 1);
//  int curPtVal = (int)imgGrayThresholds[selectIndex].at<uchar>(row, col) -
//                 (int)imgGrayThresholds[selectIndex + 1].at<uchar>(row, col);

//  if (leftPtVal == curPtVal) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }
//  float distK = -float(curPtVal) / (leftPtVal - curPtVal);
//  if (distK > 1 || distK < -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  *subPixel = col + distK;
//}

// void
// getEdSubPixelGray(int row,
//                   int col,
//                   std::vector<cv::Mat>& imgGrayThresholds,
//                   cv::Mat& pairMat,
//                   cv::Mat& imgCol,
//                   double* subPixel,
//                   bool* isAdd)
//{
//   int curId = imgCol.at<int>(row, col);
//   int nextId = imgCol.at<int>(row, col + 1);
//   int foundIndex = -1;

//  if (nextId == -1) {
//    for (int i = 0; i < imgGrayThresholds.size(); i++) {
//      if (imgGrayThresholds[i].at<int>(row, col) *
//            imgGrayThresholds[i].at<int>(row, col + 1) <=
//          0) {
//        foundIndex = i;
//        break;
//      }
//    }

//  } else {
//    foundIndex = pairMat.at<int>(curId, nextId);
//  }
//  if (foundIndex == -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  cv::Mat& imgGray = imgGrayThresholds[foundIndex];
//  int rightPtVal = imgGray.at<int>(row, col + 1);
//  int curPtVal = imgGray.at<int>(row, col);

//  if (rightPtVal == curPtVal) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }
//  double distK = -double(curPtVal) / (rightPtVal - curPtVal);
//  if (distK > 1 || distK < -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  *subPixel = col + distK;
//}

// void
// getEdSubPixelGray2(int row,
//                    int col,
//                    std::vector<cv::Mat>& imgGrayThresholds,
//                    cv::Mat& pairMat,
//                    cv::Mat& imgCol,
//                    float* subPixel,
//                    bool* isAdd)
//{
//   int curId = imgCol.at<int>(row, col);
//   int nextId = imgCol.at<int>(row, col + 1);
//   int foundIndex = -1;

//  if (nextId == -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;

//  } else {
//    foundIndex = pairMat.at<int>(curId, nextId);
//  }
//  if (foundIndex == -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  int selectIndex = 2 + foundIndex * 2;
//  int rightPtVal =
//    (int)imgGrayThresholds[selectIndex].at<uchar>(row, col + 1) -
//    (int)imgGrayThresholds[selectIndex + 1].at<uchar>(row, col + 1);
//  int curPtVal = (int)imgGrayThresholds[selectIndex].at<uchar>(row, col) -
//                 (int)imgGrayThresholds[selectIndex + 1].at<uchar>(row, col);

//  if (rightPtVal == curPtVal) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }
//  float distK = -float(curPtVal) / (rightPtVal - curPtVal);
//  if (distK > 1 || distK < -1) {
//    *subPixel = col;
//    *isAdd = false;
//    return;
//  }

//  *subPixel = col + distK;
//}

// void
// imgDenoise(cv::Mat& imgCol)
//{
//   cv::parallel_for_(cv::Range(0, imgCol.rows), [&](const cv::Range& range) {
//     for (int row = range.start; row < range.end; row++) {
//       bool isInit = false;
//       bool isPre = false;
//       bool isCur = false;
//       bool isNext = false;
//       int col = 0;
//       PtInfo prePt;
//       PtInfo curPt;
//       PtInfo nextPt;
//       PtInfo stNoise;
//       PtInfo edNoise;
//       while (isInit == false && col < imgCol.cols) {
//         while (col < imgCol.cols && imgCol.at<int>(row, col) == -1) {
//           col++;
//           continue;
//         }

//        if (isPre == false && col < imgCol.cols) {
//          prePt._col = col;
//          prePt._idPlane = imgCol.at<int>(row, col);
//          isPre = true;
//          col++;
//          continue;
//        }

//        if (isCur == false && col < imgCol.cols) {
//          curPt._col = col;
//          curPt._idPlane = imgCol.at<int>(row, col);
//          isCur = true;
//          col++;
//          continue;
//        }

//        if (isNext == false && col < imgCol.cols) {
//          nextPt._col = col;
//          nextPt._idPlane = imgCol.at<int>(row, col);
//          isNext = true;
//          col++;
//          isInit = true;
//        }

//        break;
//      }

//      if (isInit == false)
//        continue;
//      bool isEnd = false;
//      bool isInNoise = false;
//      while (isEnd == false) {
//        while (col < imgCol.cols && imgCol.at<int>(row, col) == -1) {
//          col++;
//          continue;
//        }
//        if (col >= imgCol.cols) {
//          isEnd = true;
//          break;
//        }
//        prePt._col = curPt._col;
//        prePt._idPlane = curPt._idPlane;
//        curPt._col = nextPt._col;
//        curPt._idPlane = nextPt._idPlane;
//        nextPt._col = col;
//        nextPt._idPlane = imgCol.at<int>(row, col);
//        col++;
//        if (nextPt._idPlane < curPt._idPlane) {
//          if (isInNoise == false) {
//            if (abs(curPt._idPlane - prePt._idPlane) >
//                abs(curPt._idPlane - nextPt._idPlane)) {
//              stNoise._col = curPt._col;
//              stNoise._idPlane = curPt._idPlane;
//            } else {
//              stNoise._col = nextPt._col;
//              stNoise._idPlane = nextPt._idPlane;
//            }
//            isInNoise = true;
//            continue;
//          }

//        } else {

//          if (isInNoise == true) {
//            if (nextPt._idPlane > curPt._idPlane) {
//              edNoise._col = nextPt._col;
//              edNoise._idPlane = nextPt._idPlane;
//              imgCol({ row, row + 1 }, { stNoise._col, edNoise._col + 1 }) =
//              -1; isInNoise = false;
//            }
//          }
//        }
//      }
//    }
//  });
//}

// void
// generate_feature_from_col_list(cv::Mat& imgCol,
//                                cv::Mat& pairMat,
//                                std::vector<cv::Mat>& imgGrayThresholds,
//                                std::vector<FeatureNode>& featureInfo)
//{
//   cv::Mat valueColSubPixelMat =
//     cv::Mat(imgCol.rows, imgCol.cols, CV_64FC1, cv::Scalar(-1));

//  //  cv::Mat testMask = cv::Mat::zeros(imgCol.rows, imgCol.cols, CV_8UC1);

//  for (int row = 0; row < imgCol.rows; row++) {
//    bool isInit = false;
//    int col = 0;
//    PtInfo stPt;
//    PtInfo curPt;
//    PtInfo edPt;
//    while (isInit == false) {
//      while (col < imgCol.cols && imgCol.at<int>(row, col) == -1) {
//        col++;
//        continue;
//      }

//      if (col < imgCol.cols && imgCol.at<int>(row, col) != -1) {
//        stPt._col = col;
//        stPt._idPlane = imgCol.at<int>(row, col);
//        curPt._col = col;
//        curPt._idPlane = imgCol.at<int>(row, col);
//        isInit = true;
//        col++;
//        break;
//      } else {
//        if (col >= imgCol.cols)
//          break;
//      }
//    }

//    // 完成初始化
//    if (isInit == false)
//      continue;

//    bool isEnd = false;
//    while (isEnd == false) {
//      while (col < imgCol.cols && imgCol.at<int>(row, col) == -1) {
//        col++;
//        continue;
//      }
//      if (col >= imgCol.cols) {
//        //结束
//        edPt = curPt;

//        //  验证结果可视化
//        //        testMask({ row, row + 1 }, { stPt._col, edPt._col + 1 }) =
//        //        125;
//        isEnd = true;
//        int stPlaneCol = stPt._col;
//        double stSubPixel;
//        if (stPlaneCol != 0 &&
//            valueColSubPixelMat.at<double>(row, stPlaneCol - 1) != -1) {
//          stSubPixel = valueColSubPixelMat.at<double>(row, stPlaneCol - 1);
//        } else {
//          if (stPlaneCol == 0) {
//            stSubPixel = 0;
//          } else {
//            bool isAdd;
//            getStSubPixelGray(row,
//                              stPlaneCol,
//                              imgGrayThresholds,
//                              pairMat,
//                              imgCol,
//                              &stSubPixel,
//                              &isAdd);
//            if (isAdd)
//              valueColSubPixelMat.at<double>(row, stPlaneCol) = stSubPixel;
//          }
//        }
//        int edPlaneCol = edPt._col;
//        double edSubPixel;

//        if (edPlaneCol == imgCol.cols - 1) {

//          edSubPixel = imgCol.cols - 1;
//        } else {
//          bool isAdd;
//          getEdSubPixelGray(row,
//                            edPlaneCol,
//                            imgGrayThresholds,
//                            pairMat,
//                            imgCol,
//                            &edSubPixel,
//                            &isAdd);
//          if (isAdd)
//            valueColSubPixelMat.at<double>(row, edPlaneCol) = edSubPixel;
//        }

//        double midSubPixel = (stSubPixel + edSubPixel) / 2;
//        int midColCeil = std::min({ int(ceil(midSubPixel)), imgCol.cols - 1
//        }); int midColFloor = std::max({ int(floor(midSubPixel)), 1 }); double
//        midColParam = midSubPixel - midColFloor; FeatureNode fn;
//        fn._midColFloor = midColFloor;
//        fn._midColCeil = midColCeil;
//        fn._midColParam = midColParam;
//        fn._idPlane = edPt._idPlane;
//        fn._row = row;
//        fn._midSubPixel = int(midSubPixel);
//        //        testMask.at<uchar>(row, int(fn._midSubPixel)) = 255;
//        featureInfo.push_back(fn);
//        break;
//      }

//      if (imgCol.at<int>(row, col) == curPt._idPlane) {
//        curPt._col = col;
//        col++;
//      } else {
//        edPt = curPt;
//        //        testMask({ row, row + 1 }, { stPt._col, edPt._col + 1 }) =
//        //        125;
//        curPt._col = col;
//        curPt._idPlane = imgCol.at<int>(row, col);
//        int stPlaneCol = stPt._col;
//        stPt._col = col;
//        stPt._idPlane = curPt._idPlane;
//        col++;
//        double stSubPixel;

//        if (stPlaneCol != 0 &&
//            valueColSubPixelMat.at<double>(row, stPlaneCol - 1) != -1) {
//          stSubPixel = valueColSubPixelMat.at<double>(row, stPlaneCol - 1);
//        } else {
//          if (stPlaneCol == 0) {
//            stSubPixel = 0;
//          } else {
//            bool isAdd;
//            getStSubPixelGray(row,
//                              stPlaneCol,
//                              imgGrayThresholds,
//                              pairMat,
//                              imgCol,
//                              &stSubPixel,
//                              &isAdd);
//            if (isAdd)
//              valueColSubPixelMat.at<double>(row, stPlaneCol) = stSubPixel;
//          }
//        }

//        int edPlaneCol = edPt._col;
//        double edSubPixel;

//        if (edPlaneCol == imgCol.cols - 1) {

//          edSubPixel = imgCol.cols - 1;
//        } else {
//          bool isAdd;
//          getEdSubPixelGray(row,
//                            edPlaneCol,
//                            imgGrayThresholds,
//                            pairMat,
//                            imgCol,
//                            &edSubPixel,
//                            &isAdd);
//          if (isAdd)
//            valueColSubPixelMat.at<double>(row, edPlaneCol) = edSubPixel;
//        }

//        double midSubPixel = (stSubPixel + edSubPixel) / 2;
//        int midColCeil = std::min({ int(ceil(midSubPixel)), imgCol.cols - 1
//        }); int midColFloor = std::max({ int(floor(midSubPixel)), 1 }); double
//        midColParam = midSubPixel - midColFloor; FeatureNode fn;
//        fn._midColFloor = midColFloor;
//        fn._midColCeil = midColCeil;
//        fn._midColParam = midColParam;
//        fn._idPlane = edPt._idPlane;
//        fn._row = row;
//        fn._midSubPixel = int(midSubPixel);
//        //        testMask.at<uchar>(row, int(fn._midSubPixel)) = 255;
//        featureInfo.push_back(fn);
//      }
//    }
//  }
//  //  cv::imwrite("E:/projects/EXP/log/testMask.bmp", testMask);
//}

// void
// generate_feature_from_col_list2(cv::Mat& imgCol,
//                                 cv::Mat& pairMat,
//                                 std::vector<cv::Mat>& imgList,
//                                 std::vector<FeatureNode>& featureInfo)
//{
//   std::vector<FeatureNode> tmpFeatureInfo(imgCol.rows * imgCol.cols);
//   cv::Mat valueColSubPixelMat =
//     cv::Mat(imgCol.rows, imgCol.cols, CV_32FC1, cv::Scalar(-1));
//   cv::parallel_for_(cv::Range(0, imgCol.rows), [&](const cv::Range& range) {
//     for (int row = range.start; row < range.end; row++) {
//       bool isInit = false;
//       int col = 0;
//       PtInfo stPt;
//       PtInfo curPt;
//       PtInfo edPt;
//       while (isInit == false) {
//         while (col < imgCol.cols && imgCol.at<int>(row, col) == -1) {
//           col++;
//           continue;
//         }

//        if (col < imgCol.cols && imgCol.at<int>(row, col) != -1) {
//          stPt._col = col;
//          stPt._idPlane = imgCol.at<int>(row, col);
//          curPt._col = col;
//          curPt._idPlane = imgCol.at<int>(row, col);
//          isInit = true;
//          col++;
//          break;
//        } else {
//          if (col >= imgCol.cols)
//            break;
//        }
//      }

//      // 完成初始化
//      if (isInit == false)
//        continue;

//      bool isEnd = false;
//      while (isEnd == false) {
//        while (col < imgCol.cols && imgCol.at<int>(row, col) == -1) {
//          col++;
//          continue;
//        }
//        if (col >= imgCol.cols) {
//          //结束
//          edPt = curPt;
//          isEnd = true;
//          int stPlaneCol = stPt._col;
//          float stSubPixel;
//          if (stPlaneCol != 0 &&
//              valueColSubPixelMat.at<float>(row, stPlaneCol - 1) != -1) {
//            stSubPixel = valueColSubPixelMat.at<float>(row, stPlaneCol - 1);
//          } else {
//            if (stPlaneCol == 0) {
//              stSubPixel = 0;
//            } else {
//              bool isAdd;
//              getStSubPixelGray2(
//                row, stPlaneCol, imgList, pairMat, imgCol, &stSubPixel,
//                &isAdd);
//              if (isAdd)
//                valueColSubPixelMat.at<float>(row, stPlaneCol) = stSubPixel;
//            }
//          }
//          int edPlaneCol = edPt._col;
//          float edSubPixel;

//          if (edPlaneCol == imgCol.cols - 1) {

//            edSubPixel = imgCol.cols - 1;
//          } else {
//            bool isAdd;
//            getEdSubPixelGray2(
//              row, edPlaneCol, imgList, pairMat, imgCol, &edSubPixel, &isAdd);
//            if (isAdd)
//              valueColSubPixelMat.at<float>(row, edPlaneCol) = edSubPixel;
//          }

//          float midSubPixel = (stSubPixel + edSubPixel) / 2;
//          int midColCeil =
//            std::min({ int(ceil(midSubPixel)), imgCol.cols - 1 });
//          int midColFloor = std::max({ int(floor(midSubPixel)), 1 });
//          double midColParam = midSubPixel - midColFloor;
//          int midSubPixelnt = int(midSubPixel);

//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midColFloor =
//            midColFloor;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midColCeil =
//            midColCeil;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midColParam =
//            midColParam;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._idPlane =
//            edPt._idPlane;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._row = row;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midSubPixel =
//            int(midSubPixel);
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._isValid = true;

//          break;
//        }

//        if (imgCol.at<int>(row, col) == curPt._idPlane) {
//          curPt._col = col;
//          col++;
//        } else {
//          edPt = curPt;

//          curPt._col = col;
//          curPt._idPlane = imgCol.at<int>(row, col);
//          int stPlaneCol = stPt._col;
//          stPt._col = col;
//          stPt._idPlane = curPt._idPlane;
//          col++;
//          float stSubPixel;

//          if (stPlaneCol != 0 &&
//              valueColSubPixelMat.at<float>(row, stPlaneCol - 1) != -1) {
//            stSubPixel = valueColSubPixelMat.at<float>(row, stPlaneCol - 1);
//          } else {
//            if (stPlaneCol == 0) {
//              stSubPixel = 0;
//            } else {
//              bool isAdd;
//              getStSubPixelGray2(
//                row, stPlaneCol, imgList, pairMat, imgCol, &stSubPixel,
//                &isAdd);
//              if (isAdd)
//                valueColSubPixelMat.at<float>(row, stPlaneCol) = stSubPixel;
//            }
//          }

//          int edPlaneCol = edPt._col;
//          float edSubPixel;

//          if (edPlaneCol == imgCol.cols - 1) {

//            edSubPixel = imgCol.cols - 1;
//          } else {
//            bool isAdd;
//            getEdSubPixelGray2(
//              row, edPlaneCol, imgList, pairMat, imgCol, &edSubPixel, &isAdd);
//            if (isAdd)
//              valueColSubPixelMat.at<float>(row, edPlaneCol) = edSubPixel;
//          }

//          double midSubPixel = (stSubPixel + edSubPixel) / 2;
//          int midColCeil =
//            std::min({ int(ceil(midSubPixel)), imgCol.cols - 1 });
//          int midColFloor = std::max({ int(floor(midSubPixel)), 1 });
//          double midColParam = midSubPixel - midColFloor;
//          int midSubPixelnt = int(midSubPixel);

//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midColFloor =
//            midColFloor;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midColCeil =
//            midColCeil;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midColParam =
//            midColParam;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._idPlane =
//            edPt._idPlane;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._row = row;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._midSubPixel =
//            midSubPixelnt;
//          tmpFeatureInfo[row * imgCol.cols + midSubPixelnt]._isValid = true;
//        }
//      }
//    }
//  });

//  for (auto ft = tmpFeatureInfo.begin(); ft != tmpFeatureInfo.end(); ft++) {
//    if (ft->_isValid) {
//      featureInfo.push_back(*ft);
//    }
//  }

//  //  cv::imwrite("E:/projects/EXP/log/testMask.bmp", testMask);
//}

// void
// line_plane_intersection_subpixel(
//   std::vector<FeatureNode>& featureInfo,
//   ReconstructRealTimeInputParam& reconstructParam2,
//   pcl::PointCloud<pcl::PointXYZ>* cloud)
//{
//   auto camOriPt = reconstructParam2._camOriPt;
//   cloud->resize(featureInfo.size());
//   cv::parallel_for_(
//     cv::Range(0, featureInfo.size()), [&](const cv::Range& range) {
//       for (int i = range.start; i < range.end; i++) {
//         FeatureNode* ft = &featureInfo[i];
//         int idPlane = ft->_idPlane;

//        auto planeinfo =
//          reconstructParam2._externalPlaneMat.at<Vec4f>(0, ft->_idPlane);

//        auto dirlineRight =
//          reconstructParam2._dirLinethetas.at<Vec3f>(ft->_row,
//          ft->_midColCeil);
//        auto dirlineLeft = reconstructParam2._dirLinethetas.at<Vec3f>(
//          ft->_row, ft->_midColFloor);

//        auto dirLinetheta = ft->_midColParam * dirlineLeft +
//                            (1 - ft->_midColParam) * dirlineRight;

//        auto dirLineVector = dirLinetheta;
//        dirLineVector[0] = cos(dirLineVector[0]);
//        dirLineVector[1] = cos(dirLineVector[1]);
//        dirLineVector[2] = cos(dirLineVector[2]);

//        float t =
//          (planeinfo[3] - (planeinfo[0] * camOriPt.at<float>(0, 0) +
//                           planeinfo[1] * camOriPt.at<float>(0, 1) +
//                           planeinfo[2] * camOriPt.at<float>(0, 2))) /
//          (planeinfo[0] * dirLineVector[0] + planeinfo[1] * dirLineVector[1] +
//           planeinfo[2] * dirLineVector[2]);

//        cloud->points[i].x = camOriPt.at<float>(0, 0) + t * dirLineVector[0];
//        cloud->points[i].y = camOriPt.at<float>(0, 1) + t * dirLineVector[1];
//        cloud->points[i].z = camOriPt.at<float>(0, 2) + t * dirLineVector[2];
//      }
//    });
//}

// void
// line_plane_intersection_pixel(cv::Mat& imgCol,
//                               ReconstructRealTimeInputParam&
//                               reconstructParam2,
//                               pcl::PointCloud<pcl::PointXYZ>* cloud)
//{
//   auto camOriPt = reconstructParam2._camOriPt;
//   //  std::vector<std::vector<double>> ptList;
//   for (int row = 0; row < imgCol.rows; row++) {
//     for (int col = 0; col < imgCol.cols; col++) {
//       if (imgCol.at<int>(row, col) == -1)
//         continue;
//       int idPlane = imgCol.at<int>(row, col);
//       auto dirLineVector =
//         reconstructParam2._dirLineVectors.at<Vec3f>(row, col);
//       auto planeinfo =
//         reconstructParam2._externalPlaneMat.at<Vec4f>(0, idPlane);

//      float t =
//        (planeinfo[3] - (planeinfo[0] * camOriPt.at<float>(0, 0) +
//                         planeinfo[1] * camOriPt.at<float>(0, 1) +
//                         planeinfo[2] * camOriPt.at<float>(0, 2))) /
//        (planeinfo[0] * dirLineVector[0] + planeinfo[1] * dirLineVector[1] +
//         planeinfo[2] * dirLineVector[2]);

//      pcl::PointXYZ p;
//      p.x = camOriPt.at<float>(0, 0) + t * dirLineVector[0];
//      p.y = camOriPt.at<float>(0, 1) + t * dirLineVector[1];
//      p.z = camOriPt.at<float>(0, 2) + t * dirLineVector[2];
//      cloud->points.push_back(p);
//    }
//  }
//}

// void
// convertToDepthImage(pcl::PointCloud<pcl::PointXYZ>& cloud,
//                     cv::Mat& projExternalParam,
//                     cv::Mat& projInterParam,
//                     int imageHeight,
//                     int imageWidth,
//                     int scaleDepth,
//                     cv::Mat* depthImage)
//{
//   // N*3

//  int ptNum = cloud.points.size();
//  cv::Mat ptsMat = cv::Mat(4, cloud.points.size(), CV_32FC1);
//  for (int col = 0; col < ptNum; col++) {
//    ptsMat.at<float>(0, col) = cloud.points[col].x;
//    ptsMat.at<float>(1, col) = cloud.points[col].y;
//    ptsMat.at<float>(2, col) = cloud.points[col].z;
//    ptsMat.at<float>(3, col) = 1;
//  }

//  //  //  cv::Mat onesMat = cv::Mat(1, ptNum, ptsMat.type());
//  //  //  cv::vconcat(ptsMat, onesMat, ptsMat);
//  cv::Mat ptsImgWorld = projExternalParam * ptsMat;
//  cv::Mat ptsImgPlaneWorld = projInterParam * ptsImgWorld;

//  //  //周0610改 -> 转换数据类型
//  //  cv::Mat projExternalParam32, projInterParam32;
//  //  projExternalParam.convertTo(projExternalParam32, CV_32FC1);
//  //  projInterParam.convertTo(projInterParam32, CV_32FC1);
//  //  cv::Mat ptsImgWorld = projExternalParam32 * ptsMat;
//  //  cv::Mat ptsImgPlaneWorld = projInterParam32 * ptsImgWorld;

//  ptsImgPlaneWorld({ 0, 1 }, { 0, ptsImgPlaneWorld.cols }) =
//    ptsImgPlaneWorld({ 0, 1 }, { 0, ptsImgPlaneWorld.cols }) /
//    ptsImgPlaneWorld({ 2, 3 }, { 0, ptsImgPlaneWorld.cols });

//  ptsImgPlaneWorld({ 1, 2 }, { 0, ptsImgPlaneWorld.cols }) =
//    ptsImgPlaneWorld({ 1, 2 }, { 0, ptsImgPlaneWorld.cols }) /
//    ptsImgPlaneWorld({ 2, 3 }, { 0, ptsImgPlaneWorld.cols });

//  ptsImgPlaneWorld({ 0, 2 }, { 0, ptsImgPlaneWorld.cols }) =
//    ptsImgPlaneWorld({ 0, 2 }, { 0, ptsImgPlaneWorld.cols }) + 0.5;
//  cv::Mat indexMat;
//  ptsImgPlaneWorld({ 0, 2 }, { 0, ptsImgPlaneWorld.cols })
//    .convertTo(indexMat, CV_32SC1);
//  cv::Mat imgDepth = cv::Mat::zeros(imageHeight, imageWidth, CV_16UC1);
//  for (int i = 0; i < ptNum; i++) {
//    int row = indexMat.at<int>(1, i);
//    int col = indexMat.at<int>(0, i);
//    if (row < 0 || row >= imageHeight || col < 0 || col >= imageWidth)
//      continue;
//    float depth = ptsImgWorld.at<float>(2, i);
//    imgDepth.at<ushort>(row, col) = depth * scaleDepth;
//    //        int aa = depth * scaleDepth;
//    //        std::cout << aa << std::endl;
//  }
//  cv::swap(*depthImage, imgDepth);
//}

// void
// recon_3D_info(std::vector<cv::Mat>& imgList,
//               ReconstructRealTimeInputParam& reconstructParam,
//               pcl::PointCloud<pcl::PointXYZ>* cloud)
//{
//   esb::Profiler::Scoper timer(gProfiler, "recon3D");

//  {
//    float contrastParam = 0.3;
//    int maxProjectorValue = 255;
//    int channel = (imgList.size() - 2) / 2;
//    std::vector<cv::Mat> imgDiffList(channel);
//    std::vector<cv::Mat> imgBinList(channel);
//    Eigen::Tensor<float, 3> imgListTensor(
//      imgList[0].rows, imgList[0].cols, channel);
//    cv::Mat maskValid = (*(imgList.begin()) - *(imgList.begin() + 1)) >
//                        contrastParam * maxProjectorValue;
//    int index = 0;
//    {
//      esb::Profiler::Scoper timer(gProfiler, "gengerateImgList");

//      for (auto it = imgList.begin() + 2; it != imgList.end(); it++, it++) {
//        //二值
//        cv::Mat binMat = *(it) > *(it + 1);
//        imgBinList[index] = binMat;
//        index++;
//      }
//    }

//    // 解码
//    int codeLength = reconstructParam._codeLength;
//    cv::Mat imgCol(
//      imgBinList[0].rows, imgBinList[0].cols, CV_32SC1, cv::Scalar(-1));
//    {
//      esb::Profiler::Scoper timer(gProfiler, "decode");
//      decodeGrayCodeVector(imgBinList,
//                           reconstructParam._offsetGrayCode,
//                           maskValid,
//                           reconstructParam._codeLength,
//                           imgCol);
//    }
//    std::cout << 1 << std::endl;
//    imgDenoise(imgCol);
//    std::vector<FeatureNode> featureInfo;
//    {
//      esb::Profiler::Scoper timer(gProfiler, "extractFeature");
//      generate_feature_from_col_list2(
//        imgCol, reconstructParam._pairMat, imgList, featureInfo);
//    }
//    std::cout << 2 << std::endl;
//    int numFeature = featureInfo.size();
//    {
//      esb::Profiler::Scoper timer(gProfiler, "triangle");
//      line_plane_intersection_subpixel(featureInfo, reconstructParam, cloud);
//    }
//    std::cout << 3 << std::endl;
//    cloud->height = 1;
//    cloud->width = cloud->points.size();
//    cloud->is_dense = false;
//  }
//}
