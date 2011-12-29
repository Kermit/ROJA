#ifndef PAGE_H
#define PAGE_H

#include <QtCore/QObject>

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = 0);

    virtual void show() = 0;
    virtual void hide() = 0;
};

#endif // PAGE_H
