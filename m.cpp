#include "m.h"

Magazine::Magazine(const QString& name) :
    name(name),condition(Condition::Init)
{
}

Magazine::Condition& Magazine::getCondition()
{
    return condition;
}

QString Magazine::getName() const
{
    return name;
}

