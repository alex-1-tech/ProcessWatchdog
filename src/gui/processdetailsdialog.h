#pragma once

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

class ProcessDetailsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ProcessDetailsDialog(int pid, QWidget *parent = nullptr);

private:
    QString readFile(const QString &path) const;
    QString readLink(const QString &path) const;
};
