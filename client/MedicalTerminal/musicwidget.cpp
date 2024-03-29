#include "musicwidget.h"
#include "ui_musicwidget.h"
#include "musicplaylist.h"
#include <QMovie>


MusicWidget::MusicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicWidget)
{
    ui->setupUi(this);
    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/bg01.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);
    QMovie * movie=new QMovie(this);
    ui->musicLabel->setMovie(movie);
    movie->start();
    initPlayer();
}

MusicWidget::~MusicWidget()
{
    delete ui;
}

void MusicWidget::initPlayer()
{
    setWindowFlags(Qt::FramelessWindowHint);

    // 创建媒体图
    mediaObject = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);

    // 关联媒体对象的tick()信号来更新播放时间的显示
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(updateTime(qint64)));

    // 创建顶部标签，用于显示一些信息
    topLabel = new QLabel(tr("musicplayer"));
//    topLabel->setTextFormat(Qt::RichText);
    topLabel->setFont(QFont("times",15,QFont::Bold));
    topLabel->setAlignment(Qt::AlignCenter);

    // 创建控制播放进度的滑块
    Phonon::SeekSlider *seekSlider = new Phonon::SeekSlider(mediaObject, this);

    QToolBar *widgetBar = new QToolBar(this);
    // 显示播放时间的标签
    timeLabel = new QLabel(tr("00:00 / 00:00"), this);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 音量控制部件
    Phonon::VolumeSlider *volumeSlider = new Phonon::VolumeSlider(audioOutput, this);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // 添加到工具栏
    widgetBar->addWidget(volumeSlider);
    widgetBar->addSeparator();
    widgetBar->addWidget(timeLabel);

    // 创建播放控制动作工具栏
    QToolBar *toolBar = new QToolBar(this);
    // 播放动作
    playAction = new QAction(this);
    playAction->setIcon(QIcon(":/img/play.png"));
    playAction->setText(tr("播放"));
    connect(playAction, SIGNAL(triggered()), this, SLOT(setPaused()));
    // 停止动作
    stopAction = new QAction(this);
    stopAction->setIcon(QIcon(":/img/stop.png"));
    stopAction->setText(tr("停止"));
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));
    // 跳转到上一首动作
    skipBackwardAction = new QAction(this);
    skipBackwardAction->setIcon(QIcon(":/img/skipBackward.png"));
    skipBackwardAction->setText(tr("上一首"));
    connect(skipBackwardAction, SIGNAL(triggered()), this, SLOT(skipBackward()));
    // 跳转到下一首动作
    skipForwardAction = new QAction(this);
    skipForwardAction->setIcon(QIcon(":/img/skipForward.png"));
    skipForwardAction->setText(tr("下一首"));
    connect(skipForwardAction, SIGNAL(triggered()), this, SLOT(skipForward()));

    // 创建图标，用于控制是否显示播放列表
    QAction *PLAction = new QAction(this);
    PLAction->setIcon(QIcon(":/img/list_22px_1175613_easyicon.net.png"));
    connect(PLAction, SIGNAL(triggered()), this, SLOT(setPlaylistShown()));

    // 打开文件动作
    QAction *openAction = new QAction(this);
    openAction->setIcon(QIcon(":/img/files_22px_1163352_easyicon.net.png"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    // 添加到工具栏
    toolBar->addAction(stopAction);
    toolBar->addSeparator();
    toolBar->addAction(skipBackwardAction);
    toolBar->addSeparator();
    toolBar->addAction(playAction);
    toolBar->addSeparator();
    toolBar->addAction(skipForwardAction);
    toolBar->addSeparator();
    toolBar->addAction(PLAction);
    toolBar->addAction(openAction);


    backBtn = new QPushButton();
    backBtn->setIcon(QIcon(QPixmap(":/img/music_back.png")));
    backBtn->setFlat(true);
    backBtn->setIconSize(QSize(36,36));
    hideBtn = new QPushButton();
    hideBtn->setIcon(QIcon(QPixmap(":/img/music_hidden.png")));
    hideBtn->setIconSize(QSize(36,36));
    hideBtn->setFlat(true);
    topLayout = new QHBoxLayout;
    topLayout->addWidget(backBtn);
    topLayout->addStretch();
    topLayout->addWidget(hideBtn);

    connect(backBtn,SIGNAL(clicked(bool)),this,SLOT(closeWindow()));
    connect(hideBtn,SIGNAL(clicked(bool)),this,SLOT(hide()));

    // 创建主界面布局管理器

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addStretch(2);
    mainLayout->addWidget(topLabel);
    mainLayout->addStretch(1);
    mainLayout->addWidget(seekSlider);
    mainLayout->addStretch(1);
    mainLayout->addWidget(widgetBar);
    mainLayout->addWidget(toolBar);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(mediaObject, SIGNAL(stateChanged(Phonon::State, Phonon::State)),
            this, SLOT(stateChanged(Phonon::State, Phonon::State)));

    // 创建播放列表
    playlist = new MusicPlaylist(this);
    connect(playlist, SIGNAL(cellClicked(int, int)), this, SLOT(tableClicked(int)));
    connect(playlist, SIGNAL(playlistClean()), this, SLOT(clearSources()));

    // 创建用来解析媒体的信息的元信息解析器
    metaInformationResolver = new Phonon::MediaObject(this);
    // 需要与AudioOutput连接后才能使用metaInformationResolver来获取歌曲的总时间
    Phonon::AudioOutput *metaInformationAudioOutput =
            new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(metaInformationResolver, metaInformationAudioOutput);
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State, Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State, Phonon::State)));

    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    // 初始化动作图标的状态
    playAction->setEnabled(false);
    stopAction->setEnabled(false);
    skipBackwardAction->setEnabled(false);
    skipForwardAction->setEnabled(false);
}

