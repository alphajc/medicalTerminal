/*this class inherits QWSInputMethod*/
#include "keyboard.h"
#include <QWSInputMethod>
#include <QSignalMapper>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRecord>
#include <QWSServer>

class IMFrame:public QWSInputMethod
{
Q_OBJECT
public:
        IMFrame();
        ~IMFrame();
	void showKeyboard(bool flag);
        Keyboard *kb;
private:
               /*virtual keyboard*/
        //
        QSignalMapper *mapper;
        //
        bool shift; /*indicate input capital letter or small letter*/
        bool num;   /*indicate input character or number&punctuation*/
        bool chn;   /*indicate input English or Chinese*/
        //
        int pageCount;
        int currentPage;
        //
        QString chinese[128];
        QSqlTableModel *model;
        //
        void setMapping();
        void setConnect();
        void listChn();
        //
private slots:
        void sendContent(const QString&);
        void setShift();
        void setChaNum();
        void setEngChn();
        void transPy(const QString &text);
        void turnLeft();
        void turnRight();
};
