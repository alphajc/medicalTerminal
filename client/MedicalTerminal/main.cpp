#include "loginwidget.h"
//#include "callKeyBoard.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    CallKeyBoard call;
//    a.setInputContext(&call);
    QTextCodec *code =  QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForTr(code);
   // if (!createConnection()) return 1;

    QPixmap pixmap(":/img/splash.jpg");
    QSplashScreen splash(pixmap);
    splash.show();

    LoginWidget w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
