#include "processcontroller.h"
#include "core/processmanager.h"

ProcessController::ProcessController(QObject *parent) : QObject(parent) {}

void ProcessController::refreshProcesses() {
    ProcessMonitor monitor;
    auto list = monitor.getProcessList();
    emit processListReady(list);
}

void ProcessController::handleProcessAction(int pid, const QString &action) {
    bool success = false;

    if (action == "kill") {
        success = ProcessManager::killProcess(pid);
    } else if (action == "stop") {
        success = ProcessManager::stopProcess(pid);
    } else if (action == "continue") {
        success = ProcessManager::continueProcess(pid);
    }

    emit actionResult(pid, action, success);
}
