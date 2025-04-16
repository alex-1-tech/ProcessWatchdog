#pragma once

#include <QObject>
#include <QVector>
#include <QFutureWatcher>
#include "core/processmonitor.h"

class ProcessController : public QObject
{
    Q_OBJECT
public:
    explicit ProcessController(QObject *parent = nullptr);

public slots:
    void refreshProcesses();
    void handleProcessAction(int pid, const QString &action);

signals:
    void processListReady(QVector<ProcessInfo> list);
    void actionResult(int pid, const QString &action, bool success);
private:
    QFutureWatcher<QVector<ProcessInfo>> watcher;
};
