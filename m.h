#ifndef M_H
#define M_H

#include <QObject>

class Subscriber;

class Magazine : public QObject
{
    Q_OBJECT

public:
    // Конструктор принимает имя журнала
    explicit Magazine(const QString& name);

    // Деструктор создаётся по умолчанию компилятором
    ~Magazine() = default;

    // Возвращает имя журнала
    // const - спецификатор, означающий что функция не изменяет поля класса ( исключения mutable )
    QString getName() const;

    enum Condition
        {
            Init = 0,
            Delete,
            DeleteWin
        };

    Condition& getCondition();

private:
    QString name;
    Condition condition;

};
#endif // M_H
