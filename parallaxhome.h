#ifndef PARALLAXHOME_H
#define PARALLAXHOME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include "navibar.h"
 #define PAGE_COUNT 5
class ParallaxHome: public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene m_scene;
    NaviBar *m_naviBar;
    QGraphicsPixmapItem *m_wallpaper;
    QTimeLine m_pageAnimator;
    qreal m_pageOffset;
    QList<QGraphicsPixmapItem*> m_items;
    QList<QPointF> m_positions;
public:
    ParallaxHome(QWidget *parent = 0);
    void init();
signals:
    void pageChanged(int page);
public slots:
    void slideRight();
    void slideLeft();
    void slideBy(int dx);
    void choosePage(int page);
private slots:
    void shiftPage(int frame) ;
protected:
    void resizeEvent(QResizeEvent *event) ;
    void keyPressEvent(QKeyEvent *event) ;
private:
    void layoutScene() ;
    void setupScene() ;
};

#endif // PARALLAXHOME_H
