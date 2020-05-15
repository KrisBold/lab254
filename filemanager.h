#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QTimer>
#include "Condition.h"
#include <QTimer>

class FileInformation;
class Subscriber;

class FileManager final : public QObject
{
    Q_OBJECT
    QTimer timer;
     FileManager();
public:
      ~FileManager();
     QStringList printFile();
    // Функция "взывать". Она возвращает ссылку на единственный объекьт класса FileManager
     static FileManager& instance();
     QVector<FileInformation*> files;
     void check();
     Q_SIGNAL void sendInformation(QString namef, Condition conditi);
};

#endif // FILEMANAGER_H
