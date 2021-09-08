#ifndef FURRAINSLIDER_H
#define FURRAINSLIDER_H

#include <QWidget>

class FurrainSlider : public QWidget
{
    Q_OBJECT
public:
    explicit FurrainSlider(QWidget *parent = nullptr);
    ~FurrainSlider() {};
    void SetMaximum(const qint64 t);
    void SetValue(const qint64 t);
    void SetHeight(const qreal l);
    void SetNeedHandle(bool f) { mNeedHandle = f;};
    void SetHandlerSize(qreal f) {mHandlerSize = f;};
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    qint64 mTotalNum = 100; // 最大值
    qreal mHandlerSize = 0.0; //handler的半径
    qreal mCurrentPos = 0.0; // 当前的num
    QBrush mAddBrush;
    QBrush mBaseBrush;
    qreal mPerNum; // 每个value的代表像素
    qreal mPadding = 10.0;
    qreal mZhanbi = 4;

    bool mIsPressed = false;
    bool mNeedHandle = true;
    QColor mHandleColor = QColor(156,227,233);
    void ChangeValue(qreal now, qreal &pos);
signals:
    void CurrentPosChanged(qint64 pos);
};

#endif // FURRAINSLIDER_H
