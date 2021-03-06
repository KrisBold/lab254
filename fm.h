#ifndef FM_H
#define FM_H
#include <QObject>
#include <QTimer>
#include "Condishion.h"

class FileInformation;
class Subscriber;

class FileManager final : public QObject
{
    Q_OBJECT
    QTimer timer;
public:
    ~FileManager();
     FileManager();
    // Функция "взывать". Она возвращает ссылку на единственный объекьт класса FileManager
    static FileManager& instance();
    QVector<FileInformation*> files;

    Q_SLOT void check();
    Q_SIGNAL void conSub1(QString namemag, Condition conditi);
};
#endif // FM_H
