#include "PatternCoding.hpp"

PatternCoding::PatternCoding(GaoCe::GaoCe& algo, QWidget* parent)
  : _S(parent)
  , _algo(algo)

{
  _codingPattern = new QGroupBox();
  _patternType = new QGroupBox();
  _offset = new QGroupBox();
  _codingPattern->setTitle("设置编码格式");
  _patternType->setTitle("设置投影图案类型");
  _offset->setTitle("设置偏移");

  _grayButton = new QRadioButton("格雷码");
  _grayButton->setChecked(true);
  _binaryButton = new QRadioButton("二进制码");
  auto vlayout1 = new QVBoxLayout();
  vlayout1->addWidget(_grayButton);
  vlayout1->addWidget(_binaryButton);
  _codingPattern->setLayout(vlayout1);

  _rowButton = new QRadioButton("行");
  _colButton = new QRadioButton("列");
  _colButton->setChecked(true);
  _slashButton = new QRadioButton("斜线");
  auto vlayout2 = new QVBoxLayout();
  vlayout2->addWidget(_rowButton);
  vlayout2->addWidget(_colButton);
  vlayout2->addWidget(_slashButton);
  _patternType->setLayout(vlayout2);

  _offset1 = new QSpinBox();
  _offset1->setPrefix("偏移值");
  _offset2 = new QSpinBox();
  _offset2->setPrefix("偏移值");
  _offset2->setValue(2);
  _offset3 = new QSpinBox();
  _offset3->setPrefix("偏移值");
  auto vlayout3 = new QVBoxLayout();
  vlayout3->addWidget(_offset1);
  vlayout3->addWidget(_offset2);
  vlayout3->addWidget(_offset3);
  _offset->setLayout(vlayout3);

  auto finalLayout = new QHBoxLayout();
  finalLayout->addWidget(_codingPattern);
  finalLayout->addWidget(_patternType);
  finalLayout->addWidget(_offset);

  _calButton = new QPushButton();
  _calButton->setText("标定");
  finalLayout->addWidget(_calButton);
  setLayout(finalLayout);

  // 连接信号
  connect(_calButton, &QPushButton::clicked, this, &_T::on_calButton_clicked);
}

void
PatternCoding::on_calButton_clicked()
{
  //_algo.rays_palnes()
  _algo.rays_palnes(&_algo._calibOutputParam);
}
