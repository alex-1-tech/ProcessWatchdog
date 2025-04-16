#pragma once
#include <QObject>

class TestProcessManager : public QObject {
    Q_OBJECT

private slots:
    void testSendSignalsToSelf();
};
