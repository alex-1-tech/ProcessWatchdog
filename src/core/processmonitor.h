#pragma once

#include <QVector>
#include <QString>

struct ProcessInfo
{
    int pid;
    QString name;
};

class ProcessMonitor
{
public:
    QVector<ProcessInfo> getProcessList();
};