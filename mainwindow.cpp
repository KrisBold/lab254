#include "mainwindow.h"
#include <QTextStream>
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(printSub()));
    timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSub1()
{
    for (const auto& sub : subscribers)
    {
        QObject :: connect(&FileManager::instance(), &FileManager::conSub1, sub, &Subscriber::f1);
    }
}

QStringList MainWindow::printSub()
{
    ui->list_fm->clear();
    qint32 i = 0;
    QStringList prsub;
    FileManager::instance().check();

    for (const auto& sub : subscribers)
    {
        if (sub->getCondition() == Condition::Init)
        {
            if(QFileInfo(sub->getFile()).exists())
            {
                prsub.append(QString::number(i)+": "+ QString(sub->getName())+" -file: "+ QString(sub->getFile())+ " -exist- "+"size: "+ QString::number(QFileInfo(sub->getFile()).size())+ QString("byte"));
                i++;
            }
            else
            {
               prsub.append(QString::number(i++)+": "+ QString(sub->getName())+ QString(" Files WAS DELETE WINAPI"));
            }
          }

        else if (sub->getCondition() == Condition::DeleteWin)
        {
          prsub.append(QString::number(i++)+": "+ QString(sub->getName())+ QString(" Files WAS DELETE WINAPI"));
        }

        else if(sub->getCondition() == Condition::Not)
        {
            prsub.append(QString::number(i)+": "+ QString(sub->getName()));
        }
    }
  return prsub;
}

void MainWindow:: Resign()
{
  subscribers[subscribers.size()-1]->getFile()= ui->line_sub->text();
  ui->list_sub->clear();
  ui->list_sub->addItems(printSub());
  QTextStream(stdout)<<"resign"<<endl;
}

void MainWindow:: DeleteSubscriber()
{
    subscribers.removeAt(subscribers.size()-1);
    FileManager::instance().check();
    ui->list_sub->clear();
    ui->list_sub->addItems(printSub());
}

void MainWindow:: DeleteFile()
{
    FileManager::instance().files.removeAt(FileManager::instance().files.size()-1);
    FileManager::instance().check();
    ui->list_fm->clear();
    ui->list_fm->addItems(FileManager::instance().printfile());
}

void MainWindow:: AddSubscriber()
{
    //if(QFileInfo(FileManager::instance().files.last()).exsist());

    Subscriber s(ui->line_sub->text());
    bool is=true;
    for(const auto& sub : subscribers)
        {
          if(sub->getName()==s.getName())
          {
              is=false;
          }
        }
     if(is==true)
     {
        subscribers.append(new Subscriber (ui->line_sub->text()));
        subscribers.last()->getFile() = FileManager::instance().files.last()->getName();
        subscribers.last()->subscribe() = true;
        subscribers.last()->getCondition()=Init;
        QTextStream(stdout)<<"connect"<<endl;
        ui->list_sub->clear();
        ui->list_sub->addItems(printSub());
      }
     else if(is==false)
     {
         QTextStream(stdout)<<"error, name already exists"<<endl;
     }
}

void MainWindow:: UpdateS()
{
    ui->list_sub->clear();
    ui->list_sub->addItems(printSub());
}

void MainWindow:: UpdateF()
{
    ui->list_fm->clear();
    ui->list_fm->addItems(FileManager::instance().printfile());
}

void MainWindow:: AddFile()
{
   FileManager::instance().check();
   FileInformation file(ui->line_fm->text());
   bool is=true;
   if(QFileInfo(ui->line_fm->text()).exists())
   {
       for(const auto& f : FileManager::instance().files)
       {
         if(f->getName()==file.getName())
         {
             is=false;
         }
       }
      if(is==true)
      {
         FileManager::instance().files.append(new FileInformation(ui->line_fm->text()));
         ui->list_fm->clear();
         ui->list_fm->addItems(FileManager::instance().printfile());
         for(int i=0; i<subscribers.size();i++)
                {
                    if(subscribers[i]->getFile()==file.getName())
                    {
                        subscribers[i]->getCondition()=file.getCondition();
                    }
                }
       }
      else if(is==false)
      {
          QTextStream(stdout)<<"error, path already exists"<<endl;
      }
    }
   else
   {
       QTextStream(stdout)<<"error, no such path"<<endl;
   }
}
