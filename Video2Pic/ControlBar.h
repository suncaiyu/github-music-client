#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>
#include <QLabel>
#include <QSlider>

namespace Ui {
class ControlBar;
}

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    explicit ControlBar(QWidget *parent = nullptr);
    ~ControlBar();
    QLabel *mPositionLabel = nullptr;
    bool mSliderPressed = false;
    QString mAllDuration = nullptr;
    qint64 mAllDurtionint64 = 0;
    void Init();
    void SetVideoDuration(qint64);
    void SetVideoTime(qint64);
    void SetVolumn(qint64);
private slots:
    void on_start_pause_clicked();

    void on_stop_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pre_clicked();

    void on_next_clicked();

public slots:
    void ChangeStatus(int);

private:
    Ui::ControlBar *ui;
    bool mIsPlay = false;

signals:
    void SeekSignal(qint64);
    void VolumnSignal(int);
    void StatueChangeSignal(int);
    void RateSignal(qreal);
    void NextSignal();
    void PreSignal();
};

#endif // CONTROLBAR_H
