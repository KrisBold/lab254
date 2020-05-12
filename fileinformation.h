#ifndef FILEINFORMATION_H
#define FILEINFORMATION_H

#include <QObject>
#include "Condition.h"

class Subscriber;

class FileInformation : public QObject
{
    Q_OBJECT

public:
    // Конструктор принимает имя файла
    explicit FileInformation(const QString& name);
    // Деструктор создаётся по умолчанию компилятором
    ~FileInformation() = default;
    // Возвращает имя журнала
    // const - спецификатор, означающий что функция не изменяет поля класса
    QString getName() const;
    Condition& getCondition();

private:
    QString name;
    Condition condition;

};
#endif // FILEINFORMATION_H
