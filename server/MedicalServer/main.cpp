#include "mainwidget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *code = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForTr(code);

    MainWidget w ;
    w.show();

    return a.exec();
}
