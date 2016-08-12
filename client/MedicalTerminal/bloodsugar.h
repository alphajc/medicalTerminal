#ifndef BLOODSUGAR_H
#define BLOODSUGAR_H

#include <QWidget>

namespace Ui {
class BloodSugar;
}

class BloodSugar : public QWidget
{
    Q_OBJECT

public:
    explicit BloodSugar(QWidget *parent = 0);
    ~BloodSugar();
    void create_connection();

private:
    Ui::BloodSugar *ui;
};

#endif // BLOODSUGAR_H
