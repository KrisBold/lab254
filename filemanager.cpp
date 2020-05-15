#include "filemanager.h"
#include "fileinformation.h"
#include <QTextStream>
#include <QFileInfo>
#include <thread>
#include <QTimer>
#include <QObject>
#include <QDebug>

FileManager::FileManager() :
    QObject(nullptr)
{
}


FileManager:: ~FileManager()
{
    for (const auto& file :files)
    {
        delete file;
    }
};

QStringList FileManager::printFile()
{
  QStringList listFiles;
  qint32 i=0;
  //FileManager::instance().check();

  for (const auto& file : FileManager::instance().files)
  {
          if (file->getCondition() != Condition::DeleteWin)
          {
              listFiles.append(QString::number(i++)+": "+QString(file->getName())+ QString(" -EXSIST- size: ")+ QString::number(QFileInfo(file->getName()).size()));
          }
          else if (file->getCondition() == Condition::DeleteWin)
          {
              listFiles.append(QString::number(i++)+QString(": ")+(file->getName())+ QString(" DELETE WINAPI "));
          }
  }
  return listFiles;
}

void FileManager:: check()
{
  QTextStream cout(stdout);
  if (!FileManager::instance().files.isEmpty())
  {
      for (const auto& file : FileManager::instance().files)
      {
          if (!QFileInfo(file->getName()).exists() && file->getCondition() == Condition::Init)
          {
              emit sendInformation(file->getName(), Condition::DeleteWin, -1);
              file->getCondition() = Condition::DeleteWin;
          }

          if ((QFileInfo(file->getName()).exists() && file->getCondition() == Condition::DeleteWin)||QFileInfo(file->getName()).size()!=file->getSize())
          {
              emit sendInformation(file->getName(), Condition::Init, QFileInfo(file->getName()).size());
              file->getCondition() = Condition::Init;
              file->getSize() = QFileInfo(file->getName()).size();
          }
      }
   }
}

FileManager& FileManager::instance()
{
    static FileManager obj;
    return obj;
}



