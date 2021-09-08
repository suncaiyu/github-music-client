#ifndef VIDEOLIST_H
#define VIDEOLIST_H

#include <QWidget>
#include <QStringListModel>
#include <QFileInfo>
namespace Ui {
class VideoList;
}

class VideoList : public QWidget
{
    Q_OBJECT

public:
    explicit VideoList(QWidget *parent = nullptr);
    ~VideoList();
    bool GetFiles(QString);
    void UpdateList(QString str);

public slots:
    void NextSlot();
    void PreSlot();
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::VideoList *ui;
    QStringListModel mListModel;
    void ChargeFile(QFileInfo);
    QStringList mList;
signals:
    void FileSelectSignal(QString);
};

#endif // VIDEOLIST_H
