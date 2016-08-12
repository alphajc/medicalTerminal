#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <Phonon>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QToolBar>
#include <QTime>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTextCodec>


class MusicPlaylist;

namespace Ui {
    class MusicWidget;
}

class MusicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWidget(QWidget *parent = 0);
    ~MusicWidget();

private slots:
    void updateTime(qint64 time);
    void setPaused();
    void skipBackward();
    void skipForward();
    void openFile();
    void setPlaylistShown();

    void stateChanged(Phonon::State newState, Phonon::State);

    void sourceChanged(const Phonon::MediaSource &source);
    void aboutToFinish();
    void metaStateChanged(Phonon::State newState, Phonon::State);
    void tableClicked(int row);
    void clearSources();

    void closeWindow();

private:
    Ui::MusicWidget *ui;
    void initPlayer();
    Phonon::MediaObject *mediaObject;
    QAction *playAction;
    QAction *stopAction;
    QAction *skipBackwardAction;
    QAction *skipForwardAction;
    QLabel *topLabel;
    QLabel *timeLabel;
    QPushButton *backBtn,*hideBtn;
    QHBoxLayout *topLayout;
    QVBoxLayout *mainLayout;

    MusicPlaylist *playlist;
    Phonon::MediaObject *metaInformationResolver;
    QList<Phonon::MediaSource> sources;
    void changeActionState();
};

#endif // MYWIDGET_H
