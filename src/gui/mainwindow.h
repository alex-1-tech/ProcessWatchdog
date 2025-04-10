#pragma once
#include <QMainWindow>
#include <QTimer>
#include "../threads/datacollection.h"
#include <QStandardItemModel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onProcessListUpdated(QVector<ProcessInfo> list);

private:
    QStandardItemModel *model;
    QTimer *updateTimer;
    DataCollection *worker;
};