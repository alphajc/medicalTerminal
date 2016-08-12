#include "callKeyBoard.h"
#include <QDebug>
#include <QtCore>
#include <QWSServer>

CallKeyBoard::CallKeyBoard():QInputContext()
{
    im=new IMFrame();
    QWSServer::setCurrentInputMethod(im);
}

CallKeyBoard::~CallKeyBoard()
{
    delete im;
}
bool CallKeyBoard::filterEvent(const QEvent *event)
{
    if (event->type() == QEvent::RequestSoftwareInputPanel)
    {
        qDebug()<<"softkeyboard";
        im->kb->setVisible(true);
        return true;
    } else if (event->type() == QEvent::CloseSoftwareInputPanel) {
        im->kb->setVisible(false);
        return true;
    }
    return false;
}

QString CallKeyBoard::identifierName()
{
    return "CallKeyBoard";
}

void CallKeyBoard::reset()
{
}

bool CallKeyBoard::isComposing() const
{
    return false;
}

QString CallKeyBoard::language()
{
    return "en_US";
}



