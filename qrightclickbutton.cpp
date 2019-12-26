#include "qrightclickbutton.h"

//klasa koja nasledjuje QPushButton
//jedina razlika je drugacije implementiran mousePressEvent
QRightClickButton::QRightClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

//override mousePressEvent tako da salje razlicite signale
//pritiskom na levi ili desni klik
void QRightClickButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked();
    else if(e->button()==Qt::LeftButton)
        emit released();
}
