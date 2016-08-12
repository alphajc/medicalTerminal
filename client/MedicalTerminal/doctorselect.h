#ifndef DOCTORSELECT_H
#define DOCTORSELECT_H

#include <QWidget>
#include <clientdatabase.h>
#include <QStringList>

#include "communication.h"
namespace Ui {
class DoctorSelect;
}

class DoctorSelect : public QWidget
{
    Q_OBJECT
    
public:
    explicit DoctorSelect(QWidget *parent = 0);
    ~DoctorSelect();
     void setDoctorName();
     void init();
    
private slots:
    void on_doctorReturnPushButton_clicked();
    void otherDoctorThingsLook(QString nowName);

private:
    Ui::DoctorSelect *ui;
    ClientDataBase *db;
};

#endif // DOCTORSELECT_H
