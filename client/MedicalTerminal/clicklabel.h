/*this class providing mouse click event inherits QLabel*/
#include <QLabel>

class ClickLabel:public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QString name,QWidget *parent = 0);
    virtual ~ClickLabel();
private:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    bool status;
signals:
    void clicked();
};
