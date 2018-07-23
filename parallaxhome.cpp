#include "parallaxhome.h"

#include <QKeyEvent>
#include <QTime>
#include <QDebug>
#include <QGridLayout>
#include "imagebutton.h"
#include "launcherrootview.h"
ParallaxHome::ParallaxHome(QWidget *parent)
            : QGraphicsView(parent)
            , m_pageOffset(-2) {
        init();
        setupScene();
        setScene(&m_scene);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFrameShape(QFrame::NoFrame);
        setWindowTitle("QLauncher");
        connect(&m_pageAnimator, SIGNAL(frameChanged(int)), SLOT(shiftPage(int)));
        m_pageAnimator.setDuration(500);
        m_pageAnimator.setFrameRange(0, 100);
        m_pageAnimator.setCurveShape(QTimeLine::EaseInCurve);
        pageChanged(static_cast<int>(m_pageOffset));
}

void ParallaxHome::slideRight() {
        if (m_pageAnimator.state() != QTimeLine::NotRunning)
            return;
        int edge = -(m_pageOffset - 1);
        if (edge < PAGE_COUNT)
            slideBy(-1);
}
void ParallaxHome::slideLeft() {
        if (m_pageAnimator.state() != QTimeLine::NotRunning)
            return;
        if (m_pageOffset < 0)
            slideBy(1);
}
void ParallaxHome::slideBy(int dx) {
        int start = m_pageOffset * 1000;
        int end = (m_pageOffset + dx) * 1000;
        m_pageAnimator.setFrameRange(start, end);
        m_pageAnimator.start();
}
void ParallaxHome::choosePage(int page) {
        if (m_pageAnimator.state() != QTimeLine::NotRunning)
            return;
        if (static_cast<int>(-m_pageOffset) == page)
            return;
        slideBy(-page - m_pageOffset);
}
void ParallaxHome::shiftPage(int frame) {
        int ww = width();
        int hh = height() - m_naviBar->rect().height();
        int oldPage = static_cast<int>(-m_pageOffset);
        m_pageOffset = static_cast<qreal>(frame) / qreal(1000);
        int newPage = static_cast<int>(-m_pageOffset);
        m_naviBar->setPageOffset(-m_pageOffset);
        if (oldPage != newPage)
            emit pageChanged(newPage);
        int ofs = m_pageOffset * ww;
        for (int i = 0; i < m_items.count(); ++i) {
            QPointF pos = m_positions[i];
            QPointF xy(pos.x() * ww, pos.y() * hh);
            m_items[i]->setPos(xy + QPointF(ofs, 0));
        }
        int center = m_wallpaper->pixmap().width() / 2;
        const int parallax = 3;
        int base = center - (ww / 2) - (PAGE_COUNT >> 1) * (ww / parallax);
        int wofs = base - m_pageOffset * ww / parallax;
        m_wallpaper->setPos(-wofs, 0);
}
void ParallaxHome::resizeEvent(QResizeEvent *event) {
        Q_UNUSED(event);
        layoutScene();
}
void ParallaxHome::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Right)
            slideRight();
        if (event->key() == Qt::Key_Left)
            slideLeft();
        event->accept();
}
void ParallaxHome::layoutScene() {
        qDebug()<<"layoutScene"<<endl;
        int ww = width();
        int hh = height();
        m_scene.setSceneRect(0, 0, PAGE_COUNT * ww - 1, hh - 1);
        qDebug()<<"width"<<ww<<"height"<<hh<<endl;
        centerOn(ww / 2, hh / 2);
        int nw = m_naviBar->rect().width();
        int nh = m_naviBar->rect().height();
        m_naviBar->setPos((ww - nw) / 2, hh - nh);
        shiftPage(m_pageOffset * 1000);
}

void ParallaxHome::init( ){
        qDebug() <<"begin pares xml"<<endl;
        LauncherRootView *launcherRootView = new LauncherRootView();
        launcherRootView->parseLauncherRootViewXml("../QLauncher/res/xml/launcher.xml", launcherRootView);
        qDebug() <<"end pares xml"<<endl;

        //this->setFixedSize(launcherRootView->width, launcherRootView->height);
        this->resize(launcherRootView->width, launcherRootView->height);
}

void ParallaxHome::setupScene() {
        qDebug()<<"setupScene"<<endl;
        qsrand(QTime::currentTime().second());

        for(int i =0; i<PAGE_COUNT; i++){

            QWidget     *mWidget     = new QWidget( );
            QGridLayout *mGridLayout = new QGridLayout() ;
            ImageButton  *mButton[9];
            for( int i=0; i<3;  i++){
                for( int j =0; j <3; j++){
                    mButton[i*3+j]   = new ImageButton(QPixmap(":/res/images/ic_launcher_email.png"),
                                                QPixmap(":/res/images/sym_def_app_icon.png")  );
                    mButton[i*3+j]->setFixedSize(72, 72);
                    mGridLayout->addWidget( mButton[i*3+j], i, j);
                }
            }
            mWidget->setLayout( mGridLayout );
            mWidget->resize(480,720);
            m_scene.addWidget( mWidget );
        }
        m_naviBar = new NaviBar();
        m_scene.addItem(m_naviBar);
        m_naviBar->setZValue(2);
        connect(m_naviBar, SIGNAL(pageSelected(int)), SLOT(choosePage(int)));
        m_wallpaper = m_scene.addPixmap(QPixmap(":/icons/surfacing.png"));
        m_wallpaper->setZValue(0);
        m_scene.setItemIndexMethod(QGraphicsScene::NoIndex);
}
