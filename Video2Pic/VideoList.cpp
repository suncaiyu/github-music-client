#include "VideoList.h"
#include "ui_VideoList.h"
#include <QDir>
#include <QDebug>

VideoList::VideoList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoList)
{
    ui->setupUi(this);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    GetFiles("G:\\新建文件夹");
    mListModel.setStringList(mList);
    ui->listView->setModel(&mListModel);
}

VideoList::~VideoList()
{
    delete ui;
}

bool VideoList::GetFiles(QString path)
{
    QDir dir(path);
    if (!dir.exists()){
        return false ;
    }
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::Hidden);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    int i=0;
    do {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName()== "." |fileInfo.fileName()== ".." )
        {
            i++;
            continue ;
        }
        bool bisDir=fileInfo.isDir();
        if (bisDir)
        {
            //            qDebug()<<fileInfo.filePath();
            ChargeFile(fileInfo);
            GetFiles(fileInfo.filePath());
        } else {
            ChargeFile(fileInfo);
            //            qDebug()<<fileInfo.filePath();
        }
        i++;
    } while (i<list.size());
    return true ;
}

void VideoList::UpdateList(QString str)
{
    if (str.isEmpty()) {
        return;
    }
    qDebug() << str;
    mList.clear();
    mListModel.removeRows(0, mListModel.rowCount());
    GetFiles(str);
    qDebug() << mList.size();
    mListModel.setStringList(mList);
    ui->listView->setModel(&mListModel);
}

void VideoList::NextSlot()
{
    QModelIndex id = ui->listView->currentIndex();
    if (!id.isValid()) {
        return;
    }
    QModelIndex next = ui->listView->model()->index(id.row() + 1, 0);
    if (!next.isValid()) {
        return;
    }
    ui->listView->setCurrentIndex(next);
    FileSelectSignal(next.data().toString());
}

void VideoList::PreSlot()
{
    QModelIndex id = ui->listView->currentIndex();
    if (!id.isValid()) {
        return;
    }
    QModelIndex pre = ui->listView->model()->index(id.row() - 1, 0);
    if (!pre.isValid()) {
        return;
    }
    ui->listView->setCurrentIndex(pre);
    FileSelectSignal(pre.data().toString());
}

void VideoList::ChargeFile(QFileInfo info)
{
    if (info.isDir()){
        return;
    }
    QString name = info.fileName();
    if (name.endsWith("mp4") || name.endsWith("wmv") || name.endsWith("mkv") || name.endsWith("avi")) {
        if (info.size() < 500 * 1024 * 1024) {
            return;
        }
        mList.append(info.filePath());
    }
}

void VideoList::on_listView_doubleClicked(const QModelIndex &index)
{
    FileSelectSignal(index.data().toString());
}
