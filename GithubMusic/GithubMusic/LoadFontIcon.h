#ifndef LOADFONTICON_H
#define LOADFONTICON_H
#include <QAbstractButton>
#include <QDebug>
class Manager;
class LoadFontIcon
{
public:
    static LoadFontIcon *GetIndtance()
    {
        if(mMe == nullptr) {
            mMe = new LoadFontIcon();
        }
        return mMe;
    }
    ~LoadFontIcon() {};
    void SetIcon(QAbstractButton *target, int pointSize, QChar iconId);
private:
    LoadFontIcon() {};
    static LoadFontIcon *mMe;

    class Manager {
    public:
        Manager() {qDebug() << "create manager";};
        ~Manager()
        {
            qDebug() << "delete Manager";
            if (LoadFontIcon::mMe) {
                delete LoadFontIcon::mMe;
                LoadFontIcon::mMe = nullptr;
            }
        }
    };
    static Manager manager;
};

#endif // LOADFONTICON_H
