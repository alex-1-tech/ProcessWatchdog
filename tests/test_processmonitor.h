#pragma once
#include <QObject>

class TestProcessMonitor : public QObject {
    Q_OBJECT

private slots:
    void testListNotEmpty();
    void testEntriesValid();
};
