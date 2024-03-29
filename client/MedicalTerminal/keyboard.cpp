#include "keyboard.h"
#include <QHBoxLayout>

Keyboard::Keyboard():QWidget(0,Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint)
{
    chnPanel=new ChnPanel();
    chnPanel->setParent(this);
    chnPanel->setGeometry(0,0,240,60);
    //
    int i;
    for(i=0;i<26;i++)
    {
        key[i]=new Key(english[i],20,25);
    }
    //
    keyShift=new Key(tr("SFT"),28,25);
    keyDelete=new Key(tr("DEL"),28,25);
    keyComma=new Key(tr(","),20,25);
    keyPeriod=new Key(tr("."),20,25);
    keyChaNum=new Key(tr(".?123"),38,25);
    keyEngChn=new Key(tr("CHN"),28,25);
    keySpace=new Key(tr("SPACE"),82,25);
    keyGo=new Key(tr("CLOSE"),28,25);
    //
    QHBoxLayout *layout1=new QHBoxLayout();
    layout1->setSpacing(4);
    layout1->setContentsMargins(0,5,0,0);
    layout1->addStretch();
    for(i=0;i<10;i++)
    {
        layout1->addWidget(key[i]);
    }
    layout1->addStretch();
    //
    QHBoxLayout *layout2=new QHBoxLayout();
    layout2->setSpacing(4);
    layout2->setContentsMargins(0,0,0,0);
    layout2->addStretch();
    for(i=10;i<19;i++)
    {
        layout2->addWidget(key[i]);
    }
    layout2->addStretch();
    //
    QHBoxLayout *layout3=new QHBoxLayout();
    layout3->setSpacing(4);
    layout3->setContentsMargins(5,0,5,0);
    layout3->addWidget(keyShift);
    layout3->addStretch();
    for(i=19;i<26;i++)
    {
        layout3->addWidget(key[i]);
    }
    layout3->addStretch();
    layout3->addWidget(keyDelete);
    //
    QHBoxLayout *layout4=new QHBoxLayout();
    layout4->setSpacing(4);
    layout4->setContentsMargins(0,0,0,0);
    layout4->addStretch();
    layout4->addWidget(keyChaNum);
    layout4->addWidget(keyEngChn);
    layout4->addWidget(keyComma);
    layout4->addWidget(keySpace);
    layout4->addWidget(keyPeriod);
    layout4->addWidget(keyGo);
    layout4->addStretch();
    //
    QVBoxLayout *layoutKeyboard=new QVBoxLayout();
    layoutKeyboard->setSpacing(5);
    layoutKeyboard->setContentsMargins(0,0,0,0);
    layoutKeyboard->addLayout(layout1);
    layoutKeyboard->addLayout(layout2);
    layoutKeyboard->addLayout(layout3);
    layoutKeyboard->addLayout(layout4);
    keyBoard=new QWidget(this);
    keyBoard->setLayout(layoutKeyboard);
    keyBoard->setGeometry(0,0,240,140);
    //
    setCursor(QCursor(Qt::BlankCursor));
    setGeometry(0,180,240,140);
    setObjectName(QString::fromUtf8("KEYBOARD"));
    //
    setVisible(true);
}

Keyboard::~Keyboard()
{
}
