#include "im.h"
#include <QInputContext>
#include <QWSInputMethod>

class CallKeyBoard:public QInputContext
{
public:
    CallKeyBoard();
    ~CallKeyBoard();
    bool filterEvent(const QEvent *event);
    QString identifierName();
    QString language();
    bool isComposing() const;
    void reset();
private:
    IMFrame *im;
};
