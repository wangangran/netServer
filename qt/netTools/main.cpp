#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>

void load_css(QApplication& a)  {
    //…Ë÷√»´æ÷ Stylesheet
    QFile fd("./res/default.css");
    if (fd.open(QFile::ReadOnly)) {
        QString styleSheet = fd.readAll();
        a.setStyleSheet(styleSheet);
        fd.close();
    }
}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QCoreApplication::setApplicationName("HDSetUpgrade");
    QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::China));

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    load_css(a);
    MainWindow w;
    w.show();
    return a.exec();
}
