#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include "qopenglitem.h"
#include <QApplication>
#include <QQmlContext>
#include <QtQuickWidgets/QQuickWidget>
#include <QOpenGLWidget>
#include <QQuickView>
#include <QMainWindow>








int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qmlRegisterType<QOpenGLItem>("MyQOpenGL",1,0,"QOpenGLItem");

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QMainWindow frame;
    frame.setWindowTitle("LALLALALALL");
    QQuickWidget *central = new QQuickWidget();
    central->setMinimumSize(QSize(1280,768));
    frame.setCentralWidget(central);


//    QQuickView *view = new QQuickView;
//    view->setSource(QUrl(QLatin1String("qrc:/main.qml")));
//    view->setMinimumSize(QSize(1280,768));

//    QWidget *wview = QWidget::createWindowContainer(view,central,Qt::Widget);
//    wview->setMinimumSize(QSize(1280,768));
    QQuickWidget *qqwidget = new QQuickWidget(central);
    qqwidget->setSource(QUrl(QLatin1String("qrc:/main.qml")));

    //QSurfaceFormat fmt=qqwidget->format();
    //fmt.setSamples(8);
    frame.show();

    return app.exec();
}
