#include "datacollection.h"

DataCollection::DataCollection(QObject *parent) : QObject(parent) {}

void DataCollection::update() {
    ProcessMonitor monitor;
    auto list = monitor.getProcessList();
    emit processListUpdated(list);
}