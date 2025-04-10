#include "processmanager.h"
#include <signal.h>
#include <unistd.h>

bool ProcessManager::terminateProcess(int pid) {
    return kill(pid, SIGTERM) == 0;
}

bool ProcessManager::stopProcess(int pid) {
    return kill(pid, SIGSTOP) == 0;
}

bool ProcessManager::continueProcess(int pid) {
    return kill(pid, SIGCONT) == 0;
}