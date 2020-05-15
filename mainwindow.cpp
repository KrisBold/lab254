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
   updateFiles();
   updateSubscribers();
}

MainWindow::~MainWindow()
{
    delete ui;
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
             subscribers[i]->getSize() = QFileInfo(ui->line_sub->text()).size();
             if(file->getCondition()==Init)
             {
               subscribers[i]->getCondition()=Init;
             }
             else if(file->getCondition()==DeleteWin)
             {
                 subscribers[i]->getCondition()=DeleteWin;
             }
             isFileInList=true;
           }
         }
        if(isFileInList==false && i>=0)
        {
            subscribers[i]->getFile() = ui->line_sub->text();
            subscribers[i]->getName() = ui->line_sub->text();
            subscribers[i]->getCondition()=Not;
            subscribers[i]->getSize()=-1;
        }
        ui->list_sub->item(i)->setText(ui->line_sub->text());
    }
}

void MainWindow:: deleteSubscriber()
{
    int i=ui->list_sub->currentRow();
    if(!(subscribers.isEmpty()) && i>=0)
    {
      subscribers.removeAt(i);
      delete ui->list_sub->takeItem(i);
    }
}

void MainWindow:: deleteFile()
{
    int i=ui->list_fm->currentRow();
    if(!(FileManager::instance().files.isEmpty()) && i>=0)
    {
      FileManager::instance().files.removeAt(i);
      delete ui->list_fm->takeItem(i);
    }
}

void MainWindow:: addSubscriber()
{
    //Subscriber s(ui->line_sub->text());
    bool isFileInManager=false;
    subscribers.append(new Subscriber (ui->line_sub->text()));
    QObject :: connect(&FileManager::instance(), &FileManager::sendInformation, subscribers.last(), &Subscriber::acceptsFileInformation);
    for(qint32 i=0; i<FileManager::instance().files.size(); i++)
    {
      if(ui->line_sub->text()==FileManager::instance().files[i]->getName())
      {
         subscribers.last()->getFile() = ui->line_sub->text();
         subscribers.last()->subscribe() = true;
         subscribers.last()->getSize()=QFileInfo(FileManager::instance().files[i]->getName()).size();
         subscribers.last()->getCondition()=FileManager::instance().files[i]->getCondition();
         isFileInManager=true;
       }
    }
    if(isFileInManager==false)
    {
        subscribers.last()->getFile() = ui->line_sub->text();
        subscribers.last()->subscribe() = true;
        subscribers.last()->getSize()=-1;
        subscribers.last()->getCondition()=Not;
    }
    ui->list_sub->addItem(new QListWidgetItem (ui->line_sub->text()));
}

void MainWindow:: updateSubscribers()
{
    for (qint32 i=0; i<subscribers.size(); i++)
    {
        Subscriber* sub=subscribers[i];
        if (sub->getCondition() == Condition::Init)
        {
         ui->list_sub->item(i)->setText(QString::number(i)+": "+ QString(sub->getFile())+ " -exist- "+"size: "+ QString::number(sub->getSize())+ QString("byte"));
        }
        else if (sub->getCondition() == Condition::DeleteWin)
        {
          ui->list_sub->item(i)->setText(QString::number(i)+": "+ QString(sub->getFile())+ QString(" Files WAS DELETE WINAPI"));
        }

        else if(sub->getCondition() == Condition::Not)
        {
            ui->list_sub->item(i)->setText(QString::number(i)+": "+ QString(sub->getFile())+"-no information");
        }
    }
}

void MainWindow:: updateFiles()
{
    for (qint32 i=0; i<FileManager::instance().files.size(); i++)
    {
        FileInformation* file=FileManager::instance().files[i];
        if (file->getCondition() != Condition::DeleteWin)
        {
            ui->list_fm->item(i)->setText(QString::number(i)+": "+QString(file->getName())+ QString(" -EXSIST- size: ")+ QString::number(QFileInfo(file->getName()).size()));
        }
        else if (file->getCondition() == Condition::DeleteWin)
        {
            ui->list_fm->item(i)->setText(QString::number(i)+QString(": ")+(file->getName())+ QString(" DELETE WINAPI "));
        }
    }
}

void MainWindow:: addFile()
{
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
      ui->list_fm->addItem(new QListWidgetItem (ui->line_fm->text()));
      for(int i=0; i<subscribers.size();i++)
      {
          if(subscribers[i]->getFile()==file.getName())
          {
              subscribers[i]->getCondition()=file.getCondition();
              subscribers[i]->getSize()=QFileInfo(file.getName()).size();
          }
      }
   }
}
