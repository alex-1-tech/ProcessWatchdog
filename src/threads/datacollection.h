#pragma once
#include <QObject>
#include <QVector>
#include "core/processmonitor.h"

class DataCollection : public QObject
{
    Q_OBJECT
public:
    explicit DataCollection(QObject *parent = nullptr);

public slots:
    void update();

signals:
    void processListUpdated(QVector<ProcessInfo> list);
};