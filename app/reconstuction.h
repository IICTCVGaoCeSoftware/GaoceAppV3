#ifndef RECONSTUCTION_H
#define RECONSTUCTION_H

#include <QWidget>

namespace Ui {
class Reconstuction;
}

class Reconstuction : public QWidget
{
  Q_OBJECT

    public:
             explicit Reconstuction(QWidget *parent = nullptr);
  ~Reconstuction();

private:
  Ui::Reconstuction *ui;
};

#endif // RECONSTUCTION_H
