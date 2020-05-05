#include <QCoreApplication>
#include "fm.h"
#include <QTextStream>
#include "m.h"
#include "s.h"
#include <QFileInfo>
#include <QObject>
#include <QTimer>

//Q_SIGNAL void conSub2(Subscriber* _name, Subscriber::Condition conditi);
QVector<Subscriber*>subscribers;

void connectSub1()
{
    for (const auto& sub : subscribers)
    {
        QObject :: connect(&FileManager::instance(), &FileManager::conSub1, sub, &Subscriber::f1);
    }
}

//void condi(QString _name, Subscriber::Condition conditi)
//{
//    for (const auto& sub : subscribers)
//    {
//        if(sub->getMagazine()==_name)
//        {
//            sub->getCondition() =conditi;
//            emit conSub2(sub, conditi);
//        }
//    }
//}
//
//void connectSub1()
//{
//    for (const auto& sub : subscribers)
//    {
//        QObject :: connect(&FileManager::instance(), &FileManager::conSub1, sub, &condi);
//    }
//}
//
//void connectSub2()
//{
//    for (const auto& sub : subscribers)
//    {
//        QObject :: connect(&FileManager::instance(), conSub2, sub, &Subscriber::conditi1);
//    }
//    FileManager::instance().check();
//}

bool resign_r(qint32 idSubscriber, qint32 idMagazine)
{
   if (((idMagazine!=' ' && idSubscriber!=' ') && idSubscriber >= 0) && idSubscriber < subscribers.size())
        {
            if (idMagazine >= 0 && idMagazine < FileManager::instance().magazines.size())
            {
                if(FileManager::instance().magazines[idMagazine]->getCondition()== Magazine::Init)
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
                                subscribers[idSubscriber]->getMagazine() = FileManager::instance().magazines[idMagazine]->getName();
                                subscribers[idSubscriber]->subscribe() = true;
                                subscribers[idSubscriber]->getCondition() = Subscriber::Condition::Init;
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

bool connect_t(qint32 idMagazine, qint32 idSubscriber)
{
    QTextStream cin(stdin), cout(stdout);
     // Если ввели правильные IDs, то выполняем
     if (((idMagazine!=' ' && idSubscriber!=' ') && (idMagazine >= 0 && idMagazine < FileManager::instance().magazines.size())) && (idSubscriber >= 0 && idSubscriber < subscribers.size()))
     {
         // Если подписчик не подписан, то подписываем его на журнал
         if (!subscribers[idSubscriber]->subscribe())
         {
             if(FileManager::instance().magazines[idMagazine]->getCondition()== Magazine::Init)
             {
                 if (!subscribers[idSubscriber]->subscribe())
                 {
                     // Добавляем подписчику журнал
                     subscribers[idSubscriber]->getMagazine() = FileManager::instance().magazines[idMagazine]->getName();

                     // Выставляем подписчику флаг, что он был подписан
                     subscribers[idSubscriber]->subscribe() = true;
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
                    return QFileInfo(subscribers[idSubscriber]->getMagazine()).size();
                }
                else return -1;
            }
            else return -1;
     }
    else return -1;
}

void printMagazines()
{
    QTextStream(stdout) << "\tMAGAZINES" << endl;
    qint32 i = 0;
    FileManager::instance().check();

    for (const auto& magazine : FileManager::instance().magazines)
    {
            if (magazine->getCondition() != Magazine::Condition::DeleteWin)
            {
                QTextStream(stdout) << "\t" << i++ << " ---> " << magazine->getName() << " exsist " << endl;
            }
            else if (magazine->getCondition() == Magazine::Condition::DeleteWin)
            {
                QTextStream(stdout) << "\t" << i++ << " ---> " << magazine->getName() << " DELETE WINAPI" << endl;
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
        if (sub->getCondition() != Subscriber::Condition::DeleteWin)
        {
            QTextStream(stdout) << "\t" << i << " ---> " << sub->getName();
            if(QFileInfo(sub->getMagazine()).exists())
                {
                    QTextStream(stdout)<<" magazine  "<<sub->getMagazine() <<"  exist"<<endl;
                    QTextStream(stdout) << "\t\tSize is " << size(i) << " byte" << endl;
                    i++;
                }
            else
            {
                QTextStream(stdout)<<" "<<endl;
                i++;
            }
          }

        else if (sub->getCondition() == Subscriber::Condition::DeleteWin)
        {
          QTextStream(stdout) << "\t" << i++ << " ---> " << sub->getName() << " MAGAZINE WAS DELETE WINAPI" << endl;
        }
    }
}

void printm()
{
    QTextStream cin(stdin), cout(stdout);
    QString name1, name, path,path1, path2, name2;
    qint32 idMagazine,idSubscriber, byte, byte1;

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

    cout << '\t' << "Input magazine: " << flush;
    path = cin.readLine();
    FileManager::instance().magazines.push_back(new Magazine(path));
    printMagazines();

    cout << '\t' << "Input magazine: " << flush;
    path1 = cin.readLine();
    FileManager::instance().magazines.push_back(new Magazine(path1));

    cout << '\t' << "Input magazine: " << flush;
    path2 = cin.readLine();
    FileManager::instance().magazines.push_back(new Magazine(path2));

    printSubscribers();
    printMagazines();

    cout << "\tInput ID magazine which you want to connect: " << flush;
    idMagazine = cin.readLine().toInt();
    cout << "\tInput ID subscriber which you want to connect: " << flush;
    idSubscriber = cin.readLine().toInt();
    if(connect_t(idMagazine,idSubscriber))
    {
        cout<<"Connect"<<endl;
    }
    else
    {
        cout<<"Not connect"<<endl;
    }

    cout << "\tInput ID magazine which you want to connect: " << flush;
    idMagazine = cin.readLine().toInt();
    cout << "\tInput ID subscriber which you want to connect: " << flush;
    idSubscriber = cin.readLine().toInt();
    if(connect_t(idMagazine,idSubscriber))
    {
        cout<<"Connect"<<endl;
    }
    else
    {
        cout<<"Not connect"<<endl;
    }

    cout << "\tInput ID magazine which you want to connect: " << flush;
    idMagazine = cin.readLine().toInt();
    cout << "\tInput ID subscriber which you want to connect: " << flush;
    idSubscriber = cin.readLine().toInt();
    if(connect_t(idMagazine,idSubscriber))
    {
        cout<<"Connect"<<endl;
    }
    else
    {
        cout<<"Not connect"<<endl;
    }

    cout << "\tEnter the id of the subscriber from whom you want to find out the size of magazine: " << flush;
    idSubscriber = cin.readLine().toInt();
    byte1=size(idSubscriber);
    cout << "\t\tSize is " << byte1 << " byte" << endl;


    //cout << "\t\tInput number magazine which you want to delete: " << flush;
    //idMagazine = cin.readLine().toInt();
    //for (qint32 i = 0; i < magazines.size(); ++i)
    //{
    //    // Находим нужный индекс журнала, который надо удалить
    //    if (i == idMagazine)
    //    {
    //        // Удаляем журнал из вектора ( массива )
    //        magazines.remove(i);
    //
    //        break;
    //    }
    //}
    //
    //cout << "\t\tInput number of subcriber which you want to delete: " << flush;
    //idSubscriber = cin.readLine().toInt();
    //for (qint32 i = 0; i < subscribers.size(); ++i)
    //{
    //    // Ищем индекс нужного подписчика, которого надо удалить
    //    if (i == idSubscriber)
    //    {
    //        // Удаляем подписчика из вектора ( массива )
    //        subscribers.remove(i);
    //
    //        break;
    //    }
    //}

    printSubscribers();
    printMagazines();

    cout << "\t\tInput number subscriber which you want to re-sign: " << flush;
    idSubscriber = cin.readLine().toInt();
    cout << "\t\tInput the idMagazine which you want to subscribe to: " << flush;
    idMagazine = cin.readLine().toInt();
    if(resign_r(idSubscriber, idMagazine))
    {
        cout<<"Resign"<<endl;
    }
    else
    {
        cout<<"Not resign"<<endl;
    }

    cout << "\tEnter the id of the subscriber from whom you want to find out the size of magazine: " << flush;
    idSubscriber = cin.readLine().toInt();
    byte=size(idSubscriber);
    cout << "\t\tSize is " << byte << " byte" << endl;

    printSubscribers();
    printMagazines();

    connectSub1();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer timer;
    timer.setInterval(1000);
    QObject::connect(&timer, &QTimer::timeout, &FileManager::instance(), &printm);
    timer.start();

    return a.exec();
}
