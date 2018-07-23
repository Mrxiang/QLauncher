#ifndef NAVIBAR_H
#define NAVIBAR_H


#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
class NaviBar : public QObject, public QGraphicsRectItem
{
   Q_OBJECT
public:
   NaviBar();
   void setPageOffset(qreal ofs);
signals:
   void pageSelected(int page);
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
private:
   QList<QGraphicsItem*> m_icons;
   QGraphicsRectItem *m_cursor;
};

#endif // NAVIBAR_H
