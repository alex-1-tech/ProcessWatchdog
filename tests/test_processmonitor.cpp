#include <QtTest>
#include "test_processmonitor.h"
#include "core/processmonitor.h"

void TestProcessMonitor::testListNotEmpty() {
    ProcessMonitor monitor;
    auto list = monitor.getProcessList();
    QVERIFY(!list.isEmpty());
}

void TestProcessMonitor::testEntriesValid() {
    ProcessMonitor monitor;
    auto list = monitor.getProcessList();

    for (const auto &proc : list) {
        QVERIFY(proc.pid > 0);
        QVERIFY(!proc.name.trimmed().isEmpty());
    }
}
