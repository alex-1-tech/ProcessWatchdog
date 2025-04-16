#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include "core/processcontroller.h"
#include "gui/processviewmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onProcessListUpdated(QVector<ProcessInfo> list);
    void onRequestActionWidget(const QModelIndex &index, int pid);
    void onActionResult(int pid, const QString &action, bool success);
private:
    ProcessViewModel *model;
    ProcessController *controller;;
    QTableView *tableView;
    QLineEdit *searchEdit;
};
