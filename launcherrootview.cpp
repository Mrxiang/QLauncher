#include "launcherrootview.h"
#include <QFile>
#include <QDebug>

LauncherRootView::LauncherRootView():width(0),height(0),fitsSystemWindows(true){

}

void LauncherRootView::parseLauncherRootViewXml(QString str, LauncherRootView    *launcherRootView){

    QFile file(str);
    bool  flag =  file.open(QIODevice::ReadOnly |QIODevice::Text);

    qDebug()<<"open file "<<flag<<endl;
    if( flag ){
        QXmlStreamReader reader( &file );

        while( !reader.atEnd() ){
            QXmlStreamReader::TokenType nType = reader.readNext();
            qDebug()<<"TokenType"<< nType<<endl;
            if( nType == QXmlStreamReader::StartElement){
                parseLauncherRootView(reader, launcherRootView);
            }
        }
        if (reader.hasError()) {  // 解析出错
            qDebug() << QString::fromLocal8Bit("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
        }
        file.close();  // 关闭文件
    }
    return ;
}

void LauncherRootView::parseLauncherRootView( QXmlStreamReader &reader,LauncherRootView    *launcherRootView){
    qDebug() << QString::fromLocal8Bit("********** parseLauncherRootView ********** ");
    while (!reader.atEnd()) {

        if (reader.isStartElement()) {  // 开始元素
            QString strElementName = reader.name().toString();
            qDebug() << QString::fromLocal8Bit("********** 开始元素<%1> ********** ").arg(strElementName);
            if (QString::compare(strElementName, "com.qt.launcher.LauncherRootView") == 0) {
                QXmlStreamAttributes attributes = reader.attributes();
                for (int i = 0; i < attributes.size(); ++i) {

                   QXmlStreamAttribute  attribute = attributes.at(i);
                   QString sName = attribute.name().toString();
                   QString sValue = attribute.value().toString();
                   qDebug()<<i<<" "<<attribute.name()<<":"<<attribute.value()<<endl;
                   if (QString::compare(sName,"id")==0) {  // 存在属性 Version
                       QString  sId= sValue;
                       qDebug() << "id : " << sId;
                       launcherRootView->id = sId;
                   }else if (QString::compare(sName,"layout_width")==0) {  // 存在属性 Version
                       QString  sWidth= sValue;
                       qDebug() << "width : " << sWidth;
                       launcherRootView->width = sWidth.toInt();
                   }else if (QString::compare(sName,"layout_height")==0) {  // 存在属性 Version
                       QString  sHeight= sValue;
                       qDebug() << "height : " << sHeight;
                       launcherRootView->height = sHeight.toInt();
                   }else if (QString::compare(sName,"fitsSystemWindows")==0) {  // 存在属性 Version
                       QString  sFitsSystemWindows= sValue;
                       qDebug() << "fitsSystemWindows : " << sFitsSystemWindows;
                       QString::compare(sFitsSystemWindows, "true")==0 ?
                                   launcherRootView->fitsSystemWindows = true :
                                    launcherRootView->fitsSystemWindows = false;
                   }
                }

                break;
            }
        }else if (reader.isEndElement()) {  // 结束元素
            QString strElementName = reader.name().toString();
            qDebug() << QString::fromLocal8Bit("********** 结束元素<%1> ********** ").arg(strElementName);
            if (QString::compare(strElementName, "Blogs") == 0) {
                qDebug() << QString::fromLocal8Bit("********** 结束元素<Blogs> ********** ");
                break;  // 跳出循环（解析 QXmlStreamReader::EndDocument）
            }
        }
        reader.readNext();
    }

}
