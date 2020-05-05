#include "s.h"
#include <QTextStream>

Subscriber::Subscriber(const QString& name) :
    name(name),isSubscribe(false), condition(Condition::Init)
{
}

QString Subscriber::getName() const
{
    return name;
}

QString& Subscriber::getMagazine()
{
    return magazine;
}

bool& Subscriber::subscribe()
{
    return isSubscribe;
}

Subscriber::Condition& Subscriber::getCondition()
{
    return condition;
}

//void Subscriber::conditi1(Subscriber* _name, Subscriber::Condition conditi)
//{
//  _name->getCondition()=conditi;
//}
void Subscriber:: f1(QString namemag, Condition conditi)
{
    if(namemag==magazine)
    {
        condition =conditi;
    }
}

