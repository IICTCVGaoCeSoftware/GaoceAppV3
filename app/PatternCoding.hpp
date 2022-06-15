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
  GaoCe::GaoCe& _algo;
  QGroupBox *_codingPattern, *_patternType, *_offset;
  QRadioButton *_grayButton, *_binaryButton;
  QRadioButton *_rowButton, *_colButton, *_slashButton;
  QSpinBox *_offset1, *_offset2, *_offset3;
  QPushButton* _calButton;

private slots:
  void on_calButton_clicked();
};