// 更新timeLabel标签显示的播放时间
void MusicWidget::updateTime(qint64 time)
{
    qint64 totalTimeValue = mediaObject->totalTime();
    QTime totalTime(0, (totalTimeValue / 60000) % 60, (totalTimeValue / 1000) % 60);
    QTime currentTime(0, (time / 60000) % 60, (time / 1000) % 60);
    QString str = currentTime.toString("mm:ss") + " / " + totalTime.toString("mm:ss");
    timeLabel->setText(str);
}

// 播放或者暂停
void MusicWidget::setPaused()
{
    // 如果先前处于播放状态，那么暂停播放;否则，开始播放
    if (mediaObject->state() == Phonon::PlayingState)
        mediaObject->pause();
    else
        mediaObject->play();
}

// 播放上一首，与skipBackwardAction动作的触发信号关联
void MusicWidget::skipBackward()
{
    int index = sources.indexOf(mediaObject->currentSource());
    mediaObject->setCurrentSource(sources.at(index - 1));
    mediaObject->play();
}

// 播放下一首，与skipForwardAction动作的触发信号关联
void MusicWidget::skipForward()
{
    int index = sources.indexOf(mediaObject->currentSource());
    mediaObject->setCurrentSource(sources.at(index + 1));
    mediaObject->play();
}

// 打开文件，与openAction动作的触发信号关联
void MusicWidget::openFile()
{
//    QFileDialog fd(this,"select musics");
//    fd.resize(240,320);
//    fd.setAcceptMode(QFileDialog::AcceptOpen);
//    fd.setNameFilter("Music (*.mp3 *.wmv *.wma)");
//    fd.exec();
//    // 从系统音乐目录打开多个音乐文件
//    QStringList list = fd.selectedFiles();
    QFileDialog fd;
//    fd.resize(240,320);
    QStringList list = fd.getOpenFileNames(this,tr("select musics"),
                                      QDesktopServices::storageLocation(QDesktopServices::MusicLocation),
                                                     "Music (*.mp3 *.wma)");
    if (list.isEmpty())
        return;
    // 获取当前媒体源列表的大小
    int index = sources.size();
    // 将打开的音乐文件添加到媒体源列表后
    foreach (QString string, list) {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
    // 如果媒体源列表不为空，则将新加入的第一个媒体源作为当前媒体源，
    // 这时会发射stateChanged()信号，从而调用metaStateChanged()函数进行媒体源的解析
    if (!sources.isEmpty())
        metaInformationResolver->setCurrentSource(sources.at(index));
}

// 显示或者隐藏播放列表，与PLAction动作的触发信号关联
void MusicWidget::setPlaylistShown()
{
//    if (playlist->isHidden()) {
//        playlist->move(frameGeometry().bottomLeft());
//        playlist->show();
//    } else {
//        playlist->hide();
//    }
    playlist->show();
}

// 媒体对象状态发生了改变
void MusicWidget::stateChanged(Phonon::State newState, Phonon::State)
{
    switch (newState)
    {
    case Phonon::ErrorState :
        if(mediaObject->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("致命错误"),
                                 mediaObject->errorString());
        } else {
            QMessageBox::warning(this, tr("错误"), mediaObject->errorString());
        }
        break;
    case Phonon::PlayingState :
        stopAction->setEnabled(true);
        playAction->setIcon(QIcon(":/img/pause.png"));
        playAction->setText(tr("暂停"));
        topLabel->setText(QFileInfo(mediaObject->
                                    currentSource().fileName()).baseName());
        break;
    case Phonon::StoppedState :
        stopAction->setEnabled(false);
        playAction->setIcon(QIcon(":/img/play.png"));
        playAction->setText(tr("播放"));
        topLabel->setText(tr("musicplayer"));
        timeLabel->setText(tr("00:00 / 00:00"));
        break;
    case Phonon::PausedState :
        stopAction->setEnabled(true);
        playAction->setIcon(QIcon(":/img/play.png"));
        playAction->setText(tr("播放"));
        topLabel->setText(QFileInfo(mediaObject->
                                    currentSource().fileName()).baseName());
        break;
    case Phonon::BufferingState :
        break;
    default :
        ;
    }
}

