#include "fm.h"
#include "m.h"
//#include "s.h"

#include <QTextStream>
#include <QFileInfo>
#include <thread>
#include <QTimer>
#include <QObject>

FileManager::FileManager() :
    QObject(nullptr)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(check()));
    timer.start(1000);
}


FileManager:: ~FileManager()
{
    for (const auto& f :files)
    {
        delete f;
    }
};

void FileManager:: check()
{
  QTextStream cout(stdout);
  if (!FileManager::instance().files.isEmpty())
  {
      for (const auto& f : FileManager::instance().files)
      {
          if (!QFileInfo(f->getName()).exists() && f->getCondition() == Condition::Init)
          {
               emit conSub1(f->getName(), Condition::DeleteWin);
              //for (const auto& subscriber : subscribers)
              //{
                //  if(subscriber->getMagazine()==magazine->getName())
                  //{
              //        subscriber->getCondition() = Subscriber::Condition::DeleteWin;
              //}
              f->getCondition() = Condition::DeleteWin;
          }

          if (QFileInfo(f->getName()).exists() && f->getCondition() == Condition::DeleteWin)
          {
              emit conSub1(f->getName(), Condition::Init);
              //for (const auto& subscriber : subscribers)
              //{
              //    if(subscriber->getMagazine()==magazine->getName())
              //        subscriber->getCondition() = Subscriber::Condition::Init;
              //
              f->getCondition() = Condition::Init;
          }
       }
    }
}



FileManager& FileManager::instance()
{
    static FileManager obj;
    return obj;
}



