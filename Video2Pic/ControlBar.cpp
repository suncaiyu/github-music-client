#include "ControlBar.h"
#include "ui_ControlBar.h"
#include <QFontDatabase>
#include "LoadFontIcon.h"

ControlBar::ControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlBar)
{
    ui->setupUi(this);
    mPositionLabel = (ui->posiotion_label);
    LoadFontIcon *load = LoadFontIcon::GetIndtance();
    load->SetIcon(ui->start_pause, 15, QChar(0xf04b));
    load->SetIcon(ui->stop, 15, QChar(0xf04d));
    load->SetIcon(ui->pre, 15, QChar(0xf048));
    load->SetIcon(ui->next, 15, QChar(0xf051));
    ui->widget->SetHeight(2.1);
    ui->widget->SetHandlerSize(6);
    ui->widget_2->SetHeight(2.1);
    ui->widget_2->SetHandlerSize(6);
    connect(ui->widget, &FurrainSlider::CurrentPosChanged, this, [this](qint64 t){
        VolumnSignal(t);
    });
    connect(ui->widget_2, &FurrainSlider::CurrentPosChanged, this, [this](qint64 t){
        emit SeekSignal(t);
    });
    QStringList rateList;
    rateList << "1.0" << "1.5" << "2.0" << "2.5" << "3.0" << "0.8" << "0.6" << "0.4" << "0.2";
    ui->comboBox->addItems(rateList);
}

ControlBar::~ControlBar()
{
    delete ui;
}

void ControlBar::Init()
{
    ui->widget->SetValue(100);
    ui->comboBox->setCurrentIndex(0);
}

void ControlBar::SetVideoDuration(qint64 t)
{
    ui->widget_2->SetMaximum(t);
}

void ControlBar::SetVideoTime(qint64 t)
{
    ui->widget_2->SetValue(t);
}

void ControlBar::SetVolumn(qint64 t)
{
    ui->widget->SetValue(t);
}

void ControlBar::ChangeStatus(int s)
{
    LoadFontIcon *load = LoadFontIcon::GetIndtance();
    if (s < 0) {
        load->SetIcon(ui->start_pause, 15, QChar(0xf04b));
        mIsPlay = false;
    } else if (s > 0) {
        load->SetIcon(ui->start_pause, 15, QChar(0xf04c));
        mIsPlay = true;
    }
}

void ControlBar::on_start_pause_clicked()
{
    if(mIsPlay) {
        emit StatueChangeSignal(0);
    } else {
        emit StatueChangeSignal(1);
    }
}

void ControlBar::on_stop_clicked()
{
    emit StatueChangeSignal(-1);
    mIsPlay = false;
}

void ControlBar::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qreal rate = arg1.toDouble();
    emit RateSignal(rate);
}

void ControlBar::on_pre_clicked()
{
    PreSignal();
}

void ControlBar::on_next_clicked()
{
    NextSignal();
}
