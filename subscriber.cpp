#include "subscriber.h"

#include <QTextStream>
#include <QDebug>

Subscriber::Subscriber(const QString& name) :
    name(name),isSubscribe(false), condition(Condition::Not),size(-1)
{
}

QString Subscriber::getName() const
{
    return name;
}

QString& Subscriber::getFile()
{
    return file;
}

bool& Subscriber::subscribe()
{
    return isSubscribe;
}

Condition& Subscriber::getCondition()
{
    return condition;
}

qint32& Subscriber::getSize()
{
    return size;
}

void Subscriber:: acceptsFileInformation(QString namemag, Condition conditi, qint32 siz)
{
    if(namemag==file)
    {
        condition =conditi;
        size=siz;
    }
}
