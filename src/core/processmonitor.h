#pragma once

#include <vector>
#include <string>

struct ProcessInfo
{
    int pid;
    std::string name;
};

class ProcessMonitor
{
public:
    std::vector<ProcessInfo> getProcessList();
};