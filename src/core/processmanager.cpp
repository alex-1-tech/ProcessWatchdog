#include "processmanager.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

bool ProcessManager::killProcess(int pid)
{
    return (kill(pid, SIGKILL) == 0);
}

bool ProcessManager::stopProcess(int pid)
{
    return (kill(pid, SIGSTOP) == 0);
}

bool ProcessManager::continueProcess(int pid)
{
    return (kill(pid, SIGCONT) == 0);
}
