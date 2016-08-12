#ifndef DAYARRANGEWIDGET_H
#define DAYARRANGEWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QTableView>
#include <QDebug>
#include <QSqlError>
#include <QMovie>

class QSqlTableModel;

namespace Ui {
class DayArrangeWidget;
}

class DayArrangeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DayArrangeWidget(QWidget *parent = 0);
    ~DayArrangeWidget();
    void openArrange();
    
private slots:

    void on_exitPushButton_clicked();

    void on_deletePushButton_clicked();

    void on_addPushButton_clicked();

private:
    Ui::DayArrangeWidget *ui;
    QSqlTableModel *model;
};

#endif // DAYARRANGEWIDGET_H
