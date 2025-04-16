#include <QtTest>
#include "test_processmanager.h"
#include "core/processmanager.h"
#include <unistd.h>

void TestProcessManager::testSendSignalsToSelf() {
    int pid = getpid();
    QVERIFY(ProcessManager::stopProcess(pid));
    QVERIFY(ProcessManager::continueProcess(pid));
    // QVERIFY(ProcessManager::killProcess(pid));
}
