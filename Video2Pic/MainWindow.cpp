#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QLabel>
#include <QTime>
#include "FurrainSlider.h"
#include <QMouseEvent>
#include <QLineEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    InitUi();
    mVl =  std::unique_ptr<VideoList>(new VideoList);
    mMainLayout->addWidget(mVl.get());
    mMainLayout->setStretch(0,7);
    mMainLayout->setStretch(1,3);
    connect(mVl.get(), &VideoList::FileSelectSignal, this, [this](QString str){
        mVideoPlayer->setMedia(QUrl::fromLocalFile(str));
        mVideoPlayer->play();
    });
    connect(mBar.get(), &ControlBar::PreSignal, mVl.get(), &VideoList::PreSlot);
    connect(mBar.get(), &ControlBar::NextSignal, mVl.get(), &VideoList::NextSlot);
    this->setFocus(Qt::ShortcutFocusReason);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi()
{
    mMainLayout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout);
    mSubLayout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    mVideoPlayer = std::unique_ptr<QMediaPlayer>(new QMediaPlayer);
    mMainLayout->addLayout(mSubLayout.get());
    centralWidget()->setLayout(mMainLayout.get());
    mShowVideo = std::unique_ptr<QVideoWidget>(new QVideoWidget);
    mShowVideo->setStyleSheet("QVideoWidget{background:black}");
    mSubLayout->addWidget(mShowVideo.get());
    mVideoPlayer->setVideoOutput(mShowVideo.get());
    //    mShowLabel = std::unique_ptr<QLabel>(new QLabel);
    //    mVideoSurface =std::unique_ptr<VideoSurface>(new VideoSurface);
    //    mVideoPlayer->setVideoOutput(mVideoSurface.get());
    //    mMainLayout->addWidget(mShowLabel.get());
    //    connect(&*mVideoSurface, &VideoSurface::GetFrameSignal, this, [this](QVideoFrame &frame){
    //        frame.map(QAbstractVideoBuffer::ReadOnly);
    //        QImage recvImage(frame.bits(), frame.width(), frame.height(), frame.bytesPerLine(), QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    //        mShowLabel->setPixmap(QPixmap::fromImage(recvImage));
    //    });
    mBar = std::unique_ptr<ControlBar>(new ControlBar);
    mSubLayout->addWidget(mBar.get());
    //    mBar->hide();

    connect(mBar.get(), &ControlBar::SeekSignal, this, [this](qint64 t){
        qDebug() << t;
        mVideoPlayer->setPosition(t);
    });
    connect(mBar.get(), &ControlBar::VolumnSignal, this, [this](int v){
        mVideoPlayer->setVolume(v);
    });
    mVideoPlayer->setNotifyInterval(1000);
    connect(mVideoPlayer.get(), &QMediaPlayer::positionChanged, this, [this](qint64 time){
        int allmin = time / 1000.0 / 60.0;
        int hour = allmin / 60;
        int min =  allmin - hour * 60;
        int sec = time / 1000.0 - hour * 60.0 * 60.0 - min * 60.0;
        QTime t (hour, min, sec);
        mBar->mPositionLabel->setText(t.toString("hh:mm:ss") + "/" + mBar->mAllDuration);
        mBar->SetVideoTime(time);
    });
    connect(mVideoPlayer.get(), &QMediaPlayer::durationChanged, this, [this](qint64 time){
        int allmin = time / 1000.0 / 60.0;
        int hour = allmin / 60;
        int min =  allmin - hour * 60;
        int sec = time / 1000.0 - hour * 60.0 * 60.0 - min * 60.0;
        QTime t (hour, min, sec);
        mBar->mAllDuration = t.toString("hh:mm:ss");
        mBar->mAllDurtionint64 = time;
        mBar->SetVideoDuration(time);
        mBar->show();
        mBar->Init();
    });
    connect(mBar.get(), &ControlBar::StatueChangeSignal, this, [this](int flag){
        if (flag == 0) {
            mVideoPlayer->pause();
        } else if (flag < 0){
            mVideoPlayer->stop();
        } else {
            mVideoPlayer->play();
        }
    });
    connect(mVideoPlayer.get(), &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State newState){
        if (newState == QMediaPlayer::StoppedState) {
            mBar->ChangeStatus(-1);
            mBar->SetVideoTime(0);
        } else if (newState == QMediaPlayer::PlayingState) {
            mBar->ChangeStatus(1);
        } else {
            mBar->ChangeStatus(-1);
        }
    });
    connect(mBar.get(), &ControlBar::RateSignal, this, [this](qreal t){
        mVideoPlayer->setPlaybackRate(t);
    });
}


void MainWindow::on_actionOpen_triggered()
{
    QFileDialog fileDialog(this);
    //定义文件对话框标题
    fileDialog.setWindowTitle(QStringLiteral("选中文件"));
    //设置默认文件路径
    fileDialog.setDirectory(".");
    //设置文件过滤器
    fileDialog.setNameFilter(tr("File(*.*)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    //    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog.setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
    }
    if (fileNames.isEmpty()) {
        return;
    }
    qDebug() << fileNames[0];
    mVideoPlayer->setMedia(QUrl::fromLocalFile(fileNames[0]));
    //        mVideoPlayer->setMedia(QMediaContent(QUrl("rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov")));
    mVideoPlayer->play();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier) {
        if (e->key() == Qt::Key_C) {
            mBar->setVisible(!mBar->isVisible());
        }
        if (e->key() == Qt::Key_L) {
            mVl->setVisible(!mVl->isVisible());
        }
        if (e->key() == Qt::Key_B) {
            qint64 t = mVideoPlayer->position();
            mBar->SetVideoTime(t - 3000);
            mVideoPlayer->setPosition(t - 3000);
            qDebug() << "++";
        }
        if (e->key() == Qt::Key_F) {
            qint64 t = mVideoPlayer->position();
            mBar->SetVideoTime(t + 3000);
            mVideoPlayer->setPosition(t + 3000);
            qDebug() << "++";
        }
        if (e->key() == Qt::Key_Equal) {
            qint64 t = mVideoPlayer->volume();
            mBar->SetVolumn(t + 10);
            mVideoPlayer->setVolume(t + 10);
            qDebug() << "++";
        }
        if (e->key() == Qt::Key_Minus) {
            qint64 t = mVideoPlayer->volume();
            mBar->SetVolumn(t - 10);
            mVideoPlayer->setVolume(t - 10);
            qDebug() << "--";
        }
        if (e->key() == Qt::Key_U) {
            QLineEdit *edit = new QLineEdit;
            connect(edit, &QLineEdit::returnPressed, this, [edit,this](){
                mVl->UpdateList(edit->text());
                edit->deleteLater();
            });
            edit->show();
            connect(edit, &QLineEdit::close, this, [edit](){
                edit->deleteLater();
            });
        }
    }
    qDebug() << e->key();
}