// 解析媒体文件的元信息
void MusicWidget::metaStateChanged(Phonon::State newState, Phonon::State)
{
    // 错误状态，则从媒体源列表中除去新添加的媒体源
    if(newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("打开文件时出错"), metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource()))
        {};
        return;
    }

    // 如果既不处于停止状态也不处于暂停状态，则直接返回
    if(newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;

    // 如果媒体源类型错误，则直接返回
    if(metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
        return;

    // 获取媒体信息
    QMap<QString, QString> metaData = metaInformationResolver->metaData();
    // 获取标题，如果为空，则使用文件名
    QString title = metaData.value("TITLE");
    if (title == "") {
        QString str = metaInformationResolver->currentSource().fileName();
        title = QFileInfo(str).baseName();
    }
    QTableWidgetItem *titleItem = new QTableWidgetItem(title);
    // 设置数据项不可编辑
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    // 获取艺术家信息
    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);

    // 插入到播放列表
    int currentRow = playlist->rowCount();
    playlist->insertRow(currentRow);
    playlist->setItem(currentRow, 0, titleItem);
    playlist->setItem(currentRow, 1, artistItem);

    // 如果添加的媒体源还没有解析完，那么继续解析下一个媒体源
    int index = sources.indexOf(metaInformationResolver->currentSource()) + 1;
    if (sources.size() > index) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    } else { // 如果所有媒体源都已经解析完成
        // 如果播放列表中没有选中的行
        if (playlist->selectedItems().isEmpty()) {
            // 如果现在没有播放歌曲则设置第一个媒体源为媒体对象的当前媒体源
            //（因为可能正在播放歌曲时清空了播放列表，然后又添加了新的列表）
            if (mediaObject->state() != Phonon::PlayingState &&
                    mediaObject->state() != Phonon::PausedState) {
                mediaObject->setCurrentSource(sources.at(0));
            } else {
                //如果正在播放歌曲，则选中播放列表的第一个曲目,并更改图标状态
                playlist->selectRow(0);
                changeActionState();
            }
        } else {
            // 如果播放列表中有选中的行，那么直接更新图标状态
            changeActionState();
        }
    }
}

// 根据媒体源列表内容和当前媒体源的位置来改变主界面图标的状态
void MusicWidget::changeActionState()
{
    // 如果媒体源列表为空
    if (sources.count() == 0) {
        // 如果没有在播放歌曲，则播放和停止按钮都不可用
        //（因为可能歌曲正在播放时清除了播放列表）
        if (mediaObject->state() != Phonon::PlayingState &&
                mediaObject->state() != Phonon::PausedState) {
            playAction->setEnabled(false);
            stopAction->setEnabled(false);
        }
        skipBackwardAction->setEnabled(false);
        skipForwardAction->setEnabled(false);
    } else { // 如果媒体源列表不为空
        playAction->setEnabled(true);
        stopAction->setEnabled(true);
        // 如果媒体源列表只有一行
        if (sources.count() == 1) {
            skipBackwardAction->setEnabled(false);
            skipForwardAction->setEnabled(false);
        } else { // 如果媒体源列表有多行
            skipBackwardAction->setEnabled(true);
            skipForwardAction->setEnabled(true);
            int index = playlist->currentRow();
            // 如果播放列表当前选中的行为第一行
            if (index == 0)
                skipBackwardAction->setEnabled(false);
            // 如果播放列表当前选中的行为最后一行
            if (index + 1 == sources.count())
                skipForwardAction->setEnabled(false);
        }
    }
}

// 当媒体源改变时，在播放列表中选中相应的行并更新图标的状态
void MusicWidget::sourceChanged(const Phonon::MediaSource &source)
{
    int index = sources.indexOf(source);
    playlist->selectRow(index);
    changeActionState();
}

// 当前媒体源播放将要结束时，如果在列表中当前媒体源的后面还有媒体源，
// 那么将它添加到播放队列中，否则停止播放
void MusicWidget::aboutToFinish()
{
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        mediaObject->enqueue(sources.at(index));
        // 跳转到歌曲最后
        mediaObject->seek(mediaObject->totalTime());
    } else {
        mediaObject->stop();
    }
}

// 单击播放列表
void MusicWidget::tableClicked(int row)
{
    // 首先获取媒体对象当前的状态，然后停止播放并清空播放队列
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();

    // 如果单击的播放列表中的行号大于媒体源列表的大小，则直接返回
    if(row >= sources.size())
        return;
    // 设置单击的行对应的媒体源为媒体对象的当前媒体源
    mediaObject->setCurrentSource(sources.at(row));
    // 如果以前媒体对象处于播放状态，那么开始播放选中的曲目
    if (wasPlaying)
        mediaObject->play();
}

// 清空媒体源列表，它与播放列表的playListClean()信号关联
void MusicWidget::clearSources()
{
    sources.clear();
    // 更改动作图标状态
    changeActionState();
}

void MusicWidget::closeWindow()
{
    playlist->close();
    delete mediaObject;
    mediaObject = NULL;
    this->close();
}


