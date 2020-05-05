#ifndef FM_H
#define FM_H
#include <QObject>
#include <QTimer>

class Magazine;
class Subscriber;

class FileManager final : public QObject
{
    Q_OBJECT
    QTimer timer;
public:
    ~FileManager()=default;
     FileManager();
    // Функция "взывать". Она возвращает ссылку на единственный объекьт класса FileManager
    static FileManager& instance();
    enum Condition
        {
            Init = 0,
            Delete,
            DeleteWin
        };
    QVector<Magazine*> magazines;

    Q_SLOT void check();
    Q_SIGNAL void conSub1(QString namemag, Condition conditi);
};
#endif // FM_H
