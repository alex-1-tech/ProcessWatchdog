#include "processviewmodel.h"
#include <QStandardItem>

ProcessViewModel::ProcessViewModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setHorizontalHeaderLabels({"PID", "Name", "Actions"});
}

void ProcessViewModel::updateProcessList(const QVector<ProcessInfo> &list)
{
    fullProcessList = list;
    filterByName(currentFilter);
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
