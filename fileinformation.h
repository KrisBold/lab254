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
    // const - спецификатор, означающий что функция не изменяет поля класса
    QString getName() const;
    Condition& getCondition();
    qint32& getSize();

private:
    QString name;
    Condition condition;
    qint32 size;
};
#endif // FILEINFORMATION_H
