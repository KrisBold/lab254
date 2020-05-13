#include "subscriber.h"

#include <QTextStream>

Subscriber::Subscriber(const QString& name) :
    name(name),isSubscribe(false), condition(Condition::Not)
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

void Subscriber:: acceptsFileInformation(QString namemag, Condition conditi)
{
    if(namemag==file)
    {
        condition =conditi;
    }
}
