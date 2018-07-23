#include "navibar.h"

#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#define ICON_SIZE 50
#define ICON_PAD 4
NaviBar::NaviBar()
       : QGraphicsRectItem()
{
   setRect(0, 0, 5 * ICON_SIZE, ICON_SIZE);
   setPen(Qt::NoPen);
   QStringList names;
   names << "1" << "2" << "3" << "4" << "5";
   for (int i = 0; i < names.count(); ++i) {
       QString fname = names[i];
       fname.prepend(":/res/images/ind");
       fname.append(".png");
       QGraphicsPixmapItem *icon = new QGraphicsPixmapItem(fname);
       icon->setParentItem(this);
       const int dim = ICON_SIZE - ICON_PAD * 2;
       qreal sw = dim / icon->boundingRect().width();
       qreal sh = dim / icon->boundingRect().height();
       icon->setTransform(QTransform().scale(sw, sh));
       icon->setZValue(2);
       m_icons << icon;
   }
   m_cursor = new QGraphicsRectItem;
   m_cursor->setParentItem(this);
   m_cursor->setRect(0, 0, ICON_SIZE, ICON_SIZE);
   m_cursor->setZValue(1);
   m_cursor->setPen(Qt::NoPen);
   m_cursor->setBrush(QColor(Qt::white));
   m_cursor->setOpacity(0.6);
}
void NaviBar::setPageOffset(qreal ofs)
{
   m_cursor->setPos(ofs * ICON_SIZE, 0);
   for (int i = 0; i < m_icons.count(); ++i) {
       int y = (i == static_cast<int>(ofs + 0.5)) ? ICON_PAD : ICON_PAD * 2;
       m_icons[i]->setPos(i * ICON_SIZE + ICON_PAD, y);
       m_icons[i]->setOpacity(1);
   }
}
void NaviBar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   emit pageSelected(static_cast<int>(event->pos().x() / ICON_SIZE));
}
void NaviBar::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setBrush(Qt::white);
   painter->setOpacity(0.2);
   painter->drawRect(option->rect.adjusted(-20, ICON_PAD, 20, 0));
}
