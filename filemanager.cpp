#include "filemanager.h"
#include "fileinformation.h"
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

QStringList FileManager::printfile()
{
  QStringList prfiles;
  qint32 i=0;
  FileManager::instance().check();

  for (const auto& f : FileManager::instance().files)
  {
          if (f->getCondition() != Condition::DeleteWin)
          {
              prfiles.append(QString::number(i++)+": "+QString(f->getName())+ QString(" -EXSIST- size: ")+ QString::number(QFileInfo(f->getName()).size()));
          }
          else if (f->getCondition() == Condition::DeleteWin)
          {
              prfiles.append(QString::number(i++)+QString(": ")+(f->getName())+ QString(" DELETE WINAPI "));
          }
  }
  return prfiles;
}

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
               f->getCondition() = Condition::DeleteWin;
          }

          if (QFileInfo(f->getName()).exists() && f->getCondition() == Condition::DeleteWin)
          {
              emit conSub1(f->getName(), Condition::Init);
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



