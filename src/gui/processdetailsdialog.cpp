#include "processdetailsdialog.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

ProcessDetailsDialog::ProcessDetailsDialog(int pid, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QString("Details for PID %1").arg(pid));
    resize(500, 400);

    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    setLayout(layout);

    QString status = readFile(QString("/proc/%1/status").arg(pid));
    QString cmdline = readFile(QString("/proc/%1/cmdline").arg(pid)).replace('\0', ' ');
    QString exe = readLink(QString("/proc/%1/exe").arg(pid));

    QString fullInfo = QString(
        "<b> Status:</b><pre>%1</pre><br>"
        "<b> Cmdline:</b> %2<br>"
        "<b> Executable Path:</b> %3"
    ).arg(status.toHtmlEscaped(), cmdline.toHtmlEscaped(), exe.toHtmlEscaped());
    
    textEdit->setHtml(fullInfo);
    
}

QString ProcessDetailsDialog::readFile(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "N/A";

    QTextStream in(&file);
    return in.readAll();
}

QString ProcessDetailsDialog::readLink(const QString &path) const
{
    QFileInfo info(path);
    return info.isSymLink() ? info.symLinkTarget() : "N/A";
}
