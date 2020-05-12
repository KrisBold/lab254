#include "mainwindow.h"
#include "fileinformation.h"
#include <QTextStream>
#include "filemanager.h"
#include "subscriber.h"
#include <QFileInfo>
#include <QObject>
#include <QTimer>
#include <QApplication>

QVector<Subscriber*>subscribers;

void connectSub1()
{
    for (const auto& sub : subscribers)
    {
        QObject :: connect(&FileManager::instance(), &FileManager::conSub1, sub, &Subscriber::f1);
    }
}

bool resign(qint32 idSubscriber, qint32 idFile)
{
   if (idSubscriber >= 0 && idSubscriber < subscribers.size())
        {
            if (idFile >= 0 && idFile < FileManager::instance().files.size())
            {
                if(FileManager::instance().files[idFile]->getCondition()== Condition::Init)
                {
                    for (qint32 i = 0; i < subscribers.size(); ++i)
                    {
                        // Находим ID подписчика, которого надо переподписать
                        if (i == idSubscriber)
                        {
                            // Если подписчик ещё не подписан, то выполняем
                            if (subscribers[idSubscriber]->subscribe())
                            {
                                // Здесь подписываем на новый журнал
                                subscribers[idSubscriber]->getFile() = FileManager::instance().files[idFile]->getName();
                                subscribers[idSubscriber]->subscribe() = true;
                                subscribers[idSubscriber]->getCondition() = Condition::Init;
                              }
                        }
                    }
                   return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
   else
   {
       return false;
   }
}

bool connect(qint32 idFile, qint32 idSubscriber)
{
    QTextStream cin(stdin), cout(stdout);
     // Если ввели правильные IDs, то выполняем
     if (idFile >= 0 && idFile < FileManager::instance().files.size() && (idSubscriber >= 0 && idSubscriber < subscribers.size()))
     {
         // Если подписчик не подписан, то подписываем его на журнал
         if (!subscribers[idSubscriber]->subscribe())
         {
             if(FileManager::instance().files[idFile]->getCondition()== Condition::Init)
             {
                 if (!subscribers[idSubscriber]->subscribe())
                 {
                     // Добавляем подписчику журнал
                     subscribers[idSubscriber]->getFile() = FileManager::instance().files[idFile]->getName();

                     // Выставляем подписчику флаг, что он был подписан
                     subscribers[idSubscriber]->subscribe() = true;
                     subscribers[idSubscriber]->getCondition()=Init;
                 }
               return true;
             }
             else
             {
                 return false;
             }
         }
         else
         {
             return false;
         }
     }
     else
     {
         return false;
     }
}


qint32 size(qint32 idSubscriber)
{
    QTextStream cin(stdin), cout(stdout);
  // Если подписчики есть
    if (!subscribers.isEmpty())
    {
 // Если ввели верный ID, то выполняем
            if (idSubscriber >= 0 && idSubscriber < subscribers.size())
            {
                // Если подписчик подписан на журнал, то выводим размер журнала, на который он подписан
                if (subscribers[idSubscriber]->subscribe())
                {
                    return QFileInfo(subscribers[idSubscriber]->getFile()).size();
                }
                else return -1;
            }
            else return -1;
     }
    else return -1;
}

void printFiles()
{
    QTextStream(stdout) << "\tFiles" << endl;
    qint32 i = 0;
    FileManager::instance().check();

    for (const auto& f : FileManager::instance().files)
    {
            if (f->getCondition() != Condition::DeleteWin)
            {
                QTextStream(stdout) << "\t" << i++ << " ---> " << f->getName() << " exsist " << endl;
            }
            else if (f->getCondition() == Condition::DeleteWin)
            {
                QTextStream(stdout) << "\t" << i++ << " ---> " << f->getName() << " DELETE WINAPI" << endl;
            }
    }
}

void printSubscribers()
{
    QTextStream(stdout) << "\tSUBSCRIBERS" << endl;
    qint32 i = 0;
    FileManager::instance().check();

    for (const auto& sub : subscribers)
    {
        if (sub->getCondition() == Condition::Init)
        {
            if(QFileInfo(sub->getFile()).exists())
            {
                QTextStream(stdout) << "\t" << i << " ---> " << sub->getName();
                QTextStream(stdout)<<" file  "<<sub->getFile() <<"  exist"<<endl;
                QTextStream(stdout) << "\t\tSize is " << size(i) << " byte" << endl;
                i++;
            }
            else
            {
               QTextStream(stdout) << "\t" << i++ << " ---> " << sub->getName() << " Files WAS DELETE WINAPI" << endl;
            }
          }

        else if (sub->getCondition() == Condition::DeleteWin)
        {
          QTextStream(stdout) << "\t" << i++ << " ---> " << sub->getName() << " Files WAS DELETE WINAPI" << endl;
        }

        else if(sub->getCondition() == Condition::Not)
        {
            QTextStream(stdout) << "\t" << i++ << " ---> " << sub->getName()<<endl;
        }
    }
}

void printm()
{
    QTextStream cin(stdin), cout(stdout);
    QString name1, name, path,path1, path2, name2;
    qint32 idFile,idSubscriber, byte, byte1;

    cout << '\t' << "Input subscriber: " << flush;
    name = cin.readLine();
    subscribers.push_back(new Subscriber(name));
    printSubscribers();

    cout << '\t' << "Input subscriber: " << flush;
    name1 = cin.readLine();
    subscribers.push_back(new Subscriber(name1));
    printSubscribers();

    cout << '\t' << "Input subscriber: " << flush;
    name2 = cin.readLine();
    subscribers.push_back(new Subscriber(name2));
    printSubscribers();

    cout << '\t' << "Input file: " << flush;
    path = cin.readLine();
    FileManager::instance().files.push_back(new FileInformation(path));
    printFiles();

    cout << '\t' << "Input file: " << flush;
    path1 = cin.readLine();
    FileManager::instance().files.push_back(new FileInformation(path1));

    cout << '\t' << "Input file: " << flush;
    path2 = cin.readLine();
    FileManager::instance().files.push_back(new FileInformation(path2));

    printSubscribers();
    printFiles();

    cout << "\tInput ID file which you want to connect: " << flush;
    idFile = cin.readLine().toInt();
    cout << "\tInput ID subscriber which you want to connect: " << flush;
    idSubscriber = cin.readLine().toInt();
    if(connect(idFile,idSubscriber))
    {
        cout<<"Connect"<<endl;
    }
    else
    {
        cout<<"Not connect"<<endl;
    }

    cout << "\tInput ID file which you want to connect: " << flush;
    idFile = cin.readLine().toInt();
    cout << "\tInput ID subscriber which you want to connect: " << flush;
    idSubscriber = cin.readLine().toInt();
    if(connect(idFile,idSubscriber))
    {
        cout<<"Connect"<<endl;
    }
    else
    {
        cout<<"Not connect"<<endl;
    }

    cout << "\tInput ID file which you want to connect: " << flush;
    idFile = cin.readLine().toInt();
    cout << "\tInput ID subscriber which you want to connect: " << flush;
    idSubscriber = cin.readLine().toInt();
    if(connect(idFile,idSubscriber))
    {
        cout<<"Connect"<<endl;
    }
    else
    {
        cout<<"Not connect"<<endl;
    }

    cout << "\tEnter the id of the subscriber from whom you want to find out the size of file: " << flush;
    idSubscriber = cin.readLine().toInt();
    byte1=size(idSubscriber);
    cout << "\t\tSize is " << byte1 << " byte" << endl;


    cout << "\t\tInput number file which you want to delete: " << flush;
    idFile = cin.readLine().toInt();
    for (qint32 i = 0; i < FileManager::instance().files.size(); ++i)
    {
        // Находим нужный индекс журнала, который надо удалить
        if (i == idFile)
        {
            // Удаляем журнал из вектора ( массива )
            FileManager::instance().files.removeAt(i);
            break;
        }
    }

    cout << "\t\tInput number of subcriber which you want to delete: " << flush;
    idSubscriber = cin.readLine().toInt();
    for (qint32 i = 0; i < subscribers.size(); ++i)
    {
        // Ищем индекс нужного подписчика, которого надо удалить
        if (i == idSubscriber)
        {
            // Удаляем подписчика из вектора ( массива )
            subscribers.remove(i);
            break;
        }
    }

    printSubscribers();
    printFiles();

    cout << "\t\tInput number subscriber which you want to re-sign: " << flush;
    idSubscriber = cin.readLine().toInt();
    cout << "\t\tInput the file which you want to subscribe to: " << flush;
    idFile = cin.readLine().toInt();
    if(resign(idSubscriber, idFile))
    {
        cout<<"Resign"<<endl;
    }
    else
    {
        cout<<"Not resign"<<endl;
    }

    cout << "\tEnter the id of the subscriber from whom you want to find out the size of file: " << flush;
    idSubscriber = cin.readLine().toInt();
    byte=size(idSubscriber);
    cout << "\t\tSize is " << byte << " byte" << endl;

    printSubscribers();
    printFiles();

    connectSub1();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qint32 execCode=0;

    w.show();
    execCode=a.exec();

    for (const auto& sub : subscribers)
    {
        delete sub;
    }

    return execCode;
}
