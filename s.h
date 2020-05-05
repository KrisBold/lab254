#ifndef S_H
#define S_H

#include <QObject>
#include "Condishion.h"

class Subscriber : public QObject
{
    Q_OBJECT

public:
    // Инициализация имени
    explicit Subscriber(const QString& name);
    ~Subscriber() = default;

    QString getName() const;

    QString& getFile();

    // Возвращает флаг, подписан ли подпичик на журнал или нет
    bool& subscribe();

    Condition& getCondition();
    //Q_SLOT void conditi1(Subscriber* _name, Subscriber::Condition conditi);

    Q_SLOT void f1(QString namemag, Condition conditi);
private:
    QString name;
    QString file;
    bool isSubscribe;
    Condition condition;
};
#endif // S_H
