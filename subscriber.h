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
    qint32& getSize();
    Q_SLOT void acceptsFileInformation(QString namemag, Condition conditi, qint32 siz);
private:
    QString name;
    QString file;
    bool isSubscribe;
    Condition condition;
    qint32 size;
};

#endif // SUBSCRIBER_H
