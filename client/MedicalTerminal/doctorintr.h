#ifndef DOCTORINTR_H
#define DOCTORINTR_H

#include <QWidget>
#include "sendinformation.h"
#include <QString>


namespace Ui {
class DoctorIntr;
}

class DoctorIntr : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorIntr(QWidget *parent = 0);
    ~DoctorIntr();
    void create_connection();
    void init_widget();

private slots:
    void on_doctorEnterPushButton_clicked();

    void on_doctorReturnPushButton_clicked();

private:
    Ui::DoctorIntr      *ui;
    SendInformation *infor;
    QString                 message;
};

#endif // DOCTORINTR_H
