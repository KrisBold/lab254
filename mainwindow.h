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
    void connectSub1();
    Q_SLOT void AddSubscriber();
    QStringList printSub();
    Q_SLOT void AddFile();
    Q_SLOT void DeleteSubscriber();
    Q_SLOT void DeleteFile();
    Q_SLOT void Resign();
    Q_SLOT void UpdateS();
    Q_SLOT void UpdateF();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
