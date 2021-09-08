#include "TestWidget.h"
#include "ui_TestWidget.h"
#include "LoadFontIcon.h"
#include "HttpManager.h"
#include "ProcessJson.h"

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::on_pushButton_clicked()
{
//    HttpManager *infoManager = HttpManager::GetInstance();
//    connect(infoManager, &HttpManager::UrlGetInfo, this, [this](QByteArray array){
//        ui->textBrowser->append(QString(array));
//        ProcessJson pj;
//        pj.Process(array);
//    });
//    infoManager->getNetworkInfo(QUrl("https://api.github.com/repos/music-repo-chi/chi-music/contents/%E9%99%88%E5%A5%95%E8%BF%85"));
}
