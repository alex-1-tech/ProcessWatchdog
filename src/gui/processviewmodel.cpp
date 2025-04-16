#include "processviewmodel.h"
#include <QStandardItem>

ProcessViewModel::ProcessViewModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setHorizontalHeaderLabels({"PID", "Name", "Actions"});
}

void ProcessViewModel::updateProcessList(const QVector<ProcessInfo> &list)
{
    QMap<int, QString> newMap;
    for(const auto& proc: list)
        newMap[proc.pid] = proc.name;

    for(int row = rowCount() - 1; row >= 0; --row){
        int pid = item(row, 0)->text().toInt();
        if(!newMap.contains(pid)){
            removeRow(row);
            cachedProcesses.remove(pid);
        }
    }

    for (const auto& [pid, name] : newMap.toStdMap()) {
        if (cachedProcesses.contains(pid)) {
            if (cachedProcesses[pid] != name) {
                for (int row = 0; row < rowCount(); ++row) {
                    if (item(row, 0)->text().toInt() == pid) {
                        item(row, 1)->setText(name);
                        break;
                    }
                }
                cachedProcesses[pid] = name;
            }
        } else {
            addProcessRow(pid, name);
            cachedProcesses[pid] = name;
        }
    }
}

void ProcessViewModel::filterByName(const QString &filter)
{   
    currentFilter = filter;
    clear();
    setHorizontalHeaderLabels({"PID", "Name", "Actions"});

    for (const ProcessInfo &proc : fullProcessList)
    {
        QString pidStr = QString::number(proc.pid);
        if (proc.name.contains(filter, Qt::CaseInsensitive) ||
    pidStr.contains(filter))
        {
            addProcessRow(proc.pid, proc.name);
        }
    }
}

void ProcessViewModel::addProcessRow(int pid, const QString &name)
{
    auto *pidItem = new QStandardItem(QString::number(pid));
    auto *nameItem = new QStandardItem(name);
    auto *actionItem = new QStandardItem();

    appendRow({pidItem, nameItem, actionItem});

    emit requestActionWidget(index(rowCount() - 1, 2), pid);
}

void ProcessViewModel::setSearchFilter(const QString &filter) {
    filterByName(filter);
}
