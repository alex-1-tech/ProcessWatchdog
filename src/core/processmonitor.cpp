#include "processmonitor.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

QVector<ProcessInfo> ProcessMonitor::getProcessList()
{
    QVector<ProcessInfo> processes;
    QDir procDir("/proc");

    for (const QString &entry : procDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        if (entry.toInt() > 0)
        {
            QString commPath = "/proc/" + entry + "/comm";
            QFile file(commPath);
            if (file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file);
                QString name = in.readLine();
                processes.append({entry.toInt(), name});
            }
        }
    }

    return processes;
}
