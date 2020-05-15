#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "subscriber.h"
#include "filemanager.h"
#include "fileinformation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVector<Subscriber*> subscribers;
    QTimer timer;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectSubscriberToManeger();
    Q_SLOT void addSubscriber();
    Q_SLOT QStringList printSubscriber();
    Q_SLOT void addFile();
    Q_SLOT void deleteSubscriber();
    Q_SLOT void deleteFile();
    Q_SLOT void resign();
    Q_SLOT void updateSubscribers();
    Q_SLOT void updateFiles();
    Q_SLOT void updateAll();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
