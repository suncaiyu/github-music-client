#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H
#include <QAbstractVideoSurface>


class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QObject *parent = nullptr);
    virtual ~VideoSurface();
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType =
            QAbstractVideoBuffer::NoHandle) const;
        bool present(const QVideoFrame &frame);

signals:
    void GetFrameSignal(QVideoFrame &frame);
};

#endif // VIDEOSURFACE_H
