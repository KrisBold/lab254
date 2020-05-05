#include "m.h"

FileInformation::FileInformation(const QString& name) :
    name(name),condition(Condition::Init)
{
}

Condition& FileInformation::getCondition()
{
    return condition;
}

QString FileInformation::getName() const
{
    return name;
}

