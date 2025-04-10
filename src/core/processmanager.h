#pragma once

class ProcessManager
{
public:
    static bool terminateProcess(int pid);
    static bool stopProcess(int pid);
    static bool continueProcess(int pid);
};