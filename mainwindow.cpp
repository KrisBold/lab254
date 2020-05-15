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
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateAll()));
    timer.start(1000);
}

void MainWindow:: updateAll()
{
   FileManager::instance().check();
   connectSubscriberToManeger();
   updateFiles();
   updateSubscribers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSubscriberToManeger()
{
    for (const auto& sub : subscribers)
    {
        QObject :: connect(&FileManager::instance(), &FileManager::sendInformation, sub, &Subscriber::acceptsFileInformation);
    }
}

QStringList MainWindow::printSubscriber()
{
    ui->list_sub->clear();
    qint32 i = 0;
    QStringList listSubscriber;
    //FileManager::instance().check();
    for (const auto& sub : subscribers)
    {
        if (sub->getCondition() == Condition::Init)
        {
          listSubscriber.append(QString::number(i)+": "+ QString(sub->getFile())+ " -exist- "+"size: "+ QString::number(QFileInfo(sub->getFile()).size())+ QString("byte"));
          i++;
        }
        else if (sub->getCondition() == Condition::DeleteWin)
        {
          listSubscriber.append(QString::number(i++)+": "+ QString(sub->getFile())+ QString(" Files WAS DELETE WINAPI"));
        }

        else if(sub->getCondition() == Condition::Not)
        {
            listSubscriber.append(QString::number(i++)+": "+ QString(sub->getFile())+"-no information");
        }
    }
  return listSubscriber;
}

void MainWindow:: resign()
{
    bool isFileInList=false;
    int i=ui->list_sub->currentRow();
    if (!(ui->line_sub->text().isEmpty()) && !(subscribers.isEmpty()) && i>=0)
    {
        for(const auto& file: FileManager::instance().files)
        {
          if(ui->line_sub->text()==file->getName())
          {
             subscribers[i]->getFile() = ui->line_sub->text();
             subscribers[i]->getName() = ui->line_sub->text();
             if(file->getCondition()==Init)
             {
               subscribers[i]->getCondition()=Init;
             }
             else if(file->getCondition()==DeleteWin)
             {
                 subscribers[i]->getCondition()=DeleteWin;
             }
             ui->list_sub->clear();
             ui->list_sub->addItems(printSubscriber());
             isFileInList=true;
           }
         }
        if(isFileInList==false && i>=0)
        {
            subscribers[i]->getFile() = ui->line_sub->text();
            subscribers[i]->getName() = ui->line_sub->text();
            subscribers[i]->getCondition()=Not;
            ui->list_sub->clear();
            ui->list_sub->addItems(printSubscriber());
        }
    }
}

void MainWindow:: deleteSubscriber()
{
    int i=ui->list_sub->currentRow();
    if(!(subscribers.isEmpty()) && i>=0)
    {
      subscribers.removeAt(i);
      //FileManager::instance().check();
      ui->list_sub->clear();
      ui->list_sub->addItems(printSubscriber());
    }
}

void MainWindow:: deleteFile()
{
    int i=ui->list_fm->currentRow();
    if(!(FileManager::instance().files.isEmpty()) && i>=0)
    {
      FileManager::instance().files.removeAt(i);
      //FileManager::instance().check();
      ui->list_fm->clear();
      ui->list_fm->addItems(FileManager::instance().printFile());

    }
}

void MainWindow:: addSubscriber()
{
    Subscriber s(ui->line_sub->text());
    bool isFileInManager=false;
    subscribers.append(new Subscriber (ui->line_sub->text()));
    for(qint32 i=0; i<FileManager::instance().files.size(); i++)
    {
      if(ui->line_sub->text()==FileManager::instance().files[i]->getName())
      {
         subscribers.last()->getFile() = ui->line_sub->text();
         subscribers.last()->subscribe() = true;
         subscribers.last()->getCondition()=FileManager::instance().files[i]->getCondition();
         ui->list_sub->clear();
         ui->list_sub->addItems(printSubscriber());
         isFileInManager=true;
       }
    }
    if(isFileInManager==false)
    {
        subscribers.last()->getFile() = ui->line_sub->text();
        subscribers.last()->subscribe() = true;
        subscribers.last()->getCondition()=Not;
        ui->list_sub->clear();
        ui->list_sub->addItems(printSubscriber());
    }
}

void MainWindow:: updateSubscribers()
{
    ui->list_sub->clear();
    ui->list_sub->addItems(printSubscriber());
}

void MainWindow:: updateFiles()
{
    ui->list_fm->clear();
    ui->list_fm->addItems(FileManager::instance().printFile());
}

void MainWindow:: addFile()
{
   //FileManager::instance().check();
   FileInformation file(ui->line_fm->text());
   bool isFileInList=false;
   for(const auto& f : FileManager::instance().files)
   {
     if(f->getName()==file.getName())
     {
         isFileInList=true;
     }
   }
   if(isFileInList==false)
   {
      FileManager::instance().files.append(new FileInformation(ui->line_fm->text()));
      ui->list_fm->clear();
      ui->list_fm->addItems(FileManager::instance().printFile());
      for(int i=0; i<subscribers.size();i++)
      {
          if(subscribers[i]->getFile()==file.getName())
          {
              subscribers[i]->getCondition()=file.getCondition();
          }
      }
   }
}
