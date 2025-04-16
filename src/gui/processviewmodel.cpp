#include "processviewmodel.h"
#include <QStandardItem>

ProcessViewModel::ProcessViewModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setHorizontalHeaderLabels({"PID", "Name", "Actions"});
}

void ProcessViewModel::updateProcessList(const QVector<ProcessInfo> &list)
{
    clear();
    setHorizontalHeaderLabels({"PID", "Name", "Actions"}); // Восстановить заголовки

    for (const ProcessInfo &proc : list)
    {
        addProcessRow(proc.pid, proc.name);
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
