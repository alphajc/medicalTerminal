#ifndef PATIENTSELECT_H
#define PATIENTSELECT_H

#include <QWidget>
#include <clientdatabase.h>

#include "communication.h"
#include "sendinformation.h"

namespace Ui {
class PatientSelect;
}

class PatientSelect : public QWidget
{
    Q_OBJECT
    
public:
    explicit PatientSelect(QWidget *parent = 0);
    ~PatientSelect();
    void setPatientName();
    void init();
    void set_connection();
    
private:
    Ui::PatientSelect *ui;
    ClientDataBase *db;
    int selectLineEdit;
private slots:
    void otherThingsLook(QString nowName);
    void on_returnButton_clicked();
    void on_commitButton_clicked();
    bool eventFilter(QObject *,QEvent *);
    void setLineEdit();
};

#endif // PATIENTSELECT_H
