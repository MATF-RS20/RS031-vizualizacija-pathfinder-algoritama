#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QMouseEvent>
#include <QPushButton>

class QRightClickButton : public QPushButton
{
    Q_OBJECT

  public:
    explicit QRightClickButton(QWidget *parent = 0);

  private slots:
    void mousePressEvent(QMouseEvent *e);

  signals:
    void rightClicked();
    void middleClicked();

  public slots:
};

#endif // QRIGHTCLICKBUTTON_H
