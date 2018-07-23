#include "imagebutton.h"

#include <QPainter>
#include <QDebug>
#include <QProcess>
ImageButton::ImageButton(QPixmap normal, QPixmap pressed, QWidget *parent):
        QAbstractButton(parent),m_normal(normal),m_pressed(pressed),m_bPressed(false)
{
    connect( this, SIGNAL(pressed()), this, SLOT(onPressed()));
    connect( this, SIGNAL(released()), this, SLOT(onReleased()));
    setAttribute( Qt::WA_NoSystemBackground);
}

void ImageButton::paintEvent(QPaintEvent *e){

    QPainter painter( this );
    painter.drawPixmap( rect(), m_bPressed? m_pressed: m_normal);
}

void ImageButton::onPressed(){
    qDebug()<<"onPressed"<<endl;
    m_bPressed = true;
    update();
}

void ImageButton::onReleased(){
    qDebug()<<"onReleased"<<endl;
    m_bPressed = false;
    update();

    QString program = "../TestXml/TestXml";
    QStringList arguments;
    //arguments << "-style" << "fusion";

    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, arguments);
}
