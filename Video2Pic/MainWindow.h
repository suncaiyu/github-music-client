#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVideoWidget>
#include "VideoSurface.h"
#include <QTextEdit>
#include "ControlBar.h"
#include "VideoList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
protected:
    void keyPressEvent(QKeyEvent *e)override;

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QHBoxLayout> mMainLayout = nullptr;
    std::unique_ptr<QVBoxLayout> mSubLayout = nullptr;
    std::unique_ptr<QMediaPlayer> mVideoPlayer = nullptr;


    std::unique_ptr<QLabel> mShowLabel = nullptr;
    std::unique_ptr<QVideoWidget> mShowVideo = nullptr;
    std::unique_ptr<VideoSurface> mVideoSurface = nullptr;
    std::unique_ptr<ControlBar> mBar = nullptr;
    std::unique_ptr<VideoList> mVl = nullptr;
    //    VideoList *mVl = nullptr;
    void InitUi();
};
#endif // MAINWINDOW_H
