#include "musicplaylist.h"
#include <QContextMenuEvent>
#include <QMenu>

MusicPlaylist::MusicPlaylist(QWidget *parent) :
    QTableWidget(parent)
{
    setWindowTitle(tr("播放列表"));
    // 设置窗口标志，表明它是一个独立窗口且有一个只带有关闭按钮的标题栏
    setWindowFlags(Qt::Window  | Qt::WindowTitleHint);
    // 设置初始大小，并且锁定部件宽度
    resize(240, 320);
    setMaximumWidth(240);
    setMinimumWidth(240);
    // 设置行列数目
    setRowCount(0);
    setColumnCount(2);
    setColumnWidth(0,this->width()/2);
    setColumnWidth(1,this->width()/2);

    // 设置表头标签
    QStringList list;
    list << tr("标题") << tr("艺术家");
    setHorizontalHeaderLabels(list);

    verticalHeader()->setVisible(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // 设置只能选择单行
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    // 设置不显示网格
    setShowGrid(false);
}

// 上下文菜单事件处理函数，当点击鼠标右键时运行一个菜单
void MusicPlaylist::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(tr("清空列表"), this, SLOT(clearPlaylist()));
    menu.exec(event->globalPos());
}

// 清空播放列表
void MusicPlaylist::clearPlaylist()
{
    while (rowCount())
        removeRow(0);
    // 发射播放列表已清空信号
    emit playlistClean();
}

// 关闭事件处理函数，如果部件处于显示状态，则使其隐藏
void MusicPlaylist::closeEvent(QCloseEvent *event)
{
    if (isVisible()) {
        hide();
        event->ignore();
    }
}

