#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QDebug>
#include "qtquick2applicationviewer.h"
#include "shuffler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qDebug() << "Hello Margareth";

    Shuffler shuffler;

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("Shuffler", &shuffler);
    viewer.setMainQmlFile(QStringLiteral("qml/Shuffl0rz/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
