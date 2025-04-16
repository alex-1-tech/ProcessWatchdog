#pragma once

#include <QString>

class ProcessManager
{
public:
    static bool killProcess(int pid);
    static bool stopProcess(int pid);
    static bool continueProcess(int pid);
};
