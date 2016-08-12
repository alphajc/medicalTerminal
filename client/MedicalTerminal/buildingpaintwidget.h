#ifndef BUILDINGPAINTWIDGET_H
#define BUILDINGPAINTWIDGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class BuildingPaintWidget;
}

class BuildingPaintWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit BuildingPaintWidget(QWidget *parent = 0);
    ~BuildingPaintWidget();
    void initBuilding();
protected:
    void paintEvent(QPaintEvent *);
    
private:
    Ui::BuildingPaintWidget *ui;
};

#endif // BUILDINGPAINTWIDGET_H
