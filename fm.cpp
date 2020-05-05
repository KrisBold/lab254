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


void FileManager:: check()
{
  QTextStream cout(stdout);
  if (!FileManager::instance().magazines.isEmpty())
  {
      for (const auto& magazine : FileManager::instance().magazines)
      {
          if (!QFileInfo(magazine->getName()).exists() && magazine->getCondition() == Condition::Init)
          {
               emit conSub1(magazine->getName(), Condition::DeleteWin);
              //for (const auto& subscriber : subscribers)
              //{
                //  if(subscriber->getMagazine()==magazine->getName())
                  //{
              //        subscriber->getCondition() = Subscriber::Condition::DeleteWin;
              //}
              magazine->getCondition() = Condition::DeleteWin;
          }

          if (QFileInfo(magazine->getName()).exists() && magazine->getCondition() == Condition::DeleteWin)
          {
              emit conSub1(magazine->getName(), Condition::Init);
              //for (const auto& subscriber : subscribers)
              //{
              //    if(subscriber->getMagazine()==magazine->getName())
              //        subscriber->getCondition() = Subscriber::Condition::Init;
              //
              magazine->getCondition() = Condition::Init;
          }
       }
    }
}



FileManager& FileManager::instance()
{
    static FileManager obj;
    return obj;
}



