#include "processcontroller.h"
#include "processmanager.h"
#include <QtConcurrent>

ProcessController::ProcessController(QObject *parent)
    : QObject(parent)
{
    connect(&watcher, &QFutureWatcher<QVector<ProcessInfo>>::finished, this, [this]()
            {
        QVector<ProcessInfo> result = watcher.result();
        emit processListReady(result); });
}

void ProcessController::refreshProcesses()
{
    watcher.setFuture(QtConcurrent::run([]()
                                        {
        ProcessMonitor monitor;
        return monitor.getProcessList(); }));
}

void ProcessController::handleProcessAction(int pid, const QString &action)
{
    bool success = false;

    if (action == "kill")
    {
        success = ProcessManager::killProcess(pid);
    }
    else if (action == "stop")
    {
        success = ProcessManager::stopProcess(pid);
    }
    else if (action == "continue")
    {
        success = ProcessManager::continueProcess(pid);
    }

    emit actionResult(pid, action, success);
}
