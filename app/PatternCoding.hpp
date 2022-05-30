#pragma once
#include "GaoCe.hpp"

/**
 * @brief 图案编码选择窗口
 */
class PatternCoding : public QWidget
{
  Q_OBJECT

  using _T = PatternCoding;
  using _S = QWidget;

public:
  PatternCoding(GaoCe::GaoCe& algo, QWidget* parent = nullptr);

private:
  struct CalibOutputParam
  {
    cv::Mat _camOriPt;             //  相机原点
    cv::Mat _dirLineVectors;       // 相机直线的方向向量
    cv::Mat _internalCamParamMat;  // 相机内参
    cv::Mat _externalPlaneMat;     // 投影仪面方程信息
    cv::Mat _externalProjParamMat; // 投影仪外参
    cv::Mat _internalProjParamMat; //  投影仪内参
  };

public:
  //点击标定按钮，得到相机像素对应的射线，投影仪的面方程
  void rays_palnes(cv::Size camResolution, //输入，相机的分辨率
                   CV_OUT CalibOutputParam* calibOutputParam);

private:
  GaoCe::GaoCe& _algo;
  QGroupBox *_codingPattern, *_patternType, *_offset;
  QRadioButton *_grayButton, *_binaryButton;
  QRadioButton *_rowButton, *_colButton, *_slashButton;
  QSpinBox *_offset1, *_offset2, *_offset3;
  QPushButton* _calButton;
};
