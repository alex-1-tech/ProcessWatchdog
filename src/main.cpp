#include "core/processmonitor.h"
#include "threads/datacollection.h"
#include <iostream>
#include <mutex>

std::mutex printMutex;

void updateProcessList() {
    ProcessMonitor monitor;
    auto processes = monitor.getProcessList();

    std::lock_guard<std::mutex> lock(printMutex);
    system("clear");
    std::cout << "Обновление списка процессов:\n";
    for (const auto& proc : processes) {
        std::cout << "PID: " << proc.pid << " | Name: " << proc.name << "\n";
    }
}

int main() {
    DataCollectorThread updater(2000, updateProcessList); 
    updater.start();

    std::cout << "\nНажмите Enter для выхода...\n";
    std::cin.get();

    updater.stop();
    return 0;
}