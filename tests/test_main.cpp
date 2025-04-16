#include <QCoreApplication>
#include <QtTest>

#include "test_processmonitor.h"
#include "test_processmanager.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    int status = 0;

    status |= QTest::qExec(new TestProcessMonitor, argc, argv);
    status |= QTest::qExec(new TestProcessManager, argc, argv);

    return status;
}
