#ifndef S_H
#define S_H

#include <QObject>

class Subscriber : public QObject
{
    Q_OBJECT

public:
    // Инициализация имени
    explicit Subscriber(const QString& name);
    ~Subscriber() = default;

    QString getName() const;

    QString& getMagazine();

    // Возвращает флаг, подписан ли подпичик на журнал или нет
    bool& subscribe();

    enum Condition
        {
            Init = 0,
            Delete ,
            DeleteWin
        };

    Condition& getCondition();
    //Q_SLOT void conditi1(Subscriber* _name, Subscriber::Condition conditi);

    Q_SLOT void f1(QString namemag, Condition conditi);
private:
    QString name;
    QString magazine;
    bool isSubscribe;
    Condition condition;
};
#endif // S_H
