/*this class defines the panel used to input Chinese via Pingyin*/
#include "clicklabel.h"
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>

class ChnPanel:public QWidget
{
    Q_OBJECT
public:
    ChnPanel();
    ~ChnPanel();
    QLineEdit *chnLineEdit;
    ClickLabel *chnLabel[5];
    QToolButton *btnLeft;
    QToolButton *btnRight;
};
