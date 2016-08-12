#ifndef PATIENTINFO_H
#define PATIENTINFO_H

#include <QWidget>
#include <QString>
#include "sendinformation.h"

namespace Ui {
class PatientInfo;
}

class PatientInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PatientInfo(QWidget *parent = 0);
    ~PatientInfo();
    void create_connection();
    void init_widget();
    void set_record(QString record);

private slots:
    void sendMessage();
    void on_exitButton_clicked();
    bool eventFilter(QObject *,QEvent *);
    void setLineEdit();

private:
    Ui::PatientInfo     *ui;
    QString             message;
    SendInformation     *infor;
    QString             record;
    int selectLineEdit;
};

#endif // PATIENTINFO_H
