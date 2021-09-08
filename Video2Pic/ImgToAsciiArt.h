#ifndef IMGTOASCIIART_H
#define IMGTOASCIIART_H
#include <QObject>
#include <QImage>
#include <QColor>
#include <QByteArray>
#include <QDebug>
#include <QTime>
#include <QtGlobal>

class ImgToAsciiArt : public QObject
{
    Q_OBJECT
public:
    explicit ImgToAsciiArt(QObject *parent = 0);
    ~ImgToAsciiArt();
    QString imgToAscii(QImage &image,QByteArray asciiArray=QByteArray());
    QStringList imgToHtml(QImage &image, QString htmlStrSet, bool isOrder,bool isAlpha = false);

signals:

public slots:

private:

};

#endif // IMGTOASCIIART_H
