#pragma once

#include <QStandardItemModel>
#include "core/processmonitor.h"

class ProcessViewModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ProcessViewModel(QObject *parent = nullptr);
    void updateProcessList(const QVector<ProcessInfo> &list);
    void setSearchFilter(const QString &filter);

public slots:
    void filterByName(const QString &filter);

signals:
    void processAction(int pid, const QString &action);
    void requestActionWidget(const QModelIndex &index, int pid);

private:
    void addProcessRow(int pid, const QString &name);

    QVector<ProcessInfo> fullProcessList;
    QString currentFilter;
    QMap<int, QString> cachedProcesses;
};
