#ifndef M_H
#define M_H

#include <QObject>
#include "Condishion.h"

class Subscriber;

class FileInformation : public QObject
{
    Q_OBJECT

public:
    // Конструктор принимает имя журнала
    explicit FileInformation(const QString& name);

    // Деструктор создаётся по умолчанию компилятором
    ~FileInformation() = default;

    // Возвращает имя журнала
    // const - спецификатор, означающий что функция не изменяет поля класса ( исключения mutable )
    QString getName() const;

    Condition& getCondition();

private:
    QString name;
    Condition condition;

};
#endif // M_H
