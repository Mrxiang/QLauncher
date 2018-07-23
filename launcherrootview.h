#ifndef LAUNCHERROOTVIEW_H
#define LAUNCHERROOTVIEW_H

#include <QXmlStreamReader>
#include <QString>
class LauncherRootView
{
public:
    int     width;
    int     height;
    QString  id;
    bool    fitsSystemWindows;
public:
    LauncherRootView();
    void parseLauncherRootViewXml(QString str, LauncherRootView    *launcherRootView);
    void parseLauncherRootView( QXmlStreamReader &reader,LauncherRootView    *launcherRootView);

};

#endif // LAUNCHERROOTVIEW_H
