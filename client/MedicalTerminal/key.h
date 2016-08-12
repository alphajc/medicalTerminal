/*this class defines the key of the keyboard, including set text, size and font*/
#include <QToolButton>

class Key:public QToolButton
{
    Q_OBJECT
public:
    Key(QString name,int w,int h);
    ~Key();
};
