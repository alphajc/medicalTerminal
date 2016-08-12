#include "key.h"

Key::Key(QString name,int w,int h):QToolButton()
{
    setText(name);
    setFixedSize(w,h);
    setObjectName(QString::fromUtf8("KEYBOARD"));
}

Key::~Key()
{
}
