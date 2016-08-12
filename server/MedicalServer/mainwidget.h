#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QTableWidget>
#include <QtNetwork>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QMessageBox>
#include <QModelIndex>
#include <QVariant>

#include "serverdatabase.h"
#include "ui_mainwidget.h"
#include "fortuneserver.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void init_socket();
    void set_connection();
    void init_widget();
    void update_patient_tab();
    void update_doctor_tab();

private:
    Ui::MainWidget              *ui;
    QSqlTableModel              *patientModel;
    QSqlTableModel              *doctorModel;
    QSqlTableModel              *model;
    ServerDataBase              *db;
    QTableView                  *tableView;
    FortuneServer               *server;

private slots:
    void on_newPushButton_clicked();
    void on_selectPushButton_clicked();
    void on_deletePushButton_clicked();
    void on_notUpdatePushButton_clicked();
    void on_submitPushButton_clicked();
    void on_addPushButton_clicked();
    void on_upPushButton_clicked();
    void on_downPushButton_clicked();
    void tab_changed(int);
};

#endif // MAINWIDGET_H
