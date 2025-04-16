#pragma once

#include <QMainWindow>
#include <QTableView>
#include "threads/datacollection.h"
#include "gui/processviewmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onProcessListUpdated(QVector<ProcessInfo> list);
    void onProcessAction(int pid, const QString &action);
    void onRequestActionWidget(const QModelIndex &index, int pid);

private:
    ProcessViewModel *model;
    DataCollection *worker;
    QTableView *tableView;
};
