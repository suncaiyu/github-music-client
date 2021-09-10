#include "LoadFontIcon.h"
#include <QFontDatabase>

LoadFontIcon::Manager LoadFontIcon::manager = Manager();
LoadFontIcon *LoadFontIcon::mMe = nullptr;

void LoadFontIcon::SetIcon(QAbstractButton *target, int pointSize, QChar iconId)
{
    int fontId = QFontDatabase::addApplicationFont(":/icon/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    iconFont.setPointSize(pointSize);
    target->setFont(iconFont);
    target->setText(iconId);//0xf00d对应的是"关闭"字体图标，具体可以看官网
}
