#include "core/processmonitor.h"
#include "core/processmanager.h"
#include <iostream>

int main() {
    ProcessMonitor monitor;
    auto processes = monitor.getProcessList();

    for (const auto& proc : processes) {
        std::cout << "PID: " << proc.pid << " | Name: " << proc.name << "\n";
    }

    // Тест завершения процесса
    /*
    int pidToKill;
    std::cout << "Enter PID to kill: ";
    std::cin >> pidToKill;
    if (ProcessManager::terminateProcess(pidToKill)) {
        std::cout << "Process terminated.\n";
    } else {
        std::cout << "Failed to terminate process.\n";
    }
    */

    return 0;
}