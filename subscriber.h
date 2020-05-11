#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include "Condition.h"

class Subscriber : public QObject
{
    Q_OBJECT

public:
    explicit Subscriber(const QString& name);
    ~Subscriber() = default;
    QString getName() const;
    QString& getFile();
    // Возвращает флаг, подписан ли подпичик на файл или нет
    bool& subscribe();
    Condition& getCondition();
    Q_SLOT void f1(QString namemag, Condition conditi);
private:
    QString name;
    QString file;
    bool isSubscribe;
    Condition condition;
};

#endif // SUBSCRIBER_H
