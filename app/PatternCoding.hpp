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
}
