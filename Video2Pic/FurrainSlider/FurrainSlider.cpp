#include "FurrainSlider.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

FurrainSlider::FurrainSlider(QWidget *parent) : QWidget(parent)
{
    mBaseBrush = QBrush(QColor(225, 225, 225));
}

void FurrainSlider::SetMaximum(const qint64 t)
{
    mTotalNum = t;
    qreal nowWidth = width() - mHandlerSize * 2;
    mPerNum = nowWidth / mTotalNum;
}

void FurrainSlider::SetValue(const qint64 t)
{
    if (t > mTotalNum) {
        mCurrentPos = mTotalNum;
    } else if (t < 0) {
        mCurrentPos = 0;
    } else {
        mCurrentPos = t;
    }
    update();
}

void FurrainSlider::SetHeight(const qreal l)
{
    if (l < 2.5) {
        mZhanbi = 2.5;
    }
    mZhanbi = l;
}

void FurrainSlider::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    //  全部
    qreal h = height() - mPadding * 2.0;
    QPainterPath p1;
    p1.addRoundedRect(rect().adjusted(mHandlerSize, mPadding, -mHandlerSize, -mPadding),h / 2, h / 2);
    p.fillPath(p1, mBaseBrush);

    // add
    QRect addRect= rect().adjusted(mHandlerSize,mPadding,-mHandlerSize,-mPadding);
    addRect.setWidth(mCurrentPos * mPerNum);
    QLinearGradient line(0,0, addRect.width(), 0);
    line.setColorAt(0, Qt::red);
    line.setColorAt(1, Qt::blue);
    mAddBrush = QBrush(line);
    p.setBrush(mAddBrush);
    QPainterPath p2;
    p.setClipping(true);
    p2.addRoundedRect(addRect, h / 2, h / 2);
    p.setClipPath(p1);
    p.fillPath(p2, mAddBrush);
    p.setClipping(false);
    QRectF handleRect;
    if (!mNeedHandle) {
        return;
    }
    qreal centerX = mCurrentPos * mPerNum + mHandlerSize + 1.0;
    if (centerX > width() - mHandlerSize - 1.0) {
        centerX = width() - mHandlerSize - 1.0;
    }
    qreal centerY =  height() / 2.0;
    handleRect = QRectF(centerX - mHandlerSize, centerY - mHandlerSize, mHandlerSize * 2, mHandlerSize * 2);
    QPainterPath p3;
    p3.addRoundedRect(handleRect, mHandlerSize, mHandlerSize);
    p.fillPath(p3, mHandleColor);
}

void FurrainSlider::resizeEvent(QResizeEvent *event)
{
    mPadding = height() / mZhanbi;
    if (mHandlerSize > height() / 2.0 - 1.0) {
        mHandlerSize = height() / 2.0 - 1.0;
    }
    qreal nowWidth = width() - mHandlerSize * 2;
    mPerNum = nowWidth / mTotalNum;
    return QWidget::resizeEvent(event);
}

void FurrainSlider::ChangeValue(qreal now, qreal &pos)
{
    qint64 p = (int)pos;
    qint64 nowi = qreal(now);
    if (nowi == p) {
        return;
    }
    pos = (qreal) nowi;
    qDebug() << pos;
    emit CurrentPosChanged(nowi);
}

void FurrainSlider::mousePressEvent(QMouseEvent *event)
{
    mIsPressed = true;
    QPoint pos = event->pos();
    qreal min = mHandlerSize;
    qreal max = width() - mHandlerSize;
    qreal currentPos = pos.x() - min;
    if (currentPos < 0) {
        currentPos = 0;
    }
    if (currentPos > max) {
        currentPos = max;
    }
    currentPos = currentPos / mPerNum;
    ChangeValue(currentPos, mCurrentPos);
    update();
}

void FurrainSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (!mIsPressed) {
        return;
    }
    QPoint pos = event->pos();
    qreal min = mHandlerSize;
    qreal max = width() - mHandlerSize;
    qreal currentPos = pos.x() - min;
    if (currentPos < 0) {
        currentPos = 0;
    }
    if (currentPos > max) {
        currentPos = max;
    }
    currentPos = currentPos / mPerNum;
    ChangeValue(currentPos, mCurrentPos);
    update();
}

void FurrainSlider::mouseReleaseEvent(QMouseEvent *event)
{
    mIsPressed = false;
}
