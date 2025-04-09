#include "processmonitor.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

std::vector<ProcessInfo> ProcessMonitor::getProcessList()
{
    std::vector<ProcessInfo> processes;

    DIR *procDir = opendir("/proc");
    if (!procDir)
    {
        perror("opendir(/proc)");
        return processes;
    }

    struct dirent *entry;
    while ((entry = readdir(procDir)) != nullptr)
    {
        if (entry->d_type == DT_DIR)
        {
            const char *name = entry->d_name;
            if (std::all_of(name, name + strlen(name), ::isdigit))
            {
                int pid = std::stoi(name);
                std::string commPath = "/proc/" + std::to_string(pid) + "/comm";
                std::ifstream commFile(commPath);
                std::string processName;

                if (commFile.is_open())
                {
                    std::getline(commFile, processName);
                    processes.push_back({pid, processName});
                }
            }
        }
    }

    closedir(procDir);
    return processes;
}