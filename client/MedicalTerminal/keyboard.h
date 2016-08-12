/*this class defines the virtual keyboard*/
#include "key.h"
#include "chnpanel.h"
#include <QWidget>

const static QString english[26]={"Q","W","E","R","T","Y","U","I","O","P",
                                  "A","S","D","F","G","H","J","K","L",
                                  "Z","X","C","V","B","N","M"};

const static QString number[26]={"0","1","2","3","4","5","6","7","8","9",
                                 "#","$","%","&&","=","+","-","*","/",
                                 "?","!",":",";","\"","(",")"};

class Keyboard:public QWidget
{
    Q_OBJECT
public:
    Keyboard();
    ~Keyboard();
    //
    ChnPanel *chnPanel;
    QWidget *keyBoard;
    //
    Key *key[26];
    //
    Key *keyShift;
    Key *keyDelete;
    Key *keyComma;
    Key *keyPeriod;
    Key *keyChaNum;
    Key *keyEngChn;
    Key *keySpace;
    Key *keyGo;
};
